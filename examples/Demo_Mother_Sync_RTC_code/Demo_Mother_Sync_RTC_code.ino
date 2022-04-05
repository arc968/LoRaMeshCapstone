#include "RTClib.h"

RTC_DS3231 rtcMasterClock;
RTC_DS3231 rtcSlaveClock;

#define INTERRUPT_PIN 5
// the pin that is connected to SQW
#define CLOCK_INTERRUPT_PIN 2
#define LED_PIN 6

void setup() {
  // put your setup code here, to run once:

  pinMode(LED_PIN, OUTPUT);
  digitalWrite(LED_PIN, LOW);

  // Making it so, that the alarm will trigger an interrupt
  pinMode(CLOCK_INTERRUPT_PIN, INPUT_PULLUP);
  attachInterrupt(digitalPinToInterrupt(CLOCK_INTERRUPT_PIN), onAlarm, FALLING);

  while (!Serial) {
    Serial.begin(115200);
  }

  // initializing the rtc
  while (!rtcMasterClock.begin()) {
      
  }

  rtcMasterClock.disableAlarm(2);
  rtcMasterClock.disable32K();
  rtcMasterClock.clearAlarm(1);
  rtcMasterClock.clearAlarm(2);
  rtcMasterClock.writeSqwPinMode(DS3231_OFF);
  rtcMasterClock.adjust(DateTime(0, 0, 0, 0, 0, 0));
  rtcMasterClock.setAlarm1(rtcMasterClock.now() + TimeSpan(15), DS3231_A1_Day);
    
  Serial.println("RTC READY");

}

void loop() {
  // put your main code here, to run repeatedly:

  if (rtcMasterClock.alarmFired(1)) {
    DateTime current = rtcMasterClock.now();
    if (rtcSlaveClock.begin()) {
      rtcSlaveClock.adjust(current);
      rtcSlaveClock.clearAlarm(1);
      rtcSlaveClock.setAlarm1(current + TimeSpan(15), DS3231_A1_Day);
      digitalWrite(LED_PIN, HIGH);
    }
    rtcMasterClock.clearAlarm(1);
    rtcMasterClock.setAlarm1(current + TimeSpan(15), DS3231_A1_Day);
  }

  delay(10);

  digitalWrite(LED_PIN, LOW);

}

void onAlarm() {
  
}
