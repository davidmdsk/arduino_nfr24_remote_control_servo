/*
 *  RX part - reads one byte 0-255 value which tells us the value of the joystick knob on
 *  Sender (remote control TX part)
 *  
 *  Used an existing NRF24 library by Dejan Nedelkovski
 *  Library: TMRh20/RF24, https://github.com/tmrh20/RF24/
 */
 
#include <SPI.h>
#include <nRF24L01.h>
#include <RF24.h>
#include <Servo.h>

Servo myservo;  // create servo object to control a servo

RF24 radio(7, 8); // CE, CSN
const byte address[6] = "00001";
void setup() {
  myservo.attach(3);  // attaches the servo on pin 3 to the servo object
  Serial.begin(9600);
  radio.begin();
  radio.openReadingPipe(0, address);
  radio.setPALevel(RF24_PA_MIN);
  radio.startListening();
}
void loop() {
  if (radio.available()) {
    unsigned char text[10] = "";
    radio.read(&text, sizeof(text));
    Serial.println((int) text[0]);
    myservo.write(text[0] * 90 / 255); //map 0-255 to 0-90
  }
}
