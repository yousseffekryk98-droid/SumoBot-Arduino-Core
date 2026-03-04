// ==========================================
// SUMO ROBOT - DUAL BTS7960 - SERIAL CONTROL
// ==========================================

// LEFT SIDE MOTORS (Driver 1)
const int L_RPWM = 5;
const int L_LPWM = 6;

// RIGHT SIDE MOTORS (Driver 2)
const int R_RPWM = 9;
const int R_LPWM = 10;

// SPEED SETTING (0-255)
int speedVal = 255; // Set to MAX for competition

void setup() {
  Serial.begin(9600);
  
  pinMode(L_RPWM, OUTPUT);
  pinMode(L_LPWM, OUTPUT);
  pinMode(R_RPWM, OUTPUT);
  pinMode(R_LPWM, OUTPUT);

  stopRobot();
  
  Serial.println("--- SUMO TANK READY ---");
  Serial.println("Controls: W=Forward, S=Backward, A=Spin Left, D=Spin Right, X=Stop");
}

void loop() {
  if (Serial.available() > 0) {
    char cmd = Serial.read();
    
    // Switch handles both uppercase and lowercase
    switch (cmd) {
      case 'w': case 'W': moveForward();  break;
      case 's': case 'S': moveBackward(); break;
      case 'a': case 'A': spinLeft();     break;
      case 'd': case 'D': spinRight();    break;
      case 'x': case 'X': stopRobot();    break;
      
      // Quick Speed Adjustment
      case '1': speedVal = 100; Serial.println("Speed: 40%"); break;
      case '2': speedVal = 180; Serial.println("Speed: 70%"); break;
      case '3': speedVal = 255; Serial.println("Speed: 100%"); break;
    }
  }
}

// --- MOTION FUNCTIONS ---

void moveForward() {
  analogWrite(L_LPWM, 0); analogWrite(R_LPWM, 0); // Clear reverse
  analogWrite(L_RPWM, speedVal);
  analogWrite(R_RPWM, speedVal);
  Serial.println(">> CHARGING FORWARD");
}

void moveBackward() {
  analogWrite(L_RPWM, 0); analogWrite(R_RPWM, 0); // Clear forward
  analogWrite(L_LPWM, speedVal);
  analogWrite(R_LPWM, speedVal);
  Serial.println("<< REVERSING");
}

void spinLeft() {
  // Left side moves BACK, Right side moves FORWARD
  analogWrite(L_RPWM, 0); analogWrite(R_LPWM, 0);
  analogWrite(L_LPWM, speedVal);
  analogWrite(R_RPWM, speedVal);
  Serial.println("↺ SPINNING LEFT");
}

void spinRight() {
  // Right side moves BACK, Left side moves FORWARD
  analogWrite(L_LPWM, 0); analogWrite(R_RPWM, 0);
  analogWrite(L_RPWM, speedVal);
  analogWrite(R_LPWM, speedVal);
  Serial.println("↻ SPINNING RIGHT");
}

void stopRobot() {
  analogWrite(L_RPWM, 0); analogWrite(L_LPWM, 0);
  analogWrite(R_RPWM, 0); analogWrite(R_LPWM, 0);
  Serial.println("|| HALT");
}
