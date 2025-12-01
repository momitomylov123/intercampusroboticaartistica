#include <WiFi.h>
#include <WiFiUdp.h>
#include <Adafruit_NeoPixel.h>


#define LED_PIN 5
#define LED_COUNT 16


Adafruit_NeoPixel strip(LED_COUNT, LED_PIN, NEO_GRB + NEO_KHZ800);


// Datos de la red AP
const char *ssid = "LucesLed-Bizcochito";
const char *password = "loquequieras";


WiFiUDP udp;
unsigned int localUdpPort = 4210;
char incomingPacket[255];


void setup() {
  Serial.begin(115200);


  // Iniciar AP
  WiFi.mode(WIFI_AP);
  WiFi.softAP(ssid, password);
  Serial.println("Access Point iniciado");
  Serial.print("IP: ");
  Serial.println(WiFi.softAPIP());


  // Iniciar servidor UDP
  udp.begin(localUdpPort);
  Serial.printf("UDP escuchando en puerto %d\n", localUdpPort);


  // NeoPixel
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
    } else if (msg == "VIOLETA") {
      efectoLuces_Violeta();
    } else if (msg == "ROJO") {
      efectoLuces_Rojo();
    }else if (msg == "AMARILLO") {
      efectoLuces_Rojo();
    }else if (msg == "CALIDA") {
      efectoLuces_Rojo();
    }else if (msg == "AZUL") {
      efectoLuces_Rojo();
    }




  }
}


// Ejemplo de efectos
void efectoEspada() {
  // EFECTO DE LUCES DE ESPADA
  for (int i=0; i<strip.numPixels(); i++) {
    strip.setPixelColor(i, strip.Color(255,0,0));
  }
  strip.show();
  Serial.printf("Estoy en efectoEspada");
  delay(1000);


}


void efectoLuces_Violeta() {
  for (int i=0; i<strip.numPixels(); i++) {
    strip.setPixelColor(i, strip.Color(0,255,0));
  }
  strip.show();
  Serial.printf("Estoy en efectoLuces_Violeta");
  delay(1000);


}


void efectoLuces_Rojo() {
  for (int i=0; i<strip.numPixels(); i++) {
    strip.setPixelColor(i, strip.Color(0,0,255));
  }
  strip.show();
  Serial.printf("Estoy en efectoLuces_Rojo");
  delay(1000);
}


void efectoLuces_Amarillo() {
  for (int i=0; i<strip.numPixels(); i++) {
    strip.setPixelColor(i, strip.Color(0,0,255));
  }
  strip.show();
  Serial.printf("Estoy en efectoLuces_Amarillo");
  delay(1000);
}


void efectoLuces_Calida() {
  for (int i=0; i<strip.numPixels(); i++) {
    strip.setPixelColor(i, strip.Color(0,0,255));
  }
  strip.show();
  Serial.printf("Estoy en efectoLuces_Calida");
  delay(1000);
}


void efectoLuces_Azul() {
  for (int i=0; i<strip.numPixels(); i++) {
    strip.setPixelColor(i, strip.Color(0,0,255));
  }
  strip.show();
  Serial.printf("Estoy en efectoLuces_Azul");
  delay(1000);
}