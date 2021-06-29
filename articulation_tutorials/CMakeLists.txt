cmake_minimum_required(VERSION 3.0.2)
project(articulation_tutorials)


find_package(catkin REQUIRED COMPONENTS
  roscpp
  rospy
  std_msgs
  geometry_msgs
  articulation_model
)

find_package(Eigen3 REQUIRED)


catkin_package(
#  INCLUDE_DIRS include
#  LIBRARIES articulation_tutorials
 CATKIN_DEPENDS roscpp rospy std_msgs geometry_msgs
#  DEPENDS system_lib
)

include_directories(
  ${catkin_INCLUDE_DIRS}
  ${EIGEN3_INCLUDE_DIRS}  
)


add_executable(model_fitting_demo cpp_model_fitting/model_fitting_demo.cpp)
target_link_libraries(model_fitting_demo 
    ${catkin_LIBRARIES}
    ${GSL_LIBRARIES}
    )


add_executable(sub_and_model_fitting cpp_model_fitting/sub_and_model_fitting.cpp)
target_link_libraries(sub_and_model_fitting 
    ${catkin_LIBRARIES}
    ${GSL_LIBRARIES}
    )