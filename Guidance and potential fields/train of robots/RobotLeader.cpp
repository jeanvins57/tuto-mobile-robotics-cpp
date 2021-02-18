#include <cmath>
#include <iostream>
#include "RobotLeader.h"
#include "vibes.h"

using namespace std; // only used in .cpp files

RobotLeader::RobotLeader()
{

}

void RobotLeader::draw() const
{
  Robot::draw("#CE3607");
}

void RobotLeader::euler(float dt, vec2d& u)
{
  Robot::euler(dt, u);
  m_ds += dt*m_state.v;

  if(m_ds > 0.1) // reset after each 0.1 of traveled path
  {
    m_ds = 0.;
    m_history_x.push_back(m_state);
  }
}

const vector<State>& RobotLeader::states_history() const
{
  return m_history_x;
}