#include <cstdlib>
#include <unistd.h> // for usleep
#include "Road.h"
#include "AutonomousCar.h"

using namespace std;

int main()
{
  // Constants:
  const int n = 15;
  const float l = 100.;
  const float dt = 0.08;
  const float d0 = l/n;
  const float v0 = 3.;

  // Road (environment)
  Road road(l);

  // Creating autonomous cars
  vector<AutonomousCar> v_cars;
  for(int i = 0 ; i < n ; i++)
    v_cars.push_back(AutonomousCar(&road, 3.8*i, 1.));

  // Setting neighbours for each car
  for(int i = 0 ; i < n ; i++)
    v_cars[i].set_front_car(&v_cars[(i+1)%n]);

  for(float t = 0. ; t < 100. ; t+=dt) // each time
  {
    for(int i = 0 ; i < n ; i++) // each car
    {
      // Cars are not autonomous up to 20s
      if(t > 20.)
        v_cars[i].set_autonomous();

      // State evolution:
      float xdot, vdot;
      v_cars[i].f(v_cars[i].u(d0, v0), xdot, vdot); // derivative computation
      v_cars[i].set(v_cars[i].x() + xdot * dt, v_cars[i].v() + vdot * dt); // euler integration
    }

    // Collisions:
    for(int i = 0 ; i < n ; i++)
      if(v_cars[i].collision())
        v_cars[i].stop();

    road.draw((const vector<Car>&)v_cars); // casting const vector<AutonomousCar> in vector<Car> object
    usleep(dt * 500000.); // animation speed
  }

  return EXIT_SUCCESS;
}