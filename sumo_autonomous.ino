// Motor Pins (Assuming an L298N or similar driver)
const int IN1 = 5; 
const int IN2 = 6;
const int IN3 = 9;
const int IN4 = 10;

// Sensor Pins
const int lineSensor = 2;   // Digital IR sensor for the white ring
const int trigPin = 11;     // Ultrasonic Trigger
const int echoPin = 12;     // Ultrasonic Echo

void setup() {
  pinMode(IN1, OUTPUT); pinMode(IN2, OUTPUT);
  pinMode(IN3, OUTPUT); pinMode(IN4, OUTPUT);
  pinMode(lineSensor, INPUT);
  pinMode(trigPin, OUTPUT);
  pinMode(echoPin, INPUT);
  
  // 5-second safety delay required by most competitions
  delay(5000); 
}

void loop() {
  int lineDetected = digitalRead(lineSensor);
  long distance = getDistance();

  if (lineDetected == LOW) { // Assuming LOW means white line detected
    reverseAndTurn();
  } 
  else if (distance < 40) { // Opponent detected within 40cm
    attack();
  } 
  else {
    scan(); // Rotate slowly to find the opponent
  }
}

long getDistance() {
  digitalWrite(trigPin, LOW); delayMicroseconds(2);
  digitalWrite(trigPin, HIGH); delayMicroseconds(10);
  digitalWrite(trigPin, LOW);
  long duration = pulseIn(echoPin, HIGH);
  return duration * 0.034 / 2;
}

void attack() {
  analogWrite(IN1, 255); digitalWrite(IN2, LOW);
  analogWrite(IN3, 255); digitalWrite(IN4, LOW);
}

void scan() {
  analogWrite(IN1, 150); digitalWrite(IN2, LOW);
  digitalWrite(IN3, LOW); analogWrite(IN4, 150);
}

void reverseAndTurn() {
  // Move back
  digitalWrite(IN1, LOW); analogWrite(IN2, 200);
  digitalWrite(IN3, LOW); analogWrite(IN4, 200);
  delay(500);
  // Sharp turn
  analogWrite(IN1, 200); digitalWrite(IN2, LOW);
  digitalWrite(IN3, LOW); analogWrite(IN4, 200);
  delay(300);
}
