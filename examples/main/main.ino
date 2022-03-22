#include "LoRaMeshCapstone.h"

void onSleep() {
  //digitalWrite(9, LOW);
}

void onWake() {
  //digitalWrite(9, HIGH);
}

void nineOn(void * arg __attribute__((unused))) {
  digitalWrite(9, HIGH);
}

void nineOff(void * arg __attribute__((unused))) {
  digitalWrite(9, LOW);
}

void blinkOn(void * arg __attribute__((unused))) {
  digitalWrite(LED_BUILTIN, HIGH);
}

void blinkOff(void * arg __attribute__((unused))) {
  digitalWrite(LED_BUILTIN, LOW);
}

void sevenOff(void * arg __attribute__((unused))) {
  digitalWrite(7, LOW);
}

void sevenOn_Off(void * arg __attribute__((unused))) {
  drv_sched_once(sevenOff, NULL, DRV_SCHED_PRI__NORMAL, 1000);
  digitalWrite(7, HIGH);
}

void checkDateSet(void * arg __attribute__((unused))) {
  if (drv_timer_absoluteTimeIsAvailable()) {
    digitalWrite(7, HIGH);
  }
}

void eightOff(void * arg __attribute__((unused))) {
  drv_sched_once(eightOn, NULL, DRV_SCHED_PRI__NORMAL, 2000);
  digitalWrite(8, LOW);
}

void eightOn(void * arg __attribute__((unused))) {
  drv_sched_once(eightOff, NULL, DRV_SCHED_PRI__NORMAL, 100);
  digitalWrite(8, HIGH);
}

void setTestDate(void * arg __attribute__((unused))) {
  struct lib_datetime_s dt;
  dt.year = 2000;
  dt.month = 1;
  dt.day = 1;
  dt.hour = 0;
  dt.min = 0;
  dt.sec = 1;
  dt.ms = 0;
  drv_timer_setAbsoluteDateTime(&dt);
  drv_sched_once_at(nineOn, NULL, DRV_SCHED_PRI__NORMAL, 3000);
  drv_sched_once_at(nineOff, NULL, DRV_SCHED_PRI__NORMAL, 10000);
}

void onRecv(struct drv_mesh_packet_s *) {

}

void setup() {
  // put your setup code here, to run once:
  pinMode(LED_BUILTIN, OUTPUT);
  pinMode(7, OUTPUT);
  pinMode(8, OUTPUT);
  pinMode(9, OUTPUT);

  pinMode(0, INPUT_PULLUP);

  while (!Serial);
  Serial.begin(115200);
  delay(500);
  Serial.print("Ready\n");
  delay(500);


  drv_sched_init();
  drv_sched_setOnSleepCallback(onSleep);
  drv_sched_setOnWakeCallback(onWake);

  //drv_gps_init(NULL);

  //drv_sched_once(setTestDate, NULL, DRV_SCHED_PRI__NORMAL, 1000);
  drv_sched_repeating(blinkOn, NULL, DRV_SCHED_PRI__NORMAL, 0, 2000);
  drv_sched_repeating(blinkOff, NULL, DRV_SCHED_PRI__NORMAL, 1000, 2000);
  //drv_sched_repeating(checkDateSet, NULL, DRV_SCHED_PRI__NORMAL, 0, 1000);
  //drv_sched_repeating(sevenOn_Off, NULL, DRV_SCHED_PRI__NORMAL, 0, 5000);
  //drv_sched_once(eightOn, NULL, DRV_SCHED_PRI__NORMAL, 0);

  drv_mesh_init(onRecv);
  drv_sched_start();
}

void loop() {
  // put your main code here, to run repeatedly:

}
