# NotNameBot
An -up to now- nameless robot based on the Robotics Operating System (ROS).

## ROS important commands (WIP)
* ```roscore``` to start ROS environment (always first command).
* ```rosrun``` to run a ROS command.
* ```rviz``` to open the ROS visualizer.
* ```rosnode``` or ```rostopic``` to get info about a specific ROS node or topic.
* ```rostopic echo /[your-topic]``` to print data whenever is published in the topic.
* ```rosrun rosserial_arduino serial_node.py [serial-port]``` to connect the Arduino to the Raspberry Pi thorugh serial port.
* ```roslaunch server``` to launch a ROS server (only used for esp32, esp82 or similar).

## Codes
* [Arduino](arduino)
* [Python](Python)

## Links
* [ROS Wiki](http://wiki.ros.org/Documentation)
* [Rosserial (in ROS Wiki)](http://wiki.ros.org/rosserial)
* [Navigation (in ROS Wiki)](http://wiki.ros.org/navigation)
* [Init](https://roboticsbackend.com/make-ros-launch-start-on-boot-with-robot_upstart/)
* [Twist (GitHub)](https://github.com/Reinbert/ros_diffdrive_robot/blob/master/ros_diffdrive_robot.ino)
* [Camera (GitHub)](https://github.com/YoungKippur/IP-CAMERA)
* [IMU Setup (Electropeak)](https://electropeak.com/learn/interfacing-mpu9250-spi-i2c-9-axis-gyro-accelerator-magnetometer-module-with-arduino/)
* [IMU Calibration (Makersportal)](https://makersportal.com/blog/calibration-of-an-inertial-measurement-unit-imu-with-raspberry-pi-part-ii)
* [IMU - RP](https://github.com/chrisspen/ros_mpu6050_node)

# 
![image](https://user-images.githubusercontent.com/82680610/160292044-05cf89da-715c-4f46-a860-a5844a6c1a98.png)
