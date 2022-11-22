# NotNameBot
An -up to now- nameless robot based on the Robotics Operating System (ROS).

![image](https://user-images.githubusercontent.com/82680610/199367322-5d0fb02f-fce2-4f9b-b1e5-340259bee235.png)

## Overview

The aim of this robot is to provide...

## Getting started

### Robotics Operating System

ROS (Robotics Operating System) is an operating system, complied above Linux, whose main goal is to provide all the tools needed to build a Robotics project. As ROS projects use to have many interconnected parts, the OS provides features, such as topics, messages, publishers, and subscribers, to establish communication between these parts. Most of the documentation of the used libraries could be found in the [ROS Wiki](http://wiki.ros.org/).

The main motivation for using ROS is the existance of the [navigation library](http://wiki.ros.org/navigation), which we will fully explain in the next section.

#### Installation and configuration

To get started, download your preferred distro of ROS from the [official Wiki website](http://wiki.ros.org/ROS/Installation).
> **Warning** \
> This project uses the first version of ROS, so you shouldn't install ROS 2 as there could be many incompatibilities.

After installing ROS, we need to source different locations to control them simultaneously thorugh the shell:
```
$ source /opt/ros/<distro>/setup.bash
```
Where <distro> needs to be replaced with your distro short name (e.g. kinetic, melodic, noetic, etc).

The workspace is the folder in which all our projects and libraries would be located. ROS uses a custom build system, catkin, in where we will create our packages.  By now, let's just create a catkin workspace:
```
$ mkdir -p ~/catkin_ws/src
$ cd ~/catkin_ws/
$ catkin_make
```
Inside the new catkin folder you will find the 'build', 'devel', and 'src' folders. Thus, you might source the 'devel' folder:
```
$ source devel/setup.bash
```
> **Note** \
> You might prefer to remember this last command by heart, since it usually works as a panacea. Make sure to run it before rosrunning or roslaunching any other command, especially if it's from an installed package.

A package is a collection of codes built to be runned through the shell. In order to create the first package, you should run:
```
$ catkin_create_pkg not_name_bot std_msgs rospy roscpp
```
Thus, you create the package ```not_name_bot``` with dependences on ```std_msgs``` (for custom variable types), ```rospy``` (for using Python) and ```roscpp``` (for using C++). After the package is created, you can build it with ```catkin_make```.

#### ROS basic commands

First of all, you should write:
```
$ roscore
```
This command is the core of all the ROS enviroment and you must keep this bash terminal open while the project is running. You might do this every time you start the ROS project. 

A node represents and individual piece of code. In ROS, different nodes communicate to each other. This structure is very convenient to keep our project separated and organized. You can print all the active nodes with:
```
$ rosnode list
```
You will see that the only running node is ```/rosout```. This node is always running since the ROS enviroment is started. We can print info about it with:
```
$ rosnode info /rosout
```
The communication between nodes ocurrs through topics. Publishers can write data into a topic, whereas subscribers can read data from a topic. From the previous command, we learnt that ```/rosout``` publishes data to the topic ```/rosout_agg``` and is subscribed to the topic ```/rosout```. To print the info about a topic, write:
```
$ rostopic info /rosout_agg
```
This informs the type of message (msg), publishers and subscribers of this topic. If you want to print the data currently held by the topic, use:
```
$ rostopic echo /rosout_agg
```
> **Note**\
> With this command you can check the information published in a topic through the shell, thus, it might be convenient for debugging. 

#### Example

We can see nodes and topics in action by running a built-in example node. First, rosrun the node:
```
$ rosrun turtlesim turtlesim_node
```
This command should open a new window with a little turtle in the center. If you run ```rosnode list``` you will see the new node ```/turtlesim``` in the list. You must not close the shell, otherwise the node will be killed. Then, open another terminal and rosrun the second node:
```
$ rosrun turtlesim turtle_teleop_key
```
Thus, you can press the arrow keys while this shell is focused and let the turtle move around the other window.

In this example, the ```/turtle_teleop_key``` node is publishing the pressed key information in the ```/turtle1/command_velocity``` topic, whereas the ```/turtlesim_node``` is subscribed and listens to each publication in the topic. 

> **Note** (optional)\
> You can install the rqt_graph package:
> ```
> $ sudo apt-get install ros-<distro>-rqt
> $ sudo apt-get install ros-<distro>-rqt-common-plugins
> ```
> And then we can visually see the nodes and topics:
> ```
> rosrun rqt_graph rqt_graph
> ```

### Connecting to Raspberry Pi
Raspberry Pi is a series of single-board computers chiefly for educational and recreational purpose. Raspberry Pi uses the Raspberry Pi OS, a distribution of Debian which is able run ROS on top. We will use a Raspberry Pi for hosting the ROS enviroment of the whole project.

#### Installation

#### Connection

We first begin the connection from your computer to the Raspberry Pi through ssh:
```
$ ssh [username]@[rpi-ip]
```

You need to install all the libraries and download all the files in the RaspberryPi in order to use it as the core of the robot.
  
> **Note** (optional)\
> If you want to open a rviz window within the computer, you might first export
> ``` 
> export ROS_MASTER_URI=[rpi-ip]:[port]
> ```
> The ROS master port is 11311 by default.

### Preparing the Arduino

Arduino is the most known series of microcontrollers for Electronics and Robotics projetcs. In our project, we use an Arduino UNO to control the motors of the robot. To use an Arduino within a ROS enviroment, we need to establish a connection between the Arduino and the Raspberry Pi through serial port, using the USB port of the Raspberry Pi.

#### Installation
You can download the Arduino IDE from the [official webpage](https://www.arduino.cc/en/software).

Now let's install the rosserial libraries:
```
sudo apt-get install ros-<distro>-rosserial-arduino
sudo apt-get install ros-<distro>-rosserial
```

#### Differential drive
In this project, we use a [differential wheeled robot](https://en.wikipedia.org/wiki/Differential_wheeled_robot).

#### Deploying
First of all, we need to run the Arduino node connected through rosserial:
```
$ rosrun rosserial_arduino serial_node.py [your-serial-port]
```
Then, we can upload the Arduino code to the Arduino UNO using the Arduino IDE.

> **Note** \
> In case you are using an esp32, esp82 or similar, it's possible to establish a connection through WiFi. Firstly, launch the server:
> ```
> roslaunch server
> ```
> Then...

### Rotatory Lidar

Lidar, acronym Light Detection and Ranging or Laser Imaging, Detection and Ranging, is a rotatory sensor used in this project to map obstacles in a 2-dimensional surface. We use the library ```rplidar_ros``` to establish the connection between the Raspberry Pi and the Lidar.

#### Testing
First, download and build the ```rplidar_ros``` library from its [GitHub repository](https://github.com/Slamtec/rplidar_ros).

To launch the Lidar node, write the code:
```
roslaunch rplidar_ros rplidar.launch
```

Now, you can write ```rviz``` into the terminal to open the ROS Visualizer. Inside the rviz window, you click the button Add and select the By topic list. Then, click the topic of your Lidar, in our case, ```/scan```. Then, rviz most probably will give an error. To fix it, you should change the Fixed Frame variable inside Global Options from ```/map``` to ```/laser```.

### Hector Slam

Hector Slam is a library which can interpret the Lidar reading and return instead a map of the enviroment. By using odometry techniques, it will compute the movement and rotation of the robot. You can install this library from its [GitHub repository](https://github.com/tu-darmstadt-ros-pkg/hector_slam).

To launch the Hector Slam node, write:
```
roslaunch hector_slam_launch tutorial.launch
```

If you're running this from your RaspberryPi, then you would like to open the rviz and add the ```/map``` topic to see the generated map. You can try to slightly move your robot and see the cursor moving in the visualizer.  

### Saving and serving a map

You can generate a map by running the previous line and moving your robot slowly. The ```hector_slam``` node publishes the generated map onto the ```/map``` topic. When the map generation is ready, you should run
```
rosrun map_server map_saver -f my_map
```
This line will save the hitherto  map on two files: ```my_map.yaml``` (data file) and ```my_map.pgm``` (image file).
Thus, if you write
```
rosrun map-server map-server my_map.yaml
```
the saved map will be continously served on the ```/map``` topic.
  
## Localization and navigation

In order to build a fully autonomous robot, we are going to use the built-in Navigation Stack from ROS. You can install it with
```
sudo apt-get install ros-<distro>-navigation
```

### The problem
Classically, different sensors, such as encoders or IMUs are used in order to get the robot's odometry (current position in the map). Nevertheless, in this project we provide a navigation built only upon Hector Slam.
Hector Slam publishes a transform ```map -> odom``` which hypotetically would give the current robot's odometry. However, since ```map_server``` is also publishing in ```/map```, we should not use this transformation.
Thus, we might use an undocumented feature, namely setting ```pub_odometry = true```, which in turn will make Hector Slam to publish robot's odometry in the topic ```/scanmatcher_odom```. In order to get the proper transform we refer to the ```odomtransformer.py``` node.
Thus, we are able to use the ```amcl``` node with the ```map_server``` publishing the map to estimate our current location on a pre-generated map.
With this estimated position, we are abble to run ```move_base``` to create a plan for reaching the goal sent through rviz.
  
A launch file ```bigboy_config.launch``` is given in order to be able to run all this commands simultaneously. To launch it, you can write
```
roslaunch [path]/bigboy_config.launch
```

## External links
* [ROS Wiki documentation](http://wiki.ros.org/Documentation)
* [Rosserial (in ROS Wiki)](http://wiki.ros.org/rosserial)
* [Init](https://roboticsbackend.com/make-ros-launch-start-on-boot-with-robot_upstart/)
* [Twist (GitHub)](https://github.com/Reinbert/ros_diffdrive_robot/blob/master/ros_diffdrive_robot.ino)
* [Camera (GitHub)](https://github.com/YoungKippur/IP-CAMERA)
* [IMU setup (Electropeak)](https://electropeak.com/learn/interfacing-mpu9250-spi-i2c-9-axis-gyro-accelerator-magnetometer-module-with-arduino/)
* [IMU calibration (Makersportal)](https://makersportal.com/blog/calibration-of-an-inertial-measurement-unit-imu-with-raspberry-pi-part-ii)
* [IMU visualization](https://automaticaddison.com/visualize-imu-data-using-the-mpu6050-ros-and-jetson-nano/)
* [Encoders - Arduino](https://automaticaddison.com/how-to-publish-wheel-odometry-information-over-ros/)
* [Navigation (in ROS Wiki)](http://wiki.ros.org/navigation)
* [Navigation setup (Automatic Addison)](https://automaticaddison.com/how-to-set-up-the-ros-navigation-stack-on-a-robot/)
* [Navigation only with hector_mapping (yoraish)](https://yoraish.com/2021/09/08/a-full-autonomous-stack-a-tutorial-ros-raspberry-pi-arduino-slam/) 
