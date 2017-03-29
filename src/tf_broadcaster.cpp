#include <ros/ros.h>
#include <tf/transform_broadcaster.h>

int main(int argc, char** argv){
	ros::init(argc,argv,"robot_tf_publisher");
	ros::NodeHandle nh;

	ros::Rate r(100);

	tf::TransformBroadcaster broadcaster;

	while(nh.ok()){
		broadcaster.sendTransform(
			tf::StampedTransform(
				tf::Transform(tf::Quaternion(0,0,0,1),tf::Vector3(0.0,0.0,0.0)),
				ros::Time::now(),"kinect", "kinect_link"));

		r.sleep();
	}
}