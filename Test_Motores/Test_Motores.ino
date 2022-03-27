#include <ros.h>
#include <std_msgs/String.h>

#define ENA 2
#define IN1 3
#define IN2 4

#define ENB 7
#define IN3 6
#define IN4 5

ros::NodeHandle  nh;

int vel = 75;

String msgg;

void str_msg(const std_msgs::String& msg) {
  msgg = msg.data;
}

ros::Subscriber<std_msgs::String> sub("/chatter", &str_msg);

void setup() {
  pinMode (IN1, OUTPUT);
  pinMode (IN2, OUTPUT);
  pinMode (ENA, OUTPUT);
  pinMode (IN3, OUTPUT);
  pinMode (IN4, OUTPUT);
  pinMode (ENB, OUTPUT);

  moveAdelanteA(0);
  moveAdelanteB(0);

  nh.initNode();
  nh.subscribe(sub);
}

void loop() {
  msgRead(msgg.toInt());
  nh.spinOnce();
  delay(10);
}

void msgRead(int str) {
  switch (str) {
    case 1:
      moveAdelanteA(vel);
      moveAdelanteB(vel);
      break;
    case 2:
      moveAdelanteA(vel);
      moveAdelanteB(0);
      break;
    case 3:
      moveAdelanteA(0);
      moveAdelanteB(0);
      break;
    case 4:
      moveAdelanteA(0);
      moveAdelanteB(vel);
      break;
  }
}

void moveAdelanteA(int num) {
  digitalWrite(IN1, HIGH);
  digitalWrite(IN2, LOW);
  analogWrite(ENA, num);
}

void moveAdelanteB(int num) {
  digitalWrite(IN3, HIGH);
  digitalWrite(IN4, LOW);
  analogWrite(ENB, num);
}
