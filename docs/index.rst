.. ENPM 662: Introduction to Robot Modelling documentation master file, created by
   sphinx-quickstart on Sun Jul  2 18:28:15 2023.
   You can adapt this file completely to your liking, but it should at least
   contain the root `toctree` directive.

Project 1 Documentation
=====================================================================

.. toctree::
   :maxdepth: 2
   :caption: Contents:

   install_ubuntu
   workspace
   package_creation
   add_urdf
   add_control
   support
   

.. Indices and tables
.. ==================

.. * :ref:`genindex`
.. * :ref:`modindex`
.. * :ref:`search`

This documentation will help you walkthrough the basics of getting a custom robot working in Gazebo, using ROS2.
This will consist of the following steps.

* Creating a Robot Model in Solidworks

* Exporting Model to URDF

* Installing Ubuntu 20.04 (Focal Fossa)

* Installing ROS 2 Galactic

* Setting Up Environment

* Setting Up Workspace

* Creating a Package 

* Adding URDF to Package and Launching in Gazebo

* Adding Controllers to Robot

* Writing a Script to Control the Robot


Software Requirements and Extensions
-----------------------------------------------------------------------

* Solidworks
   To create a model of your robot

* SW2URDF Exporter
   To export your model to URDF file format

* Ubuntu 20.04
   This is our base operating system for stable builds of our package

* ROS2 Galactic
   This is a stable version of ROS2 which works well for our project

* Gazebo 
   This is a physics simulation engine we will be using to simulate our robot



.. Subsection

.. You can use ``backticks`` for showing ``highlighted`` code.


.. .. highlight:: bash
..    :linenothreshold: 1

.. A cool bit of code::

..    #!/bin/bash
..    # Some cool Bash code
..    echo ${BASH_VERSINFO[*]}
..    ros2 pkg create --build-type ament_cmake <package_name>


.. .. code-block:: xml


..    <joint
..     name="front_right_lidar_joint"
..     type="fixed">
..     <origin
..       xyz="2.1064 -1.1064 1.92"
..       rpy="0 0 0" />
..     <parent
..       link="base_link" />
..     <child
..       link="front_right_lidar" />
..     <axis
..       xyz="0 0 0" />
..   </joint>