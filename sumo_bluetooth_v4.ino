#include <SoftwareSerial.h>

// =====================
// BLUETOOTH SETUP
// =====================
// HC-05 TX to Arduino D2, RX to Arduino D3 (via 1k/2k voltage divider)
SoftwareSerial bt(2, 3); 

// =====================
// BTS7960 PINS
// =====================
// Left Driver
const int L_RPWM = 5;
const int L_LPWM = 6;
// Right Driver
const int R_RPWM = 9;
const int R_LPWM = 10;

// =====================
// CONFIG
// =====================
int speedVal = 255; // 100% Power for XY36-555 Torque

void setup() {
  // Pin Modes
  pinMode(L_RPWM, OUTPUT);
  pinMode(L_LPWM, OUTPUT);
  pinMode(R_RPWM, OUTPUT);
  pinMode(R_LPWM, OUTPUT);

  stopRobot();

  Serial.begin(9600);
  bt.begin(9600);

  Serial.println("SYSTEM READY");
  Serial.println("Waiting 5 seconds for match start...");
  
  // COMPETITION SAFETY DELAY
  delay(5000); 
  
  Serial.println("BATTLE START! Use W, A, S, D or F, B, L, R");
}

void loop() {
  char cmd;
  
  // Listen to both Serial Monitor and Bluetooth
  if (Serial.available()) {
    cmd = Serial.read();
    handleCommand(cmd);
  }
  if (bt.available()) {
    cmd = bt.read();
    handleCommand(cmd);
  }
}

void handleCommand(char cmd) {
  switch (cmd) {
    case 'w': case 'F': moveForward(); break;
    case 's': case 'B': moveBackward(); break;
    case 'a': case 'L': spinLeft(); break;
    case 'd': case 'R': turnRight(); break; // spinRight
    case 'x': case 'S': stopRobot(); break;
    
    // Speed modifiers
    case '1': speedVal = 150; break;
    case '2': speedVal = 200; break;
    case '3': speedVal = 255; break;
  }
}

// =====================
// MOVEMENT LOGIC
// =====================

void moveForward() {
  analogWrite(L_LPWM, 0); analogWrite(R_LPWM, 0);
  analogWrite(L_RPWM, speedVal);
  analogWrite(R_RPWM, speedVal);
}

void moveBackward() {
  analogWrite(L_RPWM, 0); analogWrite(R_RPWM, 0);
  analogWrite(L_LPWM, speedVal);
  analogWrite(R_LPWM, speedVal);
}

void spinLeft() {
  analogWrite(L_RPWM, 0); analogWrite(R_LPWM, 0);
  analogWrite(L_LPWM, speedVal); // Left Back
  analogWrite(R_RPWM, speedVal); // Right Forward
}

void turnRight() {
  analogWrite(L_LPWM, 0); analogWrite(R_RPWM, 0);
  analogWrite(L_RPWM, speedVal); // Left Forward
  analogWrite(R_LPWM, speedVal); // Right Back
}

void stopRobot() {
  analogWrite(L_RPWM, 0);
  analogWrite(L_LPWM, 0);
  analogWrite(R_RPWM, 0);
  analogWrite(R_LPWM, 0);
}
