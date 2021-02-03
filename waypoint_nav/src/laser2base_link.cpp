#include <ros/ros.h>
#include <tf2/LinearMath/Quaternion.h>
#include <tf2_ros/transform_broadcaster.h>
#include <geometry_msgs/TransformStamped.h>
#include <nav_msgs/Odometry.h>

std::string turtle_name;

void poseCallback(const nav_msgs::Odometry::ConstPtr& msg){
  static tf2_ros::TransformBroadcaster br;
  geometry_msgs::TransformStamped transformStamped;
  
  transformStamped.header.stamp = ros::Time::now();
  transformStamped.header.frame_id = "base_link";
  transformStamped.child_frame_id = "base_laser";
  transformStamped.transform.translation.x = 0.2;
  transformStamped.transform.translation.y = 0.0;
  transformStamped.transform.translation.z = 0.2;
  // tf2::Quaternion q;
  // q.setRPY(0, 0, msg->theta);
  transformStamped.transform.rotation.x = 0;
  transformStamped.transform.rotation.y = 0;
  transformStamped.transform.rotation.z = 0;
  transformStamped.transform.rotation.w = 1.0;

  br.sendTransform(transformStamped);
}

int main(int argc, char** argv){
  ros::init(argc, argv, "laser2mid_mount_broadcaster");
    
  ros::NodeHandle node;
  ros::Subscriber sub = node.subscribe("/odometry/filtered", 10, &poseCallback);

  ros::spin();
  return 0;
};