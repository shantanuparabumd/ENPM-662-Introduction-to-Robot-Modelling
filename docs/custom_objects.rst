Custom Object
=========================================================================================

When working on your project you will be creating new environments for your robots.
For this you will be using existing models in Gazebo or making some custom objects.
In order to create new object models and add them to Gazebo environment follow the given process.

1. Create part or assembly in Solidworks

As done previously create assembly of the required custom object.

2. Export to URDF

Use previous tutorials to export the model to URDF

3. Convert the model to SDF

 * Move the urdf model along with the meshes to your :guilabel:`Ubuntu (ROS System)`.
 * Go to the folder containing the :guilabel:`model.urdf` file.
 * Run the below command to convert the :guilabel:`urdf` file to :guilabel:`sdf` file.

.. code-block:: bash

    gz sdf -p /model.urdf > /model.sdf

4. Create a model folder

Your model folder will consist of 2 files and 1 folder.
The folder name will be :guilabel:`meshes` and will contain the :guilabel:`.STL` meshes of the object.
:guilabel:`model.config` file will consist of the version,maintainer,description of the object.

You can use the below contents for making the config file by pasting the below lines in your file.

.. code-block:: xml
    :emphasize-lines: 7

    <?xml version="1.0"?>

    <model>
    <name>Model_Name</name>
    <version>1.0</version>
    
    <sdf version="1.1">model.sdf</sdf>

    <author>
        <name>Your Name</name>
        <email>Your Mail ID</email>
    </author>

    <description>
        Description of Your Model
    </description>
    </model>

The highlingted line will have the name of your :guilabel:`.sdf` file.

:guilabel:`model.sdf` will consist of the sdf file from above step.

Your final folder structure will be as follow

.. code-block:: bash

    -- model(your_folder_name)
        -- meshes
        -- model.config
        -- model.sdf

5. Editing SDF file

Make sure that the reference to the meshes is correct in the SDF file.
Use the below line of code for reference.

.. code-block:: xml
    :emphasize-lines: 3

        <mesh>
            <scale>1 1 1</scale>
            <uri>model://your_folder_name/meshes/part_name.STL</uri>
        </mesh>

6. Add the model to Gazebo models.

Move to the models urdf folder and run the following command to copy the  model to the 
Gazebo models location.

.. code-block:: bash

    cp -r your_folder_name/ ~/.gazebo/models


Once you run Gazebo you should be able to see the model in the model list in Gazebo.

You can add this model to the environment by dragging it into the screen. You can save this world and use it again wheever needed.
See the next tutorial for understanding world saving.