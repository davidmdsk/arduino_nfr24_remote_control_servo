/*
 *  TX part - reads joystick value 0-1024 (map it to 0-255 byte) and trasmitts  
 *  it to the RX part (reader).
 *  
 *  Used an existing NRF24 library by Dejan Nedelkovski
 *  Library: TMRh20/RF24, https://github.com/tmrh20/RF24/
 */

#include <SPI.h>
#include <nRF24L01.h>
#include <RF24.h>

RF24 radio(7, 8); // CE, CSN
int xPin = A1;
int yPin = A0;

const byte address[6] = "00001";

void setup() {
  pinMode(xPin, INPUT);
  pinMode(yPin, INPUT);
  radio.begin();
  radio.openWritingPipe(address);
  radio.setPALevel(RF24_PA_MIN);
  radio.stopListening();
}

void loop() {

  unsigned char text[1];
  text [0] = (unsigned char) (analogRead(yPin) / 4);
  radio.write(&text, sizeof(text));
  delay(200);
}
