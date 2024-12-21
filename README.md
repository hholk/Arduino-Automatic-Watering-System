# Arduino Automatic Watering System

A simple yet robust Arduino/ATmega328 project for automatically watering plants using a **capacitive soil moisture sensor** and a **low-current motor**. Perfect for beginners who want a straightforward solution with clear instructions, easily adjustable parameters, and a quick start guide.

---

## Table of Contents
1. [Project Overview](#project-overview)  
2. [Features](#features)  
3. [Hardware Requirements](#hardware-requirements)  
4. [Wiring & Soldering Tips](#wiring--soldering-tips)  
5. [Software Setup (IDE)](#software-setup-ide)  
6. [Installation & Upload](#installation--upload)  
7. [Usage](#usage)  
8. [Calibration & Adjustment](#calibration--adjustment)  
9. [Troubleshooting](#troubleshooting)  
10. [Contributing](#contributing)  
11. [License](#license)  

---

## Project Overview

This repository contains:
- A well-commented Arduino **sketch** that reads the soil moisture level using a **capacitive sensor** and directly drives a **small motor** if it draws less than ~40mA.  
- A **README** with step-by-step instructions for **wiring**, **calibration**, **uploading**, and **basic soldering/wiring considerations**.

> **Note:** If your motor requires more than ~40mA, you must add a **transistor** and **flyback diode**. This project is specifically designed for very small, low-current motors.

---

## Features

- **Beginner-Friendly**: Simple code structure and abundant comments.  
- **Minimal Components**: No extra driver needed if the motor is truly low-current.  
- **Easy Calibration**: Just adjust the moisture threshold.  
- **Scalable**: Can be expanded with additional sensors, displays, or network connectivity.

---

## Hardware Requirements

1. **Arduino Board (ATmega328-based)**  
   - e.g., Arduino Uno, Nano, or Pro Mini.

2. **Capacitive Soil Moisture Sensor (V2.0)**  
   - 3 wires: Red (VCC), Black (GND), Yellow (Signal).

3. **Small Motor**  
   - Should draw less than ~40mA at 5V.  
   - Red wire = Motor +, Black wire = Motor –.  
   - If the current is higher, **use a transistor driver**.

4. **USB Cable**  
   - To connect your Arduino board to the computer for uploading the code.

5. **Breadboard & Jumpers**  
   - For easy prototyping (optional but recommended).  
   - You may also solder components for a permanent setup.

---

## Wiring & Soldering Tips

1. **Wiring**  
   - **Sensor**:  
     - Red → 5V  
     - Black → GND  
     - Yellow → A0 (Analog input on Arduino)  
   - **Motor**:  
     - Red → Digital Pin (default: D3)  
     - Black → GND  
   - Ensure all **grounds** are connected together.

2. **Soldering**  
   - If you’re making a permanent setup, **tin** the wires first (apply a bit of solder to the stripped end).  
   - Use **heat shrink** tubing or electrical tape to cover bare wire joints.  
   - Avoid cold joints: heat both the wire and the pad before applying solder for a solid connection.

3. **Safety Checks**  
   - Double-check polarity (5V vs. GND) on your sensor and motor.  
   - If the motor is bigger or you’re unsure of the current draw, **add a transistor + flyback diode** to protect the Arduino.

---

## Software Setup (IDE)

We recommend using the [**Arduino IDE**](https://www.arduino.cc/en/software) for this project:
1. **Download & Install** the Arduino IDE for your operating system.  
2. **Launch** the Arduino IDE.  
3. In the IDE, go to **Tools** → **Board** and select your board (e.g., *Arduino Uno*).  
4. In **Tools** → **Port**, choose the COM port that matches your connected Arduino.

---

## Installation & Upload

1. **Clone or Download**  
   - Clone this repo or click on “Code” → “Download ZIP” to get the project files.

2. **Open the Sketch**  
   - Extract the ZIP (if downloaded) or open the cloned folder.  
   - Locate the `automatic_watering.ino` file and open it with the Arduino IDE.

3. **Verify & Upload**  
   - Click on **Verify** (checkmark symbol) to compile the sketch.  
   - Click on **Upload** (arrow symbol) to flash the code onto the Arduino.  
   - Wait for the IDE to display “Done uploading”.

4. **Confirmation**  
   - The Serial Monitor (set to 9600 baud) should show output from the sketch once the upload succeeds.

---

## Usage

1. **Power On**  
   - Power your Arduino via USB or an external 5V supply.

2. **Serial Monitoring**  
   - Open the **Serial Monitor** at 9600 baud to see the real-time moisture values and status messages.

3. **Watch the Motor**  
   - If the moisture reading is below the threshold, the motor will run for a set duration.  
   - Otherwise, it remains off, indicating the soil is adequately moist.

---

## Calibration & Adjustment

- **`moistureThreshold`** (`int`)  
  - Default is `600`. Adjust to your sensor’s specific readings.  
  - If your dry soil reads ~300 and wet soil ~700, pick a midpoint (~500).

- **`waterTime`** (`unsigned long`)  
  - Default is `3000` ms (3 seconds). Modify if you need more or less watering time.

- **`waitTime`** (`unsigned long`)  
  - Default is `60000` ms (1 minute). You can increase this to reduce how often the system checks and waters.

---

## Troubleshooting

1. **Motor Doesn’t Spin**  
   - Check that the motor draws less than ~40mA. If it’s larger, you need a transistor driver.  
   - Double-check the wiring (motor red → D3, motor black → GND).

2. **Moisture Sensor Reading is 0 or 1023**  
   - Ensure correct connection: red → 5V, black → GND, yellow → A0.  
   - Confirm `analogRead(A0)` in the code.

3. **No Serial Output**  
   - Make sure the **Serial Monitor** is set to **9600** baud.  
   - Check that the correct COM port is selected in **Tools** → **Port**.

4. **Overheating or Reset**  
   - The motor could be pulling more current than the Arduino can handle. Use a transistor driver setup.

5. **Unstable or Erratic Readings**  
   - Check for loose wiring or poor solder joints.  
   - Sensor calibration may need adjusting (varying thresholds between different sensor batches).

---

## Contributing

1. **Fork** the repository.  
2. Create a **new branch** for your feature or bug fix.  
3. **Commit** your changes.  
4. **Open a Pull Request** describing your modifications.

---

## License

[MIT License](./LICENSE)  
Feel free to use, modify, and share this project.
