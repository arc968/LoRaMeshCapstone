extern "C" {
//#include "../drivers/sched/drv_sched.h"
#include "../drivers/drv.h"
}

void testing(void) {
	
}

int main(void) {
	drv_sched_init();
	drv_sched_once(&testing, PRI_NORMAL, 0);
	return 0;
}
