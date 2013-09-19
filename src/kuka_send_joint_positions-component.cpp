#include "kuka_send_joint_positions-component.hpp"
#include <rtt/Component.hpp>
#include <iostream>

Kuka_send_joint_positions::Kuka_send_joint_positions(std::string const& name) : TaskContext(name){
  this->addPort("distance", port_distance);
  this->addPort("dummy_distance_out", port_dummy_double);
  this->addPort("jointState", port_joint_state);
  this->addPort("jointPositionsCommand", port_command);
  this->addPort("jointVelocitiesCommand", port_vel_command);
  this->addPort("toKRL", port_fri_to_krl);
  this->addPort("fromKRL", port_fri_frm_krl);
  std::cout << "Kuka_send_joint_positions constructed !" <<std::endl;
}

bool Kuka_send_joint_positions::configureHook(){
  distance = 0.0;
  direction = 1;

  //initialize the arrays that will be send to KRL
  for(int i=0; i<16; ++i){
      fri_to_krl.intData[i]=0;
      fri_to_krl.realData[i]=0.0;
  }

  //We chose to put 1 on the $FRI_FRM_INT[1] to trigger the fri_start()
  fri_to_krl.intData[0]=1;

  m_joint_vel_command.velocities.resize(7);
  for(int i=0; i<7; i++){
    m_joint_vel_command.velocities[i] = 0.0;
  }

  std::cout << "Kuka_send_joint_positions configured !" <<std::endl;
  return true;
}

bool Kuka_send_joint_positions::startHook(){
  port_fri_to_krl.write(fri_to_krl); //send fri array
  std::cout << "Kuka_send_joint_positions started !" <<std::endl;
  return true;
}

void Kuka_send_joint_positions::updateHook(){

  RTT::FlowStatus distanceFS = port_distance.read(distance);

  sensor_msgs::JointState dataJState;
  RTT::FlowStatus fs = port_joint_state.read(dataJState);
  if(fs == RTT::NewData){
    std::vector<double> q(dataJState.position);// = dataJState.position;//dataJState.velocity  dataJState.effort

    if(q[2] > 1.0471975512 && direction == 1){
        direction = -1;
    }
    else if( q[2] < -1.0471975512 && direction == -1){
        direction = 1;
    }

    double alpha = 0.10 - std::min( std::max(distance, 0.10), 0.60 );
    m_joint_vel_command.velocities[2] = 0.1 * alpha * direction;

    port_vel_command.write(m_joint_vel_command);

  }

}

void Kuka_send_joint_positions::stopHook() {
  for(int i=0; i<7; i++){
    m_joint_vel_command.velocities[i] = 0.0;
  }
  port_vel_command.write(m_joint_vel_command);

  fri_to_krl.intData[0]=2;
  port_fri_to_krl.write(fri_to_krl); //send fri command
  std::cout << "Kuka_send_joint_positions executes stopping !" <<std::endl;
}

void Kuka_send_joint_positions::cleanupHook() {
  std::cout << "Kuka_send_joint_positions cleaning up !" <<std::endl;
}

/*
 * Using this macro, only one component may live
 * in one library *and* you may *not* link this library
 * with another component library. Use
 * ORO_CREATE_COMPONENT_TYPE()
 * ORO_LIST_COMPONENT_TYPE(Kuka_send_joint_positions)
 * In case you want to link with another library that
 * already contains components.
 *
 * If you have put your component class
 * in a namespace, don't forget to add it here too:
 */
ORO_CREATE_COMPONENT(Kuka_send_joint_positions)
