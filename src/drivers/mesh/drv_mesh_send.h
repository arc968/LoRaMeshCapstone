#ifndef DRV_MESH_SEND_H
#define DRV_MESH_SEND_H
#if defined (__cplusplus)
extern "C" {
#endif

static void drv_mesh_buildPacket_disc(struct appointment_s * appt, struct packet_s * raw_packet) {
	raw_packet->size = sizeof(struct packet_type_disc_s);
	struct packet_type_disc_s * packet = (struct packet_type_disc_s *)&(raw_packet->asDisc);
	
	*packet = packet_type_disc_s_default;
	packet->broadcast_peer_uid = state.uid;
	packet->ciphermask.mask = CIPHER__PSK_XCHACHA20;
	memcpy(state.pubkey, packet->key_ephemeral, sizeof(state.pubkey));
	crypto_blake2b_general(packet->hmac, sizeof(packet->hmac), state.psk, sizeof(state.psk), (uint8_t *)&(*packet), sizeof(*packet)-sizeof(packet->hmac));
	
	DEBUG_PRINT_REALTIME(); DEBUG_PRINT("Sending discovery packet as [%llX]...\n", packet->broadcast_peer_uid);
}

static void drv_mesh_buildPacket_discReply(struct appointment_s * appt, struct packet_s * raw_packet) {
	raw_packet->size = sizeof(struct packet_type_discReply_s);
	struct packet_type_discReply_s * packet = (struct packet_type_discReply_s *)&(raw_packet->asDiscReply);
	
	*packet = packet_type_discReply_s_default;
	packet->reply_peer_uid = state.uid;
	packet->broadcast_peer_uid = appt->peer->uid;
	packet->ciphermask.mask = CIPHER__PSK_XCHACHA20;
	
	memcpy(state.pubkey, packet->key_ephemeral, sizeof(state.pubkey));
	crypto_blake2b_general(packet->hmac, sizeof(packet->hmac), state.psk, sizeof(state.psk), (uint8_t *)&(*packet), sizeof(*packet)-sizeof(packet->hmac));
	
	DEBUG_PRINT_REALTIME(); DEBUG_PRINT("Sending discovery reply packet as [%llX] to [%llX]...\n", packet->reply_peer_uid, packet->broadcast_peer_uid);
}

static void drv_mesh_buildPacket(struct appointment_s * appt, struct packet_s * raw_packet) {
	if (appt->type == APPT_SEND_DISC) {
		drv_mesh_buildPacket_disc(appt, raw_packet);
	} else if (appt->type == APPT_SEND_DISC_REPLY) {
		drv_mesh_buildPacket_discReply(appt, raw_packet);
	} else {
		DEBUG_PRINT_REALTIME(); DEBUG_PRINT("WARNING: Unexpected appointment type in drv_mesh_worker_send(), unable to send.\n");
	}
}

static void drv_mesh_worker_send_finish(void * arg) {
	DEBUG_PRINT_REALTIME(); DEBUG_PRINT_FUNCTION();
	DEBUG_PRINT_REALTIME(); DEBUG_PRINT("Packet sent.\n");
	
	drv_lora_setMode(&state.radio, DRV_LORA_MODE__SLEEP);
	state.radio_mutex = 0;
}

static void drv_mesh_worker_send(void * arg) {
	__label__ EXIT;
	DEBUG_PRINT_REALTIME(); DEBUG_PRINT_FUNCTION();
	struct appointment_s * appt = (struct appointment_s *) arg;
	
	if (appt->type == APPT_RECV) { //error checking
		DEBUG_PRINT_REALTIME(); DEBUG_PRINT("ERROR: Unexpected appointment type in drv_mesh_worker_send()\n");
		goto EXIT;
	}
	
	{lib_datetime_realtime_t rt;
	drv_timer_getRealtime(&rt);
	if (rt > appt->realtime+1) { //error checking
		DEBUG_PRINT_REALTIME(); DEBUG_PRINT("WARNING: drv_mesh_worker_send() late, skipping.\n");
		goto EXIT;
	}}
	
	if (state.radio_mutex) { //error checking
		DEBUG_PRINT_REALTIME(); DEBUG_PRINT("WARNING: Radio locked, unable to send discovery packet.\n");
		goto EXIT;
	}
	
	state.radio_mutex = 1;
	drv_lora_setMode(&state.radio, DRV_LORA_MODE__IDLE);
	
	setupRadioFromConfig(&state.radio, &(appt->radio_cfg));
	
	drv_lora_sendRawPacket_async(&state.radio, appt->packet->raw, appt->packet->size);
	
	enum drv_sched_err_e err = drv_sched_once(drv_mesh_worker_send_finish, NULL, DRV_SCHED_PRI__REALTIME, 5000);
	if (err != DRV_SCHED_ERR__NONE) {
		DEBUG_PRINT_REALTIME(); DEBUG_PRINT("WARNING: Failed to schedule drv_mesh_worker_send_finish()\n");
		drv_lora_setMode(&state.radio, DRV_LORA_MODE__SLEEP);
		state.radio_mutex = 0;
		goto EXIT;
	}
	
	if (appt->type == APPT_SEND_DISC) {
		state.stats.broadcasts_sent++;
	}
	
	EXIT:
	insertEmptyAppt(appt);
}

#if defined (__cplusplus)
}
#endif
#endif // DRV_MESH_SEND_H