#include <SFE_MMA8452Q.h>
#include <Accelerometer.h>
#include <Wire.h>
#include <stdio.h>
#include <stdlib.h>

Accelerometer accel;
int powerLED = 13;
int detectLED = 12;
// Default
//  Calibration Time = 1.5sec
//  Tolerance = 0.

void setup() {
// put your setup code here, to run once:
  pinMode(powerLED,OUTPUT);
  pinMode(detectLED,OUTPUT);
  Serial.begin(9600);
  accel.init();
//Set Calibration time and Tolerance here if needed
  accel.setCalibrationTime(4);
//  accel.setTol(10);
  
  accel.getBaseLine();
}

void loop() {
  if (accel.available()) {
    digitalWrite(powerLED, HIGH);
    digitalWrite(detectLED, LOW);
    accel.read();
    printValues();
    if ( accel.detect() == 1 ){
          digitalWrite(detectLED, HIGH);   // turn the LED on (HIGH is the voltage level)
          delay(500);
          digitalWrite(detectLED, LOW);
          delay(500);
          digitalWrite(detectLED, HIGH); 
          delay(500);
          digitalWrite(detectLED, LOW);
    }
    delay(500);
  }
}

void printValues(){
   String msg = "xVal: "; msg += accel.xVal;
   msg += "\txMin: "; msg += accel.xMin;
   msg += "\txMax: "; msg += accel.xMax;
   msg += "\nyVal:"; msg += accel.yVal;
   msg += "\tyMin: "; msg += accel.yMin;
   msg += "\tyMax: "; msg += accel.yMax;
   msg += "\nzVal: "; msg += accel.zVal;
   msg += "\tzMin: "; msg += accel.zMin;
   msg += "\tzMax: "; msg += accel.zMax;
   Serial.println(msg); 
   Serial.println();
 }
