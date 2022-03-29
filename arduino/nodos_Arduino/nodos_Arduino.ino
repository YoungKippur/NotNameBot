#include <ros.h>
#include <ros/time.h>
#include <sensor_msgs/Range.h>
#include <geometry_msgs/Twist.h>

#define L_PWM 2
#define L_FORW 3
#define L_BACK 4
#define R_BACK 5
#define R_FORW 6
#define R_PWM 7
#define ECHO_PIN 8
#define TRIG_PIN 9

#define PWM_MIN 300
#define PWMRANGE 500

sensor_msgs::Range range_msg;
ros::NodeHandle nh;
ros::Subscriber<geometry::Twist> sub("/cmd_vel", &on_twist);
ros::Publisher pub_range("/ultrasound", &range_msg);

// Maps x from [0, 1] to [PWM_MIN, PWMRANGE]
float map_pwm(float x) {
  return x * (PWMRANGE - PWM_MIN) + PWM_MIN;
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

void setup() {
  pinMode(L_FORW, OUTPUT);
  pinMode(L_BACK, OUTPUT);
  pinMode(L_PWM, OUTPUT);
  pinMode(R_FORW, OUTPUT);
  pinMode(R_BACK, OUTPUT);
  pinMode(R_PWM, OUTPUT);
  pinMode(TRIG_PIN, OUTPUT);
  pinMode(ECHO_PIN, INPUT);

  nh.initNode();
  nh.subscribe(sub);
  nh.advertise(pub_range);

  range_msg.radiation_type = sensor_msgs::Range::ULTRASOUND;
  range_msg.header.frame_id = frameid;
  range_msg.field_of_view = 0.1; // fake?
  range_msg.min_range = 0.0;
  range_msg.max_range = 10.0;
}

float range_time = 0;
void loop() {
  if (millis() >= range_time) { // medio feo
    if (millis() <= 10) 
      digitalWrite(TRIG_PIN, HIGH);
    else {
      digitalWrite(TRIG_PIN, LOW);
      range_msg.range = distance = pulseIn(ECHO_PIN, HIGH) * 0.0034 / 2;
      range_msg.header.stamp = nh.now();
      pub_range.publish(&range_msg);
      range_time = millis() + 50;
    }
  }
  nh.spinOnce();
}