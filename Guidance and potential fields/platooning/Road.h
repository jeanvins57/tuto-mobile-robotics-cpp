#ifndef __ROAD_H__
#define __ROAD_H__

#include <vector>
#include "Car.h"

class Car; // necessary incomplete declaration

class Road
{
  public:

    Road(float l); // initializes also the graphical view
    ~Road(); // ends the graphical view

    float length() const;
    float radius() const;
    void draw(const std::vector<Car>& v_cars) const;
    float circular_dist(const Car& c1, const Car& c2) const;

  protected:

    const float m_l;
    const float m_road_width;
};

#endif