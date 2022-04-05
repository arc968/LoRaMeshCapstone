#include "RTClib_MULTI.h"
#include <RTCZero.h>

bool alarmtrig = false;

RTCZero rtcMasterClock;
RTC_DS3231 rtcSlaveClock;

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

  //while (!Serial) {
  Serial.begin(115200);
  //}

  // initializing the rtc
  while (!rtcMasterClock.begin(true)) {
      
  }

  rtcMasterClock.setAlarmTime(0, 0, 2);
  rtcMasterClock.setAlarmDate(2000, 1, 1);
  rtcMasterClock.enableAlarm(rtcMasterClock.MATCH_DHHMMSS);
  
  rtcMasterClock.attachInterrupt(onAlarm);
    
  Serial.println("RTC READY");

}

void loop() {
  // put your main code here, to run repeatedly:

  if (alarmtrig) {
    DateTime current = {rtcMasterClock.getYear(), rtcMasterClock.getMonth(), rtcMasterClock.getDay(), 
                        rtcMasterClock.getHours(), rtcMasterClock.getMinutes(), rtcMasterClock.getSeconds()};
    if (rtcSlaveClock.begin()) {
      rtcSlaveClock.adjust(current);
      rtcSlaveClock.clearAlarm(1);
      rtcSlaveClock.setAlarm1(current + TimeSpan(15), DS3231_A1_Day);
      digitalWrite(LED_PIN, HIGH);
    }
    rtcMasterClock.setAlarmTime(current.hours(), current.minute(), current.second() + 2);
    rtcMasterClock.setAlarmDate(current.day(), 0, 0);
    rtcMasterClock.enableAlarm(rtcMasterClock.MATCH_DHHMMSS);
    alarmtrig = false;
  }

  delay(10);

  digitalWrite(LED_PIN, LOW);

}

void onAlarm() {
  alarmtrig = true;
}
