# Darrsm

This project is for the capstone design in 2016/2nd~2017/1st.

Darrsm is that 'Disaster and Rescue Robot Simulation & modeling'.


##nessesary for user to launch this project.
- "openni_launch" for running kinect
- "joint_state_publisher" & "robot_state_publisher" for display our model
- "depthimage_to_laserscan" : this package helps kinect_depthimage convert to laserscan data
- "gmapping" i.e. slam algorithm : scan + odometry -> map data

##Way to launch
"`
roslaunch darrsm darrsm.launch

"`
gui:=true
- run rviz & joint_state_gui