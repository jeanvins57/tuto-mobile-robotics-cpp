#ifndef __ROBOT_H__
#define __ROBOT_H__

#include <vector>
#include <string>

typedef double vec2d[2];

struct State
{
  double x = 0.;
  double y = 0.;
  double theta = 0.;
  double v = 1.;
}; // do not forget this ;

class Robot
{
  public:

    Robot();

    // The following methods are 'const' because they
    // do not change the object on which they are called.
    double v() const;
    void draw(const std::string& color) const;
    void u(vec2d w, vec2d dw, vec2d& u) const; // u is modified by reference with "&""
    // In the above method, there is not need to use 'const' on vec2d,
    // because vec2d is in fact a simple 'double' array. 
    // 'const' is suited for complex objects (classes).

    // The following methods are not const, because they 
    // change the attributes of the object.
    void set_position(double x, double y);
    void euler(float dt, vec2d& u);

  protected:

    State m_state;
    // The above attribute will be accessible by the class RobotLeader,
    // because it is set "protected" and the inheritance is "public".
};

#endif