#include "../../hal/hal.h"
#include "../gps/drv_gps.h"
#include "../lora/drv_lora.h"
#include "../sched/drv_sched.h"
#include "drv_mesh.h"

void drv_mesh_init(void) {
	//initialize datastructures
	
	//initialize GPS
	
	//configure GPS for timekeeping mode as appropriate
	
	//enable PPS interrupt handler (schedules mesh handler a few seconds before next run time
	
	//initialize LoRa radio
	
	//configure LoRa radio
}