/*************************************************************
	This is an examples for the SW01
	Ambient, UVA and UVB light sensor
	
	You can buy one on our store!
	-----> https://xinabox.cc/SL01/
	
	This example request a LUX meausrement to be 
	made by the SL01 and display the data over the Serial
	bus.
	
	The sensor communicates over the I2C Bus.
	
*************************************************************/
#include <xCore.h>
#include <xSL01.h>

#if defined(ESP8266)
#define RED   RED
#define GREEN GREEN
#define BLUE  BLUE
#include <ESP8266WiFi.h>
#define Serial Serial

#elif defined(ARDUINO_SAMD_ZERO)
#define RED   CC03_RED
#define GREEN CC03_GREEN
#define BLUE  CC03_BLUE
#define Serial SerialUSB

#elif defined(ARDUINO_AVR_PRO)
#define RED   CC01_RED
#define GREEN CC01_GREEN
#define BLUE  CC01_BLUE
#define Serial Serial

#elif defined(ESP32)
#define RED   CW02_RED
#define GREEN CW02_GREEN
#define BLUE  CW02_BLUE
#define Serial Serial
#endif

const int DELAY_TIME = 1000;

xSL01 SL01;

void setup() {
	// Start the Serial Monitor
	Serial.begin(115200);
	
	// Set the I2C Pins for CW01
	#ifdef ESP8266
	  Wire.pins();
	  Wire.setClockStretchLimit(15000);
	#endif
	
	// Start the I2C Comunication
	Wire.begin();
	
	// Start the  SL01 Sensor
	SL01.begin();

	// Delayy for Sensor to normalise
	delay(DELAY_TIME);
	
	Serial.println("================================");
	Serial.println(" XINABOX SL01 LUX Measurements  ");
	Serial.println("================================"); 
}

void loop() {
	  // Create a variable to store the incoming measurements
	  // from SL01 sensor
	  float lux;
	  lux = 0;

	  // Poll Sensor for collect data
	  SL01.poll();

	  // Request SL01 to return calculated UVB intensity
	  lux = SL01.getLUX();

	  // Display Data on the Serial monitor
	  Serial.print("Ambient Light Level: ");
	  Serial.print(lux);
	  Serial.println(" LUX");
	  Serial.println();

	  delay(DELAY_TIME);
}
