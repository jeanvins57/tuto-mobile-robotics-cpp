#ifndef __CAR_H__
#define __CAR_H__

#include "Road.h"

class Road; // necessary incomplete declaration

class Car
{
  public:

    Car(const Road *road, float x, float v = 0.);

    void set_front_car(const Car *front);
    const Car* front_car() const;

    float x() const;
    float v() const;

    void set(float x, float v);
    void stop();

    void f(float u, float& xdot, float& vdot) const; // evolution function
    float u(float d0, float v0) const; // input of the system (acceleration)

    bool collision() const;

    void draw() const;

  protected:

    float m_x, m_v;
    const Car *m_front_car;
    const Road *m_road; // the road is shared by all the cars
    const float m_length;
    bool m_autonomous = false; // used for animation purposes
    // (the car becomes autonomous at some point)
};

#endif