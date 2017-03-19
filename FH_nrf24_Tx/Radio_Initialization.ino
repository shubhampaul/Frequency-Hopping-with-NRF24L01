void radio1_init() {
  pinMode(8, OUTPUT);
  digitalWrite(8, HIGH);
  myRadio1.begin();
  delay(100);
  myRadio1.setChannel(i);
  myRadio1.setPALevel(RF24_PA_MIN);
  myRadio1.setDataRate(RF24_2MBPS);
  myRadio1.setAutoAck(1);
  myRadio1.enableAckPayload();
  myRadio1.enableDynamicPayloads();
  myRadio1.setRetries(15, 15);
  myRadio1.setCRCLength(RF24_CRC_8);
  myRadio1.openWritingPipe( addresses1[0]);
}

void radio2_init() {
  pinMode(10, OUTPUT);
  digitalWrite(10, HIGH);
  myRadio2.begin();
  delay(100);
  myRadio2.setChannel(124);
  myRadio2.setPALevel(RF24_PA_MAX);
  myRadio2.setDataRate(RF24_2MBPS);
  myRadio2.setAutoAck(1);
  myRadio2.enableAckPayload();
  myRadio2.enableDynamicPayloads();
  myRadio2.setRetries(15, 15);
  myRadio2.setCRCLength(RF24_CRC_8);
  myRadio2.openReadingPipe(1, addresses2[0]);
  myRadio2.startListening();
}

