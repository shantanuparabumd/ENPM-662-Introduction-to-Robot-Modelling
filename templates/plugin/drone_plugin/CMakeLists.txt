cmake_minimum_required(VERSION 3.8)
project(drone_plugin)

if(CMAKE_COMPILER_IS_GNUCXX OR CMAKE_CXX_COMPILER_ID MATCHES "Clang")
  add_compile_options(-Wall -Wextra -Wpedantic)
endif()

# find dependencies
find_package(ament_cmake REQUIRED)
# uncomment the following section in order to fill in
# further dependencies manually.
# find_package(<dependency> REQUIRED)
find_package(geometry_msgs REQUIRED)
find_package(rosidl_default_generators REQUIRED)
find_package(tf2 REQUIRED)
find_package(tf2_ros REQUIRED)
find_package(gazebo REQUIRED)
find_package(gazebo_ros REQUIRED)


install(
    DIRECTORY include/
    DESTINATION include
    )

install(DIRECTORY
    src
    msg
    DESTINATION share/${PROJECT_NAME}/
)

add_library(drone SHARED
  src/drone_plugin_.cpp
)

rosidl_generate_interfaces(${PROJECT_NAME}
  "msg/MotorSpeed.msg"
  
)
rosidl_target_interfaces(drone ${PROJECT_NAME} "rosidl_typesupport_cpp")

ament_export_dependencies(rosidl_default_runtime)

target_include_directories(drone PUBLIC include)

ament_target_dependencies(drone
  "gazebo_ros"
  "tf2_ros"
)


ament_export_libraries(drone)

install(TARGETS
  drone
  ARCHIVE DESTINATION lib
  LIBRARY DESTINATION lib
  RUNTIME DESTINATION bin)


  install(
  PROGRAMS
  scripts/minimal_publsiher.py
  DESTINATION lib/${PROJECT_NAME}
)


if(BUILD_TESTING)
  find_package(ament_lint_auto REQUIRED)
  # the following line skips the linter which checks for copyrights
  # uncomment the line when a copyright and license is not present in all source files
  #set(ament_cmake_copyright_FOUND TRUE)
  # the following line skips cpplint (only works in a git repo)
  # uncomment the line when this package is not in a git repo
  #set(ament_cmake_cpplint_FOUND TRUE)
  ament_lint_auto_find_test_dependencies()
endif()

ament_package()
