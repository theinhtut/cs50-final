# Temperature and Humidity Monitoring
#### Video Demo:  <URL HERE>
#### Description:
Monitoring temperature and humidity value over the Internet using ESP32 Dev Kits and Blynk iOS app.

#### Schematic Diagram:

#### Hardwares & Software:
- ESP32 Dev Kits
- DHT11 Sensors
- Breadboard
- Male to male jumper wires
- MicroUSB cable
- VSCode
- Arduino IDE
- Blynk iOS App


#### Environment Variables
Environment variables are stored in file `env.h`. To run the project, create `env.h` file and add your secrets.
```
#define WIFI_SSID "your_wifi_ssid"
#define WIFI_PASSWORD "your_wifi_password"
#define BLYNK_AUTH_TOKEN "your_blynk_auth_token"
```