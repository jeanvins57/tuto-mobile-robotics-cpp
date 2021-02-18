#include <unistd.h> // for usleep
#include <iostream>
#include <math.h>
#include "vibes.h"
#include "Robot.h"
#include "RobotLeader.h"

using namespace std; // only used in .cpp files

// Note : because there are no pointers in this project, 
// there cannot be memory leaks.

int main()
{
  // Constants of the simulation
  const float dt = 0.005;
  const float tmax = 100.;
  const float Lx = 20., Ly = 5.;
  const float ds = 0.1;
  const float d = 5.;
  const int n = 6;

  // Graphics initialization:
  vibes::beginDrawing();
  vibes::newFigure("Convoy");
  vibes::setFigureProperties("Convoy",
    vibesParams("x", 100, "y", 100, "width", 900, "height", 500));
  vibes::axisLimits(-25.,25.,-13.89,13.89);

  RobotLeader Ra;

  Robot Ri[n];
  for(int i = 0 ; i < n ; i++)
    Ri[i].set_position(-i,0.);

  for(float t = 0. ; t < tmax ; t+=dt)
  {
    vibes::clearFigure("Convoy");
    vibes::drawEllipse(0., 0., Lx, Ly, 0., "#646464");

    // Leader Ra
    {
      const float o = 0.1; // omega
      vec2d wa = { Lx*sin(o*t) , Ly*cos(o*t) }; // waypoint
      vec2d dwa = { o*Lx*cos(o*t) , -o*Ly*sin(o*t) }; // waypoint dynamic
      vibes::drawCircle(wa[0], wa[1], 0.1, "#CE3607[#CE3607]"); // leader's target 

      vec2d u; // the command to be computed by the following function
      Ra.u(wa, dwa, u);
      Ra.euler(dt, u); // simulation of the robot over dt
      Ra.draw();
    }

    // Followers
    for(int i = 0 ; i < n ; i++)
    {
      vec2d ui; // the command is either (0.2,0) or set to go at a given location

      // The robot will follow a previous position of the leader.
      // j is the index in the history of this previous state.
      int j = Ra.states_history().size() - d*(i+1)/ds - 1;

      if(j > 0) // if this previous position has occurred
      {
        State x_j = Ra.states_history()[j]; // getting the corresponding state

        vec2d wai = { x_j.x, x_j.y }; // waypoint
        vec2d dwai = { Ra.v()*cos(x_j.theta), Ra.v()*sin(x_j.theta) }; // waypoint dynamic
        vibes::drawCircle(wai[0], wai[1], 0.1, "#00708A[#00708A]"); // follower's target 

        Ri[i].u(wai, dwai, ui);
      }

      else
      {
        // Making rounds, waiting for a moving position to follow
        ui[0] = 0.2;
        ui[1] = 0.;
      }

      Ri[i].euler(dt, ui); // simulation of the robot over dt
      Ri[i].draw("#00708A");
    }

    usleep(1000.); // animation speed (1000 microseconds)
  }

  vibes::endDrawing();
  return EXIT_SUCCESS;
}