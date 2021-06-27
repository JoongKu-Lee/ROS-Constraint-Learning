cmake_minimum_required(VERSION 3.0.2)
project(gaussian_process)

find_package(catkin REQUIRED COMPONENTS
  roscpp
  rospy
  std_msgs
)

catkin_package(
 INCLUDE_DIRS include
 LIBRARIES gaussian_process
 CATKIN_DEPENDS roscpp rospy std_msgs
#  DEPENDS system_lib
)

include_directories(
  include
  ${catkin_INCLUDE_DIRS}
)

# Declare a C++ library
add_library(${PROJECT_NAME}
  src/covarianceFunctions.cpp
  src/SingleGP.cpp
)
