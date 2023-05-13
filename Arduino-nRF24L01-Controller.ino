#include <SPI.h>
#include "RF24.h"

int LX, LY, RX, RY, BTN1, BTN2, BTN3, BTN4;
const int DZ = 20;
byte addr = 0;
HEX channel = 0x60;
uint16_t data[8];

RF24 radio(9, 10); // CE, SCN

void setup() {
  Serial.begin(9600);

  pinMode(4, INPUT_PULLUP);
  pinMode(5, INPUT_PULLUP);
  pinMode(6, INPUT_PULLUP);
  pinMode(7, INPUT_PULLUP);
  pinMode(10, OUTPUT);

  radio.begin();
  radio.setAutoAck(1);
  radio.setRetries(0, 15);
  radio.enableAckPayload();
  radio.setPayloadSize(32);
  radio.openWritingPipe(addr);
  radio.setChannel(channel);
  radio.setPALevel(RF24_PA_MAX);
  radio.setDataRate(RF24_250KBPS);
  radio.powerUp();
  radio.stopListening();
}

void loop() {
  getValues();
  radio.write(&data, sizeof(data));
  delay(10);
}

void getValues() {
  LX = map(analogRead(A2), 0, 1000, 0, 512);
  LX = (abs(LX - 255) < DZ) ? 255 : LX;

  LY = map(analogRead(A1), 0, 1000, 0, 512);
  LY = (abs(LY - 255) < DZ) ? 255 : LY;

  RX = map(analogRead(A6), 0, 1000, 0, 512);
  RX = (abs(RX - 255) < DZ) ? 255 : RX;

  RY = map(analogRead(A7), 0, 1000, 0, 512);
  RY = (abs(RY - 255) < DZ) ? 255 : RY;

  BTN1 = !digitalRead(2);
  BTN2 = !digitalRead(3);
  BTN3 = !digitalRead(4);
  BTN4 = !digitalRead(5);

  data[0] = LX;
  data[1] = LY;
  data[2] = RX;
  data[3] = RY;
  data[4] = BTN1;
  data[5] = BTN2;
  data[6] = BTN3;
  data[7] = BTN4;
}
