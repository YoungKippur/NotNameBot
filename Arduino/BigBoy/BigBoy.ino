#include <ros.h>
#include <ros/time.h>
#include <geometry_msgs/Twist.h>

#define L_PWM 9
#define R_PWM 10

#define L_CONTROL 8
#define R_CONTROL 11

#define PWM_MIN 0
#define PWMRANGE 1023

void setup_pins();
void setup_node();
void on_twist(const geometry_msgs::Twist &msg);
float map_pwm(float x);

bool _connected = false;
float range_time = 0;

ros::NodeHandle nh;
ros::Subscriber<geometry_msgs::Twist> sub("/cmd_vel", on_twist);

void setup() {
  setup_pins();
  setup_node();
}

void setup_pins() {
  pinMode(L_PWM, OUTPUT);
  pinMode(R_PWM, OUTPUT);

  pinMode(L_CONTROL, OUTPUT);
  pinMode(R_CONTROL, OUTPUT);
}

void setup_node() {
  nh.initNode();
  nh.subscribe(sub);
}

void loop() {
  nh.spinOnce();
}

void on_twist(const geometry_msgs::Twist &msg) {
  float x = max(min(msg.linear.x, 1.0f), -1.0f);
  float z = max(min(msg.angular.z, 1.0f), -1.0f);
  float l = (msg.linear.x - msg.angular.z) / 2;
  float r = (msg.linear.x + msg.angular.z) / 2;
  digitalWrite(L_CONTROL, l > 0);
  analogWrite(L_PWM, map_pwm(fabs(l)));
  digitalWrite(R_CONTROL, r > 0);
  analogWrite(R_PWM, map_pwm(fabs(r)));
}

float map_pwm(float x) {
  return x * (PWMRANGE - PWM_MIN) + PWM_MIN;
}
