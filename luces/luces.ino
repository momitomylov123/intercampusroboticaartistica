#include <Adafruit_NeoPixel.h>
#ifdef __AVR__
 #include <avr/power.h> // Required for 16 MHz Adafruit Trinket
#endif

#define PIN        12 // acá va conectado el neopixel

#define NUMPIXELS 3 // Popular NeoPixel ring size

Adafruit_NeoPixel pixels(NUMPIXELS, PIN, NEO_GRB + NEO_KHZ800);

#define DELAYVAL 2000 // Time (in milliseconds) to pause between pixels


char comando;

void setup() {
  // These lines are specifically to support the Adafruit Trinket 5V 16 MHz.
  // Any other board, you can remove this part (but no harm leaving it):
#if defined(__AVR_ATtiny85__) && (F_CPU == 16000000)
  clock_prescale_set(clock_div_1);
#endif
  // END of Trinket-specific code.
  Serial.begin(9600); //comunicaión con módulo HC-05
  pixels.show();
  pixels.begin(); // INITIALIZE NeoPixel strip object (REQUIRED)
}

void loop() {
  if (Serial.available()){
    comando = Serial.read();
    
    switch (comando) {
      case 'q':
        setColor(25,66,78);
        break;
      case 'w':
        setColor(253, 78, 99);
        break;
      case 'e':
        setColor(222, 222,56);
        break;
      case 'r':
        setColor(178, 102,254);
        break;
      case 't':
        setColor(254, 178,102);
        break;
      case 'y':
        setColor(254, 254,254);
        break;
    
		}
	}
}
    void setColor (int r, int g, int b){
  for(int i=0; i<NUMPIXELS; i++) { // color de cada led
    pixels.setPixelColor(i, pixels.Color(r, g, b));
  }
  pixels.show();
}