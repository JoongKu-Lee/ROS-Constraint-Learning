cmake_minimum_required(VERSION 3.0.2)
project(articulation_msgs)

## Compile as C++11, supported in ROS Kinetic and newer
# add_compile_options(-std=c++11)

## Find catkin macros and libraries
## if COMPONENTS list like find_package(catkin REQUIRED COMPONENTS xyz)
## is used, also find other catkin packages
find_package(catkin REQUIRED COMPONENTS
  message_generation
  roscpp
  rospy
  std_msgs
  geometry_msgs
  sensor_msgs
  visualization_msgs
)

add_message_files(
  FILES
  ArticulatedObjectMsg.msg
  ModelMsg.msg
  ParamMsg.msg
  TrackMsg.msg
  )

add_service_files(
  FILES
  AlignModelSrv.srv
  ArticulatedObjectSrv.srv
  GetModelPriorSrv.srv
  SetModelPriorSrv.srv
  TrackModelSrv.srv
)

generate_messages(
  DEPENDENCIES
  std_msgs
  geometry_msgs
  sensor_msgs
  visualization_msgs
)

catkin_package(
    CATKIN_DEPENDS
    roscpp
    rospy
    std_msgs
    geometry_msgs
    sensor_msgs
    visualization_msgs
    message_runtime
)