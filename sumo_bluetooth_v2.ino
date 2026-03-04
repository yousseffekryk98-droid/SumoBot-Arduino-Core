#include <SoftwareSerial.h>

// =====================
// BLUETOOTH SETUP
// =====================
// HC-05 TX to D2, RX to D3 (Use a voltage divider for RX!)
SoftwareSerial bt(2, 3); 

// =====================
// BTS7960 PINS
// =====================
// Left Side (Driver 1)
const int L_RPWM = 5;
const int L_LPWM = 6;
// Right Side (Driver 2)
const int R_RPWM = 9;
const int R_LPWM = 10;

// =====================
// CONFIG
// =====================
int speedVal = 255; // 100% Full Power for competition

void setup() {
  pinMode(L_RPWM, OUTPUT);
  pinMode(L_LPWM, OUTPUT);
  pinMode(R_RPWM, OUTPUT);
  pinMode(R_LPWM, OUTPUT);

  stopRobot();

  Serial.begin(9600);
  bt.begin(9600);

  Serial.println("SYSTEM READY");
  Serial.println("Waiting 5 seconds for match start...");
  
  // MANDATORY COMPETITION DELAY
  delay(5000); 
  
  Serial.println("BATTLE START! Use W,A,S,D (Keyboard) or F,B,L,R");
}

void loop() {
  char cmd;
  
  // Listen to USB Serial
  if (Serial.available()) {
    cmd = Serial.read();
    handleCommand(cmd);
  }
  
  // Listen to Bluetooth
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
    
    // Speed modifiers
    case '1': speedVal = 130; break;
    case '2': speedVal = 200; break;
    case '3': speedVal = 255; break;
  }
}

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
  // Left wheels BACK, Right wheels FORWARD
  analogWrite(L_RPWM, 0); analogWrite(R_LPWM, 0);
  analogWrite(L_LPWM, speedVal); 
  analogWrite(R_RPWM, speedVal); 
}

void spinRight() {
  // Right wheels BACK, Left wheels FORWARD
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
