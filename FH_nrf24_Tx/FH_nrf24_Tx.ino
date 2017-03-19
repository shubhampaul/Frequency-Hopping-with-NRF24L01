#include <SPI.h>   // Comes with Arduino IDE
#include "RF24.h"  // Download and Install (See above)
byte i = 100;
boolean mode = true;
unsigned int flag = 0;
RF24 myRadio1 (9, 8);
RF24 myRadio2 (A1, 10);
void radio1_init();
void radio2_init();
unsigned int count = 0;
byte addresses1[][6] = {"1Node"};
byte addresses2[][6] = {"2Exos"};

byte dataTransmitted, prevData1, prevData2, dataReceived , ack1, ack2, prevack1;
byte tx[32] = {128, 129, 130, 131, 132, 133, 134, 255, 247, 252, 128, 129, 130, 131, 132, 133, 134, 255, 247, 252, 128, 129, 130, 131, 132, 133, 134, 255, 247, 252, 128, 147};
byte ack[32];
void setup()   /****** SETUP: RUNS ONCE ******/
{
  Serial.begin(115200);
  radio1_init();
  //  radio2_init();

  dataTransmitted = 0;
  prevData2 = dataTransmitted;

}


void loop()   /****** LOOP: RUNS CONSTANTLY ******/
{

  if ( myRadio1.write( &tx, sizeof(tx) )) {

    if (myRadio1.isAckPayloadAvailable())
    {
      myRadio1.read(&ack, sizeof(ack));
      Serial.print("Transmitted and Ack Recevied for data: ");
      for (int j = 0; j < 32; j++) {
        Serial.print(ack[j]);
        Serial.print(" ");
      }
    }
    for (int j = 0; j < 32; j++)
      tx[j]++;

    if (flag == 0) {
      i += 2;
    }
    else {
      i -= 2;
    }

    if ((i > 124) && (flag == 0)) {
      flag = 1;
    }
    else if ((i < 90) && (flag == 1)) {
      flag = 0;
    }

    myRadio1.setChannel(i);
    Serial.print(" New Channel "); Serial.println(i);

  }


  if (Serial.available()) {
    i = Serial.parseInt();
    myRadio1.setChannel(i);
  }
}
