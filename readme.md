# FELIS Control
This is the autopilot software to control FALCON FELIS (TM) with ROS noetic.     
Product info: http://www.falcon.com.cn/zdjszc/153.html

The project is working-in-progress. 

# Build
---
## Init workspace 

    catkin_init_workspace
## Make: 

    catkin build
or

    catkin_make

# Usage
---
## Start ROS master: 

    roscore
## Launch chassisctrl

    rosrun chassisctrl chassisctrl_reciver
    rosrun chassisctrl chassisctrl_sender