# 🔥 PyroSense V1 — Core

### Basic Smoke Detection System

PyroSense V1 is the first functional prototype of the PyroSense project. It is an **Arduino UNO-based smoke detection system** that uses an MQ-2 sensor to detect changes in smoke/gas levels and provides real-time visual and audible alerts.

The system displays sensor readings on an OLED and activates an alert when the detected value crosses a predefined threshold.

---

## 🎯 Objective

The objective of V1 is to build a simple, functional and reliable foundation for smoke detection using:

* MQ-2 smoke/gas sensor
* Arduino UNO R3
* OLED display
* LEDs
* Buzzer

---

## 🧩 Components

| Component             |    Quantity | Purpose                            |
| --------------------- | ----------: | ---------------------------------- |
| Arduino UNO R3        |           1 | Main controller                    |
| MQ-2 Gas/Smoke Sensor |           1 | Smoke/gas detection                |
| 1.3" I2C OLED         |           1 | Display sensor readings and status |
| Green LED             |           1 | Normal condition                   |
| Red LED               |           1 | Alert condition                    |
| 220Ω Resistor         |           2 | LED current limiting               |
| Buzzer                |           1 | Audible alert                      |
| Breadboard            |           1 | Circuit prototyping                |
| Jumper Wires          | As required | Electrical connections             |

---

## 🔌 Pin Configuration

### MQ-2

```text
VCC → 5V
GND → GND
AO  → A0
DO  → Not Connected
```

### OLED

```text
VCC → 5V
GND → GND
SDA → A4
SCL → A5
```

**OLED I2C Address:** `0x3C`

### Green LED

```text
D8 → 220Ω Resistor → LED Anode
LED Cathode → GND
```

### Red LED

```text
D9 → 220Ω Resistor → LED Anode
LED Cathode → GND
```

### Buzzer

```text
D10 → Buzzer (+)
GND → Buzzer (-)
```

---

## ⚙️ Working Principle

The MQ-2 sensor continuously monitors changes in the surrounding atmosphere.

Its analog output is connected to **A0** of the Arduino UNO.

The Arduino reads the sensor value and compares it with a predefined smoke threshold.

### Normal Condition

```text
MQ-2 Reading
     ↓
Below Threshold
     ↓
NORMAL
     ↓
Green LED ON
Buzzer OFF
```

### Alert Condition

```text
MQ-2 Reading
     ↓
Threshold Exceeded
     ↓
SMOKE ALERT
     ↓
Red LED ON
Buzzer ON
```

At the same time, the current sensor reading and system status are displayed on the OLED.

---

## 🧠 System Flow

```text
          ┌──────────────┐
          │    MQ-2      │
          │ Smoke Sensor │
          └──────┬───────┘
                 │
                 │ Analog Signal
                 ▼
          ┌──────────────┐
          │  Arduino UNO │
          │              │
          │ Read Sensor  │
          │ + Threshold  │
          └──────┬───────┘
                 │
        ┌────────┼─────────┐
        │        │         │
        ▼        ▼         ▼
      OLED     Green      Red
               LED        LED
                           +
                         Buzzer
```

---

## 📊 Detection Logic

The current V1 uses a simple threshold-based algorithm:

```text
Read MQ-2
   ↓
Display Reading
   ↓
Compare with Threshold
   ↓
 ┌───────────────┐
 │               │
 ▼               ▼
Normal          Alert
 │               │
 ▼               ▼
Green LED      Red LED
ON             ON
 │               │
 ▼               ▼
Buzzer OFF     Buzzer ON
```

---

## 🧪 Testing

The prototype was tested using incense/agarbatti smoke as a controlled smoke source.

During testing:

```text
Clean Environment
       ↓
Lower MQ-2 Reading
       ↓
Normal State
```

When smoke was introduced:

```text
Smoke Exposure
       ↓
MQ-2 Reading Increased
       ↓
Threshold Crossed
       ↓
Alert Activated
```

The test confirmed that the MQ-2 sensor could detect a significant change in its output when exposed to smoke.

---

## 🖥️ OLED Display

The OLED provides real-time feedback from the system.

Example display:

```text
--------------------
    SMOKE DETECTOR

   Smoke:  XXX

   STATUS: NORMAL
--------------------
```

During an alert:

```text
--------------------
    SMOKE DETECTOR

   Smoke:  XXX

   STATUS: ALERT
--------------------
```

---

## 💻 Software

### Platform

* Arduino UNO R3
* Arduino IDE
* Arduino C/C++

### Libraries

```text
Wire.h
Adafruit_GFX.h
Adafruit_SSD1306.h
```

---

## 📁 V1 Structure

```text
V1-Core/
│
├── README.md
│
├── code/
│   └── PyroSense_V1.ino
│
├── circuit/
│   └── circuit-diagram.png
│
└── images/
    ├── prototype.jpg
    └── oled-display.jpg
```

---

## ⚠️ Limitations

PyroSense V1 is a basic prototype and has some important limitations:

* Uses only one primary sensing element
* Depends on a fixed threshold
* May respond to non-fire sources of smoke/gas
* Does not measure temperature
* Does not specifically measure carbon monoxide
* Does not use sensor fusion
* Does not use machine learning
* Raw MQ-2 readings are not certified gas concentrations

Therefore, V1 should be considered an **experimental smoke detection prototype**, not a certified fire-safety device.

---

## 📌 Current Status

| Feature               | Status     |
| --------------------- | ---------- |
| MQ-2 Smoke Detection  | ✅ Complete |
| Analog Sensor Reading | ✅ Complete |
| OLED Display          | ✅ Complete |
| Green LED             | ✅ Complete |
| Red LED               | ✅ Complete |
| Buzzer Alert          | ✅ Complete |
| Threshold Detection   | ✅ Complete |
| Smoke Testing         | ✅ Complete |
| Circuit Prototype     | ✅ Complete |

---

## 🔥 V1 Summary

PyroSense V1 establishes the fundamental detection pipeline:

```text
SENSE
  ↓
READ
  ↓
PROCESS
  ↓
DISPLAY
  ↓
ALERT
```

This version serves as the **core hardware and software foundation** of the PyroSense project.

> **PyroSense V1 — Detecting smoke, one signal at a time.**
