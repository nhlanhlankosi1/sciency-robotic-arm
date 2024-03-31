#include <Servo.h>

//Servo code: Servo1 is the base Servo and we count up to the top servo which is Servo5
const int servo1Pin = 3;
const int servo2Pin = 4;
const int servo3Pin = 5;
const int servo4Pin = 6;
const int servo5Pin = 7;

Servo servo1;  //Base servo
Servo servo2;
Servo servo3;
Servo servo4;
Servo servo5;  //Hand servo. This is the servo located at the very top and its used to grabs items when button is pressed

const int leftJoyXPin = A0;
const int leftJoyYPin = A1;
const int rightJoyXPin = A2;
const int rightJoyYPin = A3;

int leftJoyXValue = 0;
int leftJoyYValue = 0;
int rightJoyXValue = 0;
int rightJoyYValue = 0;

int prevLeftJoyXValue = 0;
int prevLeftJoyYValue = 0;
int prevRightJoyXValue = 0;
int prevRightJoyYValue = 0;

/* This value is the absolute difference between the current joystick 
position and the previous joystick position. It is used to indicate 
a significant change in joystick position, and the servo position is 
updated accordingly. This helps prevent small fluctuations in joystick 
position from continuously triggering servo movements when the joystick 
is not being actively controlled. */
const int significantJoystickMovementThreshold = 10;

int pushButton = 8;
bool isButtonPressed = false;

void setup() {
  servo1.attach(servo1Pin);
  servo2.attach(servo2Pin);
  servo3.attach(servo3Pin);
  servo4.attach(servo4Pin);
  servo5.attach(servo5Pin);
  pinMode(pushButton, INPUT);
  Serial.begin(9600);
}

void loop() {
  //Get joystick analog values
  leftJoyXValue = analogRead(leftJoyXPin);
  leftJoyYValue = analogRead(leftJoyYPin);
  rightJoyXValue = analogRead(rightJoyXPin);
  rightJoyYValue = analogRead(rightJoyYPin);

  //Read push button value
  int pushButtonValue = digitalRead(pushButton);

  // Control servo1 (base servo)
  int servo1Pos = map(leftJoyXValue, 0, 1023, 0, 180);
  if (abs(leftJoyXValue - prevLeftJoyXValue) > significantJoystickMovementThreshold) {
    servo1.write(servo1Pos);
    prevLeftJoyXValue = leftJoyXValue;
  }

  // Control servo2 (vertical servo)
  int servo2Pos = map(leftJoyYValue, 0, 1023, 0, 180);
  if (abs(leftJoyYValue - prevLeftJoyYValue) > significantJoystickMovementThreshold) {
    servo2.write(servo2Pos);
    prevLeftJoyYValue = leftJoyYValue;
  }

  // Control servo3
  int servo3Pos = map(rightJoyXValue, 0, 1023, 0, 180);
  if (abs(rightJoyXValue - prevRightJoyXValue) > significantJoystickMovementThreshold) {
    servo3.write(servo3Pos);
    prevRightJoyXValue = rightJoyXValue;
  }

  // Control servo4
  int servo4Pos = map(rightJoyYValue, 0, 1023, 0, 180);
  if (abs(rightJoyYValue - prevRightJoyYValue) > significantJoystickMovementThreshold) {
    servo4.write(servo4Pos);
    prevRightJoyYValue = rightJoyYValue;
  }

  // Button logic for controlling servo5 (hand servo)
  if (pushButtonValue == HIGH) {
    if (isButtonPressed) {
      servo5.write(0);  // Close hand (move to 0 degrees)
      isButtonPressed = false;
    } else {
      servo5.write(30);  // Open hand (move to 30 degrees)
      isButtonPressed = true;
    }
    delay(200);  // Debounce delay
  }

  delay(10);  // Adjust the delay as needed for smoother control
}
