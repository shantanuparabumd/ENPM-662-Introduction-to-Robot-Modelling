Install Ubuntu
=====================================================================

 The version of ROS2 we will be using is :guilabel:`Galactic Geochelone`. This version is stable and supported on :guilabel:`Ubuntu Focal Fossa (20.04) 64-bit`.
Therefore we suggest everyone to use a similar combination of software for ease of resolution of errors.

.. note::
    The tutorials above are for reference you might need to make a few changes from your side to get the correct version of Ubuntu ( Focal Fossa 20.04)


There are a few different methods that you can use to get a Linux Operating System on your device. 





Dual Boot
--------------------------------
This method lets you retain your Windows Operating system along side Ubuntu. This can be easily undone by removing Ubuntu.
All the device resources are available to Ubuntu and simulations run smoother with high real time factor.

`How to Dual Boot Ubuntu 22.04 LTS and Windows 11 <https://youtu.be/QKn5U2esuRk>`_

.. warning::
    * The tutorial explains dual booting :guilabel:`Windows 11` with :guilabel:`Ubuntu 22.04`, however we will be using :guilabel:`Ubuntu 20.04`. 
    
    * The steps shown in the video can be followed just make sure you get the ISO Image for Ubuntu 20.04.
    
    * Make sure you have turned off the bitlocker or save your bitlocker encryption keys such that they are available when you want to boot back to Windows.




Docker
--------------------------------
The Docker environment is quite useful to learn the basics of Linux and also some aspects of ROS where GUI is not required. In this method we create a temporary container which is deleted after use and hence cannot retain information.

`Docker Complete Setup on Windows<https://youtu.be/2ezNqqaSjq8>`_

Virtual Box 
--------------------------------

This method creates a virtual environment to install Ubuntu. Resources are shared as both the operating systems are running at the same time and hence we experience a lot of lag.

This method is safe and good for initial testing and training purpose.

`How to Install Ubuntu in VirtualBox on Windows 11<https://youtu.be/-CIepTSsaNE>`_




Complete Boot 
--------------------------------

.. warning::
    A complete boot is not recommended as it will completely remove the Windows System from your laptop. For people who want to transition into using Linux this might be a good idea. Windows recovery is not possible.

`Completely Remove Windows 11 and install Ubuntu<https://youtu.be/P9a0TALERK8>`_