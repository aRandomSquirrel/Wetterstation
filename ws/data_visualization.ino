#include <Wire.h>
#include <Adafruit_BME280.h>

// BME280 sensor object
Adafruit_BME280 bme;

// I2C pins (ESP32 default SDA=21, SCL=22)
#define SDA_PIN 21
#define SCL_PIN 22

// BME280 I2C address (0x77 is default, 0x76 if SDO pin is grounded)
#define BME280_ADDRESS 0x77

void setup() {
  // Initialize Serial communication at 115200 baud
  Serial.begin(115200);
  delay(1000);
  
  Serial.println("\n\n======================================");
  Serial.println("BME280 Sensor Data Display");
  Serial.println("======================================\n");
  
  // Initialize I2C communication
  Wire.begin(SDA_PIN, SCL_PIN);
  
  // Initialize BME280 sensor
  if (!bme.begin(BME280_ADDRESS)) {
    Serial.println("ERROR: Could not find BME280 sensor!");
    Serial.print("Make sure the sensor is connected to SDA (GPIO ");
    Serial.print(SDA_PIN);
    Serial.print(") and SCL (GPIO ");
    Serial.print(SCL_PIN);
    Serial.println(")");
    
    while (1) {
      delay(100);
    }
  }
  
  Serial.println("BME280 sensor initialized successfully!");
  Serial.println("Reading sensor data...\n");
}

void loop() {
  // Read temperature (in Celsius)
  float temperature = bme.readTemperature();
  
  // Read pressure (in Pa, convert to hPa)
  float pressure = bme.readPressure() / 100.0F;
  
  // Read humidity (in %)
  float humidity = bme.readHumidity();
  
  // Calculate altitude (sea level pressure = 1013.25 hPa)
  float altitude = bme.readAltitude(1013.25);
  
  // Print sensor data
  Serial.print("Temperature: ");
  Serial.print(temperature);
  Serial.println(" °C");
  
  Serial.print("Pressure: ");
  Serial.print(pressure);
  Serial.println(" hPa");
  
  Serial.print("Humidity: ");
  Serial.print(humidity);
  Serial.println(" %");
  
  Serial.print("Altitude: ");
  Serial.print(altitude);
  Serial.println(" m");
  
  Serial.println("--------------------------------------");
  
  // Read sensor data every 2 seconds
  delay(2000);
}
