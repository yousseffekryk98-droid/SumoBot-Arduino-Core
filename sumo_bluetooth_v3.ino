#include <SoftwareSerial.h>

// =====================
// BLUETOOTH SETUP
// =====================
// HC-05 TX to Arduino D2, RX to Arduino D3 (via voltage divider)
SoftwareSerial bt(2, 3); 

// =====================
// BTS7960 PINS
// =====================
// Left Driver (Motors 1 & 2)
const int L_RPWM = 5;
const int L_LPWM = 6;
// Right Driver (Motors 3 & 4)
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

  // Ensure robot is stopped on startup
  stopRobot();

  Serial.begin(9600);
  bt.begin(9600);

  Serial.println("--- SUMO TANK INITIALIZED ---");
  Serial.println("Safety: Waiting 5 seconds to start...");
  
  // COMPETITION SAFETY DELAY (Required for most matches)
  delay(5000); 
  
  Serial.println("BATTLE START! Use W, A, S, D / F, B, L, R");
}

void loop() {
  char cmd;
  
  // Read from Serial Monitor
  if (Serial.available()) {
    cmd = Serial.read();
    handleCommand(cmd);
  }
  
  // Read from Bluetooth HC-05
  if (bt.available()) {
    cmd = bt.read();
    handleCommand(cmd);
  }
}

void handleCommand(char cmd) {
  switch (cmd) {
    case 'w': case 'F': moveForward();  break;
    case 's': case 'B': moveBackward(); break;
    case 'a': case 'L': spinLeft();     break;
    case 'd': case 'R': spinRight();    break;
    case 'x': case 'S': stopRobot();    break;
    
    // Speed modifiers (1=Low, 2=Med, 3=Max)
    case '1': speedVal = 120; Serial.println("Speed: LOW"); break;
    case '2': speedVal = 190; Serial.println("Speed: MED"); break;
    case '3': speedVal = 255; Serial.println("Speed: MAX"); break;
  }
}

// =====================
// MOVEMENT LOGIC
// =====================

void moveForward() {
  analogWrite(L_LPWM, 0); analogWrite(R_LPWM, 0); // Clear reverse
  analogWrite(L_RPWM, speedVal);
  analogWrite(R_RPWM, speedVal);
}

void moveBackward() {
  analogWrite(L_RPWM, 0); analogWrite(R_RPWM, 0); // Clear forward
  analogWrite(L_LPWM, speedVal);
  analogWrite(R_RPWM, speedVal);
}

void spinLeft() {
  // Left side moves BACK, Right side moves FORWARD
  analogWrite(L_RPWM, 0); analogWrite(R_LPWM, 0);
  analogWrite(L_LPWM, speedVal); 
  analogWrite(R_RPWM, speedVal); 
}

void spinRight() {
  // Right side moves BACK, Left side moves FORWARD
  analogWrite(L_LPWM, 0); analogWrite(R_RPWM, 0);
  analogWrite(L_RPWM, speedVal);
  analogWrite(R_LPWM, speedVal); 
}

void stopRobot() {
  analogWrite(L_RPWM, 0);
  analogWrite(L_LPWM, 0);
  analogWrite(R_RPWM, 0);
  analogWrite(R_LPWM, 0);
}
