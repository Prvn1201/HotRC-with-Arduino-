#include <L298NX2.h>

// Pin definition for L298N
const unsigned int EN_A = 3;
const unsigned int IN1_A = 5;
const unsigned int IN2_A = 6;
const unsigned int IN1_B = 7;
const unsigned int IN2_B = 8;
const unsigned int EN_B = 9;

// RC receiver signal input pin for Channel 2 (Throttle)
const int ch2Pin = 11;  // Channel 2 connected to Arduino pin 11

// PWM signal variable
int ch2Value;

// Thresholds for throttle behavior
const int forwardValue = 870;   // Forward throttle value
const int neutralValue = 1375; // Neutral position value (stop)
const int backwardValue = 1875; // Backward throttle value

// Tolerance for neutral
const int neutralTolerance = 50;  // Adjust if needed for stability

// Initialize motor controller
L298NX2 motors(EN_A, IN1_A, IN2_A, EN_B, IN1_B, IN2_B);

void setup() {
  // Set RC receiver pin as input
  pinMode(ch2Pin, INPUT);

  // Initialize serial monitor for debugging
  Serial.begin(9600);

  // Set default motor speed
  motors.setSpeed(255);  // Full speed
}

void loop() {
  // Read PWM value from Channel 2
  ch2Value = pulseIn(ch2Pin, HIGH, 25000);  // Read throttle signal

  // Debugging: Print the PWM value
  Serial.print("CH2 Value: ");
  Serial.println(ch2Value);

  // Determine motor behavior based on throttle input
  if (abs(ch2Value - neutralValue) <= neutralTolerance) {
    // Neutral position (stop motor)
    motors.stop();
    Serial.println("Throttle neutral. Motors stopped.");
  } else if (ch2Value > forwardValue - neutralTolerance && ch2Value < forwardValue + neutralTolerance) {
    // Forward motion
    motors.forward();
    Serial.println("Moving forward.");
  } else if (ch2Value > backwardValue - neutralTolerance && ch2Value < backwardValue + neutralTolerance) {
    // Backward motion
    motors.backward();
    Serial.println("Moving backward.");
  } else {
    // Out-of-range or invalid signal
    Serial.println("Invalid or out-of-range signal. Motors stopped.");
    motors.stop();
  }

  delay(50);  // Small delay for stability
}