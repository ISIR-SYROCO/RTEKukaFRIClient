RTEKukaFRIClient
================

This is an example of orocos component that connects to the FRI:

Run the KRL script on the robot, then the orocos example script.

Dependencies:
=============

This component depends on the ROS package `kuka_robot_hardware`

Install:
========

Go to the `ros_workspace` directory, and add the package:

    cd ros_workspace
    wstool set RTEKukaFRIClient --git https://github.com/XDE-ISIR/RTEKukaFRIClient.git
    wstool update RTEKukaFRIClient

Start Demo:
===========

First launch roscore:
	roscore

then in another terminal launch the openNi node:
	roslaunch openni_launch openni.launch

Setup the robot in GravityComp mode and runfri_open, runfri_start

Run the initialization script for the calibration
	rosrun ocl deployer-gnulinux -s Demo_disposvel01calibration.ops

Run the calibration program and follow the instructions:
	roslaunch kuka_kinect_calibration calibrate_kuka.launch

publish the /world to /camera_link transformation returned by the calibration program, example:
	rosrun tf static_transform_publisher 0.755449 -1.47254 1.16996 .166774 0.0701399 0.931835 0.314563 /world /camera_link 100

verify by launching rqt:
	rqt

Changed the fixed frame to /camera_link
Add a Tf object
Add a PointCloud2 object and change the topic to /camera/depth_registered/points to visualize the kinect image
Check that the robot segments correspond to the robot image

Run the human tracker:
	rosrun tracker tracker

Setup the robot in PositionControl mode, and run the script krl.src

Run the second demo script type:
	rosrun ocl deployer-gnulinux -s Demo_disposvel02start.ops

Add a path object in rqt and select the topic /distances/path to visualize minimum distance between the human limbs and the robot links


	
