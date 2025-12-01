 int led = 15;
 int pulse1 = 23;
 int lee;
void setup()
{
  pinMode(pulse1, INPUT);
  pinMode (led, OUTPUT);
  Serial.begin(9600);
}

void loop()
{
  lee = digitalRead(pulse1);
  Serial.println(digitalRead(pulse1));
  if (lee == 1){
    digitalWrite(led, HIGH);
    delay (1000);
  }
  /*else {
    digitalWrite(led, LOW);
  }*/
  //Serial.println(lee);
}