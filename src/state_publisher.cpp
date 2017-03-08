#include <string>
#include <ros/ros.h>
#include <sensor_msgs/JointState.h>
#include <tf/transform_broadcaster.h>

int main(int argc, char** argv){

	ros::init(argc,argv, "state_publisher");
	ros::NodeHandle nh;
	ros::Publisher joint_pub = 
		nh.advertise<sensor_msgs::JointState>("joint_states", 1);

	tf::TransformBroadcaster broadcaster;

	ros::Rate loop_rate(30);

	const double degree = M_PI/180;

	//robot state
	double inc=0.005, base_upper_inc=0.005,upper_kinect_inc=0.005,
			base_wheel1_inc=0.005,base_wheel2_inc=0.005;
	double angle=0, base_upper=0,upper_kinect=0,base_wheel1=0,base_wheel2=0;

	geometry_msgs::TransformStamped odom_trans;
	sensor_msgs::JointState joint_state;
	odom_trans.header.frame_id = "odom";
	odom_trans.child_frame_id = "base_link";

	while(ros::ok()){
		//update joint_state
		joint_state.header.stamp = ros::Time::now();
		joint_state.name.resize(4);
		joint_state.position.resize(4);
		joint_state.name[0] = "B2U";
		joint_state.position[0] = base_upper;
		joint_state.name[1] = "U2K";
		joint_state.position[1] = upper_kinect;
		joint_state.name[2] = "B2W1";
		joint_state.position[2] = base_wheel1;
		joint_state.name[3] = "B2W2";
		joint_state.position[3] = base_wheel2;


		//update transform
		odom_trans.header.stamp = ros::Time::now();
		odom_trans.transform.translation.x = cos(angle);
		odom_trans.transform.translation.y = sin(angle);
		odom_trans.transform.translation.z = 0.;
		odom_trans.transform.rotation = tf.createQuaternionMsgFromYaw(angle);

		//send the joint state and transfrom
		joint_pub.publish(joint_state);
		broadcaster.sendTransform(odom_trans);

		//Create new robot state
		

		loop_rate.sleep();
	}
	return 0;
}