#ifndef DRV_MESH_RECV_H
#define DRV_MESH_RECV_H
#if defined (__cplusplus)
extern "C" {
#endif

static void drv_mesh_parsePacket_disc(struct packet_s * raw_packet) {
	DEBUG_PRINT("\tINFO: Discovery packet received (%lu bytes).\n", raw_packet->size);
	
	if (raw_packet->size != sizeof(struct packet_type_disc_s)) {
		DEBUG_PRINT("\tWARNING: Packet size does not match type (disc), dropping.\n");
		return;
	};
	
	struct packet_type_disc_s * packet = (struct packet_type_disc_s *)&(raw_packet->asDisc);
	
	state.stats.broadcasts_recv++;
	
	int corrupt = crypto_unlock_aead((uint8_t *)&(packet->lock), state.psk, packet->nonce, packet->mac, (uint8_t *)&(packet->auth), sizeof(packet->auth), (uint8_t *)&(packet->lock), sizeof(packet->lock));
	
	if (corrupt) {
		DEBUG_PRINT("\tWARNING: Discovery packet corrupt.\n");
		return;
	}
	
	lib_datetime_realtime_t curtime;
	drv_timer_getRealtime(&curtime);
	if (absI64((int64_t)(packet->lock.timestamp) - (int64_t)(curtime)) > (60*1000)) {
		DEBUG_PRINT("\tWARNING: Discovery packet timestamp out of range.\n");
		return;
	}
	
	struct peer_s * peer = getPeerByPubDhKey(packet->lock.key_dh_pub);
	if (peer == NULL) {
		DEBUG_PRINT("\tINFO: Discovery packet from unknown peer (new peer found).\n");
		peer = popEmptyPeer();
		if (peer == NULL) {
			DEBUG_PRINT("\tWARNING: Unable to save new peer, no peer slots remaining.\n");
			return;
		}
		peer->status = PEER_PASSERBY;
		memcpy(peer->key_dh_pub, packet->lock.key_dh_pub, sizeof(peer->key_dh_pub));
		
		uint8_t key_tmp[32];
		crypto_x25519(key_tmp, state.key_dh_priv, peer->key_dh_pub);
		crypto_blake2b_general(key_tmp, sizeof(key_tmp), state.psk, sizeof(state.psk), key_tmp, sizeof(key_tmp));
		crypto_blake2b_general(peer->key_chan_send, sizeof(peer->key_chan_send), key_tmp, sizeof(key_tmp), peer->key_dh_pub, sizeof(peer->key_dh_pub));
		crypto_blake2b_general(peer->key_chan_recv, sizeof(peer->key_chan_recv), key_tmp, sizeof(key_tmp), state.key_dh_pub, sizeof(state.key_dh_pub));
		crypto_wipe(key_tmp, sizeof(key_tmp));
		
		crypto_wipe(peer->key_send, sizeof(peer->key_send));
		peer->counter_send = 0;
		crypto_wipe(peer->key_recv, sizeof(peer->key_recv));
		peer->counter_recv = 0;
		
		drv_rand_fillBuf(peer->key_ephemeral_priv, sizeof(peer->key_ephemeral_priv));
		
		peer->last_packet_timestamp = 0; //packet->body.timestamp;

		if (!RB_SPACE(peer->rb_packets)) {
			DEBUG_PRINT("\tWARNING: Failed to save new peer, no empty slots in peer packet queue available\n");
			return;
		}
		
		struct packet_s * packet_tmp = popEmptyPacket();
		if (packet_tmp == NULL) {
			DEBUG_PRINT("\tWARNING: Failed to save new peer, no empty packets available\n");
			insertEmptyPeer(peer);
			return;
		}

		drv_mesh_buildPacket_auth(peer, packet_tmp);
		
		*RB_PUT(peer->rb_packets) = packet_tmp;

		insertReadyPeer(peer);
	} else {
		DEBUG_PRINT("\tINFO: Discovery packet from known peer.\n");
	}
}

static void drv_mesh_parsePacket_auth(struct packet_s * raw_packet) {
	DEBUG_PRINT("\tINFO: Auth packet received (%lu bytes).\n", raw_packet->size);
	
	if (raw_packet->size != sizeof(struct packet_type_auth_s)) {
		DEBUG_PRINT("\tWARNING: Packet size does not match type (auth), dropping.\n");
		return;
	};
	
	struct packet_type_auth_s * packet = (struct packet_type_auth_s *)&(raw_packet->asAuth);
	
	uint8_t key_once[32];
	crypto_x25519(key_once, state.key_dh_priv, packet->auth.key_once_pub);
	crypto_blake2b_general(key_once, sizeof(key_once), state.psk, sizeof(state.psk), key_once, sizeof(key_once));
	
	DEBUG_PRINT("\tkey_once [%hhu]: [", sizeof(key_once));
	for (uint32_t i=0; i<sizeof(key_once); i++) DEBUG_PRINT(((i+1==sizeof(key_once)) ? "%hhu" : "%hhu,"), (key_once)[i]);
	DEBUG_PRINT("]\n");
	
	uint8_t nonce_tmp[24];
	crypto_wipe(nonce_tmp, sizeof(nonce_tmp));
	crypto_xchacha20((uint8_t *)&(packet->lock), (uint8_t *)&(packet->lock), sizeof(packet->lock), key_once, nonce_tmp);
	
	uint8_t hmac_tmp[sizeof(packet->hmac)];
	crypto_blake2b_general(hmac_tmp, sizeof(hmac_tmp), key_once, sizeof(key_once), (uint8_t *)(packet), (uint8_t *)&(packet->hmac[0]) - (uint8_t *)(packet));
	
	DEBUG_PRINT("\thmac_tmp [%hhu]: [", sizeof(hmac_tmp));
	for (uint32_t i=0; i<sizeof(hmac_tmp); i++) DEBUG_PRINT(((i+1==sizeof(hmac_tmp)) ? "%hhu" : "%hhu,"), (hmac_tmp)[i]);
	DEBUG_PRINT("]\n");
	
	crypto_x25519(key_once, state.key_dh_priv, packet->lock.key_dh_pub);
	crypto_blake2b_general(hmac_tmp, sizeof(hmac_tmp), hmac_tmp, sizeof(hmac_tmp), key_once, sizeof(key_once));
	
	DEBUG_PRINT("\thmac_tmp [%hhu]: [", sizeof(hmac_tmp));
	for (uint32_t i=0; i<sizeof(hmac_tmp); i++) DEBUG_PRINT(((i+1==sizeof(hmac_tmp)) ? "%hhu" : "%hhu,"), (hmac_tmp)[i]);
	DEBUG_PRINT("]\n");
	
	crypto_x25519(key_once, state.key_dh_priv, packet->lock.key_ephemeral_pub);
	crypto_blake2b_general(hmac_tmp, sizeof(hmac_tmp), hmac_tmp, sizeof(hmac_tmp), key_once, sizeof(key_once));
	
	DEBUG_PRINT("\thmac_tmp [%hhu]: [", sizeof(hmac_tmp));
	for (uint32_t i=0; i<sizeof(hmac_tmp); i++) DEBUG_PRINT(((i+1==sizeof(hmac_tmp)) ? "%hhu" : "%hhu,"), (hmac_tmp)[i]);
	DEBUG_PRINT("]\n");
	
	crypto_wipe(key_once, sizeof(key_once));
	
	if (crypto_verify16(hmac_tmp, packet->hmac)) {
		DEBUG_PRINT("\tWARNING: Discovery reply packet corrupt.\n");
		return;
	}
	
	{ //parse body of packet
		/* lib_datetime_realtime_t curtime;
		drv_timer_getRealtime(&curtime);
		if (absI64((int64_t)(packet->body.timestamp) - (int64_t)(curtime)) > (60*1000)) {
			DEBUG_PRINT("\tWARNING: Discovery reply packet timestamp out of range.\n");
			return;
		} */
		
		struct peer_s * peer = getPeerByPubDhKey(packet->lock.key_dh_pub);
		if (peer == NULL) {
			DEBUG_PRINT("\tWARNING: Discovery reply packet from unknown peer, dropping.\n");
			return;
		}
		
		if (packet->lock.timestamp < peer->last_packet_timestamp) {
			DEBUG_PRINT("\tWARNING: Discovery reply packet from known peer is too old, dropping.\n");
			return;
		}
		
		peer->last_packet_timestamp = packet->lock.timestamp;
		
		peer->index = packet->lock.index;
		
		if (peer->status == PEER_PASSERBY) {
			peer->status = PEER_STRANGER;
		}
		{ // derive key_data_send/key_data_recv
			uint8_t key_tmp[32];
			uint8_t key_shared_tmp[32];
			uint8_t key_send_tmp[32];
			uint8_t key_recv_tmp[32];
			
			crypto_x25519(key_tmp, state.key_dh_priv, peer->key_dh_pub);
			crypto_blake2b_general(key_shared_tmp, sizeof(key_shared_tmp), state.psk, sizeof(state.psk), key_tmp, sizeof(key_tmp));
			
			crypto_x25519(key_tmp, peer->key_ephemeral_priv, packet->lock.key_ephemeral_pub);
			crypto_blake2b_general(key_shared_tmp, sizeof(key_shared_tmp), key_shared_tmp, sizeof(key_shared_tmp), key_tmp, sizeof(key_tmp));
			
			{ // key_data_send
				crypto_x25519(key_tmp, peer->key_ephemeral_priv, peer->key_dh_pub);
				crypto_blake2b_general(key_send_tmp, sizeof(key_send_tmp), key_shared_tmp, sizeof(key_shared_tmp), key_tmp, sizeof(key_tmp));
			}
			{ // key_data_recv
				crypto_x25519(key_tmp, state.key_dh_priv, packet->lock.key_ephemeral_pub);
				crypto_blake2b_general(key_recv_tmp, sizeof(key_recv_tmp), key_shared_tmp, sizeof(key_shared_tmp), key_tmp, sizeof(key_tmp));
			}

			if (crypto_verify32(key_send_tmp, peer->key_send) || crypto_verify32(key_recv_tmp, peer->key_recv)) {
				DEBUG_PRINT("\tINFO: Rekeying peer...\n");
				peer->status = PEER_STRANGER;
				memcpy(peer->key_send, key_send_tmp, sizeof(peer->key_send));
				memcpy(peer->key_recv, key_recv_tmp, sizeof(peer->key_recv));
				peer->counter_send = 0;
				peer->counter_recv = 0;
				peer->counter_ack = 0;
				for (uint16_t i=0; i<RB_COUNT(peer->rb_packets); i++) {
					struct packet_s * tpack = *RB_GET(peer->rb_packets); 
					insertEmptyPacket(tpack);
				}
				crypto_wipe(&(peer->rb_packets), sizeof(peer->rb_packets));

				//drv_rand_fillBuf(peer->key_ephemeral_priv, sizeof(peer->key_ephemeral_priv));
		
				peer->last_packet_timestamp = 0; //packet->body.timestamp;

				struct packet_s * packet_tmp = popEmptyPacket();
				if (packet_tmp == NULL) {
					DEBUG_PRINT("\tWARNING: Failed to rekey peer, no empty packets available\n");
					crypto_wipe(key_tmp, sizeof(key_tmp));
					crypto_wipe(key_shared_tmp, sizeof(key_shared_tmp));
					crypto_wipe(key_send_tmp, sizeof(key_send_tmp));
					crypto_wipe(key_recv_tmp, sizeof(key_recv_tmp));
					return;
				}

				drv_mesh_buildPacket_auth(peer, packet_tmp);
		
				*RB_PUT(peer->rb_packets) = packet_tmp;
			}
			
			crypto_wipe(key_tmp, sizeof(key_tmp));
			crypto_wipe(key_shared_tmp, sizeof(key_shared_tmp));
			crypto_wipe(key_send_tmp, sizeof(key_send_tmp));
			crypto_wipe(key_recv_tmp, sizeof(key_recv_tmp));

			DEBUG_PRINT("\tkey_send [%hhu]: [", sizeof(peer->key_send));
			for (uint32_t i=0; i<sizeof(peer->key_send); i++) DEBUG_PRINT(((i+1==sizeof(peer->key_send)) ? "%hhu" : "%hhu,"), (peer->key_send)[i]);
			DEBUG_PRINT("]\n");
			DEBUG_PRINT("\tkey_recv [%hhu]: [", sizeof(peer->key_recv));
			for (uint32_t i=0; i<sizeof(peer->key_recv); i++) DEBUG_PRINT(((i+1==sizeof(peer->key_recv)) ? "%hhu" : "%hhu,"), (peer->key_recv)[i]);
			DEBUG_PRINT("]\n");
		}
		
		{ //queue ACK
			if (!RB_SPACE(peer->rb_packets)) {
				DEBUG_PRINT("\tWARNING: Failed to create peer ACK, no empty slots in peer packet queue available\n");
				return;
			}

			struct packet_s * packet_tmp = popEmptyPacket();
			if (packet_tmp == NULL) {
				DEBUG_PRINT("\tWARNING: Failed to create peer ACK, no empty packets available\n");
				return;
			}
			
			*RB_PUT(peer->rb_packets) = packet_tmp;

			drv_mesh_buildPacket_link(peer, packet_tmp, NULL, 0);
			packet_tmp->once = true;
		}
	}
}

static void drv_mesh_parsePacket_link(struct packet_s * raw_packet) {
	DEBUG_PRINT("\tINFO: Link packet received (%lu bytes).\n", raw_packet->size);
	
	struct packet_type_link_s * packet = (struct packet_type_link_s *)&(raw_packet->asLink);
	
	if (raw_packet->size < sizeof(struct packet_type_link_s)) {
		DEBUG_PRINT("\tWARNING: Packet size does not match type (link), dropping packet.\n");
		return;
	};
	
	if (packet->auth.index >= BUFFER_PEERS_SIZE) {
		DEBUG_PRINT("\tWARNING: Peer index out of range, dropping packet.\n");
		return;
	}
	
	struct peer_s * peer = &(state.peers[packet->auth.index]);
	if (peer->status != PEER_ACQUAINTANCE && peer->status != PEER_STRANGER) {
		DEBUG_PRINT("\tWARNING: Unexpected peer status (%hu) at index [%hu], dropping packet.\n", peer->status, packet->auth.index);
		return;
	}
	
	uint8_t nonce_tmp[24];
	uint32_t counter_tmp = packet->auth.counter;
	crypto_blake2b_general(nonce_tmp, sizeof(nonce_tmp), peer->key_recv, sizeof(peer->key_recv), (uint8_t *)&(counter_tmp), sizeof(counter_tmp));
	int corrupt = crypto_unlock_aead((uint8_t *)&(packet->lock), peer->key_recv, nonce_tmp, (uint8_t *)&(packet->mac[0]), (uint8_t *)&(packet->auth), sizeof(packet->auth), (uint8_t *)&(packet->lock),raw_packet->size - (sizeof(struct packet_type_link_s) - sizeof(packet->lock)));
	
	DEBUG_PRINT("\tkey_send [%hhu]: [", sizeof(peer->key_send));
	for (uint32_t i=0; i<sizeof(peer->key_send); i++) DEBUG_PRINT(((i+1==sizeof(peer->key_send)) ? "%hhu" : "%hhu,"), (peer->key_send)[i]);
	DEBUG_PRINT("]\n");
	DEBUG_PRINT("\tkey_recv [%hhu]: [", sizeof(peer->key_recv));
	for (uint32_t i=0; i<sizeof(peer->key_recv); i++) DEBUG_PRINT(((i+1==sizeof(peer->key_recv)) ? "%hhu" : "%hhu,"), (peer->key_recv)[i]);
	DEBUG_PRINT("]\n");
	
	if (corrupt) {
		DEBUG_PRINT("\tWARNING: Link packet corrupt, dropping packet.\n");
		return;
	}

	if (peer->status == PEER_STRANGER) {
		peer->status = PEER_ACQUAINTANCE;
		DEBUG_PRINT("\tINFO: Now acquainted with peer.\n");
	}

	// TODO: needs additional logic, may skip packets
	if (peer->counter_ack < LIB_BYTEORDER_NTOH_U32(packet->auth.counter)) {
		peer->counter_ack = LIB_BYTEORDER_NTOH_U32(packet->auth.counter);
	}

	{ //dequeue packets based on ACK
		uint16_t count = RB_COUNT(peer->rb_packets);
		for (uint16_t i=0; i<count; i++) {
			struct packet_s * packet_tmp = *RB_GET(peer->rb_packets);
			if (!(packet_tmp->once) && packet_tmp->counter <= packet->lock.ack) {
				insertEmptyPacket(packet_tmp);
			} else {
				*RB_PUT(peer->rb_packets) = packet_tmp;
			}
		}
	}
	
	if (raw_packet->size - sizeof(struct packet_type_link_s) > 0) {
		// { //queue ACK
		// 	if (!RB_SPACE(peer->rb_packets)) {
		// 		DEBUG_PRINT("\tWARNING: Failed to create peer ACK, no empty slots in peer packet queue available\n");
		// 		return;
		// 	}

		// 	struct packet_s * packet_tmp = popEmptyPacket();
		// 	if (packet_tmp == NULL) {
		// 		DEBUG_PRINT("\tWARNING: Failed to create peer ACK, no empty packets available\n");
		// 		return;
		// 	}
			
		// 	*RB_PUT(peer->rb_packets) = packet_tmp;

		// 	drv_mesh_buildPacket_link(peer, packet_tmp, NULL, 0);
		// 	packet_tmp->once = true;
		// }
		drv_mesh_parsePayload(peer, raw_packet, (struct payload_s *)&(packet->payload[0]));
	} else {
		DEBUG_PRINT("\tINFO: Link packet has no payload.\n");
	}
}

static void drv_mesh_parsePacket(struct packet_s * raw_packet) {
	if (raw_packet->header.type == PACKET_TYPE__DISC) {
		drv_mesh_parsePacket_disc(raw_packet);
	} else if (raw_packet->header.type == PACKET_TYPE__AUTH) {
		drv_mesh_parsePacket_auth(raw_packet);
	} else if (raw_packet->header.type == PACKET_TYPE__LINK) {
		drv_mesh_parsePacket_link(raw_packet);
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
	//raw_packet.size = drv_lora_getRawPacket(&state.radio, raw_packet.raw);
	raw_packet.raw[0] = drv_lora_readRegister(0x00);
	raw_packet.size = raw_packet.raw[0];
	for (uint32_t i=1; i<raw_packet.size; i++) {
		raw_packet.raw[i] = drv_lora_readRegister(0x00);
	}
	
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
	
/* 	if (appt->type != APPT_RECV) { //error checking
		DEBUG_PRINT("\tERROR: Unexpected appointment type in drv_mesh_worker_recv()\n");
		goto EXIT;
	} */
	
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
		
	state.radio_mutex = 1;
	
	drv_lora_setMode(&state.radio, DRV_LORA_MODE__IDLE);
	
	setupRadioFromConfig(&state.radio, &(appt->radio_cfg));
	
	drv_lora_setMode(&state.radio, DRV_LORA_MODE__RECV_ONCE);

	DEBUG_PRINT("\tINFO: Listening for packet...\n");
	
	//hal_timer_delay(PREAMBLE_MS + PADDING_MS);
	lib_datetime_interval_t start = drv_timer_getMonotonicTime();
	lib_datetime_interval_t current = drv_timer_getMonotonicTime();
	uint8_t reg_status = 0;
	
	estimateTimeOnAirInMsFromRadioCfg(&(appt->radio_cfg), 2);

	uint32_t tmp_count1 = 0;
	while (((current - start) < (PREAMBLE_MS + (appt->radio_cfg.toaEstimate - PREAMBLE_MS)) + PADDING_MS) && !(reg_status) && ((current - start) < (2*PACKET_TOA_MAX_GENERATE))) {
		reg_status = drv_lora_getStatusReg(&state.radio) & (0x1 << 0);
		//headerPacketSize = drv_lora_getHeaderPacketSize(&state.radio);
		current = drv_timer_getMonotonicTime();
		tmp_count1++;
		//DEBUG_PRINT("\tDEBUG: Waiting for preamble (%llu - %llu = %llu) [%hhu].\n", current, start, current - start, reg_status);
	}
	DEBUG_PRINT("\tDEBUG: Spun %u time(s) while waiting for preamble.\n", tmp_count1);

	if (!(reg_status)) {
		DEBUG_PRINT("\tINFO: No preamble detected in drv_mesh_worker_recv(), aborting receive.\n");
		drv_lora_setMode(&state.radio, DRV_LORA_MODE__SLEEP);
		state.radio_mutex = 0;
		goto EXIT;
	}

	uint8_t readByteIndex = drv_lora_readRegister(0x25);
	uint32_t tmp_count = 0;
	start = drv_timer_getMonotonicTime();
	current = drv_timer_getMonotonicTime();
	while (((current - start) < ((appt->radio_cfg.toaEstimate - PREAMBLE_MS) + PADDING_MS)) && (readByteIndex < 1)) {
		readByteIndex = drv_lora_readRegister(0x25);
		current = drv_timer_getMonotonicTime();
		tmp_count++;
	}
	DEBUG_PRINT("\tDEBUG: Spun %u time(s) while waiting for header.\n", tmp_count);

	if (readByteIndex == 0) {
		DEBUG_PRINT("\tINFO: No header detected in drv_mesh_worker_recv(), aborting receive.\n");
		drv_lora_setMode(&state.radio, DRV_LORA_MODE__SLEEP);
		state.radio_mutex = 0;
		goto EXIT;
	}

	uint8_t packetSize0 = drv_lora_readRegister(0x00);
	uint8_t packetSize1 = drv_lora_readRegister(0x00);
	drv_lora_writeRegister(0x0d, 0);

	if (packetSize0 != packetSize1) {
		DEBUG_PRINT("\tINFO: Header detected in drv_mesh_worker_recv(), but header is corrupt, aborting receive.\n");
		drv_lora_setMode(&state.radio, DRV_LORA_MODE__SLEEP);
		state.radio_mutex = 0;
		goto EXIT;
	}

	if (packetSize0 < sizeof(struct packet_header_s)) {
		DEBUG_PRINT("\tINFO: Header detected in drv_mesh_worker_recv(), but packet size is too small, aborting receive.\n");
		drv_lora_setMode(&state.radio, DRV_LORA_MODE__SLEEP);
		state.radio_mutex = 0;
		goto EXIT;
	}
	
	// uint8_t headerPacketSize = drv_lora_getHeaderPacketSize(&state.radio);

	drv_lora_writeRegister(0x22, packetSize0);

	estimateTimeOnAirInMsFromRadioCfg(&(appt->radio_cfg), packetSize0);
	
	enum drv_sched_err_e err = drv_sched_once(drv_mesh_worker_recv_finish, NULL, DRV_SCHED_PRI__REALTIME, (appt->radio_cfg.toaEstimate - PREAMBLE_MS) + PADDING_MS);
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