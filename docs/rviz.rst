RVIZ
=====================================================================

Visualization is a very important concept in robot simulation. In order to visualize the various sensor inputs like LIDAr, Camera etc. 
we will be using RVIZ 2 a software for visualizing the ROS2 topics. 

RVIZ 2 requires setup and configurations that might be overwhelming at this stage so to help out we will be using a few templates.


We move to the root of our package and then run the code below to download the templates.

.. code-block:: bash

    cd ~/test_ws/src/package-name/

    # Example
    cd ~/test_ws/src/test_package/

.. code-block:: bash

    svn export https://github.com/shantanuparabumd/ENPM-662-Introduction-to-Robot-Modelling.git/trunk/templates/rviz

.. code-block:: bash

    svn export https://github.com/shantanuparabumd/ENPM-662-Introduction-to-Robot-Modelling.git/trunk/templates/launch


File Description:

    * The :guilabel:`gazebo.launch.py` will launch the Gazebo environment and will load the controllers.
    * The :guilabel:`display.launch.py` will launch RVIZ 2 along with the neccessary setup for the Robot Visualization.
    * The :guilabel:`debug.launch.py` will launch both Gazebo and RVIZ 2 together.

Use any of the abouve launch files as required.


Laser Visualization
----------------------------------------------------------------------------

