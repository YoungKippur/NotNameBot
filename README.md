# NotNameBot
An -up to now- nameless robot based on the Robotics Operating System (ROS).

## Getting started

### Robotics Operating System

ROS (Robotics Operating System) is an operating system, complied above Linux, whose main goal is to provide all the tools needed to build a Robotics project. As ROS projects use to have many interconnected parts, the OS provides features, such as topics, messages, publishers, and subscribers, to establish communication between these parts. \

To get started, download your preferred distro of ROS from the [official Wiki website](http://wiki.ros.org/ROS/Installation).
> **Warning** \
> This project uses the first version of ROS, so you shouldn't install ROS 2 as there could be many incompatibilities.

#### Configuration

#### Packaging

Now, we can start the ROS enviroment:
```
$ roscore
```
This command is the core of all the ROS enviroment and we must keep this bash terminal open while the project is running.\

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

We can see nodes and topics in action by running a built-in example node.
```
$ rosrun turtlesim turtlesim_node
```

#### More
* ```rviz``` to open the ROS visualizer.
* See [ROS Wiki](http://wiki.ros.org/Documentation).

### Connecting to Raspberry Pi
Raspberry Pi is a series of single-board computers chiefly for educational and recreational purpose. Raspberry Pi uses the Raspberry Pi OS, a distribution of Debian which is able run ROS on top. We will use a Raspberry Pi for hosting the ROS enviroment of the whole project.

#### Installation

We first begin the connection from your computer to the Raspberry Pi through ssh:
```
$ ssh [username]@[remote-pcs-ip]
```

### Preparing the Arduino

Arduino is the most known series of microcontrollers for Electronics and Robotics projetcs. In our project, we use an Arduino UNO to control the motors of the robot. To use an Arduino within a ROS enviroment, we need to establish a connection between the Arduino and the Raspberry Pi through serial port, using the USB port of the Raspberry Pi.

#### Instalation
You can download the Arduino IDE from the [official webpage](https://www.arduino.cc/en/software).

#### Deploying
First of all, we need to run the Arduino node connected through rosserial:
```
$ rosrun rosserial_arduino serial_node.py [your-serial-port]
```
Then, we need to upload the Arduino code (which?) to the Arduino UNO using the Arduino IDE.
> **Note** \
> In case you are using an esp32, esp82 or similar, it's possible to establish a connection through WiFi. Firstly, launch the server:
> ```
> roslaunch server
> ```
> Then....

## GIT important commands (WIP)
* ```git push```
* ```git add```
* ```git commit -a```
* ```git pull```

## External links
* [ROS Wiki](http://wiki.ros.org/Documentation)
* [Rosserial (in ROS Wiki)](http://wiki.ros.org/rosserial)
* [Navigation (in ROS Wiki)](http://wiki.ros.org/navigation)
* [Init](https://roboticsbackend.com/make-ros-launch-start-on-boot-with-robot_upstart/)
* [Twist (GitHub)](https://github.com/Reinbert/ros_diffdrive_robot/blob/master/ros_diffdrive_robot.ino)
* [Camera (GitHub)](https://github.com/YoungKippur/IP-CAMERA)
* [IMU Setup (Electropeak)](https://electropeak.com/learn/interfacing-mpu9250-spi-i2c-9-axis-gyro-accelerator-magnetometer-module-with-arduino/)
* [IMU Calibration (Makersportal)](https://makersportal.com/blog/calibration-of-an-inertial-measurement-unit-imu-with-raspberry-pi-part-ii)
* [IMU - RP](https://github.com/chrisspen/ros_mpu6050_node)
* [Encoders - Arduino](https://automaticaddison.com/how-to-publish-wheel-odometry-information-over-ros/)
#
![WhatsApp Image 2022-07-20 at 23 55 31](https://user-images.githubusercontent.com/82680610/185521505-cee468ba-faf1-4973-8b66-a01958b17a59.jpeg)
#
![image](https://user-images.githubusercontent.com/82680610/160292044-05cf89da-715c-4f46-a860-a5844a6c1a98.png)
