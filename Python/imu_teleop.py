import rospy
import numpy as np
from sensor_msgs.msg import Imu
from geometry_msgs.msg import Twist

datos = []
vel_lin = np.array([0.0,0.0,0.0])
pos_lin = np.array([0.0,0.0,0.0])
pos_ang = np.array([0.0,0.0,0.0])

def callback(data):
    global datos, vel_lin, pos_lin, pos_ang
    if datos:
        prev = datos[-1]
        dt = data.header.stamp - prev.header.stamp
        acc_lin = np.array([data.linear_acceleration.x,
            data.linear_acceleration.y,
            data.linear_acceleration.z])
        vel_ang = np.array([data.angular_velocity.x,
            data.angular_velocity.y,
            data.angular_velocity.z])
        vel_ang *= 180 / 3.1415926535
        print (vel_ang)
        vel_lin += (dt.nsecs * acc_lin / 10**9) * (abs(acc_lin) > 1)
        pos_lin += (dt.nsecs * vel_lin / 10**9) * (abs(vel_lin) > 1)
        pos_ang += (dt.nsecs * vel_ang / 10**9) * (abs(vel_ang) > 0.5)
    datos.append(data)

def loop():
    global pos_ang
    exit = False
    while not exit:
        # print(pos_ang[2])
        act = input("Select an action: Forward - Rotate - Stop - Exit")
        if act == "f":
            tw = Twist()
            tw.angular.x = 1
            pub_vel.publish(tw)
            while abs(pos_ang[2]) < 90:
                pass
            pub_vel.publish(Twist())
        if act == "r":
            tw = Twist()
            tw.angular.z = 1
            pub_vel.publish(tw)
        if act == "s":
            pub_vel.publish(Twist())
        if act == "e":
            exit = True

if __name__ == '__main__':
    rospy.init_node("teleop_twist")
    sub_mpu = rospy.Subscriber("mpu9250", Imu, callback)
    pub_vel = rospy.Publisher("cmd_vel", Twist, queue_size = 1)

    loop()