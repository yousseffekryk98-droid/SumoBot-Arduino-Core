# 🦾 Ares-Sumo: Heavyweight Combat Unit (2.8kg Class)

An autonomous and Bluetooth-controlled Sumo Robot engineered for maximum pushing force and thermal durability. Built for high-stakes competition using a custom iron-plate chassis and high-torque DC geared motors.

---

## ⚙️ Technical Specifications

| Component | Item Details | Key Performance Spec |
| :--- | :--- | :--- |
| **Microcontroller** | Arduino Uno R3 | Central Logic & PWM Control |
| **Motors** | 4x XY36-555 DC Geared | 110 RPM / 10 kg.cm Torque (each) |
| **Motor Drivers** | 2x BTS7960 (IBT-2) | 43A High-Power H-Bridge |
| **Battery** | 4x Samsung 18650-30Q | 14.8V (4S) / 15A Continuous Discharge |
| **Communication** | HC-05 Bluetooth Module | Remote Manual Override |
| **Chassis** | Custom-Cut Iron Plate | 2.8kg Class / Integrated Heatsink |
| **Sensors** | HC-SR04 Ultrasonic | Opponent Detection & Tracking |

---

## 🛠 Engineering Highlights

### 🔋 Power System
The power plant consists of a **4S Li-ion configuration** using Samsung 30Q cells. This setup provides ~14.8V nominal voltage, delivering the high current required to prevent motor stalling during head-to-head pushes.

### ❄️ Thermal Management
To handle the 43A peak current of the **BTS7960 drivers**, the modules are mounted directly to the **iron chassis** using thermal paste. This allows the entire 2.8kg frame to act as a passive heatsink, preventing thermal cutout during prolonged combat.

### 🛡 Circuit Protection
* **Logic Levels:** A voltage divider (1kΩ / 2kΩ) is utilized on the HC-05 RX pin to safely step down the Arduino's 5V signal to 3.3V.
* **Wiring:** 2.0mm high-current silicone wiring is used for the main power loop (Battery → Drivers → Motors) to minimize voltage drop.

---

## 🧠 Software & Control
The robot features a dual-mode control system:
1. **Manual Mode:** Remote control via Bluetooth using the HC-05 module.
2. **Autonomous Mode:** (In Development) Logic utilizing the HC-SR04 for "Search & Destroy" maneuvers.

```cpp
// Example: Driving the BTS7960 with Arduino PWM! 
analogWrite(LPWM, speed); // Left side speed
analogWrite(RPWM, speed); // Right side speed
```

---

## 📁 Program Files

| File | Purpose | Control Method |
| :--- | :--- | :--- |
| `sumo_autonomous.ino` | Autonomous operation with line detection and opponent seeking | Sensors (IR + Ultrasonic) |
| `sumo_bluetooth_v1.ino` | Bluetooth control (Software Serial Pins 2,4) | HC-05 Bluetooth |
| `sumo_bluetooth_v2.ino` | Bluetooth control (Software Serial Pins 2,3) | HC-05 Bluetooth |
| `sumo_bluetooth_v3.ino` | Bluetooth control with dual input (Serial + Bluetooth) | HC-05 Bluetooth / USB Serial |
| `sumo_bluetooth_v4.ino` | Bluetooth control (alternative pin configuration) | HC-05 Bluetooth / USB Serial |
| `sumo_serial_control.ino` | USB Serial control only (no Bluetooth) | USB Serial Monitor |
| `sumo_bluetooth_simple.ino` | Simplified Bluetooth control (Software Serial Pins 10,11) | HC-05 Bluetooth |

---

## 🎮 Control Commands

### Standard Commands (All Versions)
- **W / F** → Move Forward
- **S / B** → Move Backward
- **A / L** → Spin Left
- **D / R** → Spin Right
- **X / Z** → Stop

### Speed Control
- **1** → Low Speed (40-50%)
- **2** → Medium Speed (70-75%)
- **3** → Maximum Speed (100%)

---

## 🔌 Pin Configuration

### BTS7960 H-Bridge Connections
```
Left Motor Driver:
- L_RPWM → Arduino Pin 5
- L_LPWM → Arduino Pin 6

Right Motor Driver:
- R_RPWM → Arduino Pin 9
- R_LPWM → Arduino Pin 10
```

### HC-05 Bluetooth Module (Most Versions)
```
- TX (Module) → Arduino Pin 2
- RX (Module) → Arduino Pin 3 (with voltage divider)
- VCC → 5V
- GND → GND
```

### Sensor Pins (Autonomous Version)
```
- Line Sensor → Pin 2
- Ultrasonic Trigger → Pin 11
- Ultrasonic Echo → Pin 12
```

---

## ⚡ Performance Notes
- **Max Current Draw:** 43A per driver module
- **Motor Torque Rating:** 10 kg.cm per motor
- **Pushing Force:** Approximately 40 kg at full throttle
- **Competition Weight Class:** 2.8kg

---

## 🚀 Getting Started
1. Upload desired `.ino` file to Arduino Uno
2. Check pin configurations match your hardware
3. Power on and verify motor response
4. Test control via Bluetooth or Serial monitor
5. Calibrate sensor thresholds if using autonomous mode

---
<img width="1200" height="1600" alt="image" src="https://github.com/user-attachments/assets/0fda4216-2a4f-4152-b249-0814f1bdfafd" />

## 👨‍💻 Developer
**Developed by Youssef Mohamed Fekry**  
Computer Science Major | Robotics Enthusiast
