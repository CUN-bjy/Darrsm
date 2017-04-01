cmake_minimum_required(VERSION 2.8.3)
project(darrsm)

find_package(catkin REQUIRED COMPONENTS
  roscpp
  tf
  nav_msgs
  dynamixel_workbench_msgs
)

catkin_package(
)


include_directories(include
	${catkin_INCLUDE_DIRS}
)


#----------------------------tf_broadcaster----------------------
add_executable(tf_broadcaster src/tf_broadcaster.cpp)
target_link_libraries(tf_broadcaster ${catkin_LIBRARIES})


#--------------------------odometry_publisher---------------------
add_executable(odometry_publisher src/odometry_publisher.cpp)

if(nav_msgs_EXPORTED_TARGETS)
  add_dependencies(odometry_publisher ${nav_msgs_EXPORTED_TARGETS})
endif()

target_link_libraries(odometry_publisher ${catkin_LIBRARIES})

install(TARGETS odometry_publisher
  ARCHIVE DESTINATION ${CATKIN_PACKAGE_LIB_DESTINATION}
  LIBRARY DESTINATION ${CATKIN_PACKAGE_LIB_DESTINATION}
  RUNTIME DESTINATION ${CATKIN_PACKAGE_BIN_DESTINATION})