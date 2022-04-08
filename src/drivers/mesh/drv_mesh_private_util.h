#ifndef DRV_MESH_PRIVATE_UTIL_H
#define DRV_MESH_PRIVATE_UTIL_H
#if defined (__cplusplus)
extern "C" {
#endif

#define RB_CAPACITY(rb) ((uint16_t)(sizeof(rb.buf)/sizeof(__typeof__(rb.buf[0]))))
#define RB_COUNT(rb) ((uint16_t)rb.count)
#define RB_GET(rb) ((__typeof__(rb.buf[0]) *)(\
    (rb.count == 0) ? NULL : \
        (rb.tail = ((rb.tail+1)%RB_CAPACITY(rb)),\
        rb.count--,\
        &(rb.buf[(rb.tail == 0) ? RB_CAPACITY(rb)-1 : rb.tail-1]))\
))
#define RB_PEEK(rb) ((__typeof__(rb.buf[0]) *)(\
    (rb.count == 0) ? NULL : \
        &(rb.buf[rb.tail])\
))
#define RB_PUT(rb) ((__typeof__(rb.buf[0]) *)(\
    (rb.count == RB_CAPACITY(rb)) ? NULL : \
        (rb.head = ((rb.head+1)%RB_CAPACITY(rb)),\
        rb.count++,\
        &(rb.buf[(rb.head == 0) ? RB_CAPACITY(rb)-1 : rb.head-1]))\
))

static struct route_s * popEmptyRoute(void) {
	struct route_s * route = state.head_route_empty;
	if (route != NULL) {
		state.head_route_empty = route->next;
	}
	route->next = NULL;
	return route;
}

static void insertEmptyRoute(struct route_s * route) {
	route->next = state.head_route_empty;
	state.head_route_empty = route;
}

static uint32_t getBucketIndex(ipv4_t ip_src) {
	uint32_t tmp;
	halfsiphash(&ip_src, sizeof(ipv4_t), state.key_hashtable, (uint8_t *)&tmp, sizeof(uint32_t));
	return lib_misc_fastrange32(LIB_BYTEORDER_NTOH_U32(tmp), HASHMAP_ROUTES_BUCKET_COUNT);
}

static struct route_s * deleteOldestRoute(void) { //should only be called if all routes are in use
	struct route_s * route = &(state.routes[0]);
	for (uint32_t i=0; i<BUFFER_ROUTES_SIZE; i++) {
		struct route_s * tmp_route = &(state.routes[i]);
		if (tmp_route->last_usage < route->last_usage) {
			route = tmp_route;
		}
	}
	uint32_t hm_index = getBucketIndex(route->ip_src);
	struct route_s * tmp_route = state.hm_route_buckets[hm_index];
	if (tmp_route == route) {
		state.hm_route_buckets[hm_index] = route->next;
		route->next = NULL;
		return route;
	}
	while (tmp_route->next != route) tmp_route = tmp_route->next;
	tmp_route->next = route->next;
	route->next = NULL;
	return route;
}

static struct route_s * findRoute(ipv4_t ip_src, lib_datetime_realtime_t realtime) {
	if (ip_src[0] != 10) {
		state.route_gateway.last_usage = realtime;
		return &(state.route_gateway);
	}
	struct route_s * route = state.hm_route_buckets[getBucketIndex(ip_src)];
	while (route != NULL && route->ip_src != ip_src) route = route->next;
	if (route != NULL) route->last_usage = realtime;
	return route;
}

static void insertRoute(ipv4_t ip_src, uint8_t ttl, uint16_t index_peer, lib_datetime_realtime_t realtime) {
	struct route_s * route = findRoute(ip_src, realtime);
	if (route == NULL) {
		route = popEmptyRoute();
		if (route == NULL) {
			route = deleteOldestRoute();
		}
	}
	route->last_usage = realtime;
	for (int i=0; i<ROUTE_PEER_COUNT; i++) {
		if (ttl <= route->peers[i].ttl) {
			for (int ii=ROUTE_PEER_COUNT-1; ii>i; ii--) {
				route->peers[ii].ttl = route->peers[ii-1].ttl;
				route->peers[ii].index_peer = route->peers[ii-1].index_peer;
			}
			route->peers[i].ttl = ttl;
			route->peers[i].index_peer = index_peer;
			break;
		}
	}
}

static struct peer_s * popEmptyPeer(void) {
	struct peer_s * peer = state.head_peer_empty;
	if (peer != NULL) {
		state.head_peer_empty = peer->next;
	}
	peer->next = NULL;
	return peer;
}

static void insertEmptyPeer(struct peer_s * peer) {
	peer->next = state.head_peer_empty;
	state.head_peer_empty = peer;
}

static void removeReadyPeer(struct peer_s * peer) {
	if (state.head_peer_ready == peer) {
		state.head_peer_ready = NULL;
	} else {
		struct peer_s * prev_peer = state.head_peer_ready;
		while (prev_peer->next != peer) prev_peer = prev_peer->next;
		prev_peer->next = peer->next;
		peer->next = NULL;
	}
}

static struct peer_s * getPeerByPubDhKey(uint8_t key_dh_pub[32]) {
	struct peer_s * peer = state.head_peer_ready;
	while (peer != NULL && crypto_verify32(peer->key_dh_pub, key_dh_pub)) peer = peer->next;
	return peer;
}

static void insertReadyPeer(struct peer_s * peer) {
	peer->next = state.head_peer_ready;
	state.head_peer_ready = peer;
}

static struct packet_s * popEmptyPacket(void) {
	struct packet_s * packet = state.head_packet_empty;
	if (packet != NULL) {
		state.head_packet_empty = packet->next;
	}
	packet->next = NULL;
	return packet;
}

static void insertEmptyPacket(struct packet_s * packet) {
	packet->next = state.head_packet_empty;
	state.head_packet_empty = packet;
}

static struct appointment_s * popEmptyAppt(void) {
	struct appointment_s * appt = state.head_appt_empty;
	if (appt != NULL) {
		state.head_appt_empty = appt->next;
	}
	appt->next = NULL;
	return appt;
}

static void insertEmptyAppt(struct appointment_s * appt) {
	if (appt->packet != NULL) {
		insertEmptyPacket(appt->packet);
		appt->packet = NULL;
	}
	appt->peer = NULL;
	appt->next = state.head_appt_empty;
	state.head_appt_empty = appt;
}

static uint64_t constrainU64(uint64_t x, uint64_t a, uint64_t b) {
	if(x < a) {
		return a;
	} else if(b < x) {
		return b;
	} else {
		return x;
	}
}

static int64_t absI64(int64_t x) {
	if (x < 0) x = -(x);
	return x;
}

static uint64_t map(uint64_t x, uint64_t in_min, uint64_t in_max, uint64_t out_min, uint64_t out_max) {
	return (x - in_min) * (out_max - out_min) / (in_max - in_min) + out_min;
}

static uint32_t getChannelCount(enum drv_lora_bandwidth_e bw) {
	if (bw == DRV_LORA_BW__500kHz) return LORA_US_CHANNELCOUNT_500kHz;
	if (bw == DRV_LORA_BW__250kHz) return LORA_US_CHANNELCOUNT_250kHz;
	if (bw == DRV_LORA_BW__125kHz) return LORA_US_CHANNELCOUNT_125kHz;
	if (bw == DRV_LORA_BW__62_5kHz) return LORA_US_CHANNELCOUNT_62_5kHz;
	return LORA_US_CHANNELCOUNT_500kHz;
}

//TODO: only works in US, no error handling
static uint64_t getCenterFrequency(channel_t channel, enum drv_lora_bandwidth_e bandwidth) {
	if (bandwidth == DRV_LORA_BW__500kHz) return LORA_US_FREQ_MIN + LORA_US_PADDING_500kHz + (channel * FREQ_500kHz) + (channel * LORA_US_PADDING_500kHz) + (FREQ_500kHz / 2);
	if (bandwidth == DRV_LORA_BW__250kHz) return LORA_US_FREQ_MIN + LORA_US_PADDING_250kHz + (channel * FREQ_250kHz) + (channel * LORA_US_PADDING_250kHz) + (FREQ_250kHz / 2);
	if (bandwidth == DRV_LORA_BW__125kHz) return LORA_US_FREQ_MIN + LORA_US_PADDING_125kHz + (channel * FREQ_125kHz) + (channel * LORA_US_PADDING_125kHz) + (FREQ_125kHz / 2);
	if (bandwidth == DRV_LORA_BW__62_5kHz) return LORA_US_FREQ_MIN + LORA_US_PADDING_62_5kHz + (channel * FREQ_62_5kHz) + (channel * LORA_US_PADDING_62_5kHz) + (FREQ_62_5kHz / 2);
	return 0;
}

static void setupRadioFromConfig(struct drv_lora_s * radio, struct radio_cfg_s * cfg) {
	DEBUG_PRINT("\t"); DEBUG_PRINT_FUNCTION();
	DEBUG_PRINT("\t\tpreamble:%hu, bandwidth:%lu, frequency:%llu, spreadingFactor:%lu, codingRate:%lu\n", cfg->preambleSymbols, cfg->bandwidth, cfg->frequency, cfg->spreadingFactor, cfg->codingRate);
	
	drv_lora_setPreamble(radio, cfg->preambleSymbols);
	drv_lora_setBandwidth(radio, cfg->bandwidth);
	drv_lora_setFrequency(radio, cfg->frequency);
	drv_lora_setSpreadingFactor(radio, cfg->spreadingFactor);
	drv_lora_setCodingRate(radio, cfg->codingRate);
}

/* static lib_datetime_realtime_t roundRealtimeToBlock(lib_datetime_realtime_t rt) {
	return 0;
} */

static enum drv_lora_bandwidth_e drv_lora_bandwidth_e_arr[] = {
	DRV_LORA_BW__500kHz,
	//DRV_LORA_BW__250kHz,
	//DRV_LORA_BW__125kHz,
	//DRV_LORA_BW__62_5kHz,
};
static enum drv_lora_spreadingFactor_e drv_lora_spreadingFactor_e_arr[] = {
	//DRV_LORA_SF__6,
	DRV_LORA_SF__7,
	//DRV_LORA_SF__8,
	//DRV_LORA_SF__9,
	//DRV_LORA_SF__10,
	//DRV_LORA_SF__11,
	//DRV_LORA_SF__12,
};
static enum drv_lora_codingRate_e drv_lora_codingRate_e_arr[] = {
	//DRV_LORA_CR__4_5,
	//DRV_LORA_CR__4_6,
	DRV_LORA_CR__4_7,
	//DRV_LORA_CR__4_8,
};
static void setRadioCfgAtTimeFromSeed(struct radio_cfg_s * cfg, lib_datetime_realtime_t rt, uint32_t seed) {
	seed = LIB_BYTEORDER_HTON_U32(seed);
	rt = LIB_BYTEORDER_HTON_U64(rt); //probably doesn't work properly
	crypto_blake2b_general((uint8_t *)&seed, sizeof(seed), (uint8_t *)&seed, sizeof(seed), (uint8_t *)&rt, sizeof(rt));
	seed = LIB_BYTEORDER_NTOH_U32(seed);
	
	cfg->preambleSymbols = PREAMBLE_LENGTH;
	cfg->bandwidth = drv_lora_bandwidth_e_arr[lib_misc_fastrange32(seed, sizeof(drv_lora_bandwidth_e_arr)/sizeof(drv_lora_bandwidth_e_arr[0]))];
	cfg->frequency = getCenterFrequency(lib_misc_fastrange32(seed, getChannelCount(cfg->bandwidth)), cfg->bandwidth);
	cfg->spreadingFactor = drv_lora_spreadingFactor_e_arr[lib_misc_fastrange32(seed, sizeof(drv_lora_spreadingFactor_e_arr)/sizeof(drv_lora_spreadingFactor_e_arr[0]))];
	cfg->codingRate = drv_lora_codingRate_e_arr[lib_misc_fastrange32(seed, sizeof(drv_lora_codingRate_e_arr)/sizeof(drv_lora_codingRate_e_arr[0]))];
}

#if defined (__cplusplus)
}
#endif
#endif // DRV_MESH_PRIVATE_UTIL_H