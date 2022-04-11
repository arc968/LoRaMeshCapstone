#ifndef DRV_MESH_SEND_H
#define DRV_MESH_SEND_H
#if defined (__cplusplus)
extern "C" {
#endif

static void drv_mesh_buildPacket_disc(struct packet_s * raw_packet) {
	DEBUG_PRINT("\tBuilding discovery packet...\n");
	raw_packet->size = sizeof(struct packet_type_disc_s);
	raw_packet->once = true;
	struct packet_type_disc_s * packet = (struct packet_type_disc_s *)&(raw_packet->asDisc);
	
	packet->header.type = PACKET_TYPE__DISC;
	lib_datetime_realtime_t curtime;
	drv_timer_getRealtime(&curtime);
	packet->body.timestamp = curtime;
	memcpy(packet->body.key_dh_pub, state.key_dh_pub, sizeof(state.key_dh_pub));
	drv_rand_fillBuf(packet->nonce, sizeof(packet->nonce));
	crypto_lock_aead(packet->mac, (uint8_t *)&(packet->body), state.psk, packet->nonce, (uint8_t *)&(packet->header), sizeof(packet->header), (uint8_t *)&(packet->body), sizeof(packet->body));
	
	DEBUG_PRINT("\tBuilt discovery packet.\n");
}

static void drv_mesh_buildPacket_discReply(struct peer_s * peer, struct packet_s * raw_packet) {
	DEBUG_PRINT("\tBuilding discovery reply packet ...\n");
	//struct packet_s * raw_packet = peer->packet;
	raw_packet->size = sizeof(struct packet_type_discReply_s);
	raw_packet->once = false;
	raw_packet->puid = 0;
	struct packet_type_discReply_s * packet = (struct packet_type_discReply_s *)&(raw_packet->asDiscReply);
	
	//*packet = packet_type_discReply_s_default;
	packet->header.type = PACKET_TYPE__DISC_REPLY;
	
	DEBUG_PRINT("\tGen key_once...\n");
	uint8_t key_once[32];
	drv_rand_fillBuf(key_once, sizeof(key_once));
	crypto_x25519_public_key(packet->key_once_pub, key_once);
	crypto_x25519(key_once, key_once, peer->key_dh_pub);
	crypto_blake2b_general(key_once, sizeof(key_once), state.psk, sizeof(state.psk), key_once, sizeof(key_once));
	DEBUG_PRINT("\tDone.\n");
	
	DEBUG_PRINT("\tkey_once [%hhu]: [", sizeof(key_once));
	for (uint32_t i=0; i<sizeof(key_once); i++) DEBUG_PRINT(((i+1==sizeof(key_once)) ? "%hhu" : "%hhu,"), (key_once)[i]);
	DEBUG_PRINT("]\n");
	
	{ //load body of packet
		crypto_x25519_public_key(packet->body.key_ephemeral_pub, peer->key_ephemeral_priv);
		
		DEBUG_PRINT("\tCalc index...\n");
		packet->body.index = ((uint8_t *)(peer) - (uint8_t *)&(state.peers[0])) / sizeof(struct peer_s);
		DEBUG_PRINT("\tDone (index: %hu).\n", packet->body.index);
		
		memcpy(packet->body.key_dh_pub, state.key_dh_pub, sizeof(state.key_dh_pub));
		
		lib_datetime_realtime_t curtime;
		drv_timer_getRealtime(&curtime);
		packet->body.timestamp = curtime;
	}
	
	DEBUG_PRINT("\tCalc packet hash...\n");
	crypto_blake2b_general(packet->hmac, sizeof(packet->hmac), key_once, sizeof(key_once), (uint8_t *)(packet), (uint8_t *)&(packet->hmac[0]) - (uint8_t *)(packet));
	DEBUG_PRINT("\tDone.\n");
	
	DEBUG_PRINT("\tpacket->hmac [%hhu]: [", sizeof(packet->hmac));
	for (uint32_t i=0; i<sizeof(packet->hmac); i++) DEBUG_PRINT(((i+1==sizeof(packet->hmac)) ? "%hhu" : "%hhu,"), (packet->hmac)[i]);
	DEBUG_PRINT("]\n");
	
	DEBUG_PRINT("\tEncrypt packet...\n");
	//uint8_t mac_tmp[16];
	uint8_t nonce_tmp[24];
	crypto_wipe(nonce_tmp, sizeof(nonce_tmp));
	crypto_xchacha20((uint8_t *)&(packet->body), (uint8_t *)&(packet->body), sizeof(packet->body), key_once, nonce_tmp);
	//crypto_lock_aead(mac_tmp, (uint8_t *)&(packet->body), key_once, nonce_tmp, (uint8_t *)&(packet), (uint8_t *)&(packet->body) - (uint8_t *)&(packet), (uint8_t *)&(packet->body), sizeof(packet->body));
	//crypto_blake2b_general(packet->hmac, sizeof(packet->hmac), packet->hmac, sizeof(packet->hmac), mac_tmp, sizeof(mac_tmp)); // can't unless MAC is transmitted
	DEBUG_PRINT("\tDone.\n");
	
	crypto_x25519(key_once, state.key_dh_priv, peer->key_dh_pub);
	crypto_blake2b_general(packet->hmac, sizeof(packet->hmac), packet->hmac, sizeof(packet->hmac), key_once, sizeof(key_once));
	
	DEBUG_PRINT("\tpacket->hmac [%hhu]: [", sizeof(packet->hmac));
	for (uint32_t i=0; i<sizeof(packet->hmac); i++) DEBUG_PRINT(((i+1==sizeof(packet->hmac)) ? "%hhu" : "%hhu,"), (packet->hmac)[i]);
	DEBUG_PRINT("]\n");
	
	crypto_x25519(key_once, peer->key_ephemeral_priv, peer->key_dh_pub);
	crypto_blake2b_general(packet->hmac, sizeof(packet->hmac), packet->hmac, sizeof(packet->hmac), key_once, sizeof(key_once));
	
	DEBUG_PRINT("\tpacket->hmac [%hhu]: [", sizeof(packet->hmac));
	for (uint32_t i=0; i<sizeof(packet->hmac); i++) DEBUG_PRINT(((i+1==sizeof(packet->hmac)) ? "%hhu" : "%hhu,"), (packet->hmac)[i]);
	DEBUG_PRINT("]\n");
	
	crypto_wipe(key_once, sizeof(key_once));
	//DEBUG_PRINT("\tBuilding discovery reply packet as [%llX] to [%llX]...\n", packet->reply_peer_uid, packet->broadcast_peer_uid);
	DEBUG_PRINT("\tBuilt discovery reply packet.\n");
}

static void drv_mesh_buildPacket_ack(struct peer_s * peer, struct packet_s * raw_packet, uint32_t puid) {
	raw_packet->size = sizeof(struct packet_type_ack_s);
	raw_packet->once = true;
	struct packet_type_ack_s * ack = (struct packet_type_ack_s *)&(raw_packet->asAck);
	ack->header.header.type = PACKET_TYPE__LINK;
	ack->header.index = peer->index;
	ack->header.counter = peer->counter_data_send++;
	ack->header.body.type = PACKET_TYPE__ACK;
	ack->puid = puid;
	
	uint8_t nonce_tmp[24];
	uint32_t counter_tmp = LIB_BYTEORDER_HTON_U32(ack->header.counter);
	crypto_blake2b_general(nonce_tmp, sizeof(nonce_tmp), peer->key_data_send, sizeof(peer->key_data_send), (uint8_t *)&(counter_tmp), sizeof(counter_tmp));
	crypto_lock_aead(ack->header.mac, (uint8_t *)&(ack->header.body), peer->key_data_send, nonce_tmp, (uint8_t *)ack, ((uint8_t *)&(ack->header.mac[0])) - ((uint8_t *)ack), (uint8_t *)&(ack->header.body), sizeof(struct packet_type_ack_s) - (((uint8_t *)&(ack->header.body)) - ((uint8_t *)ack)));
}

static void drv_mesh_buildPacket_data(struct packet_s * raw_packet) {
	struct packet_type_data_s * packet = &(raw_packet->asData);
	
}

/* static void drv_mesh_buildPacket_route(struct appointment_s * appt) {
	struct packet_s * raw_packet = appt->packet;
	
} */

static void drv_mesh_worker_send_finish(void * arg) {
	DEBUG_PRINT_REALTIME(); DEBUG_PRINT_FUNCTION();
	DEBUG_PRINT("\tPacket sent.\n");
	
	drv_lora_setMode(&state.radio, DRV_LORA_MODE__SLEEP);
	state.radio_mutex = 0;
}

static void drv_mesh_worker_send(void * arg) {
	__label__ EXIT;
	DEBUG_PRINT_REALTIME(); DEBUG_PRINT_FUNCTION();
	struct appointment_s * appt = (struct appointment_s *) arg;
	
	{lib_datetime_realtime_t rt;
	drv_timer_getRealtime(&rt);
	if (rt > appt->realtime+1) { //error checking
		DEBUG_PRINT("\tWARNING: drv_mesh_worker_send() late, skipping.\n");
		goto EXIT;
	}}
	
	if (state.radio_mutex) { //error checking
		DEBUG_PRINT("\tINFO: Radio busy, unable to send packet.\n");
		goto EXIT;
	}
	
	struct packet_s * packet = appt->packet;
	
	if (packet == NULL) {
		DEBUG_PRINT("\tWARNING: Unexpected NULL packet.\n");
		goto EXIT;
	}

	if (appt->radio_cfg.toaEstimate > PACKET_TOA_MAX_SEND) {
		DEBUG_PRINT("\tWARNING: Packet duration (%ums) longer than configured send limit (%ums).\n", appt->radio_cfg.toaEstimate, PACKET_TOA_MAX_SEND);
		goto EXIT;
	}
	
	state.radio_mutex = 1;
	drv_lora_setMode(&state.radio, DRV_LORA_MODE__IDLE);
	
	setupRadioFromConfig(&state.radio, &(appt->radio_cfg));
	
	drv_lora_sendRawPacket_async(&state.radio, &(packet->raw[0]), packet->size);
	
	enum drv_sched_err_e err = drv_sched_once(drv_mesh_worker_send_finish, NULL, DRV_SCHED_PRI__REALTIME, appt->radio_cfg.toaEstimate + PADDING_MS);
	if (err != DRV_SCHED_ERR__NONE) {
		DEBUG_PRINT_REALTIME(); DEBUG_PRINT("WARNING: Failed to schedule drv_mesh_worker_send_finish()\n");
		drv_lora_setMode(&state.radio, DRV_LORA_MODE__SLEEP);
		state.radio_mutex = 0;
		goto EXIT;
	}

	DEBUG_PRINT("\tsend PACKET_RAW [%hhu]: [", packet->size);
	for (uint32_t i=0; i<packet->size; i++) DEBUG_PRINT(((i+1==packet->size) ? "%hhu" : "%hhu,"), (packet->raw)[i]);
	DEBUG_PRINT("]\n");
	
/* 	if (appt->type == APPT_SEND_DISC) {
		state.stats.broadcasts_sent++;
	} */
	
	EXIT:
	insertEmptyAppt(appt);
}

#if defined (__cplusplus)
}
#endif
#endif // DRV_MESH_SEND_H