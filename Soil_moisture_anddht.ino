#include <Wire.h>
#include <Adafruit_GFX.h>
#include <Adafruit_SSD1306.h>
#include <DHT.h>

#define SCREEN_WIDTH 128
#define SCREEN_HEIGHT 64

#define OLED_ADDR 0x3C  // OLED I2C address
#define OLED_RESET -1

#define DHTPIN 2       // DHT11 data pin
#define DHTTYPE DHT11  // DHT11 sensor type
#define MOISTURE_PIN A0 // Soil moisture sensor analog pin
int moisturePercentage=0;

DHT dht(DHTPIN, DHTTYPE);                  // Initialize DHT11 sensor
Adafruit_SSD1306 display(SCREEN_WIDTH, SCREEN_HEIGHT, &Wire, OLED_RESET);  // Initialize OLED display

void setup() {
  Serial.begin(9600);
  dht.begin();
  
  // Initialize OLED display
  if (!display.begin(SSD1306_SWITCHCAPVCC, OLED_ADDR)) {
    Serial.println(F("SSD1306 allocation failed"));
    while (1);
  }

  // Clear the display
  display.clearDisplay();
  display.setTextColor(SSD1306_WHITE);
  display.setTextSize(1);
  display.setCursor(0, 0);
  display.println("Temp:        C");
  display.setCursor(0, 25);
  display.println("Humidity:    %");
  display.setCursor(0, 50);
  display.println("Moisture:    %");
  display.display();
}

void loop() {
  delay(2000);  // Delay for 2 seconds between readings

  // Read temperature and humidity from DHT11
  float temperature = dht.readTemperature();
  float humidity = dht.readHumidity();

  // Read soil moisture value
 int  moisture = analogRead(MOISTURE_PIN);

  // Print data on the serial monitor
  Serial.print("Temperature: ");
  Serial.print(temperature);
  Serial.print(" °C\t");
  Serial.print("Humidity: ");
  Serial.print(humidity);
  Serial.print(" %\t");
  Serial.print("Moisture: ");
  Serial.print(moisture);
  Serial.println();

  // Update the OLED display
  display.clearDisplay();
  display.setCursor(0, 0);
  display.print("Temp: ");
  display.print(temperature, 1);
  display.println(" C");
  display.setCursor(0, 25);
  display.print("Humidity: ");
  display.print(humidity, 1);
  display.println(" %");
  display.setCursor(0, 50);
  display.print("Moisture: ");
  
  // Adjust the following values based on your soil moisture sensor readings
  int dryValue = 1024;    // Dry soil moisture value
  int wetValue = 0;    // Wet soil moisture value

  // Map the moisture value to a range of 0-100%
 int  moisturePercentage = map(moisture, dryValue, wetValue, 0, 100);
  
  display.print(moisturePercentage);
  display.println(" %");
  display.display();
}
