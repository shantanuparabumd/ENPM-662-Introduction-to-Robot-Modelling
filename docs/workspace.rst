Workspace Setup
=====================================================================

Use the following to setup your  workspace

Inorder to setup a workspace you first need to source your ROS2 environment.


.. code-block:: bash

    source /opt/ros/galactic/setup.bash

Now you need to create a folder to act as a workspace.

.. code-block:: bash

    mkdir -p ~/test_ws/src
    cd ~/test_ws/src

Whenever you make changes to your package run this line to downlod all the dependencies before runnning a build.

.. code-block:: bash

    cd ..
    rosdep install -i --from-path src --rosdistro galactic -y

From the root of your workspace (~/test_ws) run the following command to build your workspace 

.. code-block:: bash

    colcon build

After a successfully build you will see new files and folders (build install log) in your workspace. 

.. code-block:: bash

    ├── build
    │   └── COLCON_IGNORE
    ├── install
    │   ├── COLCON_IGNORE
    │   ├── local_setup.bash
    │   ├── local_setup.ps1
    │   ├── local_setup.sh
    │   ├── _local_setup_util_ps1.py
    │   ├── _local_setup_util_sh.py
    │   ├── local_setup.zsh
    │   ├── setup.bash
    │   ├── setup.ps1
    │   ├── setup.sh
    │   └── setup.zsh
    ├── log
    │   ├── build_2023-07-02_22-49-14
    │   │   ├── events.log
    │   │   └── logger_all.log
    │   ├── COLCON_IGNORE
    │   ├── latest -> latest_build
    │   └── latest_build -> build_2023-07-02_22-49-14
    └── src

You have already sourced the underlay. However now you need to source the underlay.

.. code-block:: bash
    
    source install/local_setup.bash
