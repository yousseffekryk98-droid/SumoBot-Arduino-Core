#include <SoftwareSerial.h>

// Bluetooth Pins
SoftwareSerial BTSerial(10, 11); // RX, TX

// BTS7960 Motor Driver Pins (Left Side)
const int L_PWM = 5; 
const int L_EN = 7;
// BTS7960 Motor Driver Pins (Right Side)
const int R_PWM = 6; 
const int R_EN = 8;

// Sensors
const int trigPin = A0;
const int echoPin = A1;

void setup() {
  BTSerial.begin(9600);
  pinMode(L_PWM, OUTPUT); pinMode(L_EN, OUTPUT);
  pinMode(R_PWM, OUTPUT); pinMode(R_EN, OUTPUT);
  
  // Enable the drivers
  digitalWrite(L_EN, HIGH);
  digitalWrite(R_EN, HIGH);
}

void loop() {
  if (BTSerial.available()) {
    char command = BTSerial.read();
    executeCommand(command);
  }
}

void moveForward(int speed) {
  analogWrite(L_PWM, speed);
  analogWrite(R_PWM, speed);
}

void executeCommand(char cmd) {
  switch(cmd) {
    case 'F': moveForward(255); break; // Full speed ahead
    case 'S': moveForward(0); break;   // Stop
    // Add more cases for Turn/Reverse
  }
}
