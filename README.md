# Jackal Outdoor Waypoint Navigation



## Dependencies
```
Jackal simulator
Jackal desktop 
Jackal Navigation
```

## Instructions to use the repo
```
mkdir -p ros_ws/src
cd ros_ws/src
git clone https://github.com/jackal/jackal_desktop
git clone https://github.com/jackal/jackal_simulator.git
git clone https://github.com/jackal/jackal.git
git clone https://github.com/NithishkumarS/jackal_waypoint_navigation.git
cd ..
rosdep install --from-paths src --ignore-src -r -y
catkin_make
```

## Running the code

Using AMCL on a map without laser localization

```
roslaunch jackal_navigation amcl_demo.launch map_file:=/home/gamma-robot/ros_ws/src/outdoor_nav/waypoint_nav/map_files/Iribe_lobby_cropped.yaml  use_map_topic:=true
```

Visualize localization
```
roslaunch jackal_viz view_robot.launch config:=localization
```

## Waypoint node

```
rosparam set /longitude_goal -76.935847
rosparam set /latitude_goal 38.989960
rosrun waypoint_nav gps_waypoint
```

Running old bag files
```
rosbag play <name> --clock
rosparam set use_sim_time true
```
Increased inflatio radius in costmap_common_params.yaml to .5


Waypoints 
```
parking behind AV Williams: 
38.990683, -76.935968

AV williams
38.990599, -76.936570

Near wind tunnel
38.990180, -76.936594

Nearest:
38.989999, -76.935867
```

Things to chgange  in the jackal pakcgae:
```
costmap params:
inflation radius - 0.5 
scan_topic : scan

move_base.launch
remap /odom to /odometry/gps/filtered
```

SSH into the jackal robot

```
cd /etc/ros/kinetic/ros.d
nano base.launch
```

Added velodyne pcl launch in the base.launch
```
<include file=" $(find velodyne_pointcloud)/launch/VLP16_points.launch" />
```


Inorder to get the vlp-16 working with the exisiting jackal setup
```
change the network ip in the VLP-16 configuration to 192.168.131.0/24
```
This way you can use both the ethernet ports interchangably in the jackal.

