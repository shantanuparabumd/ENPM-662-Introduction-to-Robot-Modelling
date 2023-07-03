
Add URDF to Package
=====================================================================

Download URDF
-----------------------------------------------------------

Once you have create a URDF using Solidworks you will get a package which is compatible with ROS1. However to make it work with ROS2 we will need to make some changes.

Note:
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



