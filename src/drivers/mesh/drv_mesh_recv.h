#ifndef DRV_MESH_RECV_H
#define DRV_MESH_RECV_H
#if defined (__cplusplus)
extern "C" {
#endif

static void drv_mesh_parsePacket_disc(struct packet_s * raw_packet) {
	DEBUG_PRINT("\tINFO: Discovery packet received from [%llX] (%lu bytes).\n", raw_packet->asDisc.broadcast_peer_uid, raw_packet->size);
	
	if (raw_packet->size != sizeof(struct packet_type_disc_s)) {
		DEBUG_PRINT("\tWARNING: Packet size does not match type.\n");
		return;
	};
	
	struct packet_type_disc_s * packet = (struct packet_type_disc_s *)&(raw_packet->asDisc);
	
	state.stats.broadcasts_recv++;
	
	struct peer_s * peer = getPeerByUID(packet->broadcast_peer_uid);
	if (peer == NULL) {
		DEBUG_PRINT("\tINFO: Discovery packet from unknown peer (new peer found).\n");
		peer = popEmptyPeer();
		if (peer == NULL) {
			DEBUG_PRINT("\tWARNING: Unable to save new peer, no peer slots remaining.\n");
			return;
		}
		peer->status = PEER_PASSERBY;
		peer->uid = packet->broadcast_peer_uid;
		//memcpy(packet->key_ephemeral, peer->key, sizeof(peer->key));
		//crypto_x25519(peer->key, state.privkey, packet->key_ephemeral);
		//crypto_blake2b_general(peer->key, sizeof(peer->key), state.psk, sizeof(state.psk), peer->key, sizeof(peer->key));
		
		/*uint8_t tmp_hmac[sizeof(packet->hmac)];
		crypto_blake2b_general(tmp_hmac, sizeof(tmp_hmac), state.psk, sizeof(state.psk), (uint8_t *)&(*packet), sizeof(*packet)-sizeof(tmp_hmac));
		if (memcmp(tmp_hmac, packet->hmac, sizeof(tmp_hmac)) != 0) {
			DEBUG_PRINT_REALTIME(); DEBUG_PRINT("WARNING: HMAC mismatch.\n");
			state.stats.mac_failures++;
			insertEmptyPeer(peer);
		} else {
			insertReadyPeer(peer);
		}*/
		insertReadyPeer(peer);
	} else {
		DEBUG_PRINT("\tINFO: Discovery packet from known peer.\n");
		//peer already known
		if (peer->status == PEER_PASSERBY) {
			//heard their broadcast again, check if key is the same
		} else if (peer->status == PEER_ACQUAINTANCE) {
			//can't check if peer's key has changed since we wiped it... oops.
		} else if (peer->status == PEER_FRIEND) {
			//can't check if peer's key has changed since we wiped it... oops.
		} else {
			//shouldn't be possible
		}
	}
}

static void drv_mesh_parsePacket_discReply(struct packet_s * raw_packet) {
	DEBUG_PRINT("\tINFO: Discovery reply packet received from [%llX] (%lu bytes).\n", raw_packet->asDiscReply.reply_peer_uid, raw_packet->size);
	
	if (raw_packet->size != sizeof(struct packet_type_discReply_s)) {
		DEBUG_PRINT("\tWARNING: Packet size does not match type.\n");
		return;
	};
	
	struct packet_type_discReply_s * packet = (struct packet_type_discReply_s *)&(raw_packet->asDiscReply);
	
	if (packet->broadcast_peer_uid != state.uid) {
		DEBUG_PRINT("\tINFO: Discovery reply packet intended for different broadcaster.\n");
		return;
	}
	
	struct peer_s * peer = getPeerByUID(packet->reply_peer_uid);
	if (peer == NULL) { //PEER_STRANGER
		DEBUG_PRINT("\tINFO: Discovery reply packet received from unknown peer.\n");
		peer = popEmptyPeer();
		if (peer == NULL) {
			DEBUG_PRINT("\tWARNING: Unable to save new peer, no peer slots remaining.\n");
			return;
		}
		peer->status = PEER_ACQUAINTANCE;
		peer->uid = packet->reply_peer_uid;
		//crypto_x25519(peer->key, state.privkey, packet->key_ephemeral);
		//crypto_blake2b_general(peer->key, sizeof(peer->key), state.psk, sizeof(state.psk), peer->key, sizeof(peer->key));
		
		/*uint8_t tmp_hmac[sizeof(packet->hmac)];
		crypto_blake2b_general(tmp_hmac, sizeof(tmp_hmac), state.psk, sizeof(state.psk), (uint8_t *)&(*packet), sizeof(*packet)-sizeof(tmp_hmac));
		if (memcmp(tmp_hmac, packet->hmac, sizeof(tmp_hmac)) != 0) {
			DEBUG_PRINT_REALTIME(); DEBUG_PRINT("WARNING: HMAC mismatch.\n");
			state.stats.mac_failures++;
			insertEmptyPeer(peer);
		} else {
			insertReadyPeer(peer);
		}*/
		insertReadyPeer(peer);
	} else {
		if (peer->status == PEER_PASSERBY) {
			DEBUG_PRINT("\tINFO: Discovery reply packet received from unknown peer.\n");
			//TODO same as above?
			peer->status = PEER_ACQUAINTANCE;
			peer->uid = packet->reply_peer_uid;
			//crypto_x25519(peer->key, state.privkey, packet->key_ephemeral);
			//crypto_blake2b_general(peer->key, sizeof(peer->key), state.psk, sizeof(state.psk), peer->key, sizeof(peer->key));
			
			/*uint8_t tmp_hmac[sizeof(packet->hmac)];
			crypto_blake2b_general(tmp_hmac, sizeof(tmp_hmac), state.psk, sizeof(state.psk), (uint8_t *)&(*packet), sizeof(*packet)-sizeof(tmp_hmac));
			if (memcmp(tmp_hmac, packet->hmac, sizeof(tmp_hmac)) != 0) {
				DEBUG_PRINT_REALTIME(); DEBUG_PRINT("WARNING: HMAC mismatch.\n");
				state.stats.mac_failures++;
				insertEmptyPeer(peer); //CANT DO THIS HERE, INFINITE LOOP
			} else {
				insertReadyPeer(peer); //CANT DO THIS HERE, INFINITE LOOP
			}*/
		} else if (peer->status == PEER_ACQUAINTANCE) {
			
		} else if (peer->status == PEER_FRIEND) {
			
		} else {
			//shouldn't be possible
		}
	}
}

static void drv_mesh_parsePacket_discHandshake(struct packet_s * raw_packet) {
	DEBUG_PRINT("\tINFO: Discovery handshake packet received from [%llX] (%lu bytes).\n", raw_packet->asDiscReply.reply_peer_uid, raw_packet->size);
	
	if (raw_packet->size != sizeof(struct packet_type_discHandshake_s)) {
		DEBUG_PRINT("\tWARNING: Packet size does not match type.\n");
		return;
	};
	
	struct packet_type_discHandshake_s * packet = (struct packet_type_discHandshake_s *)&(raw_packet->asDiscHandshake);
	
}

static void drv_mesh_parsePacket_data(struct packet_s * raw_packet) {
	DEBUG_PRINT_REALTIME(); DEBUG_PRINT("INFO: Data packet received (%lu bytes).\n", raw_packet->size);
	
	struct packet_type_data_s * packet = (struct packet_type_data_s *)&(raw_packet->asData);
	
	if (raw_packet->size < ((uint8_t *)&(packet->data) - (uint8_t *)packet)) {
		DEBUG_PRINT_REALTIME(); DEBUG_PRINT("WARNING: Packet size does not match type, dropping packet.\n");
		return;
	};
	
	uint8_t packet_data_size = raw_packet->size - ((uint8_t *)&(packet->data) - (uint8_t *)packet);
	//packet size is included in MAC somehow
	
}

static void drv_mesh_parsePacket_route(struct packet_s * raw_packet) {
	DEBUG_PRINT_REALTIME(); DEBUG_PRINT("INFO: Routing packet received (%lu bytes).\n", raw_packet->size);
	
	struct packet_type_route_s * packet = (struct packet_type_route_s *)&(raw_packet->asRoute);
	
	if (raw_packet->size < ((uint8_t *)&(packet->data) - (uint8_t *)packet)) {
		DEBUG_PRINT_REALTIME(); DEBUG_PRINT("WARNING: Packet size does not match type, dropping packet.\n");
		return;
	};
	
	uint8_t packet_data_size = raw_packet->size - ((uint8_t *)&(packet->data) - (uint8_t *)packet);
	//packet size is included in MAC somehow
	
}

static void drv_mesh_parsePacket(struct packet_s * raw_packet) {
	if (raw_packet->header.type == PACKET_TYPE__DISC) {
		drv_mesh_parsePacket_disc(raw_packet);
	} else if (raw_packet->header.type == PACKET_TYPE__DISC_REPLY) {
		drv_mesh_parsePacket_discReply(raw_packet);
	} else if (raw_packet->header.type == PACKET_TYPE__DISC_HANDSHAKE) {
		drv_mesh_parsePacket_discHandshake(raw_packet);
	} else if (raw_packet->header.type == PACKET_TYPE__DATA) {
		drv_mesh_parsePacket_data(raw_packet);
	} else {
		DEBUG_PRINT("\tWARNING: Unknown packet [%X] received.\n", raw_packet->header.type);
	}
}

static void drv_mesh_worker_recv_finish(void * arg) {
	DEBUG_PRINT_REALTIME(); DEBUG_PRINT_FUNCTION();
	
	if (arg != NULL) {
		DEBUG_PRINT("\tWARNING: Unexpected non-NULL argument to drv_mesh_worker_recv_finish().\n");
	}
	
	struct packet_s raw_packet = {0};
	raw_packet.size = drv_lora_getRawPacket(&state.radio, raw_packet.raw);
	
	drv_lora_setMode(&state.radio, DRV_LORA_MODE__SLEEP);
	state.radio_mutex = 0;
	
	DEBUG_PRINT("\trecv PACKET_RAW [%hhu]: [", raw_packet.size);
	for (uint32_t i=0; i<raw_packet.size; i++) DEBUG_PRINT(((i+1==raw_packet.size) ? "%hhu" : "%hhu,"), (raw_packet.raw)[i]);
	DEBUG_PRINT("]\n");
	
	if (raw_packet.size == 0) {
		DEBUG_PRINT("\tINFO: No packet received.\n");
		return;
	}
	
	drv_mesh_parsePacket(&raw_packet);
}

static void drv_mesh_worker_recv(void * arg) {
	__label__ EXIT;
	DEBUG_PRINT_REALTIME(); DEBUG_PRINT_FUNCTION();
	struct appointment_s * appt = (struct appointment_s *) arg;
	
	if (appt->type != APPT_RECV) { //error checking
		DEBUG_PRINT("\tERROR: Unexpected appointment type in drv_mesh_worker_recv()\n");
		goto EXIT;
	}
	
	{lib_datetime_realtime_t rt;
	drv_timer_getRealtime(&rt);
	if (rt > appt->realtime+1) { //error checking
		DEBUG_PRINT("\tWARNING: drv_mesh_worker_recv() late, skipping.\n");
		goto EXIT;
	}}
	
	if (state.radio_mutex) { //error checking
		DEBUG_PRINT("\tINFO: Radio busy, unable to listen for packet.\n");
		goto EXIT;
	}
	
	DEBUG_PRINT("\tINFO: Listening for packet...\n");
	state.radio_mutex = 1;
	
	drv_lora_setMode(&state.radio, DRV_LORA_MODE__IDLE);
	
	setupRadioFromConfig(&state.radio, &(appt->radio_cfg));
	
	drv_lora_setMode(&state.radio, DRV_LORA_MODE__RECV_ONCE);
	hal_timer_delay(250); //idk if this value makes sense
	
	if (!drv_lora_isSignalDetected(&state.radio)) {
		DEBUG_PRINT("\tINFO: No preamble detected in drv_mesh_worker_recv(), aborting receive.\n");
		drv_lora_setMode(&state.radio, DRV_LORA_MODE__SLEEP);
		state.radio_mutex = 0;
		goto EXIT;
	}
	
	enum drv_sched_err_e err = drv_sched_once(drv_mesh_worker_recv_finish, NULL, DRV_SCHED_PRI__REALTIME, 5000); //the interval should be calculated
	if (err != DRV_SCHED_ERR__NONE) { //error checking
		DEBUG_PRINT("\tWARNING: Failed to schedule drv_mesh_worker_recv_finish()\n");
		drv_lora_setMode(&state.radio, DRV_LORA_MODE__SLEEP);
		state.radio_mutex = 0;
		goto EXIT;
	}
	
	EXIT:
	insertEmptyAppt(appt);
}

#if defined (__cplusplus)
}
#endif
#endif // DRV_MESH_RECV_H