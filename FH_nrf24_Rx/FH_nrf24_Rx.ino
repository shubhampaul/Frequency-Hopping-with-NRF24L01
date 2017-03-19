#include <SPI.h>   // Comes with Arduino IDE
#include "RF24.h"  // Download and Install (See above)
unsigned int flag = 0;
boolean mode = false;
RF24 myRadio1 (9, 8);
RF24 myRadio2 (A1, 10);
unsigned int count = 0, count1 = 0;
void radio1_init();
void radio2_init();
byte i = 100;
byte addresses1[][6] = {"1Node"};
byte addresses2[][6] = {"2Exos"};// Create address for 1 pipe.
byte dataTransmitted, prevData1, prevData2, dataReceived , ack1, ack2, prevack1;
byte rx[32], ack[32];
void setup()   /****** SETUP: RUNS ONCE ******/
{
  Serial.begin(115200);
  //  radio1_init();
  radio2_init();

  dataTransmitted = 0; // Arbitrary known data to transmit. Change it to test...


}


void loop()
{
  if (myRadio2.available())
  {
    myRadio2.read( &rx, sizeof(rx));

    myRadio2.writeAckPayload(1, &rx, sizeof(rx));


    Serial.print(" 2 Data received & Ack sent for data = ");
    for (int j = 0; j < 32; j++) {
      Serial.print(rx[j]);
      Serial.print(" ");
    }
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
    myRadio2.setChannel(i);
    Serial.print(" New Channel "); Serial.println(i);

  }


  if (Serial.available()) {
    i = Serial.parseInt();
    myRadio2.setChannel(i);
  }

}


