#include <SoftwareSerial.h>

// ==========================================
// SUMO TANK - DUAL BTS7960 - BLUETOOTH CONTROL
// ==========================================

// Bluetooth Pins: HC-05 TX -> Pin 2, HC-05 RX -> Pin 4
SoftwareSerial bt(2, 4); 

// Motor Pins (As per your setup)
#define L_RPWM 5
#define L_LPWM 6
#define R_RPWM 3
#define R_LPWM 11

int speedVal = 255; // FULL POWER for maximum torque

void setup() {
  // Motor Output Pins
  pinMode(L_RPWM, OUTPUT);
  pinMode(L_LPWM, OUTPUT);
  pinMode(R_RPWM, OUTPUT);
  pinMode(R_LPWM, OUTPUT);

  // Start in Stopped State
  stopRobot();

  Serial.begin(9600); // For USB Monitoring
  bt.begin(9600);     // For Bluetooth Control
  
  Serial.println("Sumo Robot Initialized...");
  Serial.println("Ready for Bluetooth Commands: F, B, L, R, S");
}

void loop() {
  if (bt.available()) {
    char cmd = bt.read();
    Serial.print("Bluetooth Command: ");
    Serial.println(cmd);

    switch (cmd) {
      case 'F': case 'w': moveForward(); break;
      case 'B': case 's': moveBackward(); break;
      case 'L': case 'a': turnLeft(); break;
      case 'R': case 'd': turnRight(); break;
      case 'S': case 'z': stopRobot(); break;
      
      // Speed presets
      case '1': speedVal = 100; break;
      case '2': speedVal = 180; break;
      case '3': speedVal = 255; break;
    }
  }
}

// =====================
// MOVEMENT FUNCTIONS
// =====================

void stopRobot() {
  analogWrite(L_RPWM, 0); analogWrite(L_LPWM, 0);
  analogWrite(R_RPWM, 0); analogWrite(R_LPWM, 0);
}

void moveForward() {
  // Balanced according to your inverted signal logic
  analogWrite(L_LPWM, 0);
  analogWrite(L_RPWM, speedVal);
  
  analogWrite(R_RPWM, 0);
  analogWrite(R_LPWM, speedVal); 
}

void moveBackward() {
  analogWrite(L_RPWM, 0);
  analogWrite(L_LPWM, speedVal);
  
  analogWrite(R_LPWM, 0);
  analogWrite(R_RPWM, speedVal);
}

void turnLeft() {
  // Spin in place (Left back, Right forward)
  analogWrite(L_RPWM, 0);
  analogWrite(L_LPWM, speedVal);
  
  analogWrite(R_RPWM, 0);
  analogWrite(R_LPWM, speedVal);
}

void turnRight() {
  // Spin in place (Left forward, Right back)
  analogWrite(L_LPWM, 0);
  analogWrite(L_RPWM, speedVal);
  
  analogWrite(R_LPWM, 0);
  analogWrite(R_RPWM, speedVal);
}
