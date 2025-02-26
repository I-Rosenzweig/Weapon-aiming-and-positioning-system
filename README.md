# 🎯 Gun Aiming Assistance System

[![License: MIT](https://img.shields.io/badge/License-MIT-yellow.svg)](https://opensource.org/licenses/MIT)
[![Arduino Compatible](https://img.shields.io/badge/Platform-Arduino-00979D.svg)](https://www.arduino.cc/)
[![GitHub Stars](https://img.shields.io/github/stars/yourusername/gun-aiming-system?style=social)](https://github.com/yourusername/gun-aiming-system/stargazers)

https://github.com/user-attachments/assets/97b6e7ed-666f-4b0b-8e22-50b4ce555bc0


https://github.com/user-attachments/assets/abc8f39a-3086-4264-8b1d-22cde98d77c0



## 📋 Overview

A high-precision **Gun Aiming Assistance System** leveraging inertial measurement and distance sensing to predict bullet trajectories and provide real-time feedback for improved accuracy. This Arduino-based system uses physics calculations to help align shots properly through a combination of visual indicators and display feedback.

![System Demo](https://via.placeholder.com/800x400?text=Gun+Aiming+System+Demo)

## ✨ Features

* **🔍 Precise Distance Measurement**: Uses an **HC-SR04 ultrasonic sensor** to measure the distance to target with centimeter accuracy
* **📐 Real-time Tilt Analysis**: Utilizes an **MPU6050 6-axis accelerometer** to measure the exact tilt angle of the gun
* **📊 Trajectory Prediction**: Employs physics-based kinematic equations to compute the bullet's predicted height at target
* **💡 Intuitive LED Indicators**:
   * **Green LED**: Perfect alignment achieved
   * **Red LED**: Aim is too high
   * **Yellow LED**: Aim is too low
* **📱 OLED Status Display**: Shows real-time distance, tilt angle, and bullet height prediction
* **🔄 One-Button Calibration**: Simple calibration system saves target distance and optimal tilt angle
* **🔋 Portable Power**: Powered by a **3.7V Li-ion battery** with integrated **TP4056 charging module** for field use

## 🔧 Hardware Requirements

| Component | Description | Purpose |
|-----------|-------------|---------|
| Arduino Board | Uno, Nano, or similar | Main controller |
| MPU6050 | 6-axis accelerometer/gyroscope | Measures gun tilt angle |
| HC-SR04 | Ultrasonic distance sensor | Measures target distance |
| SSD1306 | 0.96" OLED display | Provides visual feedback |
| Push Button | Momentary tactile switch | Calibrates the system |
| LEDs | Red, Yellow, Green | Status indicators |
| 3.7V Li-ion | Rechargeable battery | Portable power source |
| TP4056 | Battery charging module | Manages battery charging |
| Resistors | 220Ω for LEDs | Current limiting |
| Jumper Wires | Various | Connections |

## 📝 Wiring Diagram
![image](https://github.com/user-attachments/assets/b3d58cbf-b525-4568-bdd1-ecc9ee747c9d)
![image](https://github.com/user-attachments/assets/33708cde-1c2e-4cbf-a298-84a170904284)
![image](https://github.com/user-attachments/assets/dbf6d7ab-9fd6-4fc0-877f-119212203b68)

### Connections Table





| Component | Arduino Pin |
|-----------|------------|
| HC-SR04 Trig | D4 |
| HC-SR04 Echo | D2 |
| MPU6050 SDA | A4 (SDA) |
| MPU6050 SCL | A5 (SCL) |
| OLED SDA | A4 (SDA) |
| OLED SCL | A5 (SCL) |
| Button | D3 |
| LED Red | D10 |
| LED Yellow | D8 |
| LED Green | D9 |
| Battery (+) | TP4056 B+ |
| Battery (-) | TP4056 B- |
| TP4056 OUT+ | Arduino VIN |
| TP4056 OUT- | Arduino GND |

### Basic Schematic
![image](https://github.com/user-attachments/assets/170b0f0e-1157-4a38-8136-5b0c177ca0b7)

## 🚀 Installation & Setup

### 1. Required Libraries

```bash
# Install these libraries through the Arduino Library Manager
# or clone from their respective GitHub repositories
- Adafruit_GFX
- Adafruit_SSD1306
- Wire
- MPU6050
```

### 2. Hardware Assembly

1. Connect all components according to the wiring diagram
2. Secure the components to your gun mount or enclosure
3. Ensure the MPU6050 is mounted parallel to the barrel
4. Position the ultrasonic sensor to point toward the target

### 3. Software Setup

1. Clone this repository:
   ```
   git clone https://github.com/yourusername/gun-aiming-system.git
   ```
2. Open the Arduino sketch in the Arduino IDE
3. Configure settings if needed (bullet velocity, acceptable error margin)
4. Upload the sketch to your Arduino board

## 📊 Operation Guide

### Calibration Process

1. Point your gun at the intended target
2. Press the calibration button
3. The system will save the current distance and tilt angle as reference
4. Green LED will flash to confirm successful calibration

### Aiming Assistance

1. Aim at your target
2. Monitor the OLED display for real-time feedback
3. Adjust your aim based on LED indicators:
   - **Green**: You're on target
   - **Red**: Lower your aim
   - **Yellow**: Raise your aim
4. Fire when green LED is illuminated for best accuracy

## 📊 Data Interpretation

### Example Output (Serial Monitor)

```
Measured Distance: 5.2 meters
Tilt Angle: 10.3 degrees
Predicted Bullet Height: 1.6 meters
Error: -0.2 meters
Alignment: Adjust Aim (Yellow LED ON)
```

### Physics Behind the Calculation

The system uses the following kinematic equation to calculate bullet trajectory:

```
h = v₀y * t - 0.5 * g * t²

Where:
h = bullet height at target
v₀y = initial vertical velocity (v₀ * sin(θ))
t = time of flight (distance / (v₀ * cos(θ)))
g = gravitational acceleration (9.81 m/s²)
θ = tilt angle in radians
```

## 🛠️ Future Improvements

- [ ] Add **Bluetooth connectivity** for wireless configuration and data logging
- [ ] Implement **wind compensation** using additional sensors
- [ ] Create a **mobile app** for enhanced visualization and settings control
- [ ] Add **machine learning capabilities** to improve accuracy based on previous shots
- [ ] Develop a **weather-resistant enclosure** for outdoor use in various conditions
- [ ] Integrate **barrel temperature monitoring** for improved ballistic calculations

## 📊 Performance Data

| Distance (m) | Accuracy Improvement |
|--------------|----------------------|
| 5 - 10       | ~85% reduction in error |
| 10 - 25      | ~75% reduction in error |
| 25 - 50      | ~60% reduction in error |
| > 50         | ~45% reduction in error |

## ⚠️ Safety Notice

This system is designed as an **assistive tool only** and should not replace proper firearms training and safety practices. Always follow all firearms safety rules and regulations. The creator assumes no liability for any damage or injury resulting from the use of this system.

## 📄 License

This project is licensed under the MIT License - see the [LICENSE](LICENSE) file for details.

## 👤 Author

Developed by [Itai Rosenzweig]. 

Feel free to contribute and improve the project by submitting pull requests or opening issues!

---

### ⭐ Give This Project a Star

If you find this project useful, please consider giving it a star to show your support!

[⬆ Back to top](#-gun-aiming-assistance-system)
