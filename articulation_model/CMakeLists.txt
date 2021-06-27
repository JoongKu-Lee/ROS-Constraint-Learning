cmake_minimum_required(VERSION 3.0.2)
project(articulation_model)

find_package(catkin REQUIRED COMPONENTS
            std_msgs           
            roscpp
            rospy
            sensor_msgs
            geometry_msgs
            visualization_msgs
            tf
            tf2
            gaussian_process
            articulation_msgs
            # icp
            # bullet
            )

find_package(Eigen3 REQUIRED)

catkin_package(
            INCLUDE_DIRS include
            LIBRARIES ${PROJECT_NAME}
            CATKIN_DEPENDS
            std_msgs           
            roscpp
            rospy
            sensor_msgs
            geometry_msgs
            visualization_msgs
            tf
            tf2
            articulation_msgs
            # icp
            # bullet
            DEPENDS EIGEN3
)

include_directories(
    include
    ${catkin_INCLUDE_DIRS}
    ${EIGEN3_INCLUDE_DIRS}  
    ${GSL_INCLUDE_DIRS}
)

## Declare a C++ library
add_library(${PROJECT_NAME} SHARED
    src/utils.cpp
    src/models/generic_model.cpp
    src/models/prismatic_model.cpp
    src/models/rigid_model.cpp
    src/models/pca_gp_model.cpp
    src/models/factory.cpp
    src/models/rotational_model.cpp
)
target_link_libraries(${PROJECT_NAME} ${catkin_LIBRARIES})

add_executable(model_learner_msg src/model_learner_msg.cpp)
target_link_libraries(model_learner_msg 
    ${catkin_LIBRARIES}
    ${PROJECT_NAME}
    ${GSL_LIBRARIES}
    )

add_executable(model_learner_srv src/model_learner_srv.cpp)
    target_link_libraries(model_learner_srv 
        ${catkin_LIBRARIES}
        ${PROJECT_NAME}
        ${GSL_LIBRARIES}
        )
