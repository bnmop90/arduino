#include <Servo.h>

Servo servo;

// 핀 설정
int piezoPin = 11;
int echoPin = 3;
int trigPin = 2;
int servoPin = 6;

unsigned long currentTime = 0;
boolean flag = 0;


// 초음파 센서의 손 측정 시간 설정 변수
int checkTime = 500;

// 손소독제 크기에 따른 모터의 각도 조절 변수
int pushAngle = 10;
int currentAngle = 90;

void setup() {
  servo.attach(servoPin);
  servo.write(currentAngle);

  pinMode(trigPin, OUTPUT);
  pinMode(echoPin, INPUT);
  pinMode(piezoPin, OUTPUT);
}

void loop() {
  digitalWrite(trigPin, LOW);
  digitalWrite(echoPin, LOW);
  delayMicroseconds(2);
  digitalWrite(trigPin, HIGH);
  delayMicroseconds(10);
  digitalWrite(trigPin, LOW);

  unsigned long duration = pulseIn(echoPin, HIGH);
  float distance = duration / 29.0 / 2.0;

  if (distance <= 10) {
    if (flag == 0) {
      currentTime = millis();
      flag = 1;
    }

    if (millis() >= currentTime + checkTime) {
      tone(piezoPin, 1046, 200);
      delay(200);
      tone(piezoPin, 1175, 200);
      delay(200);
      tone(piezoPin, 1319, 200);
      delay(800);

      servo.write(pushAngle);
      delay(1000);
      servo.write(currentAngle);
      delay(1000);

      flag = 0;
    }
  }

  else {
    flag = 0;
    noTone(piezoPin);
  }

  delay(100);
}
