#include "kuka_send_joint_positions-component.hpp"
#include <rtt/Component.hpp>
#include <iostream>

Kuka_send_joint_positions::Kuka_send_joint_positions(std::string const& name) : TaskContext(name){
  std::cout << "Kuka_send_joint_positions constructed !" <<std::endl;
}

bool Kuka_send_joint_positions::configureHook(){
  std::cout << "Kuka_send_joint_positions configured !" <<std::endl;
  return true;
}

bool Kuka_send_joint_positions::startHook(){
  std::cout << "Kuka_send_joint_positions started !" <<std::endl;
  return true;
}

void Kuka_send_joint_positions::updateHook(){
  std::cout << "Kuka_send_joint_positions executes updateHook !" <<std::endl;
}

void Kuka_send_joint_positions::stopHook() {
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
