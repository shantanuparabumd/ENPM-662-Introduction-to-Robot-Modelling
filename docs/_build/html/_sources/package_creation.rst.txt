Create a Package in ROS 2
=====================================================================

Create Package
---------------------------------------------------------------

To create a new package head to your workspace (ros2_ws). Then move to src folder .

.. code-block:: bash


   cd ~/ros2_ws/src


Run the below code line by changing `my_package` with the name of package you want to create.

.. code-block:: bash


   ros2 pkg create --build-type ament_cmake  my_package


Example:

.. code-block:: bash


   ros2 pkg create --build-type ament_cmake  car


You will get a similar folder structure once a package is created successfully.

.. code-block:: bash


   ├── CMakeLists.txt
   ├── include
   │   └── car
   ├── package.xml
   └── src




Build Package
--------------------------------------------------------------------

Inorder to build your package move to your workspace folder.

.. code-block:: bash


   cd ~/ros2_ws

Use the following command to build a selected package

.. code-block:: bash


   colcon build --packages-select my_package

Example:

.. code-block:: bash


   colcon build --packages-select car

Once the build is complete do not forget to source your setup. This will help to reflect all the changes you have made to your package.

.. code-block:: bash


   source install/local_setup.bash

