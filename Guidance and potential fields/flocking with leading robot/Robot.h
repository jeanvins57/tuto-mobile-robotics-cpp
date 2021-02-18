#ifndef __ROBOT_H__
#define __ROBOT_H__

#include <vector>
#include <string>

class Robot
{
  public:

    Robot(const std::vector<Robot>* v_swarm);
    Robot(const std::vector<Robot>* v_swarm, float x, float y, float theta);

    float x() const;
    float y() const;
    float theta() const;

    const std::vector<double>& traj_x() const;
    const std::vector<double>& traj_y() const;

    void set(float x, float y, float theta);
    void move(float dx, float dy, float dtheta);

    void f(float u, float &xdot, float &ydot, float &thetadot) const;
    float u() const;
    void draw(const std::string& color = "black") const;

  private:

    float m_x, m_y, m_theta;
    std::vector<double> m_traj_x, m_traj_y;
    const std::vector<Robot> *m_v_swarm;
};

#endif