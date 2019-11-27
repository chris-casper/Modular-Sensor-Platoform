# Particle.io Photon Modular Sensor Platform

Platform:       Particle.io Photon 
Sensors:        SEEED Grove
Cloud Dashboard: Unidot

## Overview

The notion is to make a small cheap, modular cloud based sensor platform. Most cloud sensors are surprisingly expensive, often insecure and not flexible. Ideally this would require no soldering and be able to be setup by even a junior tech.

The software is a [https://github.com/chris-casper/Particle-Modular-Sensor-Platform-v3/blob/master/Particle_Modular_Sensor_platform.ino](single file). It is loaded into the Particle.io console or compiled into a binary that can be directly loaded. The [https://console.particle.io/](cloud console) or Particle app is very trivial to use. It should automatically include the dependencies (Adafruit_DHT_Particle.h and Ubidots.h). 

It's written for [https://ubidots.com/](Ubidots) for the dashboard, alerting and reporting. There are plenty of other options, but they have the best combination between features, pricing and ease of use. Sign up, generate an [https://help.ubidots.com/en/articles/590078-find-your-token-from-your-ubidots-account](account token) and plug it into the script in the specified location, creatively specified as "Put here your Ubidots TOKEN".

## Supported sensors:

 * [https://www.seeedstudio.com/Grove-Temperature-Humidity-Sensor-DHT11.html](DHT11) - Cheap temperature sensor, good enough quality
 * [https://www.seeedstudio.com/Grove-Temperature-Humidity-Sensor-Pro-AM2302-DHT22.html](DHT22) - Expensive temperature sensor - quite good quality
 * [https://www.seeedstudio.com/Grove-Sound-Sensor.html](Microphone) - Cheap sound sensor, good enough quality. This has come in much handy than one would intially think. Sharp increase or decrease of noise out of baseline usually means a problem. Issues with HVAC or CPUs pegging.
 * [https://www.seeedstudio.com/Grove-Light-Sensor-v1-2.html](Photocell) - Cheap temp sensor, good enough quality. Handy for letting you know when and for how long an area was accessed
 * [https://www.seeedstudio.com/Grove-Gas-Sensor-MQ2.html](Smoke) - The MQ2 is the gas sensor for smoke. They have other gas sensors for carbon monoxide, alcohol fumes, natural gas and the like. 
 * [https://www.seeedstudio.com/Grove-PIR-Motion-Sensor.html](Motion) - Motion sensor. Mostly handy for enclosures. Not so much for open areas
 
 You'll also need a [https://www.seeedstudio.com/Particle-Photon-Base-Shield.html](Photon Shield) to connect the Photon to the sensors.
 
## Sensor Configuration

Look in the program for "ENABLE OR DISABLE SENSORS HERE", flip the bits on the relevant sensors appropriately.
 
## Assembly

1. Put Particle Photon into [https://www.seeedstudio.com/Particle-Photon-Base-Shield.html](Photon Base Shield)
2. Connect sensors to the shield. The necessary locations are documented in the program.
3. Download the software to the Photon using either the cloud dashboard or the mobile app
4. (Optional) Put in an enclosure

And that's it. 
