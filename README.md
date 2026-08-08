<img width="1024" height="572" alt="image" src="https://github.com/user-attachments/assets/94a40e85-bfd7-4f01-9df9-8dd4c23104e0" />

# PyroSense - An Intelligent Smoke & Fire Detection System

An Arduino/ESP32-based **intelligent smoke and fire detection system** designed to detect abnormal smoke/gas conditions, provide real-time visual and audible alerts, and serve as the foundation for a future **multi-sensor, AI-assisted early-fire detection system**.

The current prototype focuses on reliable basic smoke detection using an **MQ-2 gas/smoke sensor**, while future versions will introduce sensor fusion, adaptive detection, machine learning, IoT connectivity, and intelligent false-alarm reduction.

---

## 🚀 Project Vision

Traditional low-cost smoke detectors generally depend on a single sensing parameter and a fixed threshold. This can result in nuisance alarms caused by conditions such as incense smoke, cooking fumes, dust, or other environmental changes.

The long-term goal of this project is to develop a system that does not simply ask:

> **"Is smoke present?"**

but instead attempts to determine:

> **"Is the observed environmental change likely to indicate an actual fire?"**

The planned system will combine multiple environmental parameters and intelligent algorithms to improve detection reliability and reduce false alarms.

---

# 📌 Current Project Status

### ✅ Currently Implemented

* MQ-2 based smoke/gas sensing
* Arduino UNO based prototype
* Analog sensor data acquisition
* Real-time smoke-value monitoring
* OLED display
* Green LED for normal condition
* Red LED for alert condition
* Buzzer for audible warning
* 220Ω resistors for LED protection
* Threshold-based smoke detection
* Basic testing using incense/agarbatti smoke
* OLED I2C communication using address `0x3C`

### Current Hardware

| Component         | Purpose                         |
| ----------------- | ------------------------------- |
| Arduino UNO R3    | Main controller                 |
| MQ-2 Gas Sensor   | Smoke/combustible gas detection |
| 1.3" OLED         | Real-time data display          |
| Green LED         | Normal status                   |
| Red LED           | Warning status                  |
| Buzzer            | Audible alert                   |
| 220Ω Resistors ×2 | LED current limiting            |
| Breadboard        | Prototyping                     |
| Jumper Wires      | Connections                     |

---

# ⚙️ Current Working Principle

The current prototype follows a simple threshold-based architecture:

```text
        Smoke / Gas
             ↓
          MQ-2
             ↓
       Analog Reading
             ↓
         Arduino UNO
             ↓
      ┌──────┴──────┐
      ↓             ↓
    OLED       Threshold Logic
                    ↓
             ┌──────┴──────┐
             ↓             ↓
          NORMAL         ALERT
             ↓             ↓
        Green LED      Red LED
                          +
                       Buzzer
```

The MQ-2 sensor produces an analog output corresponding to changes in the concentration of detectable gases/smoke in its environment.

The Arduino reads this analog signal and compares it with a predefined threshold.

If the reading exceeds the threshold, the system activates the warning indicators.

---

# 🖥️ Current Pin Configuration

### MQ-2

```text
MQ-2 AO → Arduino A0
```

### LEDs

```text
Green LED → Digital Pin 8
Red LED   → Digital Pin 9
```

### Buzzer

```text
Buzzer → Digital Pin 10
```

### OLED

The OLED communicates with the Arduino using I2C.

```text
I2C Address: 0x3C
```

> Pin configuration may change in future hardware revisions.

---

# 📊 Current Detection Logic

The present version uses a simple threshold:

```text
MQ-2 Reading < Threshold
        ↓
      NORMAL

MQ-2 Reading ≥ Threshold
        ↓
      ALERT
```

The prototype currently uses an experimentally selected threshold and is intended for demonstration and development rather than certified life-safety applications.

---

# 🧪 Initial Testing

The prototype has been tested using incense/agarbatti smoke.

During testing, the MQ-2 reading increased significantly when exposed to smoke, demonstrating that the sensor can detect changes in the surrounding atmosphere.

Example observation:

```text
Clean Air
   ↓
Lower MQ-2 Reading

Smoke Exposure
   ↓
Higher MQ-2 Reading
   ↓
Alert Condition
```

These readings are currently being used for experimentation and calibration rather than as universal gas-concentration measurements.

---

# ⚠️ Limitations of the Current Version

The current prototype has several limitations:

### 1. Single-Sensor Dependency

The system primarily depends on MQ-2.

A high MQ-2 reading does not necessarily mean that a dangerous fire is occurring.

---

### 2. False Alarm Possibility

Smoke from:

* Incense
* Cooking
* Dust
* Aerosols
* Other combustible vapors

may cause the sensor reading to increase.

Therefore:

```text
High MQ-2 Reading ≠ Confirmed Fire
```

---

### 3. Fixed Threshold

The current system relies on a predefined threshold.

Environmental conditions can change the sensor's baseline, which means a fixed threshold may not work equally well in every environment.

---

### 4. Limited Gas Selectivity

MQ-2 is a broad-response gas sensor rather than a highly selective fire detector.

It cannot independently determine the exact source of the detected gases.

---

### 5. No Context Awareness

The current system does not consider:

* Rate of temperature rise
* Carbon monoxide concentration
* Particulate concentration
* Flame presence
* Changes over time
* Environmental baseline

---

# 🔮 Future Scope

The main objective of future development is to transform the current threshold-based detector into an **intelligent multi-parameter fire-risk detection system**.

---

## 🚀 Phase 2 — Multi-Sensor Detection

Additional sensors will be introduced to obtain more information about the environment.

### Planned sensors

* **MQ-7** → Carbon monoxide detection
* **Temperature sensor** → Thermal monitoring
* **Humidity sensor** → Environmental context
* **PM2.5/PM10 sensor** → Particle concentration
* **Flame/IR sensor** → Flame detection

The system will therefore observe multiple independent indicators instead of relying solely on smoke.

```text
             MQ-2
              │
             MQ-7
              │
       Temperature
              │
          Humidity
              │
           PM2.5
              │
         Flame/IR
              ↓
       Sensor Fusion
```

---

# 🧠 Phase 3 — Sensor Fusion

Instead of:

```text
MQ-2 > Threshold
        ↓
      FIRE
```

the system will combine multiple sensor parameters.

For example:

```text
Smoke ↑
CO ↑
Temperature ↑
PM2.5 ↑
Flame detected
        ↓
High Fire Risk
```

While:

```text
Smoke ↑
Temperature ≈ Stable
CO ≈ Stable
Flame = No
        ↓
Possible Nuisance Smoke
```

This approach can potentially reduce false alarms.

---

# 📈 Phase 4 — Rate-of-Change Analysis

The system will also analyze how rapidly environmental parameters are changing.

For example, temperature can be monitored using:

```text
dT/dt
```

where:

```text
dT/dt = Rate of temperature change
```

Similarly, the rate of change of smoke/gas readings can be analyzed.

This allows the system to distinguish between:

```text
Slow Environmental Change
```

and

```text
Rapid Combustion-Like Change
```

---

# 🤖 Phase 5 — TinyML / Machine Learning

A major planned advancement is the integration of **TinyML/edge machine learning**.

Instead of relying entirely on manually selected thresholds, the system will be trained using sensor patterns collected under different conditions.

### Possible training categories

```text
NORMAL
COOKING
INCENSE / NUISANCE SMOKE
ABNORMAL COMBUSTION
FIRE
```

The model will learn relationships between multiple sensor parameters.

Conceptually:

```text
MQ-2
MQ-7
Temperature
Humidity
PM2.5
Flame
Rate of Change
       ↓
   ML Model
       ↓
Classification
       ↓
Fire Risk
```

The objective is to make the system **pattern-aware rather than threshold-dependent**.

---

# 🧬 Phase 6 — Adaptive Baseline

A future version will establish the normal environmental conditions of its surroundings.

For example:

```text
Normal Baseline

MQ-2       = X
Temperature = Y
Humidity    = Z
PM2.5       = A
```

The system will continuously compare current conditions against the learned baseline.

This can help identify unusual environmental changes without relying exclusively on a single fixed threshold.

---

# 🌐 Phase 7 — IoT Connectivity

The system will eventually transition from Arduino UNO to an **ESP32-based architecture**.

Potential features:

* Wi-Fi connectivity
* Remote monitoring
* Mobile/web dashboard
* Real-time sensor graphs
* Event logging
* Remote alerts
* Historical data storage

Possible architecture:

```text
Sensors
   ↓
ESP32
   ↓
Edge Processing
   ↓
Wi-Fi
   ↓
Cloud / Dashboard
   ↓
User
```

---

# 📱 Phase 8 — Intelligent Alert System

Instead of simply activating a buzzer, future versions can provide contextual alerts.

Example:

```text
⚠️ WARNING

Smoke level increasing rapidly.
Temperature rising.
CO concentration increasing.

Fire Risk: HIGH
```

The system could eventually provide different alert levels:

```text
🟢 NORMAL
🟡 CAUTION
🟠 WARNING
🔴 CRITICAL FIRE RISK
```

---

# 👁️ Phase 9 — Computer Vision *(Advanced Future Scope)*

A future experimental version may integrate a camera such as an ESP32-CAM.

The camera could analyze:

* Visible flames
* Smoke plumes
* Fire-like visual patterns

The vision system could be combined with physical sensors.

```text
                 Sensors
                    ↓
              Sensor Analysis
                    │
                    +
                 Camera
                    ↓
            Multimodal Analysis
                    ↓
             Fire Risk Score
```

This could provide an additional layer of verification.

---

# 🧪 Phase 10 — Electronic Nose

Another advanced research direction is the use of a **gas sensor array**.

Instead of depending on one gas sensor:

```text
MQ-2
MQ-5
MQ-7
MQ-135
...
```

different sensor responses can be combined to create a gas-response pattern.

Machine learning could then identify different environmental conditions based on these patterns.

This concept is similar to an **electronic nose**, where multiple partially selective sensors collectively produce a chemical fingerprint.

---

# 🏆 Long-Term Architecture

The final vision of the project is:

```text
                 ┌─────────────────────┐
                 │      ESP32          │
                 │ Edge Intelligence   │
                 └─────────┬───────────┘
                           │
      ┌────────┬───────────┼───────────┬─────────┐
      ↓        ↓           ↓           ↓         ↓
    MQ-2      MQ-7       Temp/Hum      PM2.5    Flame
      │        │           │           │         │
      └────────┴───────────┴───────────┴─────────┘
                           │
                           ↓
                  Sensor Data Fusion
                           │
                           ↓
                  Rate-of-Change Analysis
                           │
                           ↓
                    TinyML / AI Model
                           │
                           ↓
                    Fire Risk Score
                           │
              ┌────────────┼────────────┐
              ↓            ↓            ↓
           OLED         Buzzer        IoT
                                      Alerts
```

---

# 🌟 Expected Final Features

The long-term system aims to provide:

* Multi-sensor fire detection
* False-alarm reduction
* Smoke/gas monitoring
* CO monitoring
* Temperature monitoring
* Particle monitoring
* Flame verification
* Rate-of-change analysis
* Adaptive environmental baseline
* TinyML-based classification
* Fire-risk scoring
* OLED visualization
* Audible/visual alerts
* Wi-Fi connectivity
* Remote notifications
* Event logging
* Optional computer vision
* Experimental gas-pattern recognition

---

# 🛠️ Technology Stack

### Current

```text
Arduino UNO
MQ-2
OLED
C/C++ / Arduino IDE
```

### Planned

```text
ESP32
MQ-2
MQ-7
Temperature/Humidity Sensor
PM2.5 Sensor
Flame Sensor
TinyML
Python
Machine Learning
IoT
Cloud / Web Dashboard
Computer Vision
```

---

# 📌 Development Roadmap

```text
[✓] MQ-2 Smoke Detection
        ↓
[✓] OLED Display
        ↓
[✓] LED + Buzzer Alert
        ↓
[✓] Basic Smoke Testing
        ↓
[ ] ESP32 Migration
        ↓
[ ] Multi-Sensor Integration
        ↓
[ ] Temperature + Humidity Monitoring
        ↓
[ ] MQ-7 CO Monitoring
        ↓
[ ] PM2.5 Monitoring
        ↓
[ ] Sensor Fusion
        ↓
[ ] Rate-of-Change Analysis
        ↓
[ ] Adaptive Baseline
        ↓
[ ] Dataset Collection
        ↓
[ ] TinyML Model
        ↓
[ ] Fire/Nuisance Classification
        ↓
[ ] IoT Dashboard
        ↓
[ ] Remote Alerts
        ↓
[ ] Computer Vision
        ↓
[ ] Advanced Multimodal Fire Detection
```

---

# 🎯 Project Objective

The ultimate objective is to evolve this project from a basic smoke detector into a **low-cost intelligent early-fire detection platform** capable of analyzing multiple environmental parameters and identifying potentially dangerous combustion patterns while reducing unnecessary alarms.

The project will be developed incrementally, with each version improving the sensing capability, intelligence, reliability, and connectivity of the system.

---

# ⚠️ Disclaimer

This project is an **educational and experimental prototype**.

It is not intended to replace certified commercial fire-alarm or life-safety systems. MQ-series gas sensors are broad-response sensors and their readings should not be interpreted as certified gas concentrations without appropriate calibration and instrumentation.

---

# 👨‍💻 Author

**Anendra Narayan Dixit**

B.Tech — Electrical Engineering

Central University of Karnataka

---

## ⭐ Project Vision

> **From detecting smoke to understanding fire risk.**
>
> A step-by-step journey from a simple sensor-based prototype toward an intelligent, multi-sensor and AI-assisted fire detection system.
