# Darrsm

This project is for the capstone design in 2016/10~2017/9.

Darrsm is that 'Disaster and Rescue Robot Simulation & modeling'.


#### Nessesary for user to launch this project.
- "openni_launch" for running kinect
- "joint_state_publisher" & "robot_state_publisher" for display our model
- "depthimage_to_laserscan" : this package helps kinect_depthimage convert to laserscan data
- "gmapping" i.e. slam algorithm : scan + odometry -> map data

#### Way to Launch
    roslaunch darrsm darrsm.launch
  
with 'gui:=true' : run rviz & joint_state_gui

