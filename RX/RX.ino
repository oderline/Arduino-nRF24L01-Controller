#include <SPI.h>
#include "RF24.h"

RF24 radio(9, 10);
uint16_t data[8];

void setup() {
  Serial.begin(9600);
  radio.begin();
  radio.setAutoAck(1);
  radio.setRetries(0, 15);
  radio.enableAckPayload();
  radio.setPayloadSize(32);
  radio.openReadingPipe(1, 0);
  radio.setChannel(0x60);
  radio.setPALevel (RF24_PA_MAX);
  radio.setDataRate (RF24_250KBPS);
  radio.powerUp();
  radio.startListening();
}

void loop() {
  byte pipeNo;
  while (radio.available(&pipeNo)) {
    radio.read(&data, sizeof(data));
    Serial.println(data[0]);
    Serial.println(data[1]);
    Serial.println(data[2]);
    Serial.println(data[3]);
    Serial.println(data[4]);
    Serial.println(data[5]);
    Serial.println(data[6]);
    Serial.println(data[7]);
    Serial.println("--------------------");
  }
}
