cmake_minimum_required(VERSION 3.0.3)
project(waypoint_nav)

set(CMAKE_CXX_FLAGS "-std=c++11")
set(CMAKE_CXX_STANDARD 11)
set(CMAKE_C_STANDARD 11)


find_package(catkin REQUIRED COMPONENTS
  roscpp
  rospy
  std_msgs
  roslib
  roslaunch
  actionlib
  move_base_msgs
  diagnostic_msgs
  diagnostic_updater
  geographic_msgs
  geometry_msgs
  message_filters
  message_generation
  nav_msgs
  roslint
  sensor_msgs
  std_msgs
  tf
  tf2
  tf2_geometry_msgs
  tf2_ros
)

catkin_package()
roslaunch_add_file_check(launch)

include_directories(
  ${catkin_INCLUDE_DIRS}
)

add_executable(laser2base_link src/laser2base_link.cpp)
add_executable(gps_waypoint src/gps_waypoint.cpp)
add_executable(frameid_convertor src/frameid_con.cpp)

target_link_libraries(gps_waypoint ${catkin_LIBRARIES})
target_link_libraries(laser2base_link ${catkin_LIBRARIES})
target_link_libraries(frameid_convertor ${catkin_LIBRARIES})

install(DIRECTORY  launch
  DESTINATION ${CATKIN_PACKAGE_SHARE_DESTINATION}
)
