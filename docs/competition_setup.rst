Competition Setup
=====================================================================

Follow the given steps to setup the competition arena for your final video.

In your root folder download the competiton folder using the given command.

.. code-block:: bash

    svn export https://github.com/shantanuparabumd/ENPM-662-Introduction-to-Robot-Modelling.git/trunk/templates/competition



Add the competition folder to your CMakeLists.txt file 


.. code-block:: cmake
    :emphasize-lines: 6

    install(DIRECTORY
        urdf
        meshes
        launch
        worlds
        competition
        DESTINATION share/${PROJECT_NAME}/
        )

Move to the competition folder and run the following command to copy the arena model to the 
Gazebo models location.

.. code-block:: bash

    cd ~/test_ws/src/package-name/competition

.. code-block:: bash

    cp -r arena/ ~/.gazebo/models


Download the competition.launch file to your launch folder by moving into the launch folder and 
running the below command.

.. code-block:: bash

    svn export https://github.com/shantanuparabumd/ENPM-662-Introduction-to-Robot-Modelling.git/trunk/templates/template4/competition.launch.py


Make sure you change the `package_name` to name of your package whereever required.

Also,change the spawn location and orientation of your robot such that the robot is spawned on the track.