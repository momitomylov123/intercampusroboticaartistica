/*(Código para el control) 
Este código hace que cuando apretes un botón, cambien el color de las luces.
El control que cambia el color de las luces(cliente) se conecta por la red de las luces(servidor).
Cada botón manda una señal distinta al servidor.
*/
#include <ESP8266WiFi.h>
#include <WiFiUdp.h>


//Configuracion de red
const char *ssid = "LucesLed-Bizcochito";  
const char *password = "loquequieras";
//const char *ssid = "Wifi de Maluma baby";
//const char *password = "nicolmiraculos";


WiFiUDP udp;
const char *host = "192.168.4.1"; // IP del AP (ESP32-Luces)
const int port = 4210;


//Variables para control remoto
const int pinRojo = D5;   // Pin para activar el color
const int pinVioleta = D6;   // Pin para activar el color
const int pinAmarillo = D7;   // Pin para activar el color
const int pinCalido = D1;   // Pin para activar el color
const int pinAzul = D2;   // Pin para activar el color


//Variable para lectura de pulsadores
int leerojo;
int leeazul;
int leeamarillo;
int leecalido;
int leevioleta;










void setup() {
  Serial.begin(74880);


  //Iniciar los pines digitales
  pinMode(pinRojo,INPUT_PULLUP);
  pinMode(pinVioleta,INPUT_PULLUP);
  pinMode(pinAmarillo,INPUT_PULLUP);
  pinMode(pinCalido,INPUT_PULLUP);
  pinMode(pinAzul,INPUT_PULLUP);


  WiFi.mode(WIFI_STA); //Inicia la ESP como estacion y no como access point
  WiFi.begin(ssid, password);


  while (WiFi.status() != WL_CONNECTED) {
    delay(500);
    Serial.print(".");
  }
  Serial.println("Conectado al controlador Luces Bizcochito");
}


void loop() {


  //Leemos los pulsadores
  leerojo = digitalRead(pinRojo);
  leeazul = digitalRead(pinAzul);
  leecalido = digitalRead(pinCalido);
  leeamarillo = digitalRead(pinAmarillo);
  leevioleta = digitalRead(pinVioleta);
 
  if (leerojo == 0){
    Serial.println("luz roja");
    // Envia el color al controlador de luces
    udp.beginPacket(host, port);
    udp.print("ROJO");
    udp.endPacket();


    delay(500);
  }
  else if (leeazul == 0) {
    Serial.println("luz azul");
    // Envia el color al controlador de luces
    udp.beginPacket(host, port);
    udp.print("AZUL"); //
    udp.endPacket();


    delay(500);
  }
  else if (leeamarillo == 0) {
    Serial.println("luz amarilla");
    // Envia el color al controlador de luces
    udp.beginPacket(host, port);
    udp.print("AMARILLO"); //
    udp.endPacket();


    delay(500);
  }
  else if (leecalido == 0) {
    Serial.println("luz cálida");
    // Envia el color al controlador de luces
    udp.beginPacket(host, port);
    udp.print("CALIDA"); //
    udp.endPacket();


    delay(500);
  }
  else if (leevioleta == 0) {
    Serial.println("luz violeta");
    // Envia el color al controlador de luces
    udp.beginPacket(host, port);
    udp.print("VIOLETA"); //
    udp.endPacket();


    delay(500);
  }
 
}