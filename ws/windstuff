// Pins definieren
const int RAIN_PIN = 2;
const int WIND_SPD_PIN = 3;
const int WIND_DIR_PIN = A0;

// Variablen für Berechnungen
volatile unsigned long rain_count = 0;
volatile unsigned long wind_count = 0;
unsigned long last_millis = 0;

// Interrupt-Service-Routinen (ISR)
void IRAM_ATTR countRain() {
  rain_count++;
}

void IRAM_ATTR countWind() {
  wind_count++;
}

void setup() {
  Serial.begin(115200);
  
  pinMode(RAIN_PIN, INPUT_PULLUP);
  pinMode(WIND_SPD_PIN, INPUT_PULLUP);
  
  // Interrupts aktivieren
  attachInterrupt(digitalPinToInterrupt(RAIN_PIN), countRain, FALLING);
  attachInterrupt(digitalPinToInterrupt(WIND_SPD_PIN), countWind, FALLING);
  
  Serial.println("Wetterstation initialisiert...");
}

void loop() {
  // Alle 5 Sekunden Daten ausgeben
  if (millis() - last_millis > 5000) {
    float delta_t = (millis() - last_millis) / 1000.0;
    
    // Windgeschwindigkeit berechnen
    // 1 Impuls pro Sekunde entspricht laut Datenblatt ca. 2.4 km/h
    float wind_speed = (wind_count / delta_t) * 2.4;
    
    // Regenmenge berechnen
    // Ein Impuls entspricht 0.2794 mm Regen
    float rain_amount = rain_count * 0.2794;
    
    // Windrichtung auslesen
    int dir_adc = analogRead(WIND_DIR_PIN);
    String direction = getWindDirection(dir_adc);

    // Ausgabe
    Serial.println("--- Wetterdaten ---");
    Serial.print("Windgeschwindigkeit: "); Serial.print(wind_speed); Serial.println(" km/h");
    Serial.print("Windrichtung (Rohwert): "); Serial.print(dir_adc); Serial.print(" -> "); Serial.println(direction);
    Serial.print("Regenmenge gesamt: "); Serial.print(rain_amount); Serial.println(" mm");
    Serial.println();

    // Zähler zurücksetzen, falls gewünscht (oder für Durchschnittsberechnung behalten)
    wind_count = 0;
    last_millis = millis();
  }
}

// Hilfsfunktion zur Bestimmung der Windrichtung basierend auf Analogwerten
String getWindDirection(int adc) {
  if (adc < 80) return "NW";
  if (adc < 100) return "N";
  if (adc < 200) return "W";
  if (adc < 300) return "SW";
  if (adc < 500) return "S";
  if (adc < 700) return "NO";
  if (adc < 850) return "SO";
  if (adc < 1000) return "O";
  return "Unbekannt";
}
