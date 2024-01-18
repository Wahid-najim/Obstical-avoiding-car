#include <Servo.h>
Servo servoMotor; 

const int trigPin = 2;
const int echoPin = 3;
const int motor1Pin1 = 4;
const int motor1Pin2 = 5;
const int motor2Pin1 = 6;
const int motor2Pin2 = 7;
const int servoPin = 9;

long duration;
int distance;

void setup() {
  pinMode(trigPin, OUTPUT);
  pinMode(echoPin, INPUT);
  pinMode(motor1Pin1, OUTPUT);
  pinMode(motor1Pin2, OUTPUT);
  pinMode(motor2Pin1, OUTPUT);
  pinMode(motor2Pin2, OUTPUT);

  servoMotor.attach(servoPin);
  servoMotor.write(90); // Start with the servo facing forward

  Serial.begin(9600);
}

void loop() {
  distance = measureDistance();

  if (distance > 20) { // Safe distance
    moveForward();
  } else {
    stopCar();
    scanForPath();
  }
}

void moveForward() {
  digitalWrite(motor1Pin1, HIGH);
  digitalWrite(motor1Pin2, LOW);
  digitalWrite(motor2Pin1, HIGH);
  digitalWrite(motor2Pin2, LOW);
}

void stopCar() {
  digitalWrite(motor1Pin1, LOW);
  digitalWrite(motor1Pin2, LOW);
  digitalWrite(motor2Pin1, LOW);
  digitalWrite(motor2Pin2, LOW);
}

void scanForPath() {
  // Scan left
  servoMotor.write(0);
  delay(1000);
  if (measureDistance() > 20) {
    turnLeft();
    return;
  }

  // Scan right
  servoMotor.write(180);
  delay(1000);
  if (measureDistance() > 20) {
    turnRight();
    return;
  }

  // If no path is clear, turn around
  turnAround();
}

void turnLeft() {
  digitalWrite(motor1Pin1, LOW);
  digitalWrite(motor1Pin2, HIGH);
  digitalWrite(motor2Pin1, HIGH);
  digitalWrite(motor2Pin2, LOW);
  delay(500); // Adjust delay for the turn
  moveForward();
}

void turnRight() {
  digitalWrite(motor1Pin1, HIGH);
  digitalWrite(motor1Pin2, LOW);
  digitalWrite(motor2Pin1, LOW);
  digitalWrite(motor2Pin2, HIGH);
  delay(500); // Adjust delay for the turn
  moveForward();
}

void turnAround() {
  digitalWrite(motor1Pin1, LOW);
  digitalWrite(motor1Pin2, HIGH);
  digitalWrite(motor2Pin1, LOW);
  digitalWrite(motor2Pin2, HIGH);
  delay(1000); // Adjust delay for the turn
  moveForward();
}

int measureDistance() {
  digitalWrite(trigPin, LOW);
  delayMicroseconds(2);
  digitalWrite(trigPin, HIGH);
  delayMicroseconds(10);
  digitalWrite(trigPin, LOW);

  duration = pulseIn(echoPin, HIGH);
  int distance = duration * 0.034 / 2;
  return distance;
}
