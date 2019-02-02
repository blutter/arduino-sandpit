/*
ESP8266 Blink
Blink the blue LED on the ESP8266 module

https://electrosome.com/esp8266-arduino-programming-led-blink/
*/

#define LED 2 //Define blinking LED pin

void setup() {
  pinMode(LED, OUTPUT); // Initialize the LED pin as an output
}
// the loop function runs over and over again forever
void loop() {
  digitalWrite(LED, LOW); // Turn the LED on (Note that LOW is the voltage level)
  delay(200); // Wait for a second
  digitalWrite(LED, HIGH); // Turn the LED off by making the voltage HIGH
  delay(400); // Wait for two seconds
}
