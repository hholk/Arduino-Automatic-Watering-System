# Automatic Watering System

This repository contains two implementations of a simple plant watering controller.
The primary target is an **ESP32-C6 board with a 1.47" LCD** while a
legacy **Arduino/ATmega328 sketch** is kept for reference.

## ESP32-C6 Display Version
- JSON plant profiles stored on SPIFFS
- LVGL touch interface to select plants (e.g. Olivenbaum, Avocadobaum)
- Capacitive soil moisture sensor and pump control
- Water reservoir switch
- Wi-Fi and MQTT reporting for Home Assistant
- Weather factor input over MQTT
- Verbose serial output for debugging

### Hardware
- Waveshare ESP32-C6 with 1.47" LCD
- Capacitive soil moisture sensor (V2.0)
- Small pump (<40 mA) or use a driver stage
- Water level sensor
- Wires, 5 V power supply

### Wiring
- Moisture sensor: `VCC` to **3V3**, `GND` to **GND**, signal line to **GPIO4**
- Pump driver or transistor gate to **GPIO5** (pump powered from 5 V)
- Reservoir level switch output to **GPIO6**

### Flashing Steps
1. Install [Arduino IDE](https://www.arduino.cc/en/software) or PlatformIO.
2. Add ESP32 board URL in **File > Preferences**:
   `https://espressif.github.io/arduino-esp32/package_esp32_index.json`.
3. In **Tools > Board Manager** install *ESP32* and select **ESP32C6 Dev Module**.
4. Install libraries via **Sketch > Include Library > Manage Libraries**:
   `ArduinoJson`, `PubSubClient`, `lvgl`, `TFT_eSPI`.
5. Open `src/main.cpp` and enter your Wi-Fi and MQTT credentials.
6. Upload the JSON files in `plants/` to SPIFFS using the *ESP32 Sketch Data Upload* tool.
7. Build and upload the firmware.

### Home Assistant
Add to `configuration.yaml`:
```yaml
mqtt:
  sensor:
    - name: "Plant Moisture"
      state_topic: "home/watering/status"
      unit_of_measurement: "%"
      value_template: "{{ value_json.moisture }}"
    - name: "Water Reservoir Low"
      state_topic: "home/watering/status"
      value_template: "{{ value_json.reservoirLow }}"
      device_class: problem
```

## Legacy Arduino Sketch
A minimal offline controller for ATmega328 boards is provided in
`automatic_watering.ino`.

- Wire the sensor to **A0** and the pump to **D3**.
- Adjust `moistureThreshold`, `waterTime` and `waitTime` in the sketch.
- Upload using the Arduino IDE and monitor output at **9600 baud**.
- If the motor draws more than ~40 mA, add a transistor and flyback diode.

## License
[MIT](./LICENSE)
