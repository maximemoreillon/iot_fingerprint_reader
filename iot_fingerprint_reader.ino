
/*
 * Board type: ESP32 Dev module
 */
// Libraries
#include "IotKernel.h"
#include "SSD1306.h"
#include <Adafruit_Fingerprint.h>


// Import fonts and images for the display
#include "font.h"
#include "images.h"

//Device info
#define DEVICE_TYPE "fingerprint"
#define DEVICE_FIRMWARE_VERSION "0.0.2"

// IO

#define RX_PIN 13
#define TX_PIN 16
// GPIO 5 is for the display
#define SDA_PIN 5 
#define SCL_PIN 4
#define BUZZER_PIN 25

#define DISPLAY_WIDTH 128
#define DISPLAY_HEIGHT 64
#define DISPLAY_INVERSION_PERIOD 60000
#define DISPLAY_LOCK_STATE_TIME 5000
#define DISPLAY_DURATION 3000

#define COOLDOWN_DURATION 2000

#define BUZZER_CHANNEL 0
#define BUZZER_RESOLUTION 8



// Declaring objects
IotKernel iot_kernel(DEVICE_TYPE,DEVICE_FIRMWARE_VERSION); 
SSD1306 display(0x3c, SDA_PIN, SCL_PIN);
Adafruit_Fingerprint finger = Adafruit_Fingerprint(&Serial1);

// Global variables
long cooldown_start_time = -COOLDOWN_DURATION;
long display_start_time = DISPLAY_DURATION;
String lock_state = "unknown";

void setup() {
	Serial.begin(115200);
  Serial1.begin(57600, SERIAL_8N1, RX_PIN, TX_PIN);

  display_setup();
  buzzer_init();
  fingerprint_init();
  iot_kernel.init();
  mqtt_config();

  
  
}

void loop() {
  iot_kernel.loop();
  invert_display_periodically();
  display_reset();

  //  TODO: check if wifi and mqtt are connected before

  if(millis() - cooldown_start_time > COOLDOWN_DURATION){
    getFingerprintID();
  }


}
