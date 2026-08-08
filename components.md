# 🔧 PyroSense — Components

This document contains the hardware components used in the current **PyroSense V1** prototype and the components planned for future versions of the project.

The hardware architecture will gradually evolve from a basic MQ-2 smoke detector into a **multi-sensor, AI-assisted fire-risk detection platform**.

---

# 🟢 V1 — PyroSense Core

### Current Hardware

| Component                 |    Quantity | Status      | Purpose                           |
| ------------------------- | ----------: | ----------- | --------------------------------- |
| **Arduino UNO R3**        |           1 | ✅ Available | Main microcontroller              |
| **MQ-2 Gas/Smoke Sensor** |           1 | ✅ Available | Smoke and combustible gas sensing |
| **1.3" I2C OLED Display** |           1 | ✅ Available | Sensor values and system status   |
| **Green LED**             |           1 | ✅ Available | Normal condition indicator        |
| **Red LED**               |           1 | ✅ Available | Alert indicator                   |
| **220Ω Resistor**         |           2 | ✅ Available | LED current limiting              |
| **Buzzer**                |           1 | ✅ Available | Audible warning                   |
| **Breadboard**            |           1 | ✅ Available | Circuit prototyping               |
| **Jumper Wires**          | As required | ✅ Available | Electrical connections            |
| **USB Cable**             |           1 | ✅ Available | Arduino programming and power     |

---

## 🔌 V1 Component Roles

### Arduino UNO R3

Acts as the main controller of the current prototype.

Responsibilities:

* Reads MQ-2 analog output
* Processes sensor readings
* Applies threshold-based detection
* Controls LEDs
* Controls buzzer
* Updates OLED display

---

### MQ-2 Gas/Smoke Sensor

The primary sensing element of V1.

Used for detecting changes associated with:

* Smoke
* Combustible gases
* Various volatile/combustible compounds

Current connection:

```text
MQ-2 AO → Arduino A0
```

---

### 1.3" OLED Display

Used for real-time system feedback.

Displays information such as:

```text
SMOKE DETECTOR
Smoke Value: XXX
Status: NORMAL / ALERT
```

Current I2C address:

```text
0x3C
```

---

### Green LED

Indicates normal operating conditions.

```text
D8 → 220Ω → Green LED → GND
```

---

### Red LED

Indicates an alert condition.

```text
D9 → 220Ω → Red LED → GND
```

---

### Buzzer

Provides an audible warning when the detected smoke/gas value crosses the configured threshold.

```text
D10 → Buzzer (+)
GND  → Buzzer (-)
```

---

# 🟡 V2 — Multi-Sensor Detection

The next version will introduce additional environmental sensors to reduce dependence on the MQ-2 alone.

| Component               | Quantity | Status            | Purpose                          |
| ----------------------- | -------: | ----------------- | -------------------------------- |
| **ESP32 DevKit**        |        1 | 🔄 Planned        | More powerful controller + Wi-Fi |
| **MQ-7**                |        1 | 🔄 Planned        | Carbon monoxide sensing          |
| **Temperature Sensor**  |        1 | 🔄 Planned        | Thermal monitoring               |
| **Humidity Sensor**     |        1 | 🔄 Planned        | Environmental context            |
| **PM2.5 / PM10 Sensor** |        1 | 🔄 Planned        | Particulate/smoke measurement    |
| **Flame / IR Sensor**   |        1 | 🔄 Planned        | Flame detection/verification     |
| **Buzzer**              |        1 | Already available | Audible alert                    |
| **OLED**                |        1 | Already available | Local visualization              |
| **LEDs**                |       2+ | Already available | System status                    |

---

# 🧪 V2 Sensor Roles

## MQ-7 — Carbon Monoxide

The MQ-7 will add a dedicated carbon-monoxide sensing channel.

Why it matters:

Carbon monoxide is one of the important products associated with incomplete combustion.

The combination:

```text
Smoke + CO
```

can provide more information than smoke sensing alone.

> Note: MQ-7 is a low-cost gas sensor requiring appropriate heater-cycle operation and calibration. Its output should not be treated as a certified CO concentration without proper calibration.

---

## 🌡️ Temperature Sensor

Purpose:

* Monitor ambient temperature
* Detect abnormal temperature increases
* Calculate rate of temperature rise
* Provide thermal information for sensor fusion

Future analysis:

```text
Temperature
     ↓
Rate of Change
     ↓
dT/dt
```

---

## 💧 Humidity Sensor

Purpose:

* Monitor environmental humidity
* Provide environmental context
* Help interpret changes in other sensors
* Provide additional features for future ML models

---

## 🌫️ PM2.5 / PM10 Sensor

Unlike the MQ-2, a particulate sensor can directly measure airborne particle concentration.

Potential uses:

* Smoke detection
* Particulate monitoring
* Differentiating atmospheric conditions
* Additional input for sensor-fusion algorithms

---

## 🔥 Flame / IR Sensor

Provides an additional physical indication of flame.

Potential use:

```text
Smoke detected
      +
Flame detected
      ↓
Higher fire confidence
```

The flame sensor will not replace smoke/gas sensing; it will act as another information source.

---

# 🔵 V3 — Sensor Fusion Hardware

At this stage, the project will combine multiple sensors around a more capable ESP32 platform.

### Core Hardware

```text
ESP32
 │
 ├── MQ-2
 ├── MQ-7
 ├── Temperature Sensor
 ├── Humidity Sensor
 ├── PM2.5 Sensor
 ├── Flame Sensor
 └── OLED
```

The objective is to combine measurements from different physical phenomena rather than depending on one sensor.

---

# 🧠 V4 — TinyML / Edge AI

No major additional sensor hardware is necessarily required for this stage.

The primary upgrade will be computational/software-based.

### Required Hardware

| Component                     | Purpose               |
| ----------------------------- | --------------------- |
| **ESP32**                     | Edge ML inference     |
| **Existing Sensors**          | ML input features     |
| **MicroSD Module (Optional)** | Local data logging    |
| **RTC Module (Optional)**     | Accurate timestamping |

---

## 📊 Data Logging

A future data-collection system may use:

### MicroSD Card Module

Purpose:

* Store sensor readings
* Build training datasets
* Record abnormal events
* Analyze historical sensor behavior

Example:

```text
timestamp,
MQ2,
MQ7,
temperature,
humidity,
PM2.5,
flame,
classification
```

---

# 🌐 V5 — IoT Monitoring

The ESP32 will provide Wi-Fi connectivity.

### Additional Components

| Component                | Status      | Purpose                 |
| ------------------------ | ----------- | ----------------------- |
| **ESP32**                | 🔄 Planned  | Wi-Fi + edge processing |
| **Wi-Fi Network**        | 🔄 Required | Data transmission       |
| **Cloud / Web Server**   | 🔄 Planned  | Remote monitoring       |
| **Dashboard**            | 🔄 Planned  | Real-time visualization |
| **Notification Service** | 🔄 Planned  | Remote alerts           |

Potential architecture:

```text
Sensors
   ↓
ESP32
   ↓
Edge Processing
   ↓
Wi-Fi
   ↓
Dashboard / Cloud
   ↓
User
```

---

# 📷 V6 — Computer Vision

An advanced version may introduce a camera for visual verification.

### Planned Components

| Component                          | Status      | Purpose                        |
| ---------------------------------- | ----------- | ------------------------------ |
| **ESP32-CAM / Camera Module**      | 🔬 Research | Flame/smoke visual detection   |
| **Camera Mount**                   | 🔬 Research | Stable camera positioning      |
| **Additional Lighting (Optional)** | 🔬 Research | Controlled testing environment |

The camera would provide a second sensing modality:

```text
Physical Sensors
       +
Computer Vision
       ↓
Multimodal Fire Detection
```

---

# 👃 V7 — Electronic Nose

A future experimental version may use a gas sensor array.

### Possible Sensors

| Component                       | Status      | Possible Role                  |
| ------------------------------- | ----------- | ------------------------------ |
| **MQ-2**                        | Existing    | Smoke / combustible gases      |
| **MQ-5**                        | 🔬 Research | Gas-pattern sensing            |
| **MQ-7**                        | 🔄 Planned  | CO                             |
| **MQ-135**                      | 🔬 Research | Broad air-quality/gas response |
| **Other selective gas sensors** | 🔬 Research | Gas fingerprinting             |

The objective is not simply to detect "more gas."

Instead, multiple sensor responses can form a **chemical response pattern** that can potentially be classified using machine learning.

---

# ⚡ Power & Protection Components

As the project becomes more complex, additional power-management hardware may be required.

### Planned Components

| Component                 | Purpose                           |
| ------------------------- | --------------------------------- |
| 5V regulated supply       | Stable sensor/controller power    |
| 3.3V regulated supply     | ESP32-compatible peripherals      |
| DC-DC converter           | Voltage conversion where required |
| Fuse / protection         | Basic power protection            |
| Terminal blocks           | More reliable connections         |
| Capacitors                | Supply filtering                  |
| Transistor/MOSFET drivers | Driving higher-current loads      |
| Relay module              | Optional external alarm/control   |

---

# 🧰 Prototyping & Assembly

For future versions:

* Breadboard
* Jumper wires
* Male/Female headers
* Pin headers
* Perfboard
* PCB
* Screw terminals
* Heat-shrink tubing
* Enclosure

The project will eventually move from a breadboard prototype toward a dedicated PCB.

---

# 📦 Complete Future Hardware Stack

The long-term hardware architecture may look like:

```text
                         ┌─────────────────┐
                         │      ESP32      │
                         │ Edge AI + Wi-Fi │
                         └────────┬────────┘
                                  │
       ┌────────┬────────┬───────┼───────┬────────┐
       ↓        ↓        ↓       ↓       ↓        ↓
     MQ-2     MQ-7      Temp    Humid    PM2.5   Flame
     Smoke     CO       Sensor  Sensor   Sensor  Sensor
       │        │        │       │        │        │
       └────────┴────────┴───────┴────────┴────────┘
                                  │
                                  ↓
                          Sensor Fusion
                                  │
                                  ↓
                            TinyML / AI
                                  │
                    ┌─────────────┼─────────────┐
                    ↓             ↓             ↓
                  OLED         Buzzer          IoT
                Display         Alert        Dashboard
                                               
                         Optional Future
                               │
                         ┌─────┴─────┐
                         ↓           ↓
                       Camera    Gas Array
```

---

# 📋 Component Status Legend

| Symbol | Meaning                           |
| ------ | --------------------------------- |
| ✅      | Currently available / implemented |
| 🔄     | Planned for upcoming development  |
| 🔬     | Experimental / research direction |
| ⚙️     | Supporting hardware               |

---

# 🛣️ Hardware Development Roadmap

```text
V1
Arduino UNO
+ MQ-2
+ OLED
+ LEDs
+ Buzzer
        ↓
V2
ESP32
+ MQ-7
+ Temperature
+ Humidity
+ PM2.5
+ Flame Sensor
        ↓
V3
Sensor Fusion
+ Data Logging
        ↓
V4
TinyML / Edge AI
        ↓
V5
IoT + Remote Monitoring
        ↓
V6
Computer Vision
        ↓
V7
Electronic Nose
        ↓
Final Goal
Multimodal Intelligent Fire Detection
```

---

# ⚠️ Component Selection Note

The exact sensors used in future versions may change after testing.

Component selection will be based on:

* Sensor accuracy
* Response time
* Cost
* Power consumption
* Environmental stability
* Availability
* Calibration requirements
* Compatibility with ESP32
* Performance during controlled testing

The goal is to select components based on **measured performance**, not simply the number of sensors added.
