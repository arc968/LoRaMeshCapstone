extern "C" {
//#include "../drivers/sched/drv_sched.h"
#include "../drivers/drv.h"
}

void test(void) {
	
}

int main(void) {
	drv_sched_init();
	drv_sched_once(test, PRI_NORMAL, 0);
	return 0;
}
