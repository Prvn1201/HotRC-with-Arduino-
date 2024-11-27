// Motor A connections
const int EN_A = 3;  // ENA
const int IN1_A = 5; // Direction Pin 1 for Motor A
const int IN2_A = 6; // Direction Pin 2 for Motor A

// Motor B connections
const int IN1_B = 7; // Direction Pin 1 for Motor B
const int IN2_B = 8; // Direction Pin 2 for Motor B
const int EN_B = 9;  // ENB

// Receiver PWM pin (Channel 1)
const int receiverPin = 10; 

void setup() {
  // Set all motor control pins as output
  pinMode(EN_A, OUTPUT);
  pinMode(IN1_A, OUTPUT);
  pinMode(IN2_A, OUTPUT);
  pinMode(IN1_B, OUTPUT);
  pinMode(IN2_B, OUTPUT);
  pinMode(EN_B, OUTPUT);
  pinMode(receiverPin, INPUT);  // Read PWM input from receiver
  
  // Start the Serial Monitor
  Serial.begin(9600);

  // Set enable pins high to turn motors on
  digitalWrite(EN_A, HIGH);
  digitalWrite(EN_B, HIGH);
}

void loop() {
  // Read the receiver value (PWM signal) for Channel 1
  int receiverValue = pulseIn(receiverPin, HIGH);

  // Print the receiver value to the Serial Monitor
  Serial.print("Receiver Value: ");
  Serial.println(receiverValue);

  // Map the receiver value to the motor control
  if (receiverValue > 1500) {
    // Move right (steering input is positive)
    digitalWrite(IN1_A, HIGH);
    digitalWrite(IN2_A, LOW);
    digitalWrite(IN1_B, LOW);
    digitalWrite(IN2_B, HIGH);
    
    // Print action to the Serial Monitor
    Serial.println("Moving Right");
  }
  else if (receiverValue < 1300) {
    // Move left (steering input is negative)
    digitalWrite(IN1_A, LOW);
    digitalWrite(IN2_A, HIGH);
    digitalWrite(IN1_B, HIGH);
    digitalWrite(IN2_B, LOW);
    
    // Print action to the Serial Monitor
    Serial.println("Moving Left");
  }
  else {
    // Stop (centered input)
    digitalWrite(IN1_A, LOW);
    digitalWrite(IN2_A, LOW);
    digitalWrite(IN1_B, LOW);
    digitalWrite(IN2_B, LOW);
    
    // Print action to the Serial Monitor
    Serial.println("Stopped");
  }

  delay(50);  // Small delay for stability
}