//#include "../drivers/sched/drv_sched.h"
#include "../drivers/drv.h"

void testing(void) {
	
}

int main(void) {
	drv_sched_init(NULL, NULL);
	drv_sched_once(&testing, DRV_SCHED_PRI__NORMAL, 0);
	return 0;
}
