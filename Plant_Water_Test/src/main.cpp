
/*Initial test without alexa

#include <Arduino.h>

#define RELAY_PIN 26

void setup() {
  pinMode(RELAY_PIN, OUTPUT);
  digitalWrite(RELAY_PIN, HIGH); // HIGH = relay OFF (active LOW)
  Serial.begin(115200);
  Serial.println("Relay test starting...");
}

void loop() {
  Serial.println("Relay ON — pump running");
  digitalWrite(RELAY_PIN, LOW);  // LOW = relay ON
  delay(2000);

  Serial.println("Relay OFF — pump stopped");
  digitalWrite(RELAY_PIN, HIGH); // HIGH = relay OFF
  delay(2000);
}
*/

#include <Arduino.h>
#include <WiFi.h>
#include <SinricPro.h>
#include <SinricProSwitch.h>

#define RELAY_PIN    26
#define BAUD_RATE    115200

// Credentials from build_flags
const char* WIFI_SSID_VAL   = WIFI_SSID;
const char* WIFI_PASS_VAL   = WIFI_PASS;
const char* APP_KEY_VAL     = APP_KEY;
const char* APP_SECRET_VAL  = APP_SECRET;
const char* DEVICE_ID_VAL   = DEVICE_ID;

// Relay state handler
bool onPowerState(const String &deviceId, bool &state) {
  Serial.println(">>> Watering triggered — running for 1 second");

  // Turn pump ON
  digitalWrite(RELAY_PIN, HIGH);
  delay(2000);  // run for 2 seconds
  // Turn pump OFF
  digitalWrite(RELAY_PIN, LOW);

  // Tell Sinric the switch is back OFF
  state = false;

  Serial.println(">>> Watering complete — relay OFF");
  return true;
}

void setupWiFi() {
  Serial.printf("Connecting to %s", WIFI_SSID_VAL);
  WiFi.begin(WIFI_SSID_VAL, WIFI_PASS_VAL);
  while (WiFi.status() != WL_CONNECTED) {
    Serial.print(".");
    delay(500);
  }
  Serial.println("\nWiFi connected!");
  Serial.println(WiFi.localIP());
}

void setupSinricPro() {
  SinricProSwitch &mySwitch = SinricPro[DEVICE_ID_VAL];
  mySwitch.onPowerState(onPowerState);
  SinricPro.begin(APP_KEY_VAL, APP_SECRET_VAL);
  Serial.println("Sinric Pro connected!");
}

void setup() {
  // Set relay OFF FIRST — before anything else
  pinMode(RELAY_PIN, OUTPUT);
  digitalWrite(RELAY_PIN, LOW); // relay OFF at startup

  Serial.begin(BAUD_RATE);
  setupWiFi();
  setupSinricPro();
}

void loop() {
  SinricPro.handle();
}