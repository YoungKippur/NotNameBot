#include <ros.h>
#include <ros/time.h>
#include <ESP8266WiFi.h>
#include <ESP8266WiFiMulti.h>
#include <sensor_msgs/Range.h>
#include <geometry_msgs/Twist.h>

#define L_PWM D1
#define L_FORW D2
#define L_BACK D3
#define R_BACK D4
#define R_FORW D5
#define R_PWM D6
#define ECHO_PIN D7
#define TRIG_PIN D8

#define PWM_MIN 0
#define PWMRANGE 1023

void setup_pins();
void setup_wifi();
void setup_node();
bool ros_connected();
void on_twist(const geometry_msgs::Twist &msg);
float map_pwm(float x);

bool _connected = false;
float range_time = 0;

ESP8266WiFiMulti wifi;
IPAddress server(10,162,24,35);

sensor_msgs::Range range_msg;
ros::NodeHandle nh;
ros::Subscriber<geometry_msgs::Twist> sub("/cmd_vel", on_twist);
ros::Publisher pub_range("/ultrasound", &range_msg);

void setup() {
  Serial.begin(115200);
  setup_pins();
  setup_wifi();
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
  wifi.addAP("ORT-IoT", "OrtIOTnew22");
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

void setup_node() {
  nh.getHardware()->setConnection(server);
  nh.initNode();
  nh.subscribe(sub);
  nh.advertise(pub_range);
}

void loop() {
  ros_connected();
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

// On twist received
void on_twist(const geometry_msgs::Twist &msg) {
  float x = max(min(msg.linear.x, 1.0f), -1.0f);
  float z = max(min(msg.angular.z, 1.0f), -1.0f);
  float l = (msg.linear.x - msg.angular.z) / 2;
  float r = (msg.linear.x + msg.angular.z) / 2;
  Serial.println("Twist received");
  digitalWrite(L_FORW, l > 0);
  digitalWrite(L_BACK, l < 0);
  analogWrite(L_PWM, map_pwm(fabs(l)));
  digitalWrite(R_FORW, r > 0);
  digitalWrite(R_BACK, r < 0);
  analogWrite(R_PWM, map_pwm(fabs(r)));
}

// Maps x from [0, 1] to [PWM_MIN, PWMRANGE]
float map_pwm(float x) {
  return x * (PWMRANGE - PWM_MIN) + PWM_MIN;
}
