const int touchPin = 4;   // Pin táctil (GPIO4 en ESP32)
const int ledPin   = 16;    // LED en GPIO2 (muchas placas lo traen integrado)
int umbral = 30;           // Ajustalo según tus pruebas

void setup() {
  Serial.begin(115200);
  pinMode(ledPin, OUTPUT);
  digitalWrite(ledPin, LOW);  // LED apagado al inicio
  delay(1000);
  Serial.println("ESP32 - Sensor capacitivo espada aluminio");
}

void loop() {
  int lectura = touchRead(touchPin);
  Serial.println(lectura);

  if (lectura < umbral) {  
    digitalWrite(ledPin, HIGH);   // Enciende el LED
    Serial.println("⚡ ¡Contacto detectado!");
  } else {
    digitalWrite(ledPin, LOW);    // Apaga el LED
    Serial.println("Sin contacto");
  }

  delay(200);
}
