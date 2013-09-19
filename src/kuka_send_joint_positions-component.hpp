#ifndef OROCOS_KUKA_SEND_JOINT_POSITIONS_COMPONENT_HPP
#define OROCOS_KUKA_SEND_JOINT_POSITIONS_COMPONENT_HPP

#include <rtt/RTT.hpp>
#include <kuka_lwr_fri/friComm.h>
#include <motion_control_msgs/typekit/Types.hpp>
#include <sensor_msgs/typekit/Types.hpp>

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
    motion_control_msgs::JointVelocities m_joint_vel_command;
    tFriKrlData fri_to_krl;
    tFriKrlData fri_frm_krl;
    double distance;
    int direction;
    RTT::InputPort<double> port_distance;
	RTT::InputPort< sensor_msgs::JointState > port_joint_state;
    RTT::OutputPort<motion_control_msgs::JointPositions> port_command;
    RTT::OutputPort<motion_control_msgs::JointVelocities> port_vel_command;
    RTT::OutputPort<tFriKrlData> port_fri_to_krl;
    RTT::InputPort<tFriKrlData> port_fri_frm_krl;

    RTT::OutputPort<double> port_dummy_double;
};
#endif
