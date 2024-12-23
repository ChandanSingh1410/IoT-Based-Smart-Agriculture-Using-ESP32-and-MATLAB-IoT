#include <WiFi.h>
#include <HTTPClient.h>
#include <DHT.h>

// Wi-Fi Configuration
const char* ssid = "Your_SSID"; // Replace with your Wi-Fi SSID
const char* password = "Your_PASSWORD"; // Replace with your Wi-Fi Password

// ThingSpeak Configuration
const char* server = "http://api.thingspeak.com/update";
const char* apiKey = "Your_ThingSpeak_Write_API_Key"; // Replace with your API Key

// DHT Sensor Configuration
#define DHTPIN 4
#define DHTTYPE DHT11
DHT dht(DHTPIN, DHTTYPE);

// Sensor Pins
const int soilMoisturePin = 34; // Analog pin for soil moisture
const int ldrPin = 35;          // Analog pin for LDR
const int relayPin = 27;        // Digital pin for relay

void setup() {
  Serial.begin(115200);
  dht.begin();

  pinMode(relayPin, OUTPUT);
  digitalWrite(relayPin, LOW); // Pump OFF initially

  // Connect to Wi-Fi
  WiFi.begin(ssid, password);
  while (WiFi.status() != WL_CONNECTED) {
    delay(1000);
    Serial.println("Connecting to Wi-Fi...");
  }
  Serial.println("Connected to Wi-Fi");
}

void loop() {
  // Read Sensors
  float temperature = dht.readTemperature();
  float humidity = dht.readHumidity();
  int soilMoisture = analogRead(soilMoisturePin);
  int lightIntensity = analogRead(ldrPin);

  // Convert readings
  soilMoisture = map(soilMoisture, 4095, 0, 0, 100); // 0% (dry) to 100% (wet)
  lightIntensity = map(lightIntensity, 0, 4095, 0, 100); // 0% (dark) to 100% (bright)

  // Display Data
  Serial.print("Temperature: ");
  Serial.print(temperature);
  Serial.print(" °C, Humidity: ");
  Serial.print(humidity);
  Serial.print(" %, Soil Moisture: ");
  Serial.print(soilMoisture);
  Serial.print(" %, Light Intensity: ");
  Serial.print(lightIntensity);
  Serial.println(" %");

  // Control Irrigation System
  if (soilMoisture < 30) { // Adjust threshold as needed
    digitalWrite(relayPin, HIGH); // Turn ON pump
  } else {
    digitalWrite(relayPin, LOW); // Turn OFF pump
  }

  // Send Data to ThingSpeak
  if (WiFi.status() == WL_CONNECTED) {
    HTTPClient http;
    String url = String(server) + "?api_key=" + apiKey + "&field1=" + String(temperature) + "&field2=" + String(humidity) + "&field3=" + String(soilMoisture) + "&field4=" + String(lightIntensity);
    http.begin(url);
    int httpCode = http.GET();
    http.end();

    if (httpCode > 0) {
      Serial.println("Data Sent to ThingSpeak");
    } else {
      Serial.println("Failed to Send Data");
    }
  }

  delay(15000); // ThingSpeak accepts data every 15 seconds
}
