#ifndef DRV_MESH_PRIVATE_UTIL_H
#define DRV_MESH_PRIVATE_UTIL_H
#if defined (__cplusplus)
extern "C" {
#endif

#define RB_CAPACITY(rb) ((uint16_t)(sizeof(rb.buf)/sizeof(__typeof__(rb.buf[0]))))
#define RB_COUNT(rb) ((uint16_t)rb.count)
#define RB_SPACE(rb) ((uint16_t)(RB_CAPACITY(rb) - RB_COUNT(rb)))
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
		route->next = NULL;
	}
	return route;
}

/* static void insertEmptyRoute(struct route_s * route) {
	route->next = state.head_route_empty;
	state.head_route_empty = route;
} */

static uint32_t getBucketIndex(ipv4_t ip_src) {
	uint32_t tmp;
	halfsiphash(ip_src, sizeof(ipv4_t), state.key_hashtable, (uint8_t *)&tmp, sizeof(uint32_t));
	return lib_misc_fastrange32(tmp, HASHMAP_ROUTES_BUCKET_COUNT);
}

//TODO figure out why this hangs and why they reach this in the first place
static struct route_s * deleteOldestRoute(void) { //should only be called if all routes are in use
	DEBUG_PRINT_FUNCTION();
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
	DEBUG_PRINT_FUNCTION();
	if (ip_src[0] != 10 || (memcmp(ip_src, GATEWAY_IP, sizeof(ipv4_t)) == 0)) {
		if (realtime != 0) state.route_gateway.last_usage = realtime;
		// if (state.route_gateway.count != 0) {
		return &(state.route_gateway);
		// } else {
		// 	return NULL;
		// }
	}
	struct route_s * route = state.hm_route_buckets[getBucketIndex(ip_src)];
	while (route != NULL && memcmp(route->ip_src, ip_src, sizeof(ipv4_t))) route = route->next;
	if (route != NULL && realtime != 0) route->last_usage = realtime;
	return route;
}

//Doesn't properly handle the gateway being returned
static void insertRoute(ipv4_t ip_src, uint8_t ttl, uint16_t index_peer, lib_datetime_realtime_t realtime) {
	DEBUG_PRINT_FUNCTION();
	struct route_s * route = findRoute(ip_src, realtime);
	if (route == NULL) {
		route = popEmptyRoute();
		if (route == NULL) {
			route = deleteOldestRoute();
		}
	}
	memcpy(route->ip_src, ip_src, sizeof(ipv4_t));
	route->last_usage = realtime;
	bool peerAlreadyInList = false;
	//if peer already in list, remove it
	for (int i=0; i<ROUTE_PEER_COUNT; i++) {
		if (index_peer == route->peers[i].index_peer) {
			peerAlreadyInList = true;
			if (route->peers[i].ttl < ttl) {
				ttl = route->peers[i].ttl; //use the lower of the two TTLs
			}
			for (int ii=i; ii<ROUTE_PEER_COUNT-1; ii++) {
				route->peers[ii].ttl = route->peers[ii+1].ttl;
				route->peers[ii].index_peer = route->peers[ii+1].index_peer;
			}
			break;
		}
	}
	//add peer back to list, keep list sorted
	if (!peerAlreadyInList && route->count < ROUTE_PEER_COUNT) route->count++;
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
	if (route != &(state.route_gateway)) {
		uint32_t hm_index = getBucketIndex(ip_src);
		struct route_s * tmp = state.hm_route_buckets[hm_index];
		if (tmp == NULL) {
			state.hm_route_buckets[hm_index] = route;
			route->next = NULL;
		} else {
			while (tmp->next != NULL && memcmp(tmp->ip_src, ip_src, sizeof(ipv4_t))) tmp = tmp->next;
			if (memcmp(tmp->ip_src, ip_src, sizeof(ipv4_t)) == 0) {
				//do nothing, already in hashmap 
			} else {
				route->next = NULL;
				tmp->next = route;
			}
		}
	}
}

static void insertReadyPeer(struct peer_s * peer) {
	peer->next = state.head_peer_ready;
	state.head_peer_ready = peer;
}

static struct packet_s * popEmptyPacket(void) {
	struct packet_s * packet = state.head_packet_empty;
	if (packet != NULL) {
		state.head_packet_empty = packet->next;
		packet->next = NULL;
	}
	return packet;
}

static void insertEmptyPacket(struct packet_s * packet) {
	packet->next = state.head_packet_empty;
	state.head_packet_empty = packet;
}

static struct peer_s * popEmptyPeer(void) {
	struct peer_s * peer = state.head_peer_empty;
	if (peer != NULL) {
		state.head_peer_empty = peer->next;
		peer->next = NULL;
	}
	return peer;
}

static void insertEmptyPeer(struct peer_s * peer) {
	uint16_t count = RB_COUNT(peer->rb_packets);
	for (uint16_t i=0; i<count; i++) {
		struct packet_s * packet = *RB_GET(peer->rb_packets);
		insertEmptyPacket(packet);
	}
	peer->next = state.head_peer_empty;
	state.head_peer_empty = peer;
}

/* static void removeReadyPeer(struct peer_s * peer) {
	if (state.head_peer_ready == peer) {
		state.head_peer_ready = NULL;
	} else {
		struct peer_s * prev_peer = state.head_peer_ready;
		while (prev_peer->next != peer) prev_peer = prev_peer->next;
		prev_peer->next = peer->next;
		peer->next = NULL;
	}
} */

static struct peer_s * getPeerByPubDhKey(uint8_t key_dh_pub[32]) {
	struct peer_s * peer = state.head_peer_ready;
	while (peer != NULL && crypto_verify32(peer->key_dh_pub, key_dh_pub)) peer = peer->next;
	return peer;
}

static struct appointment_s * popEmptyAppt(void) {
	struct appointment_s * appt = state.head_appt_empty;
	if (appt != NULL) {
		state.head_appt_empty = appt->next;
		appt->next = NULL;
	}
	return appt;
}

static void insertEmptyAppt(struct appointment_s * appt) {
	if (appt->packet != NULL) {
		insertEmptyPacket(appt->packet);
		appt->packet = NULL;
	}
	//appt->peer = NULL;
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
	//DEBUG_PRINT("\t"); DEBUG_PRINT_FUNCTION();
	DEBUG_PRINT("\tpreamble:%hu, BW:%lu, Hz:%llu, SF:%lu, CR:4/%lu\n", cfg->preambleSymbols, cfg->bandwidth, cfg->frequency, cfg->spreadingFactor, cfg->codingRate+4);
	
	drv_lora_setPreamble(radio, cfg->preambleSymbols);
	drv_lora_setBandwidth(radio, cfg->bandwidth);
	drv_lora_setFrequency(radio, cfg->frequency);
	drv_lora_setSpreadingFactor(radio, cfg->spreadingFactor);
	drv_lora_setCodingRate(radio, cfg->codingRate + 4);
}

/* static lib_datetime_realtime_t roundRealtimeToBlock(lib_datetime_realtime_t rt) {
	return 0;
} */

#ifndef min
#define min(a,b) \
   ({ __typeof__ (a) _a = (a); \
       __typeof__ (b) _b = (b); \
     _a < _b ? _a : _b; })
#endif
#ifndef max
#define max(a,b) \
   ({ __typeof__ (a) _a = (a); \
       __typeof__ (b) _b = (b); \
     _a > _b ? _a : _b; })
#endif

static void estimateTimeOnAirInMsFromRadioCfg(struct radio_cfg_s * cfg, uint8_t packet_size, uint32_t * toa, uint16_t  *preambleSymbols) {
	const uint32_t CRC = 1;
	const uint32_t IH = 1;
	const uint32_t DE = 0;
	int32_t Rs = cfg->bandwidth / (1 << cfg->spreadingFactor);
	int32_t num = 8*packet_size - 4*cfg->spreadingFactor + 28 + 16*CRC - 20*IH;
	int32_t den = 4*(cfg->spreadingFactor - 2*DE);
	int32_t n_payload = 8 + (max(((num/den) + 1)*(cfg->codingRate + 4), 0)); //instead of ceil, add 1
	uint32_t t_payload = (n_payload * 1000) / Rs;

	*preambleSymbols = (uint16_t)((PREAMBLE_MS*Rs)/1000) + 4;
	//uint32_t t_preamble = ((cfg->preambleSymbols + 5) * 1000) / Rs; //should be 4.25, rounding up to 5

	*toa = PREAMBLE_MS + t_payload;
	
	if (packet_size <= 4) {
		DEBUG_PRINT("\tPacket ToA estimate: %ums preamble (%u symbols) + %ums payload (%u symbols) = %ums packet (%hhu bytes)\n", PREAMBLE_MS, *preambleSymbols, t_payload, n_payload, *toa, packet_size);
	}
}

static void setRadioCfgAtTimeFromSeed(struct radio_cfg_s * cfg, lib_datetime_realtime_t rt, uint32_t seed, uint8_t packet_size) {
	seed = LIB_BYTEORDER_HTON_U32(seed);
	rt = LIB_BYTEORDER_HTON_U64(rt); //probably doesn't work properly
	crypto_blake2b_general((uint8_t *)&seed, sizeof(seed), (uint8_t *)&seed, sizeof(seed), (uint8_t *)&rt, sizeof(rt));
	seed = LIB_BYTEORDER_NTOH_U32(seed);
	uint32_t tmp_toa;
	uint16_t tmp_preambleSymbols;
	do {
		seed = LIB_BYTEORDER_NTOH_U32(lib_misc_XORshiftLFSR32(LIB_BYTEORDER_HTON_U32(seed)));
		cfg->bandwidth = drv_lora_bandwidth_e_arr[lib_misc_fastrange32(seed, sizeof(drv_lora_bandwidth_e_arr)/sizeof(drv_lora_bandwidth_e_arr[0]))];
		seed = LIB_BYTEORDER_NTOH_U32(lib_misc_XORshiftLFSR32(LIB_BYTEORDER_HTON_U32(seed)));
		cfg->frequency = getCenterFrequency(lib_misc_fastrange32(seed, getChannelCount(cfg->bandwidth)), cfg->bandwidth);
		seed = LIB_BYTEORDER_NTOH_U32(lib_misc_XORshiftLFSR32(LIB_BYTEORDER_HTON_U32(seed)));
		cfg->spreadingFactor = drv_lora_spreadingFactor_e_arr[lib_misc_fastrange32(seed, sizeof(drv_lora_spreadingFactor_e_arr)/sizeof(drv_lora_spreadingFactor_e_arr[0]))];
		seed = LIB_BYTEORDER_NTOH_U32(lib_misc_XORshiftLFSR32(LIB_BYTEORDER_HTON_U32(seed)));
		cfg->codingRate = drv_lora_codingRate_e_arr[lib_misc_fastrange32(seed, sizeof(drv_lora_codingRate_e_arr)/sizeof(drv_lora_codingRate_e_arr[0]))];
		estimateTimeOnAirInMsFromRadioCfg(cfg, 255, &tmp_toa, &tmp_preambleSymbols);
		//DEBUG_PRINT("\t\tradio cfg seed: %u\n", seed);
	} while (tmp_toa > PACKET_TOA_MAX_GENERATE);

	estimateTimeOnAirInMsFromRadioCfg(cfg, packet_size, &(cfg->toaEstimate), &(cfg->preambleSymbols));
}

//this is kinda garbage
static uint32_t getPeerIndexFromPtr(struct peer_s * peer) {
	return ((uint8_t *)(peer) - (uint8_t *)&(state.peers[0])) / sizeof(struct peer_s);
}

static bool checkRecentPayload(struct payload_s * payload, size_t size) {
	DEBUG_PRINT_FUNCTION();
	DEBUG_PRINT_BUF(payload, size);
	uint8_t hash[sizeof(state.rb_recentPayloads.buf[0].hash)];
	crypto_blake2b_general(hash, sizeof(hash), NULL, 0, (uint8_t *)(payload) + sizeof(struct payload_header_s), size - sizeof(struct payload_header_s));
	DEBUG_PRINT_BUF(hash, sizeof(hash));

	uint16_t count = RB_COUNT(state.rb_recentPayloads);
	bool found = false;
	for (uint16_t i=0; i<count; i++) {
		__typeof__(state.rb_recentPayloads.buf[0]) * tmp = RB_GET(state.rb_recentPayloads);
		if (!memcmp(tmp->hash, hash, sizeof(hash))) { //timing attack blah blah
			found = true;
			DEBUG_PRINT("\tMATCH\n");
		}
		DEBUG_PRINT_BUF(tmp->hash, sizeof(tmp->hash));
		__typeof__(state.rb_recentPayloads.buf[0]) * tmp1 = RB_PUT(state.rb_recentPayloads);
		memcpy(tmp1, tmp, sizeof(state.rb_recentPayloads.buf[0]));
	}
	return found;
}

static void insertRecentPayload(struct payload_s * payload, size_t size) {
	DEBUG_PRINT_FUNCTION();
	if (!RB_SPACE(state.rb_recentPayloads)) {
		RB_GET(state.rb_recentPayloads);
	}
	DEBUG_PRINT_BUF(payload, size);
	__typeof__(state.rb_recentPayloads.buf[0]) * entry = RB_PUT(state.rb_recentPayloads);
	entry->ttl = payload->header.ttl;
	crypto_blake2b_general(entry->hash, sizeof(entry->hash), NULL, 0, (uint8_t *)payload + sizeof(struct payload_header_s), size - sizeof(struct payload_header_s));
	DEBUG_PRINT_BUF((uint8_t *)payload + sizeof(struct payload_header_s), size - sizeof(struct payload_header_s));
	DEBUG_PRINT_BUF(entry->hash, sizeof(entry->hash));
}

#if defined (__cplusplus)
}
#endif
#endif // DRV_MESH_PRIVATE_UTIL_H