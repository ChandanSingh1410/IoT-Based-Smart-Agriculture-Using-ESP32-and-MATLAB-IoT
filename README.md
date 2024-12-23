# IoT-Based-Smart-Agriculture-Using-ESP32-and-MATLAB-IoT
This project uses an ESP32 microcontroller to monitor farmland conditions using various sensors (temperature, light, humidity, soil moisture). Data is sent to a MATLAB IoT Analytics platform for real-time monitoring and automating the irrigation system.

Materials Required
ESP32 Development Board
DHT11/DHT22 Sensor (Temperature and Humidity)
Soil Moisture Sensor
LDR (Light-Dependent Resistor)
Relay Module (for controlling irrigation pump)
Pump Motor or an equivalent load
Resistors (10kΩ for LDR circuit)
Breadboard and jumper wires
Circuit Diagram Description
DHT11/DHT22 Sensor:

Connect the VCC to 3.3V, GND to GND, and Data to GPIO 4 of the ESP32.
Soil Moisture Sensor:

Connect VCC to 3.3V, GND to GND, and the output (AO) to GPIO 34 (Analog Input).
LDR:

Create a voltage divider using the LDR and a 10kΩ resistor.
Connect one end of the LDR to 3.3V and the other to the junction of the resistor and GPIO 35 (Analog Input).
Relay Module:

Connect the IN pin to GPIO 27, VCC to 5V, and GND to GND.
Connect the pump motor to the relay's NO (Normally Open) and COM terminals.
Circuit Diagram
If you'd like, I can generate a visual schematic for better clarity.

MATLAB IoT Setup
Create a MATLAB ThingSpeak account.
Create a new channel to log data (temperature, humidity, soil moisture, light intensity).
Copy the Write API Key and Channel ID for use in the ESP32 code.

MATLAB Analytics
Use MATLAB to analyze data from the ThingSpeak channel.
You can write MATLAB scripts for:
Plotting trends in temperature, humidity, and soil moisture.
Predictive analysis for irrigation needs.
