#include <ros.h>
#include <ros/time.h>
#include <sensor_msgs/Range.h>

#define echoPin 2
#define trigPin 3

ros::NodeHandle  nh;

sensor_msgs::Range range_msg;
ros::Publisher pub_range( "/ultrasound", &range_msg);

char frameid[] = "/ultrasound";

long duration;
int distance;

void setup() {
  pinMode(trigPin, OUTPUT);
  pinMode(echoPin, INPUT);

  nh.initNode();
  nh.advertise(pub_range);

  range_msg.radiation_type = sensor_msgs::Range::ULTRASOUND;
  range_msg.header.frame_id =  frameid;
  range_msg.field_of_view = 0.1;  // fake
  range_msg.min_range = 0.0;
  range_msg.max_range = 10.0;
}

long range_time;

void loop() {
  if ( millis() >= range_time ) {
    digitalWrite(trigPin, LOW);
    delayMicroseconds(2);
    digitalWrite(trigPin, HIGH);
    delayMicroseconds(10);
    digitalWrite(trigPin, LOW);
    duration = pulseIn(echoPin, HIGH);
    distance = duration * 0.034 / 2;
    range_msg.range = distance / 10.0;
    range_msg.header.stamp = nh.now();
    range_time =  millis() + 50;
    pub_range.publish(&range_msg);
  }
  nh.spinOnce();
}
