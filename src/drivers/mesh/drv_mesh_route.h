#ifndef DRV_MESH_ROUTE_H
#define DRV_MESH_ROUTE_H
#if defined (__cplusplus)
extern "C" {
#endif

static void queuePacketToPeer(struct peer_s * peer, uint8_t * payload, uint8_t payloadSize) {
	if (RB_SPACE(peer->rb_packets)) {
		struct packet_s * tmp_packet = popEmptyPacket();
		if (tmp_packet == NULL) {
			DEBUG_PRINT("\tWARNING: Failed to queue packet, no empty packets available\n");
			return;
		}
		drv_mesh_buildPacket_link(peer, tmp_packet, (uint8_t *)payload, payloadSize);
		*RB_PUT(peer->rb_packets) = tmp_packet;
	}
}

static void queuePacketToAllPeers(uint8_t * payload, uint8_t payloadSize) {
	struct peer_s * tmp_peer = state.head_peer_ready;
	for (; tmp_peer != NULL; tmp_peer = tmp_peer->next) {
		if (tmp_peer->status == PEER_ACQUAINTANCE) {
			if (RB_SPACE(tmp_peer->rb_packets)) {
				struct packet_s * tmp_packet = popEmptyPacket();
				if (tmp_packet == NULL) {
					DEBUG_PRINT("\tWARNING: Failed to queue packet, no empty packets available\n");
					break; //rest will fail anyway
				}
				drv_mesh_buildPacket_link(tmp_peer, tmp_packet, (uint8_t *)payload, payloadSize);
				*RB_PUT(tmp_peer->rb_packets) = tmp_packet;
			}
		}
	}
}

//don't send back to peer that delivered message
static void drv_mesh_routePayload(struct payload_s * payload, uint8_t payloadSize, lib_datetime_realtime_t realtime) {
	struct route_s * route = findRoute(payload->header.ip_dst, realtime);
	if (route == NULL) {
		DEBUG_PRINT("\tINFO: No route found, flooding...\n");
		queuePacketToAllPeers((uint8_t *)payload, payloadSize);
	} else {
		DEBUG_PRINT("\tINFO: Route found.\n"); //only sends to a single peer for now
		queuePacketToPeer(&(state.peers[route->peers[0].index_peer]), (uint8_t *)payload, payloadSize);
	}
}

static void drv_mesh_parsePayload_data(struct peer_s * peer, struct packet_s * raw_packet, struct payload_s * raw_payload) {
	uint8_t payloadSize = raw_packet->size - sizeof(struct packet_type_link_s);
	DEBUG_PRINT("\tINFO: Data payload received (%lu bytes).\n", payloadSize);
	struct payload_type_data_s * payload = &(raw_payload->asData);
	uint8_t msgSize = payloadSize - sizeof(struct payload_type_data_s);
	DEBUG_PRINT_BUF(payload->data, msgSize);

	lib_datetime_realtime_t rt;
	drv_timer_getRealtime(&rt);
	insertRoute(payload->header.ip_src, payload->header.ttl, getPeerIndexFromPtr(peer), rt);

	DEBUG_PRINT("\tDEBUG: route inserted.\n");
	
	bool recent = false;
	if (msgSize > 0) { //NEEDS TO NOT DROP EMPTY (ACK) PAYLOADS
		recent = checkRecentPayload(raw_payload, payloadSize);
		DEBUG_PRINT("\tDEBUG: recent payload checked.\n");
		if (recent) {
			DEBUG_PRINT("\tINFO: Payload seen recently, dropping...\n");
		} else {
			insertRecentPayload(raw_payload, payloadSize);
			DEBUG_PRINT("\tDEBUG: recent payload inserted.\n");
		}
	}

	DEBUG_PRINT("\tINFO: Payload TTL: %hhu.\n", payload->header.ttl);
	if (payload->header.ttl > PACKET_DROP_TTL) {
		DEBUG_PRINT("\tINFO: Payload TTL too high, dropping...\n");
		return;
	}

	if (memcmp(payload->header.ip_dst, state.ip, sizeof(ipv4_t)) != 0) {
		if (!recent) {
			DEBUG_PRINT("\tINFO: Payload destined elsewhere, relaying...\n");
			payload->header.ttl++;
			drv_mesh_routePayload(raw_payload, payloadSize, rt);
		}
	} else {
		DEBUG_PRINT("\tINFO: Payload destined for this node.\n");

		if (msgSize > 0) { //queue direct ACK
			DEBUG_PRINT("\tINFO: Payload received (seq: %u) (%hhu bytes), queuing ACK...\n", payload->auth.num_seq, payloadSize);
			struct payload_s tmp_payload;
			tmp_payload.header.type = PAYLOAD_TYPE__DATA;
			tmp_payload.header.ttl = 0;
			memcpy(tmp_payload.header.ip_src, state.ip, sizeof(ipv4_t));
			memcpy(tmp_payload.header.ip_dst, payload->header.ip_src, sizeof(ipv4_t));
			tmp_payload.header.port_src = payload->header.port_dst;
			tmp_payload.header.port_dst = payload->header.port_src;
			tmp_payload.asData.auth.num_seq = 0;
			tmp_payload.asData.auth.num_ack = payload->auth.num_seq;
			//drv_mesh_routePayload(&tmp_payload, sizeof(struct payload_type_data_s), rt);
			queuePacketToPeer(peer, (uint8_t *)&tmp_payload, sizeof(struct payload_type_data_s));
		}

		if (!recent) {
			DEBUG_PRINT("\tINFO: Message received (seq: %u) (%hhu bytes), running callback...\n", payload->auth.num_seq, msgSize);
			struct drv_mesh_packet_s packet;
			crypto_wipe(&packet, sizeof(packet));
			packet.len = msgSize;
			if (packet.len > DRV_MESH__MESSAGE_SIZE_MAX) {
				DEBUG_PRINT("\tWARNING: Message is too large (%hhu bytes), dropping.\n", packet.len);
				return;
			}
			memcpy(packet.ip, payload->header.ip_src, sizeof(ipv4_t));
			packet.port = payload->header.port_src;
			memcpy(packet.buf, payload->data, msgSize);
			if (state.func_onRecv_ptr != NULL) {
				state.func_onRecv_ptr(&packet);
			}
		}

		{ //handle ACK portion
			uint16_t count = RB_COUNT(state.rb_outboundPackets);
			for (uint16_t i=0; i<count; i++) {
				struct packet_s * packet_tmp = *RB_GET(state.rb_outboundPackets);
				if (packet_tmp->counter == payload->auth.num_ack) {
					DEBUG_PRINT("\tINFO: Message (%u) acknowledged.\n", packet_tmp->counter);
					insertEmptyPacket(packet_tmp);
				} else {
					*RB_PUT(state.rb_outboundPackets) = packet_tmp;
				}
			}
		}
	}
}

static void drv_mesh_parsePayload(struct peer_s * peer, struct packet_s * raw_packet, struct payload_s * raw_payload) {
	if (raw_payload->header.type == PAYLOAD_TYPE__DATA) {
		drv_mesh_parsePayload_data(peer, raw_packet, raw_payload);
	} else {
		DEBUG_PRINT("\tWARNING: Unknown payload [%X] received (%lu bytes).\n", raw_payload->header.type, raw_packet->size - sizeof(struct packet_type_link_s));
	}
}

#if defined (__cplusplus)
}
#endif
#endif // DRV_MESH_ROUTE_H