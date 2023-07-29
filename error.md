1 Package Not Found 
Solution: Check the package.xml file for build dependencies

check for the below tag

<export>
    <build_type>ament_cmake</build_type>
  </export>

2 Model is loaded but not visible in Gazebo

Solution: Head to the package.xml file
Add the below tag

<export>
    <build_type>ament_cmake</build_type>
    # The following tag tell yours package the loaction of your models
    <gazebo_ros gazebo_model_path="${prefix}/.." />
  </export>


3 Joint Position is Published but Joints not moving

Soli=ution: Open urdf file of robot
Check for values of limit,effor,velocity make them non zero
<limit
      lower="-3.14"
      upper="3.14"
      effort="100"
      velocity="1000" />