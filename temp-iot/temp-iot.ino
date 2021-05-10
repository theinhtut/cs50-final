#include <WiFi.h>
#include <DHT.h>
#include <BlynkSimpleEsp32.h>
#include "env.h"

// LED Pins
#define LED_PIN 2

// DHT sensor type and data pin
#define DHT_PIN 4
#define DHT_TYPE DHT11

DHT dht(DHT_PIN, DHT_TYPE);
BlynkTimer timer;

// Prototypes
void initDHT();
void initWifi();
void initBlynk();
void readSensors();

void setup() {
  // Setup serial monitor
  Serial.begin(115200);

  // Initialize DHT sensor.
  initDHT();

  // Initialize Wi-Fi connection
  initWifi();

  // Initialize Blynk
  initBlynk();
  
  // Send sensors value every x
  timer.setInterval(10000, readSensors);
}

void loop() {
  Blynk.run();
  timer.run();
}

void initDHT() {
  pinMode(DHT_PIN, INPUT);
  dht.begin();
}


void initWifi() {
  WiFi.mode(WIFI_STA);
  WiFi.begin(WIFI_SSID, WIFI_PASSWORD);
  Serial.println("Connecting to WiFi ..");
  while (WiFi.status() != WL_CONNECTED) {
    Serial.print('.');
    delay(1000);
  }
  Serial.println("\nConnected on IP Address:");
  Serial.println(WiFi.localIP());
  pinMode(LED_PIN, OUTPUT);
  digitalWrite(LED_PIN, HIGH);
}

void initBlynk() {
  Blynk.begin(BLYNK_AUTH_TOKEN, WIFI_SSID, WIFI_PASSWORD);
}

void readSensors() {
  // Read temperature(C) and humidity(%) values
  float h = dht.readHumidity();
  float t = dht.readTemperature();

  // Check if any readings failed
  if (isnan(h) || isnan(t)) {
    Serial.println("Failed to read from DHT sensor!");
    delay(5000);
    return;
  }

  Serial.print(F("Humidity: "));
  Serial.print(h);
  Serial.print(F("%  Temperature: "));
  Serial.print(t);
  Serial.println();
  Serial.println("Sending to Blynk");
  Blynk.virtualWrite(V0, t);
  Blynk.virtualWrite(V1, h);
}
