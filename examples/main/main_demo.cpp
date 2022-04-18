//LoRa Mesh library includes
#include "LoRaMeshCapstone.h"
#include "lib/byteorder/lib_byteorder.h"
#include "deps/monocypher/monocypher.h"


//demo only inlcudes
#include <MKRWAN.h>
#include <Adafruit_NeoPixel.h>
#include <stdint.h>

LoRaModem modem; //for demo IP generation

static volatile lib_datetime_interval_t timestamp = 0;
uint16_t sensordata = 0;

#define GATEWAY_NODE_SIM_IP 1

#define SENSOR_PIN          A4
#define INTERNAL_LED_PIN    6

#define GATEWAY_SENSE_PIN   4
#define GATEWAY_PULL_PIN    5

//NeoPixel
#define BRIGHTNESS          25 // Set BRIGHTNESS(max = 255)
#define RING_LED_COUNT      12
#define RING_LED_DATAIN_PIN 1
#define CON_STRIP_COUNT     10
#define CON1_STRIP_DATA_PIN 7
#define CON2_STRIP_DATA_PIN 8
#define CON3_STRIP_DATA_PIN 9

//packet type defines
#define RGBPACKET           0x00
#define PREDEFCOLORPACKET   0x01
#define GATEWAYPACKET       0x03

uint8_t isGateway = 0;

Adafruit_NeoPixel ring(RING_LED_COUNT, RING_LED_DATAIN_PIN, NEO_GRB + NEO_KHZ800);

void blinkOn(void * arg __attribute__((unused))) {
	digitalWrite(LED_BUILTIN, HIGH);
}

void blinkOff(void * arg __attribute__((unused))) {
	digitalWrite(LED_BUILTIN, LOW);
}

void loop() {}

void serialReadGateway(void * arg) {

  uint8_t slen = 0;
  uint8_t sbuf[50];
  memset(sbuf, 0, sizeof(sbuf));
  while (Serial.available() && slen < 50) {
    sbuf[slen] = Serial.read();
    slen++;
  }
  
  uint8_t buf[64];
  memset(buf, 0, sizeof(buf));
  uint8_t len = 0;
  
  for (uint8_t i = 0; i < slen; i++) {
    
    if (sbuf[i] == ',') {
      i++;
      continue;
    }

    if (sbuf[i] == '\n') {
      break;
    }

    if (len <= 2 && i + 2 < slen) {
        uint8_t temp = 0;
        temp =((sbuf[i] -  '0') * 100);
        temp = temp + (sbuf[i+1] - '0') * 10;
        temp = temp + (sbuf[i+2] - '0');

        buf[len] = temp;
        len++;
        i=i+2;
    } else if (sbuf[i] < '0' || sbuf[i] > '9') {
      buf[len] = sbuf[i];
      len++;
      break;
    } else if (i + 2 < slen) {
      uint8_t temp = 0;
      
      temp = (sbuf[i] - '0') * 100;
      temp = temp + ((sbuf[i+1] -  '0') * 10);
      temp = temp + (sbuf[i+2] - '0');
      
      buf[len] = temp;
      len++;
      i = i+2;
    } else {
      break;
    }
    
  }
  
  len = len - 2;
  
  struct drv_mesh_packet_s ledPacket = {
      .ip = {10, buf[0], buf[1], buf[2]},
      .port = 0,
      .len = len,
  };
    
  if (len == 4) {
    ledPacket.buf[0] = RGBPACKET;
    ledPacket.buf[1] = buf[3];
    ledPacket.buf[2] = buf[4];
    ledPacket.buf[3] = buf[5];

    drv_mesh_send(&ledPacket);
  } else if (len == 2) {
    ledPacket.buf[0] = RGBPACKET;
    ledPacket.buf[1] = buf[3];

    drv_mesh_send(&ledPacket);
  } else {
    
  }
}

void setLEDStripColor(Adafruit_NeoPixel *strip, uint8_t red, uint8_t green, uint8_t blue) {

  strip->fill(strip->Color(red, green, blue));
  strip->show();
  
}

void readSensorVal(void * arg) {

  sensordata = analogRead(SENSOR_PIN);
  struct drv_mesh_packet_s sensorPacket = {
  .ip = {10, 0, 0, GATEWAY_NODE_SIM_IP},
  .port = 0,
  .len = 0x03,
  };
  sensorPacket.buf[0] = GATEWAYPACKET;
  *((uint16_t *)&(sensorPacket.buf[1])) = LIB_BYTEORDER_HTON_U16(sensordata);
  Serial.print("Sending sensor data: ");
  Serial.print(sensordata);
  Serial.print("\n");
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

void messageReceived(struct drv_mesh_packet_s * receivedData) {
  switch (receivedData->buf[0]) {
    case RGBPACKET:
      if (receivedData->len == 4) {
        setLEDStripColor(&ring, receivedData->buf[1], receivedData->buf[2], receivedData->buf[3]);
      }
      break;
    case PREDEFCOLORPACKET:
     if (receivedData->len == 2) {
        setLEDPreDefColor(&ring, (char) receivedData->buf[1]);
      }
      break;
    case GATEWAYPACKET:
      if (isGateway && receivedData->len == 3) {
        char tmp[128] = {0};
        uint16_t data = LIB_BYTEORDER_NTOH_U16(*(uint16_t *)&(receivedData->buf[1]));
        sprintf (tmp, "NODE: %u.%u.%u.%u", receivedData->ip[0], receivedData->ip[1], receivedData->ip[2], receivedData->ip[3]);
        Serial.print(String(tmp));
        Serial.print("  Received Sensor Data: ");
        Serial.println(data);
      }
      break;
    default:
      break;
  } 
  
}

uint8_t TESTING_DEMO_ISGATEWAY_FLAG_THING = 0;

void setup() {
  modem.begin(US915);
  uint8_t prikey[32];
  memset(prikey, 0, sizeof(prikey));
  String eui = modem.deviceEUI();
  memcpy(prikey, eui.c_str(), eui.length());

  pinMode(INTERNAL_LED_PIN, OUTPUT);
  pinMode(SENSOR_PIN, INPUT);

  pinMode(LED_BUILTIN, OUTPUT);

  pinMode(GATEWAY_SENSE_PIN, INPUT_PULLUP);
  pinMode(GATEWAY_PULL_PIN, OUTPUT);
  digitalWrite(GATEWAY_PULL_PIN, LOW);
  if (!digitalRead(GATEWAY_SENSE_PIN)) {
    isGateway = 1;
    TESTING_DEMO_ISGATEWAY_FLAG_THING = 1;
  }
  
  digitalWrite(INTERNAL_LED_PIN, LOW);

  ring.begin();           // INITIALIZE NeoPixel strip object (REQUIRED)
  ring.fill(ring.Color(255, 0, 0));
  ring.show();            
  ring.setBrightness(BRIGHTNESS);
  
  //while (!Serial);
  Serial.begin(115200);
  Serial.print("Ready\n");
  delay(1500);

  if (isGateway) {
    Serial.print("Serial Ready, Node IP is now the Gateway Node for Serial Coms\n");
    ring.fill(ring.Color(0, 0, 255));
  }
  else {
    ring.fill(ring.Color(0, 255, 0));
  }
  
  ring.show();

  drv_sched_init();
  drv_mesh_init(NULL, prikey, messageReceived);

  if (isGateway) { 
    drv_sched_repeating(serialReadGateway, NULL, DRV_SCHED_PRI__NORMAL, 0, 1000);
  }
  else {
    drv_sched_repeating(readSensorVal, NULL, DRV_SCHED_PRI__NORMAL, 0, 60000);
  }

  drv_sched_repeating(blinkOn, NULL, DRV_SCHED_PRI__NORMAL, 0, 2000);
	drv_sched_repeating(blinkOff, NULL, DRV_SCHED_PRI__NORMAL, 1000, 2000);
 
  drv_sched_start();
}