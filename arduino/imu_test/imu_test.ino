#include "MPU9250.h"

MPU9250 IMU(Wire,0x68);
int status;

void setup() {
  Serial.begin(115200);
  while(!Serial) {}
  status = IMU.begin();
  if (status < 0) {
    Serial.println("IMU initialization unsuccessful");
    Serial.println("Check IMU wiring or try cycling power");
    Serial.print("Status: ");
    Serial.println(status);
    while(1) {}
  }
}

double angulo = 0;
int prev = 0, now = 0;
void loop() {
  IMU.readSensor();
  now = millis();
  angulo += IMU.getGyroZ_rads() * 180 / 3.1415926 * (now - prev) / 1000;
  prev = now;
  if (angulo > -360) {
    analogWrite(2, 500);
    digitalWrite(3, HIGH);
    digitalWrite(4, LOW);
    digitalWrite(5, HIGH);
    digitalWrite(6, LOW);
    analogWrite(7, 500);
  } else {
    analogWrite(2, 0);
    digitalWrite(3, LOW);
    digitalWrite(4, LOW);
    digitalWrite(5, LOW);
    digitalWrite(6, LOW);
    analogWrite(7, 0);
  }
}
