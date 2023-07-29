
Add URDF to Package
=====================================================================

Download URDF
-----------------------------------------------------------

Once you have create a URDF using Solidworks you will get a package which is compatible with ROS1. However to make it work with ROS2 we will need to make some changes.

.. note::
Make sure the name of the package from Solidworks Exporter is same as the package you created in ROS2. This will make it easy to deal with further changes.

You will get a folder with a similar structure

.. code-block:: bash


    ├── CMakeLists.txt
    ├── config
    │   └── joint_names_car.yaml
    ├── export.log
    ├── launch
    │   ├── display.launch
    │   └── gazebo.launch
    ├── meshes
    │   ├── back_left_axel.STL
    │   ├── back_left_lidar.STL
    │   ├── back_left_wheel.STL
    │   ├── back_right_axel.STL
    │   ├── back_right_lidar.STL
    │   ├── back_right_wheel.STL
    │   ├── back.STL
    │   ├── base_link.STL
    │   ├── front_left_axel.STL
    │   ├── front_left_lidar.STL
    │   ├── front_left_wheel.STL
    │   ├── front_right_axel.STL
    │   ├── front_right_lidar.STL
    │   ├── front_right_wheel.STL
    │   ├── front.STL
    │   ├── left.STL
    │   ├── right.STL
    │   └── top.STL
    ├── package.xml
    ├── textures
    └── urdf
        ├── car.csv
        └── car.urdf


Now you need to move the folders meshes and urdf to your ROS2 package.
After performing the above step your ROS2 package should look like follows.

.. code-block:: bash

    ├── CMakeLists.txt
    ├── include
    │   └── car
    ├── meshes
    │   ├── back_left_axel.STL
    │   ├── back_left_lidar.STL
    │   ├── back_left_wheel.STL
    │   ├── back_right_axel.STL
    │   ├── back_right_lidar.STL
    │   ├── back_right_wheel.STL
    │   ├── back.STL
    │   ├── base_link.STL
    │   ├── front_left_axel.STL
    │   ├── front_left_lidar.STL
    │   ├── front_left_wheel.STL
    │   ├── front_right_axel.STL
    │   ├── front_right_lidar.STL
    │   ├── front_right_wheel.STL
    │   ├── front.STL
    │   ├── left.STL
    │   ├── right.STL
    │   └── top.STL
    ├── package.xml
    ├── src
    └── urdf
        ├── car.csv
        └── car.urdf




To make sure these folders are visible to your build package you also need to change the CMakeLists as follows.

.. code-block:: cmake

    install(DIRECTORY
    urdf
    meshes
    DESTINATION share/${PROJECT_NAME}/
    )

We will be adding more directories later to make our robot spawn and add controllers.

Launch files
-----------------------------------------------------------------------------------

.. code-block:: bash

    cd ~/test_ws/src/package-name/

    # Example
    cd ~/test_ws/src/car/

Inorder to launch our robot model we need launch files that activate the following things.

* Gazebo Server

* Gazebo Client

* Spawn Entity

* Start the State Publisher

We will be downloading a few templates for ease.

.. code-block:: bash

    svn export https://github.com/shantanuparabumd/ENPM-662-Introduction-to-Robot-Modelling.git/trunk/templates/launch



We also need a empty world to spawn our robot in so we will download the world files.

.. code-block:: bash

    svn export https://github.com/shantanuparabumd/ENPM-662-Introduction-to-Robot-Modelling.git/trunk/templates/worlds


Your current package structure should look like follows.


.. code-block:: bash
    
    ├── CMakeLists.txt
    ├── include
    │   └── car
    ├── launch
    │   ├── robot_description_publisher.py
    │   ├── robot.launch.py
    │   └── spawn_robot_ros2.launch.py
    ├── meshes
    │   ├── back_left_axel.STL
    │   ├── back_left_lidar.STL
    │   ├── back_left_wheel.STL
    │   ├── back_right_axel.STL
    │   ├── back_right_lidar.STL
    │   ├── back_right_wheel.STL
    │   ├── back.STL
    │   ├── base_link.STL
    │   ├── front_left_axel.STL
    │   ├── front_left_lidar.STL
    │   ├── front_left_wheel.STL
    │   ├── front_right_axel.STL
    │   ├── front_right_lidar.STL
    │   ├── front_right_wheel.STL
    │   ├── front.STL
    │   ├── left.STL
    │   ├── right.STL
    │   └── top.STL
    ├── package.xml
    ├── src
    ├── urdf
    │   ├── car.csv
    │   └── car.urdf
    └── worlds
        └── empty_world.world


CMakeLists
--------------------------------------------------------------------

We have to make a few cahnages to the CMakeLists





Do not forget the add these folders to CMakeLists

.. code-block:: cmake

    install(DIRECTORY
        urdf
        meshes
        launch
        worlds
        DESTINATION share/${PROJECT_NAME}/
        )

* Add include DIRECTORY

    .. code-block:: cmake

        install(
            DIRECTORY include/car
            DESTINATION include
            )


* Add python files as executables

    .. code-block:: cmake

        install(
            PROGRAMS
            launch/robot_description_publisher.py
            DESTINATION lib/${PROJECT_NAME}
            )

* Add dependencies

    .. code-block:: cmake

        find_package(robot_state_publisher REQUIRED)
        find_package(xacro REQUIRED)
        find_package(tf2 REQUIRED)
        find_package(tf2_ros REQUIRED)


Package xml
-----------------------------------------------------------

A few more changes have to be made to package.xml file

.. code-block:: xml

    <buildtool_depend>ament_cmake</buildtool_depend>

    <build_depend>rosidl_default_generators</build_depend>

    <build_depend>xacro</build_depend>

    <depend>gazebo_ros_pkgs</depend>
    <depend>robot_state_publisher</depend>
    <depend>tf2</depend>
    <depend>tf2_ros</depend>
    

    <test_depend>ament_lint_auto</test_depend>
    <test_depend>ament_lint_common</test_depend>
    <test_depend>ament_cmake_gtest</test_depend>

    <export>
        <build_type>ament_cmake</build_type>
        <gazebo_ros gazebo_model_path="${prefix}/.." />
    </export>


Adding Color
---------------------------------------------------------------------

We can make use of the OGRE color format to make the colors visible in Gazebo


.. code-block:: xml

    <xacro:macro name="body_color">
        <visual>
        <material>
            <ambient>0.250980392156863 0.250980392156863 0.250980392156863 1</ambient>
            <diffuse>0.250980392156863 0.250980392156863 0.250980392156863 1</diffuse>
            <specular>0.1 0.1 0.1 1</specular>
            <emissive>0 0 0 0</emissive>
        </material>
        </visual>
    </xacro:macro>

.. code-block:: xml

    <gazebo reference="base_link">
        <xacro:body_color />
    </gazebo>

Launch Model
------------------------------------------------

Now we need to edit the launch files to fit to our package. Find the following lines and change it to your package name

File Name: `robot.launch.py`

.. code-block:: python

     world = os.path.join(
        get_package_share_directory('car'),
        'worlds',
        'empty_world.world'
    )

    package_path = get_package_share_directory('car')


File Name: `spawn_robot_ros2.launch.py`

.. code-block:: python

    ####### DATA INPUT ##########
    xacro_file = "car.urdf.xacro"
    #xacro_file = "box_bot.xacro"
    package_description = "car"
    # Position and orientation
    # [X, Y, Z]
    position = [0.0, 0.0, 0.5]
    # [Roll, Pitch, Yaw]
    orientation = [0.0, 0.0, 0.0]
    # Base Name or robot
    robot_base_name = "car"
    # Package Name
    pkg_name='car'
    ####### DATA INPUT END ##########

Once All the changes are done.
Build Your Package and Source Overlay


Launch your robot using

.. code-block:: bash

    ros2 launch car robot.launch.py
