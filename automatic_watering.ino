/****************************************************
 * Einfaches Arduino-Skript für automatische Bewässerung 
 * mit kapazitivem Bodenfeuchtesensor und kleinem Motor.
 *
 * Hinweis: Für Motoren, die mehr als ~40mA ziehen, 
 * bitte Transistor & Freilaufdiode verwenden!
 ****************************************************/

// ========== PIN-DEFINITIONEN ==========
// Hier bitte anpassen, falls andere Pins verwendet werden.
const int SENSOR_PIN = A0;   // Analoger Eingang für den kapazitiven Sensor
const int MOTOR_PIN  = 3;    // Digitaler Ausgang für den kleinen Motor

// ========== EINSTELLBARE PARAMETER ==========
// Schwellwert (Threshold) für den Feuchtesensor
int moistureThreshold = 600; 

// Bewässerungszeit in Millisekunden (z.B. 3 Sekunden)
unsigned long waterTime = 3000;

// Wartezeit zwischen Messungen in Millisekunden (z.B. 60 Sekunden)
unsigned long waitTime = 60000; 

void setup() {
  pinMode(MOTOR_PIN, OUTPUT);
  digitalWrite(MOTOR_PIN, LOW);
  
  Serial.begin(9600);
  Serial.println("=== Start: Einfaches Bewaesserungs-System ===");
}

void loop() {
  // 1. Bodenfeuchte auslesen
  int moistureValue = analogRead(SENSOR_PIN);

  // 2. Ausgabe auf dem seriellen Monitor
  Serial.print("Feuchtigkeitswert: ");
  Serial.println(moistureValue);

  // 3. Entscheidung, ob gegossen werden soll
  if (moistureValue < moistureThreshold) {
    // Erde ist zu trocken -> Motor einschalten
    Serial.println("Erde ist trocken! Starte Bewaesserung...");
    digitalWrite(MOTOR_PIN, HIGH);
    delay(waterTime);
    digitalWrite(MOTOR_PIN, LOW);
    Serial.println("Bewaesserung beendet.");
  } else {
    // Erde ist feucht genug
    Serial.println("Erde ist feucht genug. Kein Giessen noetig.");
  }

  // 4. Warte bis zur nächsten Messung
  Serial.print("Warte ");
  Serial.print(waitTime / 1000);
  Serial.println(" Sekunden, bevor erneut gemessen wird...");

  delay(waitTime);
}
