//
//  Modular Sensor Platform
//  Written by Chris Casper
// 
//  License:        CC BY-SA 4.0
//  Created On:     20180606
//  Modified:  20180704 - Made code more modular as well
//
//  Platform:       Particle.io Photon
//  Sensors:        SEEED Grove
//  Cloud Dashboard: Unidot
//   
//  Notion was to make an easy to assemble and deploy sensor platform that anyone could assemble
//  with very little difficulty. As well as swap out sensors or dead components. 
//
//


// This #include statement was automatically added by the Particle IDE.
#include <Adafruit_DHT_Particle.h>
#include <Ubidots.h>


//
// Pin definitions for sensors
#define DHTPIN D2               // temp sensor - digit D2
#define MotionSensor 6          // motion sensor - digital D6
const int LightSensor = A4;     // light sensor - analog A4
const int SoundSensor = A0;     // sound sensor - analog A40

// 
// Temp sensor setup
//#define DHTTYPE DHT11		// DHT 11, blue 
#define DHTTYPE DHT22		// DHT 22 (AM2302), white
//#define DHTTYPE DHT21		// DHT 21 (AM2301)

//
// Onboard sensors
// ************  ENABLE OR DISABLE SENSORS HERE  ************
#define ENABLE_SENSOR_DHT22 1   // Temp sensor
DHT dht(DHTPIN, DHTTYPE);       // Disable if DHT not used
#define ENABLE_SENSOR_Light 1
#define ENABLE_SENSOR_Motion 1
#define ENABLE_SENSOR_Smoke 0
#define ENABLE_SENSOR_Sound 1
// **********************************************************
//

//
// Variables

    float loudness;
    float h;
    float f;
    float dp;
    float hi;
    float t;
    int m;
    int lux;
    String eventDataLV;
    String eventDataH;
    String eventDataF;
    
//    
// Ubidots setup

#ifndef TOKEN
#define TOKEN "INSERT TOKEN HERE"  // Put here your Ubidots TOKEN
#endif
Ubidots ubidots(TOKEN);



//
//  Startup

void setup() {

    
    
    // Initialization
	Serial.begin(9600); 
    if (ENABLE_SENSOR_DHT22 == 1) { dht.begin(); }
	delay(2000);
	
	// Cloud variables to Particle.io cloud dashboard
    if (ENABLE_SENSOR_Sound == 1)  { Particle.variable("loudV", eventDataLV); }
    if (ENABLE_SENSOR_DHT22 == 1)  { Particle.variable("humdity", eventDataH); }
    if (ENABLE_SENSOR_DHT22 == 1)  { Particle.variable("tempF", eventDataF); }
    if (ENABLE_SENSOR_Motion == 1) { Particle.variable("motion", m); }
    if (ENABLE_SENSOR_Light == 1)  { Particle.variable("light", lux); }

    if (ENABLE_SENSOR_Sound == 1)  { pinMode(A0, INPUT); }
    if (ENABLE_SENSOR_Motion == 1) { pinMode(MotionSensor, INPUT); }

}


//
// Main loop 

void loop() {

    // Get Temperature and Humidity from sensor
    if (ENABLE_SENSOR_DHT22 == 1) { 
	h = dht.getHumidity();
    t = dht.getTempCelcius();
    f = dht.getTempFarenheit();
    eventDataH = String(h); // convert float to string
    eventDataF = String(f);
    }

    // Get sound level
    if (ENABLE_SENSOR_Sound == 1) { 
	loudness = analogRead(SoundSensor);
	eventDataLV = String(loudness); // convert float to string
    }
	
	// Get light level
	if (ENABLE_SENSOR_Light == 1) { lux = analogRead(LightSensor); }
	
	// Get motion level
	if (ENABLE_SENSOR_Motion == 1) { 
    if(digitalRead(MotionSensor))
        m = 1; // Motion
    else
        m = 0; // No motion
	}    
        
        
    // Ubidots cloud dashboard    
    if (ENABLE_SENSOR_DHT22 == 1) { ubidots.add("humidity", h); }
    if (ENABLE_SENSOR_DHT22 == 1) { ubidots.add("temperature", f); }
    if (ENABLE_SENSOR_Sound == 1) { ubidots.add("sound-level", loudness); }
    if (ENABLE_SENSOR_Motion == 1) { ubidots.add("motion", m); }
    if (ENABLE_SENSOR_Light == 1) { ubidots.add("light", lux); }
    ubidots.setMethod(TYPE_TCP);    //Set to TCP the way to send data
    ubidots.sendAll();              //Upload to ubidots
    
	delay(10000);

} // end loop