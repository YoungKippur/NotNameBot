# NotNameBot
An -up to now- nameless robot based on the Robotics Operating System (ROS).

## Overview

The aim of this robot is to provide...

## Getting started

### Robotics Operating System

ROS (Robotics Operating System) is an operating system, complied above Linux, whose main goal is to provide all the tools needed to build a Robotics project. As ROS projects use to have many interconnected parts, the OS provides features, such as topics, messages, publishers, and subscribers, to establish communication between these parts.

#### Installation and configuration

To get started, download your preferred distro of ROS from the [official Wiki website](http://wiki.ros.org/ROS/Installation).
> **Warning** \
> This project uses the first version of ROS, so you shouldn't install ROS 2 as there could be many incompatibilities.

After installing ROS, we need to source different locations to control them simultaneously thorugh the shell:
```
$ source /opt/ros/<distro>/setup.bash
```
Where <distro> needs to be replaced with your distro short name (e.g. kinetic, melodic, noetic, etc).

Now, let's create a catkin workspace:
```
$ mkdir -p ~/catkin_ws/src
$ cd ~/catkin_ws/
$ catkin_make
```
This commands should create the catkin repository. Inside it you will find the 'build', 'devel', and 'src' folders. Thus, we can source the 'devel' folder:
```
$ source devel/setup.bash
```
Let's create the package:
```
$ catkin_create_pkg not_name_bot std_msgs rospy roscpp
```
Then, we run ```catkin_make``` again to build the package.

#### ROS basic commands

Now, we can start the ROS enviroment:
```
$ roscore
```
This command is the core of all the ROS enviroment and we must keep this bash terminal open while the project is running.

ROS uses nodes to represent each of the indivual parts of the project. We can print all the active nodes:
```
$ rosnode list
```
You will see the only running node is ```/rosout```. This node is always running since the ROS enviroment is started. We can print info about it:
```
$ rosnode info /rosout
```

ROS uses topics to send data between different nodes. Publishers can write data into a node, whereas subscribers can read data from a node. From the previous command, we learnt that ```/rosout``` publishes data to the topic ```/rosout_agg``` and is subscribed to the topic ```/rosout```. To print the info about a topic, write:
```
$ rostopic info /rosout_agg
```
This informs the type of message, publishers and subscribers of this topic. If you want to print the data currently held by the topic, use:
```
$ rostopic echo /rosout_agg
```

#### Example

We can see nodes and topics in action by running a built-in example node:
```
$ rosrun turtlesim turtlesim_node
```
This command should open a new window with a little turtle in the center. If you run ```rosnode list``` you will see the new node ```/turtlesim``` in the list.

Then, run in a new terminal:
```
$ rosrun turtlesim turtle_teleop_key
```
Then, press the arrow keys while this terminal is focused to let the turtle move around the window. 

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

We first begin the connection from your computer to the Raspberry Pi through ssh:
```
$ ssh [username]@[remote-pcs-ip]
```

### Preparing the Arduino

Arduino is the most known series of microcontrollers for Electronics and Robotics projetcs. In our project, we use an Arduino UNO to control the motors of the robot. To use an Arduino within a ROS enviroment, we need to establish a connection between the Arduino and the Raspberry Pi through serial port, using the USB port of the Raspberry Pi.

#### Installation
You can download the Arduino IDE from the [official webpage](https://www.arduino.cc/en/software).

Now let's install the rosserial libraries:
```
sudo apt-get install ros-<distro>-rosserial-arduino
sudo apt-get install ros-<distro>-rosserial
```

#### Deploying
First of all, we need to run the Arduino node connected through rosserial:
```
$ rosrun rosserial_arduino serial_node.py [your-serial-port]
```
Then, we can upload the Arduino code (which?) to the Arduino UNO using the Arduino IDE.
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

#### Hector Slam

Hector Slam is a library which can interpret the Lidar reading and return instead a map of the enviroment. By using odometry techniques, it will compute the movement and rotation of the robot. You can install this library from its [GitHub repository](https://github.com/tu-darmstadt-ros-pkg/hector_slam).

To launch the Hector Slam node, write:
```
roslaunch hector_slam_launch tutorial.launch
```

If you're running this from your RaspberryPi, then you would like to open the rviz and add the ```/map``` topic to see the generated map. You can try to slightly move your robot and see the cursor moving in the visualizer.  

## External links
* [ROS Wiki documentation](http://wiki.ros.org/Documentation)
* [Rosserial (in ROS Wiki)](http://wiki.ros.org/rosserial)
* [Navigation (in ROS Wiki)](http://wiki.ros.org/navigation)
* [Init](https://roboticsbackend.com/make-ros-launch-start-on-boot-with-robot_upstart/)
* [Twist (GitHub)](https://github.com/Reinbert/ros_diffdrive_robot/blob/master/ros_diffdrive_robot.ino)
* [Camera (GitHub)](https://github.com/YoungKippur/IP-CAMERA)
* [IMU Setup (Electropeak)](https://electropeak.com/learn/interfacing-mpu9250-spi-i2c-9-axis-gyro-accelerator-magnetometer-module-with-arduino/)
* [IMU Calibration (Makersportal)](https://makersportal.com/blog/calibration-of-an-inertial-measurement-unit-imu-with-raspberry-pi-part-ii)
* [IMU - RP](https://automaticaddison.com/visualize-imu-data-using-the-mpu6050-ros-and-jetson-nano/)
* [Encoders - Arduino](https://automaticaddison.com/how-to-publish-wheel-odometry-information-over-ros/)
#
![WhatsApp Image 2022-07-20 at 23 55 31](https://user-images.githubusercontent.com/82680610/185521505-cee468ba-faf1-4973-8b66-a01958b17a59.jpeg)
#
![image](https://user-images.githubusercontent.com/82680610/160292044-05cf89da-715c-4f46-a860-a5844a6c1a98.png)
