#include <WiFi.h>
#include <WiFiUdp.h>
#include <Adafruit_NeoPixel.h>

#define LED_PIN 21
#define LED_COUNT 104

Adafruit_NeoPixel strip(LED_COUNT, LED_PIN, NEO_GRB + NEO_KHZ800);

// bandera del color actual
String colorActual = "NINGUNO";  

// Datos de la red
const char *ssid = "LucesLed-Bizcochito";
const char *password = "loquequieras";

WiFiUDP udp;
unsigned int localUdpPort = 4210;
char incomingPacket[255];

void setup() {
  Serial.begin(115200);

  WiFi.mode(WIFI_AP);
  WiFi.softAP(ssid, password);
  Serial.println("Access Point iniciado");
  Serial.print("IP: ");
  Serial.println(WiFi.softAPIP());

  udp.begin(localUdpPort);
  Serial.printf("UDP escuchando en puerto %d\n", localUdpPort);

  strip.begin();
  strip.show();
}

void loop() {
  int packetSize = udp.parsePacket();
  if (packetSize) {
    int len = udp.read(incomingPacket, 255);
    if (len > 0) incomingPacket[len] = '\0';
    String msg = String(incomingPacket);
    Serial.printf("Mensaje recibido: %s\n", msg.c_str());

    if (msg == "ESPADA") {
      efectoEspada();
    } 
    else if (msg == "VIOLETA") {
      colorActual = "VIOLETA"; 
      efectoLuces_Violeta();
    } 
    else if (msg == "ROJO") {
      colorActual = "ROJO";  
      efectoLuces_Rojo();
    }
    else if (msg == "AMARILLO") {
      colorActual = "AMARILLO";   
      efectoLuces_Amarillo();
    }
    else if (msg == "CALIDA") {
      colorActual = "CALIDA";  
      efectoLuces_Calida();
    }
    else if (msg == "AZUL") {
      colorActual = "AZUL";      
      efectoLuces_Azul();
    }
  }
}

/*  ---------------------------
     EFECTO ESPADA MODIFICADO 
    --------------------------- */
void efectoEspada() {

  // FLASH BLANCO
  for (int i=0; i<strip.numPixels(); i++) {
    strip.setPixelColor(i, strip.Color(255, 255, 255));
  }
  strip.show();
  Serial.println("Flash ESPADA");

  // Duración del flash
  unsigned long tiempoFlash = 500; 
  unsigned long inicio = millis();

  // BUCLE NO BLOQUEANTE: permite recibir mensajes mientras está el flash
  while (millis() - inicio < tiempoFlash) {

    int packetSize = udp.parsePacket();
    if (packetSize) {
      int len = udp.read(incomingPacket, 255);
      if (len > 0) incomingPacket[len] = '\0';
      String msg = String(incomingPacket);
      Serial.printf("Mensaje recibido durante ESPADA: %s\n", msg.c_str());

      // Si llega un color → cambiar inmediatamente y salir
      if (msg == "VIOLETA") { colorActual="VIOLETA"; efectoLuces_Violeta(); return; }
      if (msg == "ROJO") { colorActual="ROJO"; efectoLuces_Rojo(); return; }
      if (msg == "AMARILLO") { colorActual="AMARILLO"; efectoLuces_Amarillo(); return; }
      if (msg == "CALIDA") { colorActual="CALIDA"; efectoLuces_Calida(); return; }
      if (msg == "AZUL") { colorActual="AZUL"; efectoLuces_Azul(); return; }
    }
  }

  // SI NO LLEGA OTRO COLOR → volver al color original
  if (colorActual == "VIOLETA") efectoLuces_Violeta();
  else if (colorActual == "ROJO") efectoLuces_Rojo();
  else if (colorActual == "AMARILLO") efectoLuces_Amarillo();
  else if (colorActual == "CALIDA") efectoLuces_Calida();
  else if (colorActual == "AZUL") efectoLuces_Azul();
  else {
    // si no había color previo, se apaga
    for (int i=0; i<strip.numPixels(); i++) {
      strip.setPixelColor(i, 0, 0, 0);
    }
    strip.show();
  }
}

/* ----- EFECTOS ----- */

void efectoLuces_Violeta() {
  for (int i=0; i<strip.numPixels(); i++) {
    strip.setPixelColor(i, strip.Color(135, 39, 245));
  }
  strip.show();
}

void efectoLuces_Rojo() {
  for (int i=0; i<strip.numPixels(); i++) {
    strip.setPixelColor(i, strip.Color(245, 13, 0));
  }
  strip.show();
}

void efectoLuces_Amarillo() {
  for (int i=0; i<strip.numPixels(); i++) {
    strip.setPixelColor(i, strip.Color(255, 231, 13));
  }
  strip.show();
}

void efectoLuces_Calida() {
  for (int i=0; i<strip.numPixels(); i++) {
    strip.setPixelColor(i, strip.Color(204, 140, 6));
  }
  strip.show();
}

void efectoLuces_Azul() {
  for (int i=0; i<strip.numPixels(); i++) {
    strip.setPixelColor(i, strip.Color(38, 0, 255));
  }
  strip.show();
}
