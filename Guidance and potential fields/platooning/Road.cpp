#include <cmath>
#include "Road.h"
#include "vibes.h"

using namespace std;

Road::Road(float l) : m_l(l), m_road_width(5.)
{
  vibes::beginDrawing();
  vibes::newFigure("Jam");
  vibes::setFigureProperties("Jam", vibesParams("x", 200, "y", 200, "width", 400, "height", 400));
  vibes::axisLimits(-20., 20., -20., 20.);
}

Road::~Road()
{
  vibes::endDrawing();
}

float Road::length() const
{
  return m_l;
}

float Road::radius() const
{
  return m_l / (2.*M_PI);
}

void Road::draw(const vector<Car>& v_cars) const
{
  vibes::clearFigure("Jam");

  vibes::drawCircle(0., 0., radius() + m_road_width / 2., "#B8D3DA[#B8D3DA]", vibesParams("figure", "Jam"));
  vibes::drawCircle(0., 0., radius() - m_road_width / 2., "white[white]", vibesParams("figure", "Jam"));

  for(int i = 0 ; i < v_cars.size() ; i++) // displaying cars on top of the road
    v_cars[i].draw();
}

float sawtooth(float x)
{
  return 2.*atan(tan(x/2.));
  return fmod(x + M_PI, 2.*M_PI) - M_PI; // this is equivalent
}

float Road::circular_dist(const Car& c1, const Car& c2) const
{
  float dx = c2.x() - c1.x();
  return radius() * (sawtooth(dx/radius() - M_PI) + M_PI);
}