#ifndef ACCELEROMETER_H
#include "Accelerometer.h"
#endif

#include <Arduino.h>
#include <Wire.h>


Accelerometer::Accelerometer():
    tol(0.005), calibrationTime(1.50)
{
	xVal=accel.x; yVal=accel.y; zVal=accel.z;
	xMin = xVal; xMax = xVal;
    yMin = yVal; yMax = yVal;
    zMin = zVal; zMax = zVal;
}

void Accelerometer::init(){
	accel.init();
	Accelerometer();
}

void Accelerometer::read(){
	accel.read();
    xVal=accel.x; yVal=accel.y; zVal=accel.z;
}

bool Accelerometer::available(){
	return accel.available();
}


double Accelerometer::getTol(){
    return tol;
}

void Accelerometer::setTol(double value){
    tol=value;
}

double Accelerometer::getCalibrationTime(){
    return calibrationTime;
}

void Accelerometer::setCalibrationTime(double value){
    calibrationTime=value;
}

void Accelerometer::getBaseLine(){
    double clock = 0.00;
    Serial.println("=============== GETTING BASELINE... ===============");
    while ( clock < getCalibrationTime() ){
        clock = millis()/1000.000;
        printDouble (clock, 1000);
        accel.read();

     // Calibrate X-axis
        xVal = accel.x;
        if ( xVal < xMin ) { xMin = xVal; }
        else if ( xVal > xMax ) { xMax = xVal; }

     // Calibrate Y-axis
        yVal = accel.y;
        if ( yVal < yMin ) { yMin = yVal; }
        else if ( yVal > yMax ) { yMax = yVal; }

     // Calibrate Z-axis
        zVal = accel.z;
        if ( zVal < zMin ) { zMin = zVal; }
        else if ( zVal > zMax ) { zMax = zVal; }
    }
    Serial.println("=============== BASELINE READ COMPLETE ===============");
    delay(400);
}

void Accelerometer::printDouble(double val, unsigned int precision){
    Serial.print (int(val));
    Serial.print(".");
    unsigned int frac;
    if(val >= 0)
       frac = (val - int(val)) * precision;
    else
       frac = (int(val)- val ) * precision;
    Serial.println(frac,DEC) ;
}

int Accelerometer::detect(){
    double tolerance = getTol();
    if ( xVal > (xMax + tolerance ) || xVal < (xMin - tolerance) ){
        Serial.println("X Detected");
        Serial.println();
        printDouble(xVal,100);
        Serial.println();
        return 1;
    }
    else if ( yVal > (yMax + tolerance ) || yVal < (yMin - tolerance) ){
        Serial.println("Y Detected");
        printDouble(yVal,100);
        Serial.println();
        return 1;
    }
    else if ( zVal > (zMax + tolerance ) || zVal < (zMin - tolerance) ){
        Serial.println("Z Detected");
        printDouble(zVal,100);
        Serial.println();
        return 1;
    } else return 0;
}

void Accelerometer::printBoundaryValues(){
    Serial.print("xMin\txMax\t|\tyMin\tyMax\t|\tzMin\tzMax");
	Serial.println();
	Serial.print(xMin);
    Serial.print("\t");
    Serial.print(xMax);
    Serial.print("\t \t");

	Serial.print(yMin);
    Serial.print("\t");
    Serial.print(yMax);
    Serial.print("\t \t");

	Serial.print(zMin);
    Serial.print("\t");
    Serial.print(zMax);
    Serial.print("\t");
}

void Accelerometer::printAccelValues(){
	Serial.print("x\t|\ty\t|\tz");
	Serial.println();
	Serial.print(xVal);
	Serial.print("\t");

	Serial.print(yVal);
    Serial.print("\t");

	Serial.print(yVal);
}
