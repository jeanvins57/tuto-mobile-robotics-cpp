#include <cmath>
#include "Car.h"
#include "vibes.h"

using namespace std;

Car::Car(const Road *road, float x, float v) : m_road(road), m_x(x), m_v(v), m_length(4.)
{

}

void Car::set_front_car(const Car *front)
{
  m_front_car = front;
}

const Car* Car::front_car() const
{
  return m_front_car;
}

float Car::x() const
{
  return m_x;
}

float Car::v() const
{
  return m_v;
}

void Car::set(float x, float v)
{
  m_x = x;
  m_v = v;
}

void Car::stop()
{
  m_v = 0.;
}

void Car::f(float u, float &xdot, float &vdot) const
{ 
  xdot = m_v;
  vdot = u;
}

float Car::u(float d0, float v0) const
{
  return 1.; // not autonomous yet
}

void Car::draw() const
{
  float theta = m_x / m_road->radius();
  string car_color = collision() ? "red" : (m_autonomous ? "#2E8D4C" : "black");
  // note: drawTank() is available in the last version of VIBes
  vibes::drawTank(m_road->radius()*cos(theta), m_road->radius()*sin(theta),
                  (theta + M_PI/2.) * 180. / M_PI,
                  m_length, car_color + "[white]", vibesParams("figure", "Jam"));
}

bool Car::collision() const
{
  return fabs(m_road->circular_dist(*this, *front_car())) < m_length;
}