cmake_minimum_required(VERSION 2.8.3)
project(darrsm)

find_package(catkin REQUIRED COMPONENTS
  roscpp
  tf
)

catkin_package(
)

###########
## Build ##
###########

## Specify additional locations of header files
## Your package locations should be listed before other locations
include_directories(include
	${catkin_INCLUDE_DIRS}
)

add_executable(tf_broadcaster src/tf_broadcaster.cpp)
target_link_libraries(tf_broadcaster ${catkin_LIBRARIES})