#include <ros/ros.h>
#include <move_base_msgs/MoveBaseAction.h>
#include <actionlib/client/simple_action_client.h>
#include <robot_localization/navsat_conversions.h>
#include <geometry_msgs/PointStamped.h>
#include <tf/transform_listener.h>

typedef actionlib::SimpleActionClient<move_base_msgs::MoveBaseAction> MoveBaseClient;

int main(int argc, char** argv){
ros::init(argc, argv, "gps_waypoint");

MoveBaseClient ac("move_base", true);
double latitude_goal, longitude_goal;

move_base_msgs::MoveBaseGoal goal;

tf::TransformListener listener;

//Get Longitude and Latitude goals from the parameter server
ros::param::get("latitude_goal", latitude_goal);
ros::param::get("longitude_goal", longitude_goal);
ROS_INFO("Received Latitude goal:%f", latitude_goal);
ROS_INFO("Received longitude goal:%f", longitude_goal);

double utm_x = 0;
double utm_y = 0;
std::string utm_zone;

//Convert Longituded / Latitude to UTM
RobotLocalization::NavsatConversions::LLtoUTM(latitude_goal, longitude_goal, utm_y, utm_x, utm_zone);
ROS_INFO("UTM Cord is %f, %f", utm_x, utm_y);

geometry_msgs::PointStamped UTM_point;
geometry_msgs::PointStamped map_point;
UTM_point.header.frame_id = "utm" ;
UTM_point.header.stamp = ros::Time::now() ;
UTM_point.point.x = utm_x;
UTM_point.point.y = utm_y;
UTM_point.point.z = 0;


//Transform UTM to odom frame
bool notDone = true;

while(notDone)
{
  try
  {
      UTM_point.header.stamp = ros::Time::now() ;
      listener.waitForTransform("odom", "utm", ros::Time::now(), ros::Duration(0.1));
      listener.transformPoint ("odom", UTM_point, map_point);
      notDone = false;
    }
    catch (tf::TransformException ex)
    {
      ROS_ERROR("%s",ex.what());
    //  return;
    }
}



goal.target_pose.header.frame_id = "odom";
goal.target_pose.header.stamp = ros::Time::now();

//Send goal to move_base
ROS_INFO("Goal in map frame is  %f, %f", map_point.point.x,map_point.point.y);
goal.target_pose.pose.position.x = map_point.point.x;
goal.target_pose.pose.position.y = map_point.point.y;
goal.target_pose.pose.orientation.w = 1.0;
ROS_INFO("Sending goal");
ac.sendGoal(goal);

ac.waitForResult();

if(ac.getState() == actionlib::SimpleClientGoalState::SUCCEEDED)
  ROS_INFO("Jackal has reached it's goal");
else
  ROS_INFO("Jackal was unable to reach it's goal");

return 0;
}
