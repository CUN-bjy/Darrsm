TwistToMotors::TwistToMotors()
{
	init_variables();
	get_parameters();

	ROS_INFO("Started Twist to Motor node");

	cmd_vel_sub = n.subscribe("cmd_vel_mux/input/teleop",10,&TwistToMotors::twistCallback,this);
	pub_lmotor = n.advertise<std_msgs::Float32>("lwheel_vtarget",50);
	pub_rmotor = n.advertise<std_msgs::Float32>("rwheel_vtarget",50);

}

void TwistToMotors::twistCallback(const geometry_msgs::Twist &msg)
{
	ticks_since_target = 0;
	dx = msg.linear.x;
	dy = msg.linear.y;
	dr = msg.angular.z;

	right = (1.0 * dx) + (dr * w/2);
	left = (1.0 *dx) - (dr * w/2);

	std_msgs::Float32 left_;
	std_msgs::Float32 right_;

	left_.data = left;
	right_.data = right;

	pub_lmotor.publish(left_);
	pub_rmotor.publish(right_);

	ticks_since_target += 1;
	ros::spinOnce();
}