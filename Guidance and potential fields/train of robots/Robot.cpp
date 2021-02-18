#include <cmath>
#include <iostream>
#include "Robot.h"
#include "vibes.h"

using namespace std; // only used in .cpp files

Robot::Robot()
{

}

void Robot::set_position(double x, double y)
{
  m_state.x = x;
  m_state.y = y;
}

double Robot::v() const
{
  return m_state.v;
}

void Robot::u(vec2d w, vec2d dw, vec2d& u) const
{
  // Complete this:
  const double &px = m_state.x;
  const double &py = m_state.y;
  const double &theta = m_state.theta;
  const double &v = m_state.v;
  // In the above code, we simply set references to
  // variables of the 'State' structure

  // The following code has been given during the exam:
  // -------------

    double A[2][2] = {
      { -v*sin(theta), cos(theta) },
      { v*cos(theta), sin(theta) }
    };

    double det_inv_A = A[0][0]*A[1][1]-A[0][1]*A[0][1];
    
    if(det_inv_A == 0.)
    {
      cout << "Error for matrix inversion" << endl;
      exit(1);
    }

    det_inv_A = 1. / det_inv_A;

    double inv_A[2][2] = {
      { det_inv_A*A[1][1], -det_inv_A*A[0][1] },
      { -det_inv_A*A[1][0], det_inv_A*A[0][0] }
    };

    vec2d y = { px, py };
    vec2d dy = { v*cos(theta), v*sin(theta) };
    vec2d e = { w[0]-y[0]+dw[0]-dy[0], w[1]-y[1]+dw[1]-dy[1] };

    u[0] = inv_A[0][0]*e[0] + inv_A[0][1]*e[1];
    u[1] = inv_A[1][0]*e[0] + inv_A[1][1]*e[1];

  // -------------
}

void Robot::draw(const string& color) const
{
  // In case you have an old version of the VIBes viewer,
  // you may use another function such as drawVehicle(..)
  vibes::drawTank(m_state.x, m_state.y, m_state.theta* 180. / M_PI, 1.,
                  color, vibesParams("figure", "Convoy"));
}

void Robot::euler(float dt, vec2d& u)
{
  // Integration of xdot=f(x,u)
  m_state.x += dt*m_state.v*cos(m_state.theta);
  m_state.y += dt*m_state.v*sin(m_state.theta);
  m_state.theta += dt*u[0];
  m_state.v += dt*u[1];
}