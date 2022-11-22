#include <ros.h>
#include <ros/time.h>
#include <MPU9250.h>
#include <sensor_msgs/Range.h>
#include <sensor_msgs/Imu.h>
#include <geometry_msgs/Twist.h>

#define L_PWM 2
#define L_FORW 3
#define L_BACK 4
#define R_BACK 5
#define R_FORW 6
#define R_PWM 7

#define MPU 10
#define L_ENCODER 8
#define R_ENCODER 9

#define PWM_MIN 0
#define PWMRANGE 1023

void setup_pins();
void setup_mpu();
void setup_node();
void read_mpu();
void on_twist(const geometry_msgs::Twist &msg);
float map_pwm(float x);

bool _connected = false;
float range_time = 0;


MPU9250 IMU(Wire,0x68);

sensor_msgs::Range range_msg;
sensor_msgs::Imu mpu_msg;
sensor_msgs::Range encoders_msg;
ros::NodeHandle nh;
ros::Subscriber<geometry_msgs::Twist> sub("/cmd_vel", on_twist);
ros::Publisher pub_range("/ultrasound", &range_msg);
ros::Publisher pub_mpu("/mpu9250", &mpu_msg);
ros::Publisher pub_encoders("/encoders", &encoders_msg);

void setup() {
  digitalWrite(13, LOW);  
  setup_pins();
  setup_mpu();
  setup_node();
}

void setup_pins() {
  pinMode(L_FORW, OUTPUT);
  pinMode(L_BACK, OUTPUT);
  pinMode(L_PWM, OUTPUT);
  pinMode(R_FORW, OUTPUT);
  pinMode(R_BACK, OUTPUT);
  pinMode(R_PWM, OUTPUT);
  pinMode(MPU, INPUT);
  pinMode(L_ENCODER, INPUT);
  pinMode(R_ENCODER, INPUT);
}


void setup_mpu() {
  int mpu_status = IMU.begin();
  if (mpu_status < 0) {
    Serial.println("IMU initialization failed");
    Serial.print("Status: ");
    Serial.println(mpu_status);
  } else {
    Serial.println("IMU connected");
  }
}

void setup_node() {
  nh.initNode();
  nh.subscribe(sub);
  nh.advertise(pub_range);
  nh.advertise(pub_mpu);
  nh.advertise(pub_encoders);
}


void loop() {
  //read_mpu();
  //read_encoders();
  nh.spinOnce();
}

void read_mpu() {
  IMU.readSensor();
  mpu_msg.header.stamp = nh.now();
  mpu_msg.linear_acceleration.x = IMU.getAccelX_mss();
  mpu_msg.linear_acceleration.y = IMU.getAccelY_mss();
  mpu_msg.linear_acceleration.z = IMU.getAccelZ_mss();
  mpu_msg.angular_velocity.x = IMU.getGyroX_rads();
  mpu_msg.angular_velocity.y = IMU.getGyroY_rads();
  mpu_msg.angular_velocity.z = IMU.getGyroZ_rads();
  float _mx = IMU.getMagX_uT();
  float _my = IMU.getMagY_uT();
  float _mz = IMU.getMagZ_uT();
  pub_mpu.publish(&mpu_msg);
}

int l_count = 0; bool l_flag = true;
int r_count = 0; bool r_flag = true;
void read_encoders() {
  if (digitalRead(L_ENCODER) == LOW && l_flag) {
    l_count++; l_flag = false;
  } else if (digitalRead(L_ENCODER) == HIGH)
    l_flag = true;
  if (digitalRead(R_ENCODER) == LOW && r_flag) {
    r_count++; r_flag = false;
  } else if (digitalRead(R_ENCODER) == HIGH)
    r_flag = true;
  encoders_msg.min_range = l_count;
  encoders_msg.max_range = r_count;
  pub_encoders.publish(&encoders_msg);
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

float map_pwm(float x) {
  return x * (PWMRANGE - PWM_MIN) + PWM_MIN;
}
