#ifndef OROCOS_KUKA_SEND_JOINT_POSITIONS_COMPONENT_HPP
#define OROCOS_KUKA_SEND_JOINT_POSITIONS_COMPONENT_HPP

#include <rtt/RTT.hpp>
#include <motion_control_msgs/typekit/Types.hpp>

using namespace RTT;

class Kuka_send_joint_positions : public RTT::TaskContext{
  public:
    Kuka_send_joint_positions(std::string const& name);
    bool configureHook();
    bool startHook();
    void updateHook();
    void stopHook();
    void cleanupHook();
    motion_control_msgs::JointPositions m_joint_pos_command;
};
#endif
