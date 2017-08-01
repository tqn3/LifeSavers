#include <SFE_MMA8452Q.h>
#include <Accelerometer.h>
#include <Wire.h>

Accelerometer accel;
// Default
//  Calibration Time = 1.5sec
//  Tolerance = 0.005

void setup() {
// put your setup code here, to run once:
  Serial.begin(9600);
  accel.init();
  
//Set Calibration time and Tolerance here if needed
//  accel.setCalibrationTime(2);
//  accel.setTol(0.0001);

  accel.getBaseLine();
}

void loop() {
  if (accel.available()) {
    accel.read();
    Serial.println(accel.detect());
    delay(500);
  } 
}
