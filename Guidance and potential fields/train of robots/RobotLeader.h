#ifndef __ROBOT_LEADER_H__
#define __ROBOT_LEADER_H__

#include <vector>
#include <string>
#include "Robot.h"

class RobotLeader : public Robot
// The inheritance has to be public (with 'public' keyword),
// so that RobotLeader can access the items of Robot
{
  public:

    RobotLeader();
    // We list the methods for which we set an overload
    void draw() const;
    void euler(float dt, vec2d& u);
    // We add this one:
    const std::vector<State>& states_history() const;
    // The above method is 'const' because it does not change
    // the object when it is called. It is a "getter" returning 
    // the m_history_x attribute. The attribute is returned with
    // its reference, which means that no copy of vectors will be 
    // performed when calling this function. And because the method
    // is 'const', this returned reference has to be 'const' too.
    // This way, we ensure the object cannot be modified after
    // calling this method.

  private:

    double m_ds = 0.;
    std::vector<State> m_history_x;
};

#endif