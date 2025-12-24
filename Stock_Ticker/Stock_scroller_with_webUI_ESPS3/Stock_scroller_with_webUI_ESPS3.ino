#include <WiFi.h>
#include <HTTPClient.h>
#include <ArduinoJson.h>
#include <Wire.h>
#include <Adafruit_GFX.h>
#include <Adafruit_SSD1306.h>

// Wi-Fi credentials
const char* ssid = "SSID"; //Put your wifi network name here
const char* password = "PASSWORD";  // Put your wifi password here

// Finnhub API key
const char* finnhubApiKey = "finnhubAPI";  //Put your finnhub API key here 

// List of stocks to display
const char* stockSymbols[] = {"UEC", "AG", "PLTR", "SPY", "QQQ", "TSLA", "AMD", "INTC"};  //Add stocks here with quotes
const int numStocks = sizeof(stockSymbols) / sizeof(stockSymbols[0]);

// OLED display settings
#define SCREEN_WIDTH 128
#define SCREEN_HEIGHT 64
#define OLED_RESET    -1
Adafruit_SSD1306 display(SCREEN_WIDTH, SCREEN_HEIGHT, &Wire, OLED_RESET);

// Finnhub API endpoint
String finnhubUrl = "https://finnhub.io/api/v1/quote?symbol=";

// Timing variables
unsigned long previousMillis = 0;
const long interval = 7000; // 7 seconds
int currentStockIndex = 0;

void setup() {
  Serial.begin(115200);

  // Initialize I2C
  Wire.begin(16, 17); // SDA=16, SCL=17    -- Edit these lines to reflect the pins you are using
  Wire.setClock(400000);

  // Initialize OLED
  if (!display.begin(SSD1306_SWITCHCAPVCC, 0x3C)) {
    Serial.println("SSD1306 allocation failed");
    while (true);
  }
  display.clearDisplay();
  display.setTextSize(1);
  display.setTextColor(SSD1306_WHITE);
  display.setCursor(0, 0);
  display.println("Connecting to WiFi...");
  display.display();

  // Connect to Wi-Fi
  WiFi.begin(ssid, password);
  while (WiFi.status() != WL_CONNECTED) {
    delay(500);
    Serial.print(".");
  }
  Serial.println("\nWiFi connected!");
  display.clearDisplay();
  display.setCursor(0, 0);
  display.println("WiFi connected!");
  display.display();

  delay(1000);

  // Display first stock immediately
  fetchAndDisplayStock(currentStockIndex);
}

void loop() {
  unsigned long currentMillis = millis();

  // Update stock every 7 seconds
  if (currentMillis - previousMillis >= interval) {
    previousMillis = currentMillis;
    currentStockIndex++;
    if (currentStockIndex >= numStocks) currentStockIndex = 0;

    fetchAndDisplayStock(currentStockIndex);
  }
}

void fetchAndDisplayStock(int index) {
  if (WiFi.status() != WL_CONNECTED) {
    Serial.println("WiFi disconnected");
    return;
  }

  String stockSymbol = stockSymbols[index];
  String url = finnhubUrl + stockSymbol + "&token=" + finnhubApiKey;

  HTTPClient http;
  http.begin(url);
  int httpCode = http.GET();

  if (httpCode > 0) {
    String payload = http.getString();
    Serial.println(payload);

    StaticJsonDocument<512> doc;
    DeserializationError error = deserializeJson(doc, payload);
    if (!error) {
      float currentPrice = doc["c"];
      float highPrice = doc["h"];
      float lowPrice = doc["l"];
      float openPrice = doc["o"];
      float prevClose = doc["pc"];
      
      // Calculate percent change
      float percentChange = ((currentPrice - prevClose) / prevClose) * 100.0;

      display.clearDisplay();
      display.setTextSize(1);
      display.setTextColor(SSD1306_WHITE);

      display.setCursor(0, 0);
      display.print("Stock: ");
      display.println(stockSymbol);

      display.setCursor(0, 10);
      display.print("Current: $");
      display.println(currentPrice, 2);

      display.setCursor(0, 50);
      display.print("High: $");
      display.println(highPrice, 2);

      display.setCursor(0, 30);
      display.print("Low: $");
      display.println(lowPrice, 2);

      display.setCursor(0, 40);
      display.print("Open: $");
      display.println(openPrice, 2);

      display.setCursor(0, 20);
      display.print("Change: ");
      if (percentChange >= 0) display.print("+");
      display.print(percentChange, 2);
      display.println("%");

      display.display();
    } else {
      Serial.println("JSON parse failed");
      display.clearDisplay();
      display.setCursor(0, 0);
      display.println("JSON parse failed");
      display.display();
    }
  } else {
    Serial.printf("HTTP GET failed for %s, error: %s\n", stockSymbol.c_str(), http.errorToString(httpCode).c_str());
    display.clearDisplay();
    display.setCursor(0, 0);
    display.printf("HTTP GET failed\n%s", stockSymbol.c_str());
    display.display();
  }
  http.end();
}

