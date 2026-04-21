# Alexa-controlled Plant Watering System

An ESP32-based smart plant watering system controlled via Amazon Alexa voice commands. Built using Sinric Pro for cloud connectivity, with a relay module to safely drive a water pump. A resistive-moisture sensor is added to prevent overwatering and monitor moisture content in the soil.

## Tech Stack

### Hardware

1. Amazon Echo device (Alexa based device)
2. ESP32 Dev Kit
3. 5V Immersible water pump
4. Relay Switch(JQC-3FF-S-Z)
5. 0.96 Inch OLED Display module
6. USB cable to power ESP32
7. 4 x AA batteries as water-pump power source
8. Resistive Soil moisture sensor (HW-080- To check soil dryness/moisture before turning ON the water pump)
9. 10k Resistor

### Software

1. Sinric Pro account & API for Alexa App connectivity
2. Alexa Account
3. PlatformIO
4. Wifi connectivity

### Block Diagram

![til](https://github.com/vivupadi/Plant-Watering/blob/main/Plant_Water_Test/Block%20Diagram.jpg)

## Project Structure
Alexa_Water_Pump/

                    ├── platformio.ini        # PlatformIO config + build flags
                    ├── credentials.ini       
                    ├── .gitignore
                    ├── src/
                    │   └── main.cpp          # Main firmware
                    └── README.md

## Future Scope 

1. Isolated Server Setup
2. Dashboard for control 
