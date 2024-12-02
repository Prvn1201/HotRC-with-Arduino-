// Motor pins for Motors A, B, and C
int EN_A = 3;  // PWM pin for motor A speed control
int IN1_A = 5;
int IN2_A = 6;
int EN_B = 9;  // PWM pin for motor B speed control
int IN1_B = 7;
int IN2_B = 8;

// Motor C pins (third motor)
int IN3 = 12;  // Pin connected to IN3 on motor driver C
int IN4 = 2;   // Pin connected to IN4 on motor driver C

// Receiver pins
int steeringPin = 10;  // Steering connected to pin 10 (Channel 1)
int throttlePin = 11;  // Throttle connected to pin 11 (Channel 2)
int channel3Pin = 4;   // Channel 3 for controlling motor C

// Threshold values for throttle (for forward/backward)
int throttleNeutral = 1380;
int throttleForward = 1880;
int throttleBackward = 902;
int throttleThreshold = 50;  // Small margin to detect neutral range

// Steering center (neutral) and threshold for turning
int steeringNeutral = 1500;
int steeringLeft = 2000;
int steeringRight = 1000;
int steeringThreshold = 200;  // Deadzone for steering (adjustable)

// Speed settings
int maxSpeed = 255;  // Maximum speed
int turnSpeed = 180; // Reduced speed when turning (adjustable)

void setup() {
  // Motor setup for A, B, and C
  pinMode(EN_A, OUTPUT);
  pinMode(IN1_A, OUTPUT);
  pinMode(IN2_A, OUTPUT);
  pinMode(EN_B, OUTPUT);
  pinMode(IN1_B, OUTPUT);
  pinMode(IN2_B, OUTPUT);
  pinMode(IN3, OUTPUT);  // Motor C control
  pinMode(IN4, OUTPUT);

  // Receiver setup
  pinMode(steeringPin, INPUT);
  pinMode(throttlePin, INPUT);
  pinMode(channel3Pin, INPUT);

  // Initialize motor speed control (PWM)
  analogWrite(EN_A, maxSpeed);  // Full speed for motor A
  analogWrite(EN_B, maxSpeed);  // Full speed for motor B

  Serial.begin(9600);
}

void loop() {
  // Read receiver values
  int throttleValue = pulseIn(throttlePin, HIGH);
  int steeringValue = pulseIn(steeringPin, HIGH);
  int channel3Value = pulseIn(channel3Pin, HIGH);  // Motor C control

  // Print receiver values for debugging
  Serial.print("Throttle: ");
  Serial.print(throttleValue);
  Serial.print(" Steering: ");
  Serial.print(steeringValue);
  Serial.print(" Channel 3 (Motor C): ");
  Serial.println(channel3Value);

  // Control motors based on throttle input (A and B)
  if (throttleValue > throttleForward - throttleThreshold) {
    // Move forward
    analogWrite(EN_A, maxSpeed); // Full speed when moving forward
    analogWrite(EN_B, maxSpeed); // Full speed when moving forward
    digitalWrite(IN1_A, HIGH);
    digitalWrite(IN2_A, LOW);
    digitalWrite(IN1_B, HIGH);
    digitalWrite(IN2_B, LOW);
    Serial.println("Moving Forward");
  } else if (throttleValue < throttleBackward + throttleThreshold) {
    // Move backward
    analogWrite(EN_A, maxSpeed); // Full speed when moving backward
    analogWrite(EN_B, maxSpeed); // Full speed when moving backward
    digitalWrite(IN1_A, LOW);
    digitalWrite(IN2_A, HIGH);
    digitalWrite(IN1_B, LOW);
    digitalWrite(IN2_B, HIGH);
    Serial.println("Moving Backward");
  } else {
    // Stop motors when throttle is in neutral range
    analogWrite(EN_A, 0);  // Stop motor A
    analogWrite(EN_B, 0);  // Stop motor B
    digitalWrite(IN1_A, LOW);
    digitalWrite(IN2_A, LOW);
    digitalWrite(IN1_B, LOW);
    digitalWrite(IN2_B, LOW);
    Serial.println("Motors Stopped");
  }

  // Control steering based on steering input
  if (steeringValue > steeringLeft - steeringThreshold) {
    // Turn left, reduce speed for smoother turn
    analogWrite(EN_A, turnSpeed); // Reduced speed during turn
    analogWrite(EN_B, turnSpeed); // Reduced speed during turn
    digitalWrite(IN1_A, LOW);
    digitalWrite(IN2_A, HIGH);
    digitalWrite(IN1_B, HIGH);
    digitalWrite(IN2_B, LOW);
    Serial.println("Turning Left");
  } else if (steeringValue < steeringRight + steeringThreshold) {
    // Turn right, reduce speed for smoother turn
    analogWrite(EN_A, turnSpeed); // Reduced speed during turn
    analogWrite(EN_B, turnSpeed); // Reduced speed during turn
    digitalWrite(IN1_A, HIGH);
    digitalWrite(IN2_A, LOW);
    digitalWrite(IN1_B, LOW);
    digitalWrite(IN2_B, HIGH);
    Serial.println("Turning Right");
  }

  // Control third motor (C) based on Channel 3 input
  if (channel3Value > 1800) {  // Channel 3 for forward movement of motor C
    digitalWrite(IN3, HIGH);  // IN3 HIGH to move forward for motor C
    digitalWrite(IN4, LOW);   // IN4 LOW to move forward
    Serial.println("Motor C is moving forward.");
  } else {  
    digitalWrite(IN3, LOW);   // IN3 LOW to stop motor C
    digitalWrite(IN4, LOW);   // IN4 LOW to stop motor C
    Serial.println("Motor C is stopped.");
  }

  delay(100);  // Adjust delay as needed for responsiveness
}
