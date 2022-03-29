#include <ros.h>
#include <geometry_msgs/Twist.h>

#define L_PWM 2
#define L_FORW 3
#define L_BACK 4
#define R_PWM 7
#define R_FORW 6
#define R_BACK 5

#define PWM_MIN 300

ros::NodeHandle nh;
ros::Subscriber<geometry::Twist> sub("/cmd_vel", &on_twist);

void setup() {
  pinMode(L_FORW, OUTPUT);
  pinMode(L_BACK, OUTPUT);
  pinMode(L_PWM, OUTPUT);
  pinMode(R_FORW, OUTPUT);
  pinMode(R_BACK, OUTPUT);
  pinMode(R_PWM, OUTPUT);

  nh.initNode();
  nh.subscribe(sub);
}

void loop() {
  nh.spinOnce();
  delay(10);
}

void on_twist(const geometry_msgs::Twist &msg) {
  float x = max(min(msg.linear.x, 1.0f), -1.0f);
  float z = max(min(msg.angular.z, 1.0f), -1.0f);
  float l = (msg.linear.x - msg.angular.z) / 2;
  float r = (msg.linear.x + msg.angular.z) / 2;

  digitalWrite(L_FORW, l > 0);
  digitalWrite(L_BACK, l < 0);
  analogWrite(L_PWM, map_pwm(fabs(l)));
  digitalWrite(R_FORW, r > 0);
  digitalWrite(R_BACK, r < 0);
  analogWrite(R_PWM, map_pwm(fabs(r)));
}

// Maps x from [0, 1] to [PWM_MIN, PWMRANGE]
float map_pwm(float x) {
  return x * (PWMRANGE - PWM_MIN) + PWM_MIN
}
