# Alexa-controlled Plant Watering System

An ESP32-based smart plant watering system controlled via Amazon Alexa voice commands. Built using Sinric Pro for cloud connectivity, with a relay module to safely drive a water pump.

## Tech Stack

### Hardware

1. Amazon Echo device (Alexa based device)
2. ESP32 Dev Kit
3. 5V Immersible water pump
4. Relay Switch(JQC-3FF-S-Z)
5. USB cable to power ESP32
6. 4 x AA batteries as water-pump power source
7. Resistive Soil moisture sensor (for future addition - To check soil dryness before turning ON the water pump

### Software

1. Sinric Pro account & API for Alexa App connectivity
2. Alexa Account
3. PlatformIO
4. Wifi connectivity


## Project Structure
Alexa_Water_Pump/

                    ├── platformio.ini        # PlatformIO config + build flags
                    ├── credentials.ini       
                    ├── .gitignore
                    ├── src/
                    │   └── main.cpp          # Main firmware
                    └── README.md
