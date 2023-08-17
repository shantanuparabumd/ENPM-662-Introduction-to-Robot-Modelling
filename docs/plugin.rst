Plugin
=============================================================================================

Plugins are very helpful to add sensors and actuators to your Gazebo Model. We can create custom plugins or use existing plugins that are 
available.
Here we are going to use a LIDAR plugin to sense the environment of our robot using light rays.

To add a LIDAR we will be utilizing the link that we already created for LIDAR.
We will add the below code to our URDF file.

.. code-block:: xml

 <gazebo reference="add_name_of_your_link">
  <sensor name="lidar" type="ray">
    <pose>0.0 0.0 0.0 0 0 0</pose>
    <always_on>true</always_on>
    <visualize>true</visualize>
    <update_rate>5</update_rate>
    <ray>
      <scan>
        <horizontal>
          <samples>360</samples>
          <resolution>1.00000</resolution>
          <min_angle>0.000000</min_angle>
          <max_angle>6.280000</max_angle>
        </horizontal>
      </scan>
      <range>
        <min>0.120000</min>
        <max>3.5</max>
        <resolution>0.015000</resolution>
      </range>
      <noise>
        <type>gaussian</type>
        <mean>0.0</mean>
        <stddev>0.01</stddev>
      </noise>
    </ray>
    <plugin name="scan" filename="libgazebo_ros_ray_sensor.so">
      <ros>
        <remapping>~/out:=scan</remapping>
      </ros>
      <output_type>sensor_msgs/LaserScan</output_type>
      <frame_name>add_name_of_your_link</frame_name>
    </plugin>
  </sensor>
  </gazebo>


Build your project and use the Launch script to start RVIZ 2.

Click on the Add button on the bottom left corner of the screen.

.. image:: images/Add.png
  :width: 700
  :alt: Add Laser Topic


Select the LaserScan topic from the list.

.. image:: images/laser_topic.png
  :width: 700
  :alt: Add Laser Topic

Use the following configurations for Laser Scanner to work. You can make changes once you are comfortable.
Make sure you change the topic name to the topic of your laser scanner.

.. image:: images/rviz_laser_config.png
  :width: 700
  :alt: Add Laser Topic