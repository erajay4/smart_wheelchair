#include<AFMotor.h>
#include<Servo.h>
Servo name_servo;
AF_DCMotor motorR(4);
AF_DCMotor motorL(1);
char cmd;
int servo_position = 0;
int trigPin = 3;
int echoPin = 2;
int distance;
long duration;
void setup() 
{
  Serial.begin(9600);
  pinMode(trigPin, OUTPUT);
  pinMode(echoPin, INPUT);
  motorR.setSpeed(80);
  motorR.run(RELEASE);
  motorL.setSpeed(60);
  motorL.run(RELEASE);
  name_servo.attach(10);
}
void loop()
{
  digitalWrite(trigPin, LOW);
  delayMicroseconds(2);
  digitalWrite(trigPin, HIGH);
  delayMicroseconds(10);
  digitalWrite(trigPin, LOW);
  duration = pulseIn(echoPin, HIGH);
  distance = (duration*0.034/2);
  if(distance<=20)
  {
    motorR.run(RELEASE);
    motorL.run(RELEASE);
    delay(1000);
    motorR.run(BACKWARD);
    motorL.run(BACKWARD);
    delay(1000);
    motorR.run(RELEASE);
    motorL.run(RELEASE);
    delay(1000);
    for(servo_position=0; servo_position<=90; servo_position+=1)
    {
      name_servo.write(servo_position);
    }
    delay(1000);
    motorR.run(FORWARD);
    motorL.run(FORWARD);
    delay(1400);
    motorR.run(RELEASE);
    motorL.run(RELEASE);
    delay(1000);
    for(servo_position=90; servo_position>=0; servo_position-=1)
    {
      name_servo.write(servo_position); 
    }
    delay(1000);
    control();
  }
  else if(distance>20)
  {
    control();
  }
}

void control() 
{
  if(Serial.available()>0)
  {
    cmd = Serial.read();
    switch(cmd)
    {
      case 'f':
      {
        forward();
        break;
      }
      case 'b':
      {
        back();
        break;
      }
      case 's':
      {
        Stop();
        break;
      }
      case 'r':
      {
        right();
        break;
      }
      case 'l':
      {
        left();
        break;
      }
    }
  }
}
void forward()
{
  motorR.run(FORWARD);
  motorL.run(FORWARD);
}
void back()
{
  motorR.run(BACKWARD);
  motorL.run(BACKWARD);
}
void Stop()
{
  motorR.run(RELEASE);
  motorL.run(RELEASE);
}
void right()
{
  motorR.run(RELEASE);
  motorL.run(RELEASE);
  delay(1000);
  for(servo_position=0; servo_position<=90; servo_position+=1)
  {
    name_servo.write(servo_position);
  }
  delay(1000);
  motorR.run(FORWARD);
  motorL.run(FORWARD);
  delay(1400);
  motorR.run(RELEASE);
  motorL.run(RELEASE);
  delay(1000);
  for(servo_position=90; servo_position>=0; servo_position-=1)
  {
    name_servo.write(servo_position);
  }
  control();
}
void left()
{
  motorR.run(RELEASE);
  motorL.run(RELEASE);
  delay(1000);
  for(servo_position=0; servo_position<=90; servo_position+=1)
  {
    name_servo.write(servo_position);
  }
  delay(1000);
  motorR.run(BACKWARD);
  motorL.run(BACKWARD);
  delay(1300);
  motorR.run(RELEASE);
  motorL.run(RELEASE);
  delay(1000);
  for(servo_position=90; servo_position>=0; servo_position-=1)
  {
    name_servo.write(servo_position);
  }
  control();
}
