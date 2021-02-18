#include <unistd.h> // for usleep
#include <iostream>
#include <math.h>
#include <iomanip>
#include "vibes.h"
#include "Robot.h"

using namespace std;

int main()
{
  // Constants of the simulation
  const int n = 20;
  const float dt = 0.2;
  const float tmax = 1500.;

  // Random initialization
  srand(time(NULL));

  // Graphics initialization:
  vibes::beginDrawing();
  vibes::newFigure("Flocking");
  vibes::setFigureProperties("Flocking",
    vibesParams("x", 100, "y", 100, "width", 700, "height", 700));
  vibes::axisLimits(-100.,100.,-100.,100.);

  // Swarm vector
  vector<Robot> v_swarm;
  v_swarm.push_back(Robot(&v_swarm, 0., 0., 0.)); // initialization with one robot

  float prev_t = 0.;
  for(float t = 0. ; t < tmax ; t+=dt)
  {
    // Each 10 time lapse, a new robot appears:
    if(t - prev_t > 10. && v_swarm.size() < n)
    {
      v_swarm.push_back(Robot(&v_swarm));
      prev_t = t;
    }

    vibes::clearFigure("Flocking");

    for(int i = 0 ; i < v_swarm.size() ; i++)
    {
      if(i == 0) // The first robot is the leader
      {
        // It follows exactly a Lissajous curve
        float a = 30., b = 80.;
        v_swarm[i].set(a * 2*sin(t/b),
                       a * sin(2*t/b),
                       atan2(a * 2*cos(2*t/b) / b, a * 2*cos(t/b) / b));
      }

      else // The other behave in the swarm: Reynolds' rules
      {
        float xdot, ydot, thetadot; // derivative of the state, to be computed
        v_swarm[i].f(v_swarm[i].u(), xdot, ydot, thetadot); // derivative computation
        v_swarm[i].move(xdot * dt, ydot * dt, thetadot * dt); // euler integration
      }

      v_swarm[i].draw(i == 0 ? "#00839A[#00839A]" : "black[black]"); // #00839A : custom blue
    }

    usleep(1000.); // animation speed (1000 microseconds)
  }

  // Drawing lines after the simulation
  for(int i = 0 ; i < v_swarm.size() ; i++)
    vibes::drawLine(v_swarm[i].traj_x(),
                    v_swarm[i].traj_y(),
                    i == 0 ? "#00839A" : "lightGray",
                    vibesParams("figure", "Flocking"));

  vibes::endDrawing();
  return EXIT_SUCCESS;
}