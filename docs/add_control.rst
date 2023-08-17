Controllers
=====================================================================

Install dependencies
-------------------------------------------------------------

In your home folder run the following command to install dependencies for ros controllers

.. code-block:: bash

    sudo apt install ros-galactic-ros2-control ros-galactic-ros2-controllers ros-galactic-gazebo-ros2-control

CMakeLists and Package XML
----------------------------------------------------------------

Add dependencies to CMakeLists

.. code-block:: cmake

    find_package(ros2_control REQUIRED)

Add dependencies to Package xml

.. code-block:: xml

    <depend>ros2_control</depend>


URDF

----------------------------------------------------------------------

Add the controllers for your joints.

.. code-block:: xml

    <ros2_control name="GazeboSystem" type="system">
    <hardware>
        <plugin>gazebo_ros2_control/GazeboSystem</plugin>
    </hardware>
    # Velocity Controllers

    <joint name="back_right_wheel_joint">
        <command_interface name="velocity">
            <param name="min">-1000.0</param>
            <param name="max">1000.0</param>
        </command_interface>
        <state_interface name="position"/>
        <state_interface name="velocity"/>
    </joint>

   # Position Controller
    <joint name="front_left_axel_joint">
        <command_interface name="position">
            <param name="min">-3.14</param>
            <param name="max">3.14</param>
        </command_interface>
        <state_interface name="position"/>
        <state_interface name="velocity"/>
    </joint>

    </ros2_control> 


You also need to add Gazebo Plugin for the Controller

.. code-block:: xml

        <gazebo>
            <plugin filename="libgazebo_ros2_control.so" name="gazebo_ros2_control">
                <parameters>$(find test_package)/config/control.yaml</parameters>
            </plugin>
        </gazebo>

In the `parameters` tag we need to pass a control.yaml file to setup the controllers.

Control Description
-----------------------------------------------------------------------------------

In the root of the package create a folder config.

.. code-block:: xml

        mkdir config
        cd config
        touch control.yaml


You may edit the control.yaml file as follows to add controller description.


.. code-block:: xml

        controller_manager:
        ros__parameters:
            update_rate: 1000  # Hz

            use_sim_time: true

            position_controller:
            type: position_controllers/JointGroupPositionController

            joint_state_broadcaster:
            type: joint_state_broadcaster/JointStateBroadcaster

            velocity_controller:
                type: velocity_controllers/JointGroupVelocityController



        position_controller:
        ros__parameters:
            joints:
            - front_left_axel_joint
            interface_name: position
            command_interfaces:
            - position
            state_interfaces:
            - position
            - velocity


        velocity_controller:
        ros__parameters:
            joints:
            - front_left_wheel_joint
            interface_name: velocity
            command_interfaces:
            - velocity
            state_interfaces:
            - position
            - velocity


You may now build and Overlay your package

Now launch the robot model.


Start the Controller
----------------------------------------------------------------------------------------

Run the following commands terminal to start the controllers.

.. code-block:: bash

    ros2 control load_controller --set-state start joint_state_broadcaster

    ros2 control load_controller --set-state start velocity_controller

    ros2 control load_controller --set-state start position_controller


Publish commands

-------------------------------------------------------------------------------

To publish the data to the joints use the following commands

.. code-block:: bash

    ros2 topic pub /velocity_controller/commands std_msgs/msg/Float64MultiArray "{data: [1.0,-1.0,1.0,-1.0],layout: {dim:[], data_offset: 1"}}

    ros2 topic pub /position_controller/commands std_msgs/msg/Float64MultiArray "{data: [0.3,0.3,0.3,0.3],layout: {dim:[], data_offset: 1"}}

