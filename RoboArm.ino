#include "XBOXONE.h"
#ifdef dobogusinclude
#include <spi4teensy3.h>
#include <SPI.h>
#endif
USB Usb;
XBOXONE Xbox(&Usb);
int testLEDOne = 52;
int testLEDTwo = 53;
int motorOne = 3;
int motorTwo = 5;
int motorThree = 6;
int motorFour = 9;
int motorZero = 190; //pwm val at which vex motors dont move
int motorTwoXYAverageStepOne;
int motorTwoXYAverageStepTwo;
int motorThreeXYAverageStepOne;
int motorThreeXYAverageStepTwo;
void setup() {
  pinMode(testLEDOne, OUTPUT);
  pinMode(testLEDTwo, OUTPUT);
  pinMode(motorOne, OUTPUT);
  pinMode(motorTwo, OUTPUT);
  pinMode(motorThree, OUTPUT);
  pinMode(motorFour, OUTPUT);
  Serial.begin(115200);
  while (!Serial); // Wait for serial port to connect - used on Leonardo, Teensy and other boards with built-in USB CDC serial connection
  if (Usb.Init() == -1) {
    Serial.print(F("\r\nOSC did not start"));
    while (1); //halt
  }
  Serial.print(F("\r\nXBOX USB Library Started"));
}

void loop() {
  digitalWrite(53, HIGH);
  Usb.Task();
  if (Xbox.XboxOneConnected) {
    if (Xbox.getAnalogHat(LeftHatX) > 7500 || Xbox.getAnalogHat(LeftHatX) < -7500 || Xbox.getAnalogHat(LeftHatY) > 7500 || Xbox.getAnalogHat(LeftHatY) < -7500 || Xbox.getAnalogHat(RightHatX) > 7500 || Xbox.getAnalogHat(RightHatX) < -7500 || Xbox.getAnalogHat(RightHatY) > 7500 || Xbox.getAnalogHat(RightHatY) < -7500) {
      if (Xbox.getAnalogHat(LeftHatX) > 7500 || Xbox.getAnalogHat(LeftHatX) < -7500) {
        Serial.print(F("LeftHatX: "));
        Serial.print(Xbox.getAnalogHat(LeftHatX));
        Serial.print("\t");
      }
      if (Xbox.getAnalogHat(LeftHatY) > 7500 || Xbox.getAnalogHat(LeftHatY) < -7500) {
        analogWrite();
        Serial.print(F("LeftHatY: "));
        Serial.print(Xbox.getAnalogHat(LeftHatY));
        Serial.print("\t");
      }
      if (Xbox.getAnalogHat(RightHatX) > 7500 || Xbox.getAnalogHat(RightHatX) < -7500) {
        analogWrite();
        Serial.print(F("RightHatX: "));
        Serial.print(Xbox.getAnalogHat(RightHatX));
        Serial.print("\t");
      }
      if (Xbox.getAnalogHat(RightHatY) > 7500 || Xbox.getAnalogHat(RightHatY) < -7500) {
        Serial.print(F("RightHatY: "));
        Serial.print(Xbox.getAnalogHat(RightHatY));
      }
      Serial.println();
    }

    if (Xbox.getButtonPress(L2) > 0 || Xbox.getButtonPress(R2) > 0) {
      if (Xbox.getButtonPress(L2) > 190) {
        //rotate entire arm to left at speed based on l2 val
        analogWrite(motorOne, 190 + Xbox.getButtonPress(L2)/17);
        Serial.print(F("L2: "));
        Serial.print(Xbox.getButtonPress(L2));
        Serial.print("\t");
      }else{
          //stop motor going to left rotation cuz l2 isnt down at all
          analogWrite(motorOne, motorZero);
        }
      if (Xbox.getButtonPress(R2) > 0) {
        //rotate entire arm to right at speed based on r2 val
        analogWrite(motorOne, 190 - Xbox.getButtonPress(R2)/11.5);
        Serial.print(F("R2: "));
        Serial.print(Xbox.getButtonPress(R2));
        Serial.print("\t");
      }else{
        //stop motor going to right rotation cuz r2 isnt down at all
        analogWrite(motorOne, motorZero);
        }
      Serial.println();
    }else{
      analogWrite(motorOne, motorZero);
    }

    if (Xbox.getButtonClick(UP)){
      //test to make sure its all good
      digitalWrite(testLEDOne, HIGH);
      digitalWrite(testLEDTwo, HIGH);
      Serial.println(F("Up"));
    }else{
      digitalWrite(testLEDOne, LOW);
      digitalWrite(testLEDTwo, LOW);
      }
    if (Xbox.getButtonClick(DOWN)){
      //test to make sure its all good
      Serial.println(F("Down"));
    }
    if (Xbox.getButtonClick(LEFT)){
      //test to make sure its all good
      Serial.println(F("Left"));
    }
    if (Xbox.getButtonClick(RIGHT)){
      //test to make sure its all good
      Serial.println(F("Right"));
    }
    if (Xbox.getButtonClick(START))
      Serial.println(F("Start"));
    if (Xbox.getButtonClick(BACK))
      Serial.println(F("Back"));
    if (Xbox.getButtonClick(XBOX))
      Serial.println(F("Xbox"));
    if (Xbox.getButtonClick(SYNC))
      Serial.println(F("Sync"));

    if (Xbox.getButtonClick(L1))
      Serial.println(F("L1"));
    if (Xbox.getButtonClick(R1))
      Serial.println(F("R1"));
    if (Xbox.getButtonClick(L2))
      Serial.println(F("L2"));
    if (Xbox.getButtonClick(R2))
      Serial.println(F("R2"));
    if (Xbox.getButtonClick(L3))
      Serial.println(F("L3"));
    if (Xbox.getButtonClick(R3))
      Serial.println(F("R3"));


    if (Xbox.getButtonClick(A))
      Serial.println(F("A"));
    if (Xbox.getButtonClick(B))
      Serial.println(F("B"));
    if (Xbox.getButtonClick(X))
      Serial.println(F("X"));
    if (Xbox.getButtonClick(Y))
      Serial.println(F("Y"));
  }
  delay(1);
}
