#include <cmath>
#include <iostream>
#include "Robot.h"
#include "vibes.h"
#include "math.h"

using namespace std;

Robot::Robot(const vector<Robot>* v_swarm) : m_v_swarm(v_swarm)
{
  // Puts the robot randomly in a [-200,200]x[-200,200] area,
  // with a random heading.
  set(200. * customrand(), 200. * customrand(), customrand());
}

Robot::Robot(const vector<Robot>* v_swarm, float x, float y, float theta) : m_v_swarm(v_swarm)
{
  set(x, y, theta);
}

float Robot::x() const
{
  return m_x;
}

float Robot::y() const
{
  return m_y;
}

float Robot::theta() const
{
  return m_theta;
}

const vector<double>& Robot::traj_x() const
{
  return m_traj_x;
}

const vector<double>& Robot::traj_y() const
{
  return m_traj_y;
}

void Robot::set(float x, float y, float theta)
{
  m_x = x;
  m_y = y;
  m_theta = theta;

  // Saving robot's trajectory
  m_traj_x.push_back(m_x);
  m_traj_y.push_back(m_y);
}

void Robot::move(float dx, float dy, float dtheta)
{
  set(m_x + dx, m_y + dy, m_theta + dtheta);
}

void Robot::f(float u, float &xdot, float &ydot, float &thetadot) const
{
  xdot = cos(m_theta);
  ydot = sin(m_theta);
  thetadot = u;
}

float Robot::u() const
{
  float alpha = 0.005; // coefficient for cohesion rule
  float beta = 5.; // coefficient for separation rule
  float gamma = 0.5; // coefficient for alignment rule

  float sum[2]; // sum vector (TABLEAU de 2 floats)
  sum[0] = 0.; sum[1] = 0.;

  for(int j = 0 ; j < m_v_swarm->size() ; j++)
  {
    if(&(*m_v_swarm)[j] == this) // i != j
      continue;

    float dp[2];
    dp[0] = m_x - (*m_v_swarm)[j].x();
    dp[1] = m_y - (*m_v_swarm)[j].y();

    // Cohesion rule
    sum[0] += -2.*alpha*dp[0];
    sum[1] += -2.*alpha*dp[1];

    // Separation rule
    if(norm(dp) != 0.) // avoiding possible division by 0
    {
      sum[0] += beta*dp[0]/pow(norm(dp),3);
      sum[1] += beta*dp[1]/pow(norm(dp),3);
    }

    // Alignment rule
    sum[0] += gamma*cos((*m_v_swarm)[j].theta());
    sum[1] += gamma*sin((*m_v_swarm)[j].theta());
  }

  return sawtooth(angle(sum) - m_theta); // final command
}

void Robot::draw(const string& color) const
{
  vibes::drawTank(m_x, m_y, m_theta* 180. / M_PI, 1.,
                  color, vibesParams("figure", "Flocking"));
}