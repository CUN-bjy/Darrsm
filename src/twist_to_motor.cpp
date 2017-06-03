#include "ros/ros.h"
#include "std_msgs/Float32.h"
#include "std_msgs/Float64.h"

#include <dynamixel_workbench_msgs/SetDirection.h>
#include <tf/transform_broadcaster.h>
#include <nav_msgs/Odometry.h>
#include <math.h>


#define wheel_radius 0.0635
#define CM2wheel 0.19238

class TwistToMotors
{

public:
	TwistToMotors();
	void spin();

private:
	ros::NodeHandle n;

	ros::Subscriber cmd_vel_sub;
	ros::ServiceClient wheel_control_client_;

	float left;
	float right;

	float ticks_since_target;
	double timeout_ticks;

	double w;
	double rate;

	float dx,dy,dr;


	void init_variables();
	void get_parameters();

	void spinOnce();
	void twistCallback(const geometry_msgs::Twist &twist_aux);

};

TwistToMotors::TwistToMotors()
{
	init_variables();
	get_parameters();
	
	ROS_INFO("Started Twist to Motor node");
	
	cmd_vel_sub = n.subscribe("cmd_vel",10, &TwistToMotors::twistCallback, this);
	
	wheel_control_client_ = n.serviceClient<dynamixel_workbench_msgs::SetDirection>("/dynamixel_workbench_tutorials/wheel");
}

void TwistToMotors::init_variables()
{
	left = 0;
	right = 0;

	dx = dy = dr =0;

	w = CM2wheel ;
	rate = 50;
	timeout_ticks = 2;

}


void TwistToMotors::get_parameters()
{
    if(n.getParam("rate", rate)){
	 
		ROS_INFO_STREAM("Rate from param" << rate);	       
	}


	
    if(n.getParam("timeout_ticks", timeout_ticks)){
	 
		ROS_INFO_STREAM("timeout_ticks from param" << timeout_ticks);	       
	}

	
    if(n.getParam("base_width", w)){
	 
		ROS_INFO_STREAM("Base_width from param" << w);	       
	}
}


void TwistToMotors::spin()
{
	ros::Rate r(rate);
	ros::Rate idle(10);

	ros::Time then = ros::Time::now();
	
	ticks_since_target = timeout_ticks;


	while (ros::ok())
	{
		while (ros::ok() && (ticks_since_target <= timeout_ticks))	
		{		
			spinOnce();
			r.sleep();
		}
		ros::spinOnce();
        idle.sleep();	
	}
}

void TwistToMotors::spinOnce()
{


        // dx = (l + r) / 2
        // dr = (r - l) / w

	
	right = (( 0.5 * dx ) + (dr * w /2))/wheel_radius;
	left = (( 0.5 * dx ) - (dr * w /2))/wheel_radius;


//	ROS_INFO_STREAM("right = " << right << "\t" << "left = " << left << "dr"<< dr);


	dynamixel_workbench_msgs::SetDirection srv;

	srv.request.right_wheel_velocity = right;
	srv.request.left_wheel_velocity = left;

	wheel_control_client_.call(srv);

	ticks_since_target += 1;

	ros::spinOnce();
}

void TwistToMotors::twistCallback(const geometry_msgs::Twist &msg)
{

	ticks_since_target = 0;
	
	dx = msg.linear.x;
	dy = msg.linear.y;
	dr = msg.angular.z;

}


int main(int argc, char **argv)
{

	ros::init(argc, argv,"twist_to_motor");
	TwistToMotors obj;

	obj.spin();


}