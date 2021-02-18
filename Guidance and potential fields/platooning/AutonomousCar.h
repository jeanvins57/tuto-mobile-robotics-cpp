#ifndef __AUTONOMOUSCAR_H__
#define __AUTONOMOUSCAR_H__

#include "Car.h"

class AutonomousCar : public Car
{
  public:

    AutonomousCar(const Road *road, float x, float v = 0.);
    float u(float d0, float v0) const; // new command for autonomous cars
    void set_autonomous();
};

#endif