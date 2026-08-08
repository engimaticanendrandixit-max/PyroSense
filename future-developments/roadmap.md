# 🚀 PyroSense — Development Roadmap

## 1. Vision

PyroSense is being developed as a progressive platform for intelligent smoke, gas, and fire-risk detection.

The project starts with a simple MQ-2 based threshold detector and gradually evolves toward a multi-sensor, intelligent, connected, and predictive monitoring system.

The development philosophy is:

> **Sense → Understand → Classify → Predict → Respond**

---

# 2. Current Status — V1

## PyroSense V1 — Basic Smoke Detection

**Status: ✅ Completed**

The current prototype uses:

- Arduino UNO R3
- MQ-2 gas/smoke sensor
- OLED display
- Green LED
- Red LED
- Buzzer
- 220 Ω resistors

### Core Function

```text
MQ-2
  ↓
Analog Signal
  ↓
Arduino A0
  ↓
ADC
  ↓
Threshold Comparison
  ↓
NORMAL / ALERT
  ↓
OLED + LEDs + Buzzer
```

### V1 Features

- MQ-2 analog sensing
- Real-time sensor readings
- Threshold-based detection
- OLED monitoring
- Visual alert
- Audible alert
- Basic calibration
- Smoke-response testing

---

# 3. V2 — Smarter Sensing

The main objective of V2 is to overcome the limitations of relying on a single MQ-2 sensor.

## Planned Improvements

- ESP32 migration
- Multi-sensor monitoring
- Environmental sensing
- Dynamic thresholding
- Hysteresis
- Improved calibration
- Data logging
- Better alert logic

### Proposed Architecture

```text
              ┌──────────────┐
              │     MQ-2     │
              └──────┬───────┘
                     │
              ┌──────▼───────┐
              │ Temperature  │
              │   Humidity   │
              └──────┬───────┘
                     │
              ┌──────▼───────┐
              │   Optional   │
              │ PM Sensor    │
              └──────┬───────┘
                     │
                     ▼
                  ESP32
                     │
             ┌───────┼────────┐
             ▼       ▼        ▼
           OLED    Logging   Wi-Fi
```

---

# 4. V2.1 — ESP32 Migration

The Arduino UNO will eventually be replaced by an ESP32 for the advanced versions.

### Why ESP32?

The ESP32 provides:

- Wi-Fi connectivity
- Bluetooth
- Higher processing capability
- More memory
- Multiple communication interfaces
- Better support for IoT
- Better support for edge processing

### Development Direction

```text
Arduino UNO
     ↓
Basic Prototype
     ↓
ESP32
     ↓
Connected System
```

---

# 5. V2.2 — Environmental Monitoring

Environmental parameters will be added to understand how surrounding conditions affect sensor behavior.

Potential parameters:

- Temperature
- Relative humidity
- Air quality
- Particulate matter

The system can then correlate sensor response with environmental conditions.

```text
             MQ-2
               │
               │
Temperature ───┤
               │
Humidity ──────┤
               │
PM Sensor ─────┤
               ▼
        Environmental Model
```

---

# 6. V2.3 — Dynamic Thresholding

V1 uses a manually selected fixed threshold.

V2 will investigate dynamic thresholding.

Instead of:

```text
Threshold = 150
```

the system will estimate the current baseline.

```text
Sensor Data
     ↓
Baseline Estimation
     ↓
Normal Operating Range
     ↓
Dynamic Threshold
     ↓
Detection
```

This can improve adaptability to different environments.

---

# 7. V2.4 — Hysteresis

Hysteresis will be introduced to prevent rapid switching between NORMAL and ALERT.

Instead of using one threshold:

```text
ALERT → 150
```

the system can use:

```text
Enter ALERT  → 160
Return NORMAL → 140
```

This reduces unstable switching caused by sensor fluctuations.

---

# 8. V2.5 — Persistence-Based Detection

A temporary sensor spike should not necessarily trigger a high-priority alarm.

Future logic:

```text
Sensor > Threshold
       ↓
Condition persists
       ↓
Timer
       ↓
If condition remains
       ↓
ALERT
```

For example:

```text
Reading > Threshold
       ↓
For 3 seconds
       ↓
ALERT
```

This can reduce false triggers.

---

# 9. V2.6 — Data Logging

Sensor readings will be stored for later analysis.

Possible storage methods:

- MicroSD
- ESP32 flash
- Cloud database

Example data:

```text
Timestamp
MQ-2 Value
Temperature
Humidity
PM Value
Risk Level
Alert State
```

This data will become important for future machine-learning development.

---

# 10. V3 — Sensor Fusion

**Status: 🔲 Planned**

V3 will move from single-sensor detection toward **multi-sensor fusion**.

Instead of:

```text
MQ-2 → ALERT
```

the system will consider multiple signals.

Example:

```text
MQ-2 ↑
Temperature ↑
CO ↑
PM ↑
      ↓
Sensor Fusion
      ↓
Risk Estimation
```

This approach can provide stronger evidence than relying on a single sensor.

Detailed architecture and algorithms will be documented in:

```text
future-development/sensor-fusion.md
```

---

# 11. V3.1 — Multi-Level Risk Classification

The binary system:

```text
NORMAL / ALERT
```

will be replaced with multiple risk levels.

### Proposed Levels

```text
LEVEL 0 → NORMAL
LEVEL 1 → CAUTION
LEVEL 2 → WARNING
LEVEL 3 → HIGH RISK
LEVEL 4 → CRITICAL
```

Example:

```text
NORMAL
   ↓
CAUTION
   ↓
WARNING
   ↓
HIGH RISK
   ↓
CRITICAL
```

Each level can have a different response.

---

# 12. V3.2 — Rate-of-Change Analysis

Future versions will consider how quickly sensor readings change.

The system can calculate:

\[
Rate\ of\ Change = \frac{\Delta Sensor}{\Delta t}
\]

Example:

```text
100 → 105 → 110
```

represents a relatively gradual change.

While:

```text
100 → 180 → 300
```

in a short period represents a much more significant change.

This information can be combined with sensor magnitude for better risk estimation.

---

# 13. V3.3 — IoT Monitoring

The ESP32 can transmit data through Wi-Fi.

```text
Sensors
   ↓
ESP32
   ↓
Wi-Fi
   ↓
Cloud / Server
   ↓
Dashboard
   ↓
User
```

Potential features:

- Real-time monitoring
- Remote alerts
- Historical graphs
- Sensor status
- Risk level
- Event logging

---

# 14. V3.4 — Remote Alert System

The system can eventually provide remote notifications when a critical condition is detected.

Possible mechanisms include:

- Web notification
- Mobile notification
- Email
- SMS through an appropriate service

The local alarm will remain functional even if network connectivity is unavailable.

---

# 15. V4 — TinyML / Edge Intelligence

**Status: 🔲 Future**

The next major stage is introducing machine learning directly into the embedded system.

Instead of relying only on manually selected thresholds:

```text
Sensor Data
     ↓
ML Model
     ↓
Pattern Recognition
     ↓
Risk Classification
```

Possible classification outputs:

```text
NORMAL
SMOKE
GAS EVENT
HIGH RISK
UNKNOWN
```

The detailed TinyML development plan will be documented in:

```text
future-development/tinyml.md
```

---

# 16. V4.1 — Feature Extraction

Before machine learning, useful features can be extracted from raw sensor data.

Potential features include:

- Current sensor value
- Moving average
- Maximum value
- Minimum value
- Rate of change
- Sensor variance
- Exposure duration
- Recovery rate
- Temperature
- Humidity
- Multi-sensor relationships

Example:

```text
Raw Sensor Data
       ↓
Feature Extraction
       ↓
Feature Vector
       ↓
ML Model
```

---

# 17. V4.2 — Pattern Recognition

The system will investigate whether different environmental events produce distinguishable sensor patterns.

For example:

```text
Event A
MQ-2 ↑ slowly
Temperature stable
PM slightly ↑

Event B
MQ-2 ↑ rapidly
Temperature ↑
PM ↑

Event C
MQ-2 ↑
Temperature stable
Humidity changes
```

The objective is to determine whether multi-dimensional sensor patterns can improve classification.

---

# 18. V4.3 — Edge AI

The long-term objective is to run lightweight ML models directly on the ESP32 or another suitable edge device.

```text
Sensors
   ↓
ESP32
   ↓
Feature Extraction
   ↓
TinyML Model
   ↓
Risk Classification
   ↓
Local Decision
```

Advantages:

- Low latency
- Reduced cloud dependency
- Local decision making
- Lower communication requirements
- Offline operation

---

# 19. V5 — Predictive Detection

The ultimate goal is to move from reactive detection toward predictive risk estimation.

### Traditional System

```text
Hazard
  ↓
Detection
  ↓
Alarm
```

### Predictive System

```text
Sensor Trends
      ↓
Pattern Analysis
      ↓
Abnormal Trend
      ↓
Risk Increasing
      ↓
Early Warning
```

The system would attempt to recognize dangerous trends before a simple threshold is crossed.

---

# 20. V5.1 — Adaptive Learning

The system could learn the normal behavior of its installation environment.

```text
Initial Data
     ↓
Learn Baseline
     ↓
Monitor Environment
     ↓
Update Model
     ↓
Adaptive Detection
```

However, adaptive learning must include safeguards so that a dangerous condition is not accidentally learned as normal behavior.

---

# 21. V5.2 — Self-Diagnostics

A mature PyroSense system should be able to monitor its own health.

Potential diagnostics:

- Sensor disconnected
- Sensor malfunction
- Abnormal sensor drift
- Low battery
- Communication failure
- Sensor warm-up state
- Invalid readings

Example:

```text
Sensor Health
      ↓
 ┌────┴────┐
 │         │
Healthy   Fault
 │         │
 ▼         ▼
Monitor   Warning
```

---

# 22. V5.3 — Sensor Health & Aging Analysis

The system can maintain historical sensor behavior and monitor long-term drift.

```text
Historical Data
      ↓
Sensor Response Trend
      ↓
Drift Detection
      ↓
Sensor Health Estimate
```

This can help identify when recalibration or sensor replacement may be required.

---

# 23. Long-Term Architecture

The long-term PyroSense architecture could look like:

```text
                 ┌───────────────┐
                 │     MQ-2      │
                 └───────┬───────┘
                         │
                 ┌───────▼───────┐
                 │ Gas-Specific  │
                 │   Sensors     │
                 └───────┬───────┘
                         │
                 ┌───────▼───────┐
                 │ Environmental │
                 │   Sensors     │
                 └───────┬───────┘
                         │
                 ┌───────▼───────┐
                 │      ESP32    │
                 └───────┬───────┘
                         │
              ┌──────────┼──────────┐
              │          │          │
              ▼          ▼          ▼
        Sensor Fusion  TinyML     Logging
              │          │          │
              └──────────┼──────────┘
                         ▼
                  Risk Engine
                         │
              ┌──────────┼──────────┐
              │          │          │
              ▼          ▼          ▼
            OLED      Local Alarm   IoT
                                    │
                                    ▼
                                Dashboard
```

---

# 24. Development Philosophy

Each version will be developed only after validating the previous stage.

```text
V1
 ↓
Validate Basic Detection
 ↓
V2
 ↓
Improve Sensing
 ↓
V3
 ↓
Fuse Information
 ↓
V4
 ↓
Add Intelligence
 ↓
V5
 ↓
Predict & Adapt
```

The goal is to avoid adding complex technologies without first understanding and validating the underlying sensor behavior.

---

# 25. Roadmap Summary

| Version | Focus | Status |
|---|---|---|
| V1 | MQ-2 + Arduino + Threshold Detection | ✅ Completed |
| V2 | ESP32 + Environmental Monitoring | 🔲 Planned |
| V2 | Dynamic Threshold + Hysteresis | 🔲 Planned |
| V2 | Data Logging | 🔲 Planned |
| V3 | Sensor Fusion | 🔲 Planned |
| V3 | Multi-Level Risk Classification | 🔲 Planned |
| V3 | IoT Monitoring | 🔲 Planned |
| V4 | TinyML | 🔲 Future |
| V4 | Edge AI | 🔲 Future |
| V4 | Pattern Recognition | 🔲 Future |
| V5 | Predictive Detection | 🔲 Future |
| V5 | Adaptive Learning | 🔲 Future |
| V5 | Self-Diagnostics | 🔲 Future |

---

# 26. Final Vision

PyroSense is intended to evolve from a simple sensor-based prototype into an intelligent monitoring platform.

```text
         V1
          │
          ▼
   Basic Detection
          │
          ▼
         V2
          │
          ▼
   Smarter Sensing
          │
          ▼
         V3
          │
          ▼
    Sensor Fusion
          │
          ▼
         V4
          │
          ▼
     Edge AI / TinyML
          │
          ▼
         V5
          │
          ▼
 Predictive & Adaptive
       Detection
```

> **The ultimate goal of PyroSense is not simply to detect smoke, but to progressively understand environmental patterns and provide earlier, smarter, and more reliable risk assessment.**