
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
#include <Wire.h>
#include <Adafruit_GFX.h>
#include <Adafruit_SSD1306.h>


#define RELAY_PIN    26
#define MOISTURE_PIN 34
#define BAUD_RATE    115200

#define SCREEN_WIDTH 128
#define SCREEN_HEIGHT 64
#define OLED_RESET -1

Adafruit_SSD1306 display(SCREEN_WIDTH, SCREEN_HEIGHT, &Wire, OLED_RESET);

// Credentials from build_flags
const char* WIFI_SSID_VAL   = WIFI_SSID;
const char* WIFI_PASS_VAL   = WIFI_PASS;
const char* APP_KEY_VAL     = APP_KEY;
const char* APP_SECRET_VAL  = APP_SECRET;
const char* DEVICE_ID_VAL   = DEVICE_ID;

// Helper function to display status messages
void displayStatus(const char* line1, const char* line2 = "", const char* line3 = "") {
  display.clearDisplay();
  display.setTextSize(1);
  display.setTextColor(WHITE);
  
  display.setCursor(0, 0);
  display.println(line1);
  
  if (strlen(line2) > 0) {
    display.setCursor(0, 16);
    display.println(line2);
  }
  
  if (strlen(line3) > 0) {
    display.setCursor(0, 32);
    display.println(line3);
  }
  
  display.display();
}

// Relay state handler
bool onPowerState(const String &deviceId, bool &state) {
  Serial.println(">>> Watering request received...");
  displayStatus("Watering request", "Checking moisture...");

   // Check moisture level first
  int moisture = analogRead(MOISTURE_PIN);
  int percent = map(moisture, 0, 2800, 0, 100);

  Serial.printf("Current moisture: %d%%\n", percent);

  char moistureStr[20];
  sprintf(moistureStr, "Moisture: %d%%", percent);

  if (percent < 50) {
    Serial.println(">>> Moisture below 50% — watering now");
    displayStatus("Moisture low!", moistureStr, "Watering now...");

    // Turn pump ON
    digitalWrite(RELAY_PIN, HIGH);
    delay(3000);  // run for 3 seconds
    // Turn pump OFF
    digitalWrite(RELAY_PIN, LOW);

    Serial.println(">>> Watering complete — relay OFF");
    displayStatus("Watering", "complete!", "");
    delay(2000);  // Show completion message for 2 seconds
  } else {
    Serial.println(">>> Moisture sufficient — skipping watering");
    displayStatus("Moisture OK!", moistureStr, "Skipping watering");
    delay(2000);  // Show message for 2 seconds
  }

  // Tell Sinric the switch is back OFF
  state = false;

  Serial.println(">>> Watering complete — relay OFF");
  return true;
}

void setupWiFi() {
  displayStatus("Connecting to WiFi...");
  Serial.printf("Connecting to %s", WIFI_SSID_VAL);
  WiFi.begin(WIFI_SSID_VAL, WIFI_PASS_VAL);
  while (WiFi.status() != WL_CONNECTED) {
    Serial.print(".");
    delay(500);
  }
  Serial.println("\nWiFi connected!");
  Serial.println(WiFi.localIP());
  displayStatus("WiFi connected!", WiFi.localIP().toString().c_str());
  delay(2000);
}

void setupSinricPro() {
  displayStatus("Connecting to", "Sinric Pro...");
  SinricProSwitch &mySwitch = SinricPro[DEVICE_ID_VAL];
  mySwitch.onPowerState(onPowerState);
  SinricPro.begin(APP_KEY_VAL, APP_SECRET_VAL);
  Serial.println("Sinric Pro connected!");
  displayStatus("Sinric Pro", "connected!");
  delay(2000);
}

void setup() {
  // Set relay OFF FIRST — before anything else
  pinMode(RELAY_PIN, OUTPUT);
  digitalWrite(RELAY_PIN, LOW); // relay OFF at startup

  Serial.begin(BAUD_RATE);

  //Display setup
  Wire.begin(32, 33);  // SDA=32, SCL=33
  display.begin(SSD1306_SWITCHCAPVCC, 0x3C);
  display.clearDisplay();

  setupWiFi();
  setupSinricPro();

}

void loop() {
  SinricPro.handle();
  int moisture = analogRead(MOISTURE_PIN);
  int percent = map(moisture, 0, 2800, 0, 100);  // 0=dry, 2800=wet

  display.clearDisplay();
  display.setTextSize(1);
  display.setTextColor(WHITE);
  display.setCursor(0, 0);
  display.println("Moisture in soil:");
  display.setTextSize(2);
  display.setCursor(0, 16);
  display.print(percent);
  display.println("%");
  display.display();
  Serial.printf("Moisture Sensor: %d\n", moisture);
}