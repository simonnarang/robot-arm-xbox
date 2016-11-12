#include <Arduino.h>
#include "XBOXONE.h"
#ifdef dobogusinclude
#include <spi4teensy3.h>
#include <SPI.h>
#endif

USB Usb;
XBOXONE Xbox(&Usb);

int statusLED = 52;
int baseRotateMotor = 3;
int hipRotateMotor = 5;
int shoulderRotateMotor = 6;
int clawMotor = 9;
int vex3932MotorZero = 190; //PWM Value at which VEX 2-wire 393 Motors Don't Move

void setup() {

  pinMode(statusLED, OUTPUT);
  pinMode(baseRotateMotor, OUTPUT);
  pinMode(hipRotateMotor, OUTPUT);
  pinMode(shoulderRotateMotor, OUTPUT);
  pinMode(clawMotor, OUTPUT);

  Serial.begin(115200);

  while (!Serial);

  if (Usb.Init() == -1) {

    Serial.print(F("\r\n OSC did not start"));

    while (1);

  }

  Serial.print(F("\r\n Yay! XBOX USB Library Started. Give Yourself a Pat on the Back 👏"));

}

void loop() {

  Usb.Task();

  if (Xbox.XboxOneConnected) {

    if (Xbox.getAnalogHat(LeftHatX) > 7500 ||
    Xbox.getAnalogHat(LeftHatX) < -7500 ||
    Xbox.getAnalogHat(LeftHatY) > 7500 ||
    Xbox.getAnalogHat(LeftHatY) < -7500 ||
    Xbox.getAnalogHat(RightHatX) > 7500 ||
    Xbox.getAnalogHat(RightHatX) < -7500 ||
    Xbox.getAnalogHat(RightHatY) > 7500 ||
    Xbox.getAnalogHat(RightHatY) < -7500) {

      if (Xbox.getAnalogHat(LeftHatX) > 7500 || Xbox.getAnalogHat(LeftHatX) < -7500) {

        Serial.print(F("\r\n LeftHatX: "));
        Serial.print(Xbox.getAnalogHat(LeftHatX));
        Serial.print("\t");

      }
      if (Xbox.getAnalogHat(LeftHatY) > 7500 || Xbox.getAnalogHat(LeftHatY) < -7500) {

        Serial.print(F("\r\n LeftHatY: "));
        Serial.print(Xbox.getAnalogHat(LeftHatY));
        Serial.print("\t");

        if (Xbox.getAnalogHat(LeftHatY) > 7500){

        } else if (Xbox.getAnalogHat(LeftHatY) < 7500){

        } else {

        }

      } else {

      }

      if (Xbox.getAnalogHat(RightHatX) > 7500 || Xbox.getAnalogHat(RightHatX) < -7500) {

        Serial.print(F("\r\n RightHatX: "));
        Serial.print(Xbox.getAnalogHat(RightHatX));
        Serial.print("\t");

      }
      if (Xbox.getAnalogHat(RightHatY) > 7500 || Xbox.getAnalogHat(RightHatY) < -7500) {

        Serial.print(F("\r\n RightHatY: "));
        Serial.print(Xbox.getAnalogHat(RightHatY));
        Serial.print("\t");

        if (Xbox.getAnalogHat(RightHatY) > 7500){

        }

        if (Xbox.getAnalogHat(RightHatY) < -7500){

        }

      } else {

      }

    } else {

    }

    if (Xbox.getButtonPress(L2) > 0 || Xbox.getButtonPress(R2) > 0) {

      if (Xbox.getButtonPress(L2) > 0) {

        //rotate entire arm to left at speed based on l2 value
        analogWrite(baseRotateMotor, 250 - Xbox.getButtonPress(L2)/100);

        Serial.print(F("L2: "));
        Serial.print(Xbox.getButtonPress(L2));
        Serial.print("\t");

      } else {

      }

      if (Xbox.getButtonPress(R2) > 0) {

        //rotate entire arm to right at speed based on r2 val
        analogWrite(baseRotateMotor, 190 - Xbox.getButtonPress(R2)/11.5);

        Serial.print(F("R2: "));
        Serial.print(Xbox.getButtonPress(R2));
        Serial.print("\t");

      } else {

        //stop motor going to right rotation cuz r2 isnt down at all
        analogWrite(baseRotateMotor, vex3932MotorZero);

      }

      Serial.println();

    } else {

      analogWrite(baseRotateMotor, vex3932MotorZero);

    }

    if (Xbox.getButtonPress(UP)){

      //test to make sure robot is properly functioning

      digitalWrite(statusLED, HIGH);

      Serial.println(F("Up"));

    } else {

      digitalWrite(statusLED, LOW);

      if (Xbox.getButtonPress(DOWN)) {

      } else {

        analogWrite(hipRotateMotor, vex3932MotorZero);

        }

      }

    if (Xbox.getButtonPress(DOWN)) {

      //test to make sure its all good
      Serial.println(F("Down"));
      analogWrite(hipRotateMotor, 99);

    } else {

      if (Xbox.getButtonPress(DOWN)){

        } else {

          analogWrite(hipRotateMotor, vex3932MotorZero);

          }
      }
    if (Xbox.getButtonClick(LEFT)) {

      //test to make sure its all good
      Serial.println(F("Left"));

    }
    if (Xbox.getButtonClick(RIGHT)) {

      Serial.println(F("Right"));

    }

    if (Xbox.getButtonClick(START)) {

      Serial.println(F("Start"));

    }

    if (Xbox.getButtonClick(BACK)) {

      Serial.println(F("Back"));

    }

    if (Xbox.getButtonClick(XBOX)) {

      Serial.println(F("Xbox"));

    }

    if (Xbox.getButtonClick(SYNC)) {

      Serial.println(F("Sync"));

    }

    if (Xbox.getButtonClick(L1)) {

      Serial.println(F("L1"));

    }

    if (Xbox.getButtonClick(R1)) {

      Serial.println(F("R1"));

    }

    if (Xbox.getButtonClick(L2)) {

      Serial.println(F("L2"));

    }

    if (Xbox.getButtonClick(R2)) {

      Serial.println(F("R2"));

    }

    if (Xbox.getButtonPress(L3)) {

      analogWrite(clawMotor, 240);
      Serial.println(F("L3"));

    } else {

      if (Xbox.getButtonPress(R3)) {

      } else {

        analogWrite(clawMotor, vex3932MotorZero);

      }
    }

    if (Xbox.getButtonPress(R3)) {

      analogWrite(clawMotor, 90);

      Serial.println(F("R3"));

    } else {

      if(Xbox.getButtonPress(L3)) {

      } else {

        analogWrite(clawMotor, vex3932MotorZero);

      }
    }

    if (Xbox.getButtonPress(A)) {

      Serial.println(F("A"));

      analogWrite(shoulderRotateMotor, 240);

    } else {

      if (Xbox.getButtonPress(Y)) {

      } else {

        analogWrite(shoulderRotateMotor, vex3932MotorZero);

      }
    }

    if (Xbox.getButtonClick(B)) {

      Serial.println(F("B"));

    }

    if (Xbox.getButtonClick(X)) {

      Serial.println(F("X"));

    }

    if (Xbox.getButtonPress(Y)) {

      analogWrite(shoulderRotateMotor, 90);
      Serial.println(F("Y"));

    } else {

      if (Xbox.getButtonPress(A)) {

      } else {

        analogWrite(shoulderRotateMotor, vex3932MotorZero);

      }
    }
  }

  delay(1);

}
