cmake_minimum_required(VERSION 3.5)
project(mrs_automated_statistical_testing)

set(CMAKE_CXX_STANDARD 17)
set(CMAKE_CXX_STANDARD_REQUIRED ON)

add_definitions(-Wall)
add_definitions(-Wextra)

set(CATKIN_DEPENDENCIES
  cmake_modules
  roscpp
  rospy
  std_srvs
  mrs_msgs
  mrs_lib
  std_msgs
  mrs_uav_testing
  rostest
  )

find_package(catkin REQUIRED COMPONENTS
  ${CATKIN_DEPENDENCIES}
  )

catkin_package(
  LIBRARIES ${LIBRARIES}
  CATKIN_DEPENDS ${CATKIN_DEPENDENCIES}
  )

include_directories(
  ${catkin_INCLUDE_DIRS}
  ${Boost_INCLUDE_DIRS}
  )

## --------------------------------------------------------------
## |                           Testing                          |
## --------------------------------------------------------------

add_subdirectory(test)
