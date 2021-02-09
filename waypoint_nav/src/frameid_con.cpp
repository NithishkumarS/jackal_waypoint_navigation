#include <ros/ros.h>
#include <sensor_msgs/NavSatFix.h>

class SubscribeAndPublish
{
public:
  SubscribeAndPublish()
  {
    //Topic you want to publish
    pub_ = n_.advertise<sensor_msgs::NavSatFix>("/gps2", 1);

    //Topic you want to subscribe
    sub_ = n_.subscribe("/gps/fix", 1, &SubscribeAndPublish::callback, this);
  }

  void callback(const sensor_msgs::NavSatFix& input)
  {
    sensor_msgs::NavSatFix output = input;
	output.header.frame_id = "navsat_link";	
    pub_.publish(output);
  }

private:
  ros::NodeHandle n_; 
  ros::Publisher pub_;
  ros::Subscriber sub_;

};//End of class SubscribeAndPublish

int main(int argc, char **argv)
{
  //Initiate ROS
  ros::init(argc, argv, "frameid_convertor");

  //Create an object of class SubscribeAndPublish that will take care of everything
  SubscribeAndPublish SAPObject;

  ros::spin();

  return 0;
}