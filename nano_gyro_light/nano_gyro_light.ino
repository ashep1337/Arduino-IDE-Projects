#include <Wire.h>
#include <Adafruit_GFX.h>
#include <Adafruit_SSD1306.h>
#include "DHT.h"

// Include a custom font
#include <Fonts/FreeSans9pt7b.h>

// -------------------- Pin Definitions --------------------
#define DHTPIN 14       // DHT22 DATA pin
#define DHTTYPE DHT22

// -------------------- OLED Setup --------------------
#define SCREEN_WIDTH 128
#define SCREEN_HEIGHT 64
#define OLED_RESET -1
Adafruit_SSD1306 display(SCREEN_WIDTH, SCREEN_HEIGHT, &Wire, OLED_RESET);

DHT dht(DHTPIN, DHTTYPE);

void setup() {
  Serial.begin(115200);
  Wire.begin();          // RP2040 default I2C pins: SDA=4, SCL=5
  dht.begin();

  if(!display.begin(SSD1306_SWITCHCAPVCC, 0x3C)) {
    Serial.println(F("SSD1306 allocation failed"));
    while(1);
  }

  display.clearDisplay();
  display.setFont(&FreeSans9pt7b);  // Use custom font
  display.setTextColor(SSD1306_WHITE);
  display.setCursor(0, 12);
  display.println("DHT22 Init...");
  display.display();
  delay(2000);
}

void loop() {
  float humidity = dht.readHumidity();
  float temperatureF = dht.readTemperature(true); // Fahrenheit

  if (isnan(humidity) || isnan(temperatureF)) {
    Serial.println("Failed to read from DHT sensor!");
    display.clearDisplay();
    display.setCursor(0, 12);
    display.println("Sensor Error");
    display.display();
    delay(2000);
    return;
  }

  Serial.print("Temp: "); Serial.print(temperatureF);
  Serial.print(" °F\tHumidity: "); Serial.println(humidity);

  display.clearDisplay();

  // Display temperature
  display.setCursor(0, 12);
  display.print("Temp: ");
  display.print(temperatureF,1);
  display.println(" F");

  // Display humidity
  display.setCursor(0, 40);
  display.print("Hum: ");
  display.print(humidity,0);
  display.println(" %");

  display.display();
  delay(2000);
}
