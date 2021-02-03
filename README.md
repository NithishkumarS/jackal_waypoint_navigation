# Jackal Outdoor Waypoint Navigation



##Dependencies
```
Jackal simulator
Jackal desktop 

jackal Navigation
```

## Instructions to use the repo
```
mkdir -p ros_ws/src
cd ros_ws/src
git clone https://github.com/jackal/jackal_desktop
git clone https://github.com/jackal/jackal_simulator.git
git clone https://github.com/jackal/jackal.git
git clone https://github.com/NithishkumarS/jackal_waypoint_navigation.git
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


