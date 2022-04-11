#ifndef DRV_MESH_ROUTE_H
#define DRV_MESH_ROUTE_H
#if defined (__cplusplus)
extern "C" {
#endif

static void drv_mesh_parsePayload_data(struct packet_s * raw_packet, struct payload_s * raw_payload) {
	DEBUG_PRINT("\tINFO: Data payload received (%lu bytes).\n", raw_packet->size - sizeof(struct packet_type_link_s));
	struct payload_type_data_s * payload = &(raw_payload->asData);
	uint8_t msgSize = raw_packet->size - sizeof(struct packet_type_link_s) - sizeof(struct payload_type_data_s);
	DEBUG_PRINT_BUF(payload->data, msgSize);

	struct drv_mesh_packet_s packet;
	crypto_wipe(&packet, sizeof(packet));
	memcpy(packet.ip, payload->ip_src, sizeof(ipv4_t));
	packet.port = payload->port_src;
	packet.len = msgSize;
	if (packet.len < DRV_MESH__MESSAGE_SIZE_MAX) {
		DEBUG_PRINT("\tINFO: Message received (%hhu bytes), running callback...\n", packet.len);
		memcpy(packet.buf, payload->data, msgSize);
		if (state.func_onRecv_ptr != NULL) {
			state.func_onRecv_ptr(&packet);
		}
	} else {
		DEBUG_PRINT("\tWARNING: Message is too large (%hhu bytes), dropping.\n", packet.len);
	}
}

static void drv_mesh_parsePayload(struct packet_s * raw_packet, struct payload_s * raw_payload) {
	if (raw_payload->header.type == PAYLOAD_TYPE__DATA) {
		drv_mesh_parsePayload_data(raw_packet, raw_payload);
	} else {
		DEBUG_PRINT("\tWARNING: Unknown payload [%X] received (%lu bytes).\n", raw_payload->header.type, raw_packet->size - sizeof(struct packet_type_link_s));
	}
}

#if defined (__cplusplus)
}
#endif
#endif // DRV_MESH_ROUTE_H