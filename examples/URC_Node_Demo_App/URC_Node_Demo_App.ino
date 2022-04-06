//LoRa Mesh library includes
#include "LoRaMeshCapstone.h"
#include "lib/byteorder/lib_byteorder.h"

//demo only inlcudes
#include "RTClib.h" //included only for use with external rtc for The demonstration
#include <Adafruit_NeoPixel.h>
#include <stdint.h>

static volatile lib_datetime_interval_t timestamp = 0;
uint16_t sensordata = 0;

RTC_DS3231 GPSRTC;

#define CLOCK_INTERRUPT_PIN 0
#define SENSOR_PIN          A4
#define INTERNAL_LED_PIN    6

//NeoPixel
#define BRIGHTNESS          50 // Set BRIGHTNESS to about 1/5 (max = 255)
#define RING_LED_COUNT      12
#define RING_LED_DATAIN_PIN 5
#define CON_STRIP_COUNT     10
#define CON1_STRIP_DATA_PIN 7
#define CON2_STRIP_DATA_PIN 8
#define CON3_STRIP_DATA_PIN 9

//packet type defines
#define RGBPAKCT            0x00
#define PREDEFCOLORPACKET   0x01


Adafruit_NeoPixel ring(RING_LED_COUNT, RING_LED_DATAIN_PIN, NEO_GRBW + NEO_KHZ800);

Adafruit_NeoPixel con1(CON_STRIP_COUNT, CON1_STRIP_DATA_PIN, NEO_GRBW + NEO_KHZ800);
Adafruit_NeoPixel con2(CON_STRIP_COUNT, CON2_STRIP_DATA_PIN, NEO_GRBW + NEO_KHZ800);
Adafruit_NeoPixel con3(CON_STRIP_COUNT, CON3_STRIP_DATA_PIN, NEO_GRBW + NEO_KHZ800);


void setup() {

  pinMode(INTERNAL_LED_PIN, OUTPUT);
  //pinMode(CLOCK_INTERRUPT_PIN, INPUT_PULLUP);
  pinMode(SENSOR_PIN, INPUT);

  // the value at SQW-Pin (because of pullup 1 means no alarm)
  //attachInterrupt(digitalPinToInterrupt(CLOCK_INTERRUPT_PIN), onAlarm, FALLING);

  digitalWrite(INTERNAL_LED_PIN, LOW);

  ring.begin();           // INITIALIZE NeoPixel strip object (REQUIRED)
  ring.fill(ring.Color(255, 0, 0));
  ring.show();            
  ring.setBrightness(BRIGHTNESS);

  con1.begin();           // INITIALIZE NeoPixel strip object (REQUIRED)
  con1.fill(con1.Color(255, 0, 0));
  con1.show();            
  con1.setBrightness(BRIGHTNESS);

  con2.begin();           // INITIALIZE NeoPixel strip object (REQUIRED)
  con1.fill(con2.Color(255, 0, 0));
  con2.show();            
  con2.setBrightness(BRIGHTNESS);

  con3.begin();           // INITIALIZE NeoPixel strip object (REQUIRED)
  con1.fill(con3.Color(255, 0, 0));
  con3.show();            
  con3.setBrightness(BRIGHTNESS);
  
  while (!Serial);
  Serial.begin(115200);

  Serial.print("Serial Ready\n");

  readSensorVal(NULL);

  // initializing the rtc
  while (!GPSRTC.begin());

  GPSRTC.disableAlarm(2);
  GPSRTC.disable32K();
  //GPSRTC.clearAlarm(1);
  GPSRTC.clearAlarm(2);
  GPSRTC.writeSqwPinMode(DS3231_OFF);
  digitalWrite(INTERNAL_LED_PIN, HIGH);

  Serial.print("RTC GPS Substitute Ready\n");
  
  drv_sched_init();

  drv_sched_repeating(readSensorVal, NULL, DRV_SCHED_PRI__NORMAL, 0, 60000);

  drv_mesh_init(messageReceived);
  drv_sched_start();
  
}

void loop() {}

void messageReceived(struct drv_mesh_packet_s * receivedData) {

  if (receivedData->len > 0) {
    switch (receivedData->buf[0]) {
      case RGBPAKCT:
        if (receivedData->len == 4) {
          setLEDStripColor(&ring, receivedData->buf[0], receivedData->buf[1], receivedData->buf[2]);
        }
        break;
      case PREDEFCOLORPACKET:
        if (receivedData->len == 2) {
          setLEDPreDefColor(&ring, (char) receivedData->buf[0]);
        }
        break;
      default:
        break;
    }
  }
  
}

/*void resetForNextAlarm(void *) {

  DateTime curr = GPSRTC.now();

  lib_datetime_s dt;
  dt.year = curr.year();
  dt.month = curr.month(); 
  dt.day = curr.day();
  dt.hour = curr.hour();
  dt.min = curr.minute(); 
  dt.sec = curr.second();
  dt.ms = 0;

  lib_datetime_interval_t temptimestamp = drv_timer_getMonotonicTime();

  temptimestamp = timestamp + (((temptimestamp - timestamp) / 1000) * 1000);
  
  //lib_datetime_addIntervalToDatetime(&dt, temptimestamp);
  drv_timer_setAbsoluteDateTimeWithTimestamp(&dt, temptimestamp);

  GPSRTC.clearAlarm(1);
  while(!GPSRTC.setAlarm1(curr + TimeSpan(15), DS3231_A1_Day));
    
}

void onAlarm(void) {
    //clear alarm and set it to 15 seconds in the future without resetting RTC time
    
    timestamp = drv_timer_getMonotonicTime();
    drv_sched_once(resetForNextAlarm, NULL, DRV_SCHED_PRI__NORMAL, 0);
    
}*/

void readSensorVal(void*) {

  sensordata = analogRead(SENSOR_PIN);
  struct drv_mesh_packet_s sensorPacket = {
  .ip = {10, 0, 0, 0},
  .len = 0x01,
  };
  *((uint16_t *)&(sensorPacket.buf[0])) = LIB_BYTEORDER_HTON_U16(sensordata);
  drv_mesh_send(&sensorPacket);
  
}

// Input a value 0 to 255 to get a color value.
// The colours are a transition r - g - b - back to r.
uint32_t Wheel(Adafruit_NeoPixel *strip, byte WheelPos) {
  WheelPos = 255 - WheelPos;
  if(WheelPos < 85) {
    return strip->Color(255 - WheelPos * 3, 0, WheelPos * 3);
  }
  if(WheelPos < 170) {
    WheelPos -= 85;
    return strip->Color(0, WheelPos * 3, 255 - WheelPos * 3);
  }
  WheelPos -= 170;
  return strip->Color(WheelPos * 3, 255 - WheelPos * 3, 0);
}

void multiPixelColors(Adafruit_NeoPixel *strip) {
  for(uint16_t j=0; j<256*5; j++) {
    for(uint16_t i=0; i<strip->numPixels(); i++) {
      strip->setPixelColor(i, Wheel(strip, (i+j) & 255));
    }
  }
}

void setLEDStripColor(Adafruit_NeoPixel *strip, uint8_t red, uint8_t green, uint8_t blue) {

  strip->fill(strip->Color(red, green, blue));
  strip->show();
  
}

void setLEDPreDefColor(Adafruit_NeoPixel *strip, char color) {

  switch (color) {
    case 'r':
    case 'R':
      strip->fill(strip->Color(255, 0, 0));
      break;
    case 'g':
    case 'G':
      strip->fill(strip->Color(0, 255, 0));
      break;
    case 'b':
    case 'B':
      strip->fill(strip->Color(0, 0, 255));
      break;
    case 'y':
    case 'Y':
      strip->fill(strip->Color(252, 232, 3));
      break;
    case 'p':
    case 'P':
      strip->fill(strip->Color(140, 3, 252)); //purple
      break;
    case 'o':
    case 'O':
      strip->fill(strip->Color(255, 149, 0)); //orange
      break;
    case 'm':
    case 'M':
      multiPixelColors(strip);
      break;
    default:
      strip->fill(strip->Color(0, 0, 0)); //off
      break;
  }
  ring.show();
}
