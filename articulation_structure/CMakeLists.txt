cmake_minimum_required(VERSION 3.0.2)
project(articulation_structure)


find_package(catkin REQUIRED COMPONENTS
  message_generation
  roscpp
  rospy
  std_msgs
  articulation_model
  articulation_msgs
  hogman_minimal
)

find_package(Eigen3 REQUIRED)

add_message_files(
  FILES
  PoseStampedIdMsg.msg
  )

generate_messages(
  DEPENDENCIES
  std_msgs
  geometry_msgs
)

catkin_package(
#  INCLUDE_DIRS include
#  LIBRARIES articulation_tutorials
 CATKIN_DEPENDS roscpp rospy std_msgs message_runtime
#  DEPENDS system_lib
)

include_directories(
  ${catkin_INCLUDE_DIRS}
  ${EIGEN3_INCLUDE_DIRS}  
)

add_executable(graph_learner src/graph_learner.cpp src/structure_learner_base.cpp src/utils.cpp src/structs.cpp src/predict_pose.cpp src/hogman_wrapper.cpp)
target_link_libraries(graph_learner
${catkin_LIBRARIES}
${GSL_LIBRARIES}
)

add_executable(structure_learner src/structure_learner_srv.cpp src/ArticulatedObject.cpp src/hogman_wrapper.cpp src/structs.cpp src/utils.cpp )
target_link_libraries(structure_learner
${catkin_LIBRARIES}
${GSL_LIBRARIES}
)
