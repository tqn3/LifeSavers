#ifndef ACCELEROMETER_H
#define ACCELEROMETER_H

#include <Arduino.h>
#include <SFE_MMA8452Q.h>

class Accelerometer{
  public:
    Accelerometer();
    void init();
    void read();
    bool available();
    double getTol();
    void setTol(double value);
    double getCalibrationTime();
    void setCalibrationTime(double value);
    void getBaseLine();
    int detect();

    void printBoundaryValues();
    void printAccelValues();
    void printDouble(double val, unsigned int precision);

    double xMin, xMax, xVal;
    double yMin, yMax, yVal;
    double zMin, zMax, zVal;

  private:
    MMA8452Q accel;
    double tol;
    double calibrationTime;

};
#endif
