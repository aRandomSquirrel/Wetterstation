#define LED_PIN 2

void setup() {
  pinMode(LED_PIN, OUTPUT);
  Serial.begin(115200);
}

void loop() {
  digitalWrite(LED_PIN, LOW);  
  Serial.println("Hallo Welt!");
  delay(30);
  digitalWrite(LED_PIN, HIGH); 
  Serial.println("Aufweidersehen");
  delay(30);
}
