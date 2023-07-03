.. ENPM 662: Introduction to Robot Modelling documentation master file, created by
   sphinx-quickstart on Sun Jul  2 18:28:15 2023.
   You can adapt this file completely to your liking, but it should at least
   contain the root `toctree` directive.

Welcome to ENPM 662: Introduction to Robot Modelling's documentation!
=====================================================================

.. toctree::
   :maxdepth: 2
   :caption: Contents:

   install
   support
   install_ros2
   install_ubuntu
   env_setup
   package_creation

.. Indices and tables
.. ==================

.. * :ref:`genindex`
.. * :ref:`modindex`
.. * :ref:`search`

Title
=====

Section
-------

Subsection

You can use ``backticks`` for showing ``highlighted`` code.


.. highlight:: bash
   :linenothreshold: 1

A cool bit of code::

   #!/bin/bash
   # Some cool Bash code
   echo ${BASH_VERSINFO[*]}
   ros2 pkg create --build-type ament_cmake <package_name>


.. code-block:: xml


   <joint
    name="front_right_lidar_joint"
    type="fixed">
    <origin
      xyz="2.1064 -1.1064 1.92"
      rpy="0 0 0" />
    <parent
      link="base_link" />
    <child
      link="front_right_lidar" />
    <axis
      xyz="0 0 0" />
  </joint>