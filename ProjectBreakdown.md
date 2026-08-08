# 🔥 PyroSense — Project Breakdown

## 1. Project Overview

**PyroSense** is an evolving intelligent fire detection platform designed to move beyond conventional single-sensor smoke detection.

The project currently uses an **MQ-2 gas/smoke sensor with an Arduino UNO**, OLED display, LEDs, and buzzer to detect abnormal smoke/gas conditions.

The long-term goal is to transform this prototype into a **multi-sensor, AI-assisted early-fire detection system** capable of analyzing multiple environmental parameters, identifying abnormal patterns, estimating fire risk, and reducing false alarms.

---

# 2. Current System — V1

The current prototype is a basic but functional smoke detection system.

### Current Hardware

```text
Arduino UNO R3
      │
      ├── MQ-2 Gas/Smoke Sensor
      │
      ├── 1.3" OLED Display
      │
      ├── Green LED
      │
      ├── Red LED
      │
      └── Buzzer
```

### Current Features

* Real-time MQ-2 sensor monitoring
* Analog smoke/gas sensing
* OLED data visualization
* Green LED for normal conditions
* Red LED for warning conditions
* Audible buzzer alert
* Threshold-based detection
* Experimental smoke testing
* Breadboard-based prototype

---

# 3. Current System Architecture

```text
                 ┌─────────────────┐
                 │      MQ-2       │
                 │ Smoke / Gas     │
                 │    Sensor       │
                 └────────┬────────┘
                          │
                     Analog Data
                          │
                          ▼
                 ┌─────────────────┐
                 │   Arduino UNO   │
                 │                 │
                 │ Detection Logic │
                 └───────┬─────────┘
                         │
              ┌──────────┼──────────┐
              │          │          │
              ▼          ▼          ▼
           ┌─────┐    ┌─────┐   ┌────────┐
           │OLED │    │ LED │   │ Buzzer │
           └─────┘    └─────┘   └────────┘
```

---

# 4. How the Current System Works

### Step 1 — Environmental Sensing

The MQ-2 sensor continuously monitors the surrounding atmosphere for changes in smoke and combustible-gas-related concentrations.

### Step 2 — Analog Signal Acquisition

The sensor's analog output is connected to:

```text
MQ-2 AO → Arduino A0
```

The Arduino continuously reads the analog value.

### Step 3 — Threshold Comparison

The current prototype uses a predefined threshold.

```text
Sensor Reading
      │
      ▼
Compare with Threshold
      │
 ┌────┴────┐
 │         │
 ▼         ▼
Normal    Alert
 │         │
 ▼         ▼
Green     Red
LED       LED
           +
         Buzzer
```

### Step 4 — OLED Visualization

The current sensor reading and detector status are displayed on the OLED.

The OLED uses I2C communication with address:

```text
0x3C
```

---

# 5. Current Pin Configuration

| Component    | Arduino UNO Pin |
| ------------ | --------------- |
| MQ-2 AO      | A0              |
| Green LED    | D8              |
| Red LED      | D9              |
| Buzzer       | D10             |
| OLED         | I2C             |
| OLED Address | `0x3C`          |

LEDs are connected through **220Ω current-limiting resistors**.

---

# 6. Current Detection Model

The current version follows a simple threshold-based approach:

```text
             MQ-2 Reading
                   │
                   ▼
          ┌────────────────┐
          │ Threshold      │
          │ Comparison     │
          └───────┬────────┘
                  │
           ┌──────┴──────┐
           ▼             ▼
        NORMAL          ALERT
           │             │
           ▼             ▼
       Green LED      Red LED
                         +
                       Buzzer
```

This provides a simple and understandable foundation for future intelligent detection.

---

# 7. Why the Current System Needs Improvement

A single MQ-2 sensor cannot reliably determine whether an abnormal reading represents an actual fire.

For example:

```text
Incense Smoke
     ↓
MQ-2 Reading ↑
     ↓
Possible Alarm
```

while:

```text
Actual Combustion
     ↓
Smoke ↑
Temperature ↑
CO ↑
Particles ↑
Possibly Flame
     ↓
Much Stronger Fire Evidence
```

Therefore:

> **High smoke reading does not automatically mean confirmed fire.**

This limitation is the primary motivation for the future development of PyroSense.

---

# 8. V2 — Multi-Sensor Fire Detection

The next major development will introduce multiple sensing parameters.

### Planned Sensors

| Sensor             | Parameter                 | Purpose                  |
| ------------------ | ------------------------- | ------------------------ |
| MQ-2               | Smoke / combustible gases | Smoke detection          |
| MQ-7               | Carbon monoxide           | Combustion indicator     |
| Temperature sensor | Temperature               | Thermal monitoring       |
| Humidity sensor    | Humidity                  | Environmental context    |
| PM2.5 sensor       | Fine particles            | Smoke/particle detection |
| Flame/IR sensor    | Flame radiation           | Flame confirmation       |

The goal is to obtain **independent evidence from different physical phenomena**.

---

# 9. V2 Architecture

```text
                  ┌─────────────┐
                  │    MQ-2     │
                  │ Smoke / Gas │
                  └──────┬──────┘
                         │
                  ┌──────▼──────┐
                  │    MQ-7     │
                  │     CO      │
                  └──────┬──────┘
                         │
                  ┌──────▼──────┐
                  │ Temperature │
                  │  + Humidity │
                  └──────┬──────┘
                         │
                  ┌──────▼──────┐
                  │    PM2.5    │
                  │   Sensor    │
                  └──────┬──────┘
                         │
                  ┌──────▼──────┐
                  │ Flame / IR  │
                  └──────┬──────┘
                         │
                         ▼
                    ESP32
                         │
                         ▼
                  Sensor Analysis
                         │
                         ▼
                 Fire Risk Decision
```

---

# 10. V3 — Sensor Fusion

Instead of making a decision from one sensor, PyroSense will combine information from all available sensors.

### Example

```text
MQ-2          ↑
MQ-7          ↑
Temperature   ↑
PM2.5         ↑
Flame         ✓
              │
              ▼
       Multiple Parameters
              │
              ▼
        HIGH FIRE RISK
```

Whereas:

```text
MQ-2          ↑
MQ-7          →
Temperature   →
PM2.5         ↑
Flame         ✗
              │
              ▼
       Possible Nuisance
```

This allows the system to consider **context**, rather than reacting to one abnormal value.

---

# 11. V4 — Temporal Analysis

PyroSense will not only examine sensor values but also examine **how those values change over time**.

For example:

```text
Temperature:

28°C → 28.2°C → 28.4°C → 28.6°C

Slow Change
```

versus:

```text
Temperature:

28°C → 30°C → 33°C → 37°C → 42°C

Rapid Rise
```

The system can calculate parameters such as:

```text
Rate of Temperature Change
dT/dt
```

and similarly analyze the rate of change of smoke, CO and particulate measurements.

This introduces a **time dimension** into fire-risk analysis.

---

# 12. V5 — Adaptive Baseline

A major planned feature is adaptive environmental baseline detection.

Instead of assuming that one threshold works everywhere, the system will first learn the normal environmental conditions.

```text
Initial Environment
        ↓
Baseline Learning
        ↓
Normal Sensor Pattern
        ↓
Continuous Monitoring
        ↓
Detect Significant Deviation
```

For example:

```text
Normal:
MQ-2 = 110
Temp = 28°C
PM2.5 = 15
CO = Low
```

If several parameters suddenly deviate from this baseline, the system can identify an abnormal event.

---

# 13. V6 — TinyML / Edge AI

The next major advancement will introduce machine learning directly into the detection pipeline.

Instead of:

```text
Sensor > Threshold
       ↓
     ALERT
```

the system will analyze a combination of features.

### Potential Input Features

```text
MQ-2 value
MQ-7 value
Temperature
Humidity
PM2.5
Flame status
Rate of temperature change
Rate of smoke increase
Rate of CO increase
Deviation from baseline
```

These features can be provided to a lightweight ML model running on the ESP32.

---

# 14. Planned ML Classification

The model will potentially classify environmental conditions into categories such as:

```text
NORMAL
   │
   ├── COOKING
   │
   ├── INCENSE / NUISANCE SMOKE
   │
   ├── ABNORMAL COMBUSTION
   │
   └── FIRE
```

The exact classes will depend on the dataset collected during experimentation.

The objective is:

> **Pattern recognition instead of simple threshold detection.**

---

# 15. Fire Risk Scoring

A future version can convert sensor and ML outputs into a continuous risk score.

Example:

```text
0 – 20     NORMAL
20 – 40    LOW RISK
40 – 60    CAUTION
60 – 80    WARNING
80 – 100   CRITICAL
```

The exact scoring model will be determined experimentally.

The system could display:

```text
FIRE RISK
    87%

STATUS:
CRITICAL
```

on the OLED.

---

# 16. V7 — IoT Integration

The system will eventually move toward an ESP32-centered architecture.

The ESP32 can provide:

* Wi-Fi connectivity
* Remote monitoring
* Sensor data transmission
* Event logging
* Web dashboard
* Mobile notifications
* Historical graphs

### IoT Architecture

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

This will allow the system to be monitored even when the user is not physically near the device.

---

# 17. V8 — Intelligent Alerts

Future alerts will contain more information than simply:

> "SMOKE DETECTED"

Example:

```text
🚨 FIRE RISK: HIGH

Smoke:        HIGH
CO:           RISING
Temperature:  RISING RAPIDLY
PM2.5:        HIGH
Flame:        DETECTED

Confidence: 92%
```

The aim is to make the alert **informative and actionable**.

---

# 18. V9 — Computer Vision

An advanced future version may integrate a camera such as an ESP32-CAM.

The camera can provide additional information about:

* Visible flames
* Smoke plumes
* Fire-like visual patterns

The camera output can be combined with sensor data.

```text
             Sensors
                │
                ▼
          Sensor Analysis
                │
                +
             Camera
                │
                ▼
       Multimodal Analysis
                │
                ▼
          Fire Risk Score
```

This would provide a second, independent modality for fire verification.

---

# 19. V10 — Electronic Nose

Another advanced research direction is the use of multiple gas sensors as an **electronic nose**.

Instead of relying on one sensor:

```text
MQ-2
MQ-5
MQ-7
MQ-135
...
```

the system can analyze the response pattern of multiple partially selective sensors.

Different conditions may produce different sensor-response fingerprints.

Machine learning can then potentially classify these fingerprints.

---

# 20. Final System Vision

The ultimate PyroSense architecture is:

```text
                       ┌────────────────────┐
                       │       ESP32        │
                       │   Edge Processing  │
                       │    + TinyML        │
                       └─────────┬──────────┘
                                 │
       ┌────────┬────────┬───────┼───────┬────────┐
       │        │        │       │       │        │
      MQ-2     MQ-7    Temp    Humidity PM2.5   Flame
       │        │        │       │       │        │
       └────────┴────────┴───────┴───────┴────────┘
                                 │
                                 ▼
                        Sensor Data Fusion
                                 │
                                 ▼
                       Temporal Analysis
                                 │
                                 ▼
                       Adaptive Baseline
                                 │
                                 ▼
                           TinyML Model
                                 │
                                 ▼
                         Fire Risk Score
                                 │
                ┌────────────────┼────────────────┐
                │                │                │
                ▼                ▼                ▼
              OLED            Buzzer             IoT
             Display           Alert           Dashboard
```

---

# 21. Development Philosophy

PyroSense will be developed incrementally.

```text
V1
Basic Smoke Detection
        ↓
V2
Multi-Sensor Monitoring
        ↓
V3
Sensor Fusion
        ↓
V4
Temporal Analysis
        ↓
V5
Adaptive Baseline
        ↓
V6
TinyML Classification
        ↓
V7
IoT Monitoring
        ↓
V8
Intelligent Alerts
        ↓
V9
Computer Vision
        ↓
V10
Multimodal Intelligent Fire Detection
```

Each stage will be tested independently before integration into the final system.

---

# 22. Core Innovation

The primary idea behind PyroSense is **not simply adding more sensors**.

The central concept is:

> ### **Combining multiple physical indicators and their behavior over time to make a more informed fire-risk decision.**

The project aims to evolve from:

```text
"Smoke detected"
```

into:

```text
"Multiple environmental parameters indicate
a rapidly developing combustion event."
```

This transition from **single-parameter threshold detection** to **multi-parameter intelligent analysis** is the core direction of PyroSense.

---

# 23. Current vs Future

| Feature                 | Current V1 | Future PyroSense |
| ----------------------- | ---------: | ---------------: |
| MQ-2 Smoke Detection    |          ✅ |                ✅ |
| OLED Display            |          ✅ |                ✅ |
| LED Alert               |          ✅ |                ✅ |
| Buzzer                  |          ✅ |                ✅ |
| Fixed Threshold         |          ✅ |         Optional |
| MQ-7 CO Detection       |          ❌ |               🔄 |
| Temperature Monitoring  |          ❌ |               🔄 |
| Humidity Monitoring     |          ❌ |               🔄 |
| PM2.5 Monitoring        |          ❌ |               🔄 |
| Flame Verification      |          ❌ |               🔄 |
| Sensor Fusion           |          ❌ |               🔄 |
| Rate-of-Change Analysis |          ❌ |               🔄 |
| Adaptive Baseline       |          ❌ |               🔄 |
| TinyML                  |          ❌ |               🔄 |
| Fire-Risk Score         |          ❌ |               🔄 |
| IoT Dashboard           |          ❌ |               🔄 |
| Remote Alerts           |          ❌ |               🔄 |
| Computer Vision         |          ❌ |               🔬 |
| Electronic Nose         |          ❌ |               🔬 |

**Legend:**

* ✅ Implemented
* 🔄 Planned
* 🔬 Advanced research direction

---

# 🎯 Final Objective

PyroSense aims to become a **low-cost, intelligent and modular early-fire detection platform** that combines environmental sensing, temporal analysis, sensor fusion, edge AI and IoT technologies.

The project begins with a simple MQ-2 smoke detector and progressively evolves toward a system capable of answering a much more meaningful question:

> **"Does the current environmental pattern indicate a genuine fire risk?"**
