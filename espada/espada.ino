#include <WiFi.h>
#include <WiFiUdp.h>


//Configuracion de red
const char *ssid = "LucesLed-Bizcochito";  
const char *password = "loquequieras";


WiFiUDP udp;
const char *host = "192.168.4.1"; // IP del AP (ESP32-Luces)
const int port = 4210;


//Variables para la espada
const int touchPin = 4;   // Pin táctil (GPIO4 en ESP32)
int umbral = 30;           // Ajustalo según tus pruebas




void setup() {
  Serial.begin(115200);


  WiFi.mode(WIFI_STA); //Inicia la ESP como estacion y no como access point
  WiFi.begin(ssid, password);


  while (WiFi.status() != WL_CONNECTED) {
    delay(500);
    Serial.print(".");
  }
  Serial.println("Conectado al controlador Luces Bizcochito");
}


void loop() {


  int lectura = touchRead(touchPin);
 
  if (lectura < umbral) {  
   
    Serial.println("⚡ ¡Contacto detectado!");


    // Envia ESPADA al controlador de luces
    udp.beginPacket(host, port);
    udp.print("ESPADA"); // o "REMOTE_1"
    udp.endPacket();


    delay(500);
   
  }
}
