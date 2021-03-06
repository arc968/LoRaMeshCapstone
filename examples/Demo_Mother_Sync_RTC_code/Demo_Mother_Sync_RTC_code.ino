#include "RTClib.h"
#include <RTCZero.h>

bool alarmtrig = false;

RTCZero rtcMasterClock;
RTC_DS3231 rtcSlaveClock;

#define CLOCK_INTERRUPT_PIN 0 // the pin that is connected to SQW
#define LED_WRITE_INDICATOR 4

void setup() {
  
  pinMode(LED_WRITE_INDICATOR, OUTPUT);
  digitalWrite(LED_WRITE_INDICATOR, LOW);

  // Making it so, that the alarm will trigger an interrupt
  pinMode(CLOCK_INTERRUPT_PIN, INPUT_PULLUP);
  attachInterrupt(digitalPinToInterrupt(CLOCK_INTERRUPT_PIN), onAlarm, FALLING);

  //while (!Serial) {
    Serial.begin(115200);
  //}

  Wire.setTimeout(100);

  // initializing the rtc
  rtcMasterClock.begin(true);

  rtcMasterClock.setTime(0, 0, 0);
  rtcMasterClock.setDate(1, 1, 22);

  rtcMasterClock.setAlarmTime(0, 0, 2);
  rtcMasterClock.setAlarmDate(1, 1, 22);
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
      rtcSlaveClock.clearAlarm(2);
      rtcSlaveClock.writeSqwPinMode(DS3231_OFF);
      rtcSlaveClock.disable32K();
      //rtcSlaveClock.disableAlarm(2);
      DateTime alarm1 = DateTime(0,0,0,0,0,30);
      rtcSlaveClock.setAlarm1(alarm1, DS3231_A1_Second);
      DateTime alarm2 = DateTime(0,0,0,0,0,0);
      rtcSlaveClock.setAlarm2(alarm2, DS3231_A2_PerMinute);
      digitalWrite(LED_WRITE_INDICATOR, HIGH);
      Serial.println("SLAVE SET");
    }
    else {
      digitalWrite(LED_WRITE_INDICATOR, LOW);
    }
    rtcMasterClock.setAlarmTime(current.hour(), current.minute(), current.second() + 2);
    rtcMasterClock.setAlarmDate(current.day(), current.month(), current.year());
    rtcMasterClock.enableAlarm(rtcMasterClock.MATCH_DHHMMSS);
    alarmtrig = false;
    Serial.println("RTC ALARM");
  }

}

void onAlarm() {
  alarmtrig = true;
}
