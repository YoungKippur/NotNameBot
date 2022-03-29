#include <ros.h>
#include <ros/time.h>
#include <sensor_msgs/Range.h>

#define ECHO_PIN 2
#define TRIG_PIN 3

sensor_msgs::Range range_msg;

ros::NodeHandle nh;
ros::Publisher pub_range("/ultrasound", &range_msg);

void setup() {
  pinMode(TRIG_PIN, OUTPUT);
  pinMode(ECHO_PIN, INPUT);

  nh.initNode();
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
