#include <SparkFun_Weather_Meter_Kit_Arduino_Library.h>

// Pins definieren
int windDirectionPin = 34;
int windSpeedPin = 13;
int rainfallPin = 14;
SFEWeatherMeterKit weatherMeterKit(windDirectionPin, windSpeedPin, rainfallPin);

// Interrupt-Service-Routinen (ISR)
void setup()
{
    // Begin serial
    Serial.begin(115200);


    // Expected ADC values have been defined for various platforms in the
    // library, however your platform may not be included. This code will check
    // if that's the case
#ifdef SFE_WMK_PLAFTORM_UNKNOWN
    // The platform you're using hasn't been added to the library, so the
    // expected ADC values have been calculated assuming a 10k pullup resistor
    // and a perfectly linear 16-bit ADC. Your ADC likely has a different
    // resolution, so you'll need to specify it here:
    weatherMeterKit.setADCResolutionBits(10);
    
    Serial.println(F("Unknown platform! Please edit the code with your ADC resolution!"));
    Serial.println();
#endif

    // Begin weather meter kit
    weatherMeterKit.begin();
}

void loop() {
    // Print data from weather meter kit
    Serial.print(F("Wind direction (degrees): "));
    Serial.print(weatherMeterKit.getWindDirection(), 1);
    Serial.print(F("\t\t"));
    Serial.print(F("Wind speed (kph): "));
    Serial.print(weatherMeterKit.getWindSpeed(), 1);
    Serial.print(F("\t\t"));
    Serial.print(F("Total rainfall (mm): "));
    Serial.println(weatherMeterKit.getTotalRainfall(), 1);

    // Only print once per second
    delay(1000);
}

