# IoT Temperature and Humidity Monitoring System
#### Video Demo: https://youtu.be/5u8QMonj6NQ
#### Description:
Monitoring temperature and humidity value over the Internet using ESP32 Dev Kits and Blynk iOS app.

#### Schematic Diagram:
![ESP32-DHT11](https://user-images.githubusercontent.com/3690421/117928550-4d333080-b32e-11eb-8b39-af48033087b3.png)

#### Hardwares:
- ESP32 Dev Kits
- DHT11 Sensors
- Breadboard
- Male to male jumper wires
- MicroUSB cable

#### Main Code (temp-iot.ino)
```cpp
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

```
#### Environment Variables
Environment variables are stored in file `env.h`. To run the project, create `env.h` file and add your secrets.
```cpp
#define WIFI_SSID "your_wifi_ssid"
#define WIFI_PASSWORD "your_wifi_password"
#define BLYNK_AUTH_TOKEN "your_blynk_auth_token"
```
#### Library Dependencies
- DHT11
- WiFi
- Blynk
#### Folder Structure
A top-level view of files and directories.

    .
    ├── temp-iot/
    └── README.md
#### Tech-stacks
- C++
- VSCode
- Arduino IDE
- Blynk iOS App 


#### Extensions Recommendations For VSCode
- [VSCode extension for Arduino][vscode-arduino-ext]

[vscode-arduino-ext]: https://marketplace.visualstudio.com/items?itemName=vsciot-vscode.vscode-arduino

#### Possible improvements
There are always improvements to be made as application grow. Some of the improvements for the future:
- Custom PCB board with compact design instead of using breadboard.
- Weatherproof casing for the device since it can also measure outdoor temperature.
- Find ways for low energy consumption for long-term application.


