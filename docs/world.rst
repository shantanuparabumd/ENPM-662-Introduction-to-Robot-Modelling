Creating and Saving a world in Gazebo
=====================================================================


Use the below tutorial to understand how to create a world using gazebo

`Gazebo Tutorial <https://classic.gazebosim.org/tutorials?tut=build_world&ver=1.9#LoadingaWorld>`_


Your world will be saved in a SDF format like test_world.sdf. You can rename the world file to
test_world.world.

Add this file to the wordls folder in your project package.

Make sure the world folder is added to CMakeLists.txt

.. code-block:: cmake
    :emphasize-lines: 5

    install(DIRECTORY
        urdf
        meshes
        launch
        worlds
        config
        DESTINATION share/${PROJECT_NAME}/
        )




Now for your robot to spawn in the new world edit the gazebo.launch.pu file 

.. code-block:: python
    :emphasize-lines: 5

    # Get the location for empty world
    world = os.path.join(
        get_package_share_directory('quadruped_robot'),
        'worlds',
        'test_world.world'
    )

Build and run your project and the robot will spawn in new environment.