// Motor pins
int EN_A = 3;  // PWM pin for motor A speed control
int IN1_A = 5;
int IN2_A = 6;
int IN1_B = 7;
int IN2_B = 8;
int EN_B = 9;  // PWM pin for motor B speed control

// Receiver pins
int steeringPin = 10;  // Steering connected to pin 10 (Channel 1)
int throttlePin = 11;  // Throttle connected to pin 11 (Channel 2)

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
  // Motor setup
  pinMode(EN_A, OUTPUT);
  pinMode(IN1_A, OUTPUT);
  pinMode(IN2_A, OUTPUT);
  pinMode(IN1_B, OUTPUT);
  pinMode(IN2_B, OUTPUT);
  pinMode(EN_B, OUTPUT);

  // Receiver setup
  pinMode(steeringPin, INPUT);
  pinMode(throttlePin, INPUT);

  // Initialize motor speed control (PWM)
  analogWrite(EN_A, maxSpeed);  // Full speed for motor A
  analogWrite(EN_B, maxSpeed);  // Full speed for motor B

  Serial.begin(9600);
}

void loop() {
  // Read receiver values
  int throttleValue = pulseIn(throttlePin, HIGH);
  int steeringValue = pulseIn(steeringPin, HIGH);

  // Print receiver values for debugging
  Serial.print("Throttle: ");
  Serial.print(throttleValue);
  Serial.print(" Steering: ");
  Serial.println(steeringValue);

  // Control motors based on throttle input
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

  delay(100);  // Adjust delay as needed for responsiveness
}