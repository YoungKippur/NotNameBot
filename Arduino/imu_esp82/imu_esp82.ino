#include <ros.h>
#include <ros/time.h>
#include <ESP8266WiFi.h>
#include <ESP8266WiFiMulti.h>
#include <MPU9250.h>
#include <sensor_msgs/Range.h>
#include <sensor_msgs/Imu.h>
#include <geometry_msgs/Twist.h>

#define L_PWM D3
#define L_FORW D4
#define L_BACK D5
#define R_BACK D6
#define R_FORW D7
#define R_PWM D8

#define PWM_MIN 0
#define PWMRANGE 1023

void setup_pins();
void setup_wifi();
void setup_mpu();
void setup_node();
bool ros_connected();
void read_mpu();
void on_twist(const geometry_msgs::Twist &msg);
float map_pwm(float x);

bool _connected = false;
float range_time = 0;

ESP8266WiFiMulti wifi;
IPAddress server(192,168,1,100);
MPU9250 IMU(Wire,0x68);

sensor_msgs::Range range_msg;
sensor_msgs::Imu mpu_msg;
ros::NodeHandle nh;
ros::Subscriber<geometry_msgs::Twist> sub("/cmd_vel", on_twist);
ros::Publisher pub_range("/ultrasound", &range_msg);
ros::Publisher pub_mpu("/mpu9250", &mpu_msg);

void setup() {
  Serial.begin(115200);
  digitalWrite(LED_BUILTIN, LOW);
  setup_pins();
  setup_wifi();
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
}

void setup_wifi() {
  WiFi.softAPdisconnect();
  WiFi.disconnect();
  WiFi.mode(WIFI_STA);
  wifi.addAP("KIP_LAB", "47052482");
  while (wifi.run() != WL_CONNECTED) {
    delay(500);
    Serial.print(".");
  }
  Serial.println("Connected");
  Serial.print("SSID: ");
  Serial.println(WiFi.SSID());
  Serial.print("IP: ");
  Serial.println(WiFi.localIP());
}

void setup_mpu() {
  int mpu_status = IMU.begin();
  if (mpu_status < 0) {
    Serial.println("IMU initialization failed");
    Serial.print("Status: ");
    Serial.println(mpu_status);
  } else
    Serial.println("IMU connected");
}

void setup_node() {
  nh.getHardware()->setConnection(server);
  nh.initNode();
  nh.subscribe(sub);
  nh.advertise(pub_range);
  nh.advertise(pub_mpu);
}


void loop() {
  ros_connected();
  read_mpu();
  nh.spinOnce();
}

bool ros_connected() {
  bool conn = nh.connected();
  if (_connected != conn) {
    _connected = conn;
    digitalWrite(LED_BUILTIN, conn);
    Serial.println(conn ? "ROS connected" : "ROS disconnected");
  }
  return conn;
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
