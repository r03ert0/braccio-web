
// /*
//   serial_braccio.ino

//  Control Braccio using serial commands

//  Created on 16 Oct 2023
//  by Roberto Toro & Rajeev Mylapalli
//  */


#include <Braccio.h>
#include <Servo.h>

Servo base;
Servo shoulder;
Servo elbow;
Servo wrist_rot;
Servo wrist_ver;
Servo gripper;

int m0 = 20; // delay, allowed values from 10 to 30 msec.
int m1 = 0; // base degrees. Allowed values from 0 to 180 degrees.
int m2 = 15; // shoulder degrees. Allowed values from 15 to 165 degrees.
int m3 = 180; // elbow degrees. Allowed values from 0 to 180 degrees.
int m4 = 170; // wrist vertical degrees. Allowed values from 0 to 180 degrees.
int m5 = 0; // wrist rotation degrees. Allowed values from 0 to 180 degrees.
int m6 = 73; // gripper degrees. Allowed values from 10 to 73 degrees. 10: the tongue is open, 73: the gripper is closed.


void setup() {
  Braccio.begin();

  // Initialize the primary serial port at 9600 baud
  Serial.begin(9600);

  while (!Serial)
    ;

  Serial.println("Ready");

  Braccio.ServoMovement(m0, m1, m2, m3, m4, m5, m6);
}

void loop() {
  char LF = 10;

  if (Serial.available()) {
    String msg = Serial.readStringUntil(LF);

    if (msg != "") {
      Serial.println(msg); // Print the received message to the second serial port for printing

      // Split the string into values using a comma as the delimiter
      char *token = strtok(const_cast<char *>(msg.c_str()), ",");

      int index = 0;
      int receivedValues[7]; // Store the received values in an array

      while (token != NULL && index < 7) {
        // Parse the received value and store it in the array
        receivedValues[index] = atoi(token);
        token = strtok(NULL, ",");
        index++;
      }

      // Update the respective variables with the received values
      if (index == 7) {
        m0 = receivedValues[0];
        m1 = receivedValues[1];
        m2 = receivedValues[2];
        m3 = receivedValues[3];
        m4 = receivedValues[4];
        m5 = receivedValues[5];
        m6 = receivedValues[6];
      }

      // Perform the action based on the updated values
      Braccio.ServoMovement(m0, m1, m2, m3, m4, m5, m6);
    }
  }
}
