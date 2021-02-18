#include "AutonomousCar.h"

using namespace std;

AutonomousCar::AutonomousCar(const Road *road, float x, float v) : Car(road, x, v)
{

}

float AutonomousCar::u(float d0, float v0) const
{
  if(!m_autonomous)
    return 1.;

  else
    return (m_road->circular_dist(*this, *front_car()) - d0)
         - (v() - front_car()->v())
         + (v0 - v());
}

void AutonomousCar::set_autonomous()
{
  m_autonomous = true;
}