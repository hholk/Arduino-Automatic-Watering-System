# Arduino-Automatic-Watering-System
# Arduino Automatic Watering System

A simple yet robust Arduino/ATmega328 project for automatically watering plants using a **capacitive soil moisture sensor** and a **low-current motor**. Perfect for beginners who want a straightforward solution with clear instructions and easily adjustable parameters.

---

## Table of Contents
1. [Project Overview](#project-overview)  
2. [Features](#features)  
3. [Hardware Requirements](#hardware-requirements)  
4. [Installation & Setup](#installation--setup)  
5. [Usage](#usage)  
6. [Calibration & Adjustment](#calibration--adjustment)  
7. [Troubleshooting](#troubleshooting)  
8. [Contributing](#contributing)  
9. [License](#license)  
10. [Contact](#contact)

---

## Project Overview

This repository provides:
- A well-commented Arduino **sketch** that reads the soil moisture level using a capacitive sensor and controls a low-current motor directly from a digital pin.  
- A detailed **README** explaining every step to get started quickly, including **wiring**, **calibration**, and **testing**.

> **Note:** If your motor requires more than ~40mA, you must add a **transistor** and **flyback diode**. This project is specifically designed for very small motors that the Arduino pin can handle directly without damage.

---

## Features

- **Beginner-Friendly**: Simple code structure with plenty of comments.  
- **Minimal Components**: No extra driver needed if the motor draws very little current.  
- **Customizable**: Easily adjust thresholds, watering duration, and measurement intervals.  
- **Scalable**: Can be extended to multiple sensors, displays, or network connectivity.

---

## Hardware Requirements

1. **Arduino Board (ATmega328-based)**  
   - e.g., Arduino Uno, Nano, or Pro Mini.

2. **Capacitive Soil Moisture Sensor (V2.0)**  
   - 3 wires: Red (VCC), Black (GND), Yellow (Signal).

3. **Small Motor**  
   - Should draw less than ~40mA at 5V.  
   - Red wire = motor +, Black wire = motor –.

4. **USB Cable**  
   - To connect your Arduino board to the computer for uploading the code.

5. **Breadboard & Jumpers**  
   - For easy prototyping (optional but recommended).

---

## Installation & Setup

1. **Clone or Download**  
   - Clone this repo or click on “Code” → “Download ZIP” to get the project files.

2. **Open in Arduino IDE**  
   - [Install Arduino IDE](https://www.arduino.cc/en/software) if you haven’t already.  
   - Launch the IDE and open the `automatic_watering.ino` file (or the `.ino` file provided in this repo).

3. **Board & Port**  
   - Select your board under **Tools** → **Board** (e.g., *Arduino Uno*).  
   - Select the correct COM port under **Tools** → **Port**.

4. **Verify & Upload**  
   - Click **Verify** to check for compilation issues.  
   - Click **Upload** to flash the code onto the Arduino.

---

## Usage

1. **Wire the Components**  
   - Connect your soil moisture sensor:  
     - **Red** → 5V  
     - **Black** → GND  
     - **Yellow** → A0  
   - Connect your small motor:  
     - **Red** → digital pin (default = D3)  
     - **Black** → GND  
   - Ensure all grounds are common.

2. **Power On**  
   - Provide power via USB or an external 5V supply (depending on your setup).

3. **Monitor Serial Output**  
   - In the Arduino IDE, open the **Serial Monitor** at **9600 baud** to see real-time logs.

4. **Observe**  
   - The motor will spin when the soil moisture reading is below the set threshold.  
   - The motor remains off when the soil is adequately moist.

---

## Calibration & Adjustment

- **`moistureThreshold`**:  
  - Default is `600`. If your sensor reads a value < 600 when dry, the motor will activate.  
  - Calibrate by checking raw sensor values in the Serial Monitor for both **dry** and **wet** soil.

- **`waterTime`**:  
  - Time (in milliseconds) to run the motor once triggered. Default is `3000` (3 seconds).

- **`waitTime`**:  
  - Delay (in milliseconds) between consecutive measurements. Default is `60000` (1 minute).

---

## Troubleshooting

1. **Motor Doesn’t Spin**  
   - Ensure the motor’s current draw is below ~40mA.  
   - Double-check wiring: motor red → digital pin, motor black → GND.

2. **Moisture Reading Always 0 or 1023**  
   - Check sensor cable connections: red → 5V, black → GND, yellow → A0.  
   - Confirm you’re reading `analogRead(A0)` in the code.

3. **Serial Monitor Empty**  
   - Make sure the baud rate is **9600**.  
   - Confirm you have the right COM port selected.

4. **Overcurrent or Overheating**  
   - If the motor is larger, use a transistor driver circuit with a flyback diode.  
   - The Arduino pin cannot source more than ~40mA reliably.

---

## Contributing

Contributions, bug reports, and feature requests are welcome!  
1. **Fork** the repository.  
2. Create a **new branch** for your feature or bug fix.  
3. **Commit** your changes.  
4. **Open a Pull Request** describing your modifications.

---

## License

[MIT License](./LICENSE) (or choose a license of your preference)

You’re free to use, modify, and distribute this code under the terms of the MIT License.

---

## Contact

- **Author**: [Your Name or GitHub Username]  
- **Email**: [you@example.com]  
- **GitHub**: [github.com/YourUsername]

If you encounter any problems or have suggestions, feel free to **open an issue** or reach out via email.

---

**Happy building and good luck with your automatic watering system!**
