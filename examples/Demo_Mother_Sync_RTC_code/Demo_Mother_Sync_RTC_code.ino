#include "RTClib.h"
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

  while (!Serial) {
  Serial.begin(115200);
  }

  // initializing the rtc
  rtcMasterClock.begin(true);

  rtcMasterClock.setTime(0, 0, 0);
  rtcMasterClock.setDate(2000, 1, 1);

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
      rtcSlaveClock.writeSqwPinMode(DS3231_OFF);
      DateTime alarm = (0,0,0,0,0,0);
      rtcSlaveClock.setAlarm1(alarm, DS3231_A1_Second);
      rtcSlaveClock.disable32K();
      rtcSlaveClock.clearAlarm(2);
      rtcSlaveClock.disableAlarm(2);
      digitalWrite(LED_PIN, HIGH);
      Serial.println("SLAVE SET");
    }
    rtcMasterClock.setAlarmTime(current.hour(), current.minute(), current.second() + 2);
    rtcMasterClock.setAlarmDate(current.day(), 0, 0);
    rtcMasterClock.enableAlarm(rtcMasterClock.MATCH_DHHMMSS);
    alarmtrig = false;
    Serial.println("RTC ALARM");
  }

  delay(10);

  digitalWrite(LED_PIN, LOW);

}

void onAlarm() {
  alarmtrig = true;
}
