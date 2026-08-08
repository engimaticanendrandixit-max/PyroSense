# ⚙️ PyroSense V1 — Working Principle

## 1. Overview

PyroSense V1 is an Arduino UNO-based smoke detection prototype that uses an MQ-2 gas/smoke sensor to monitor changes in the surrounding atmosphere.

The sensor provides an analog signal to the Arduino, which processes the reading using a predefined threshold. The system then provides visual and audible feedback through an OLED display, LEDs, and a buzzer.

The complete working cycle can be summarized as:

**Sense → Read → Process → Compare → Display → Alert**

---

## 2. System Architecture

```text
                    Smoke / Gas
                         │
                         ▼
                ┌─────────────────┐
                │      MQ-2       │
                │ Gas/Smoke Sensor│
                └────────┬────────┘
                         │
                    Analog Output
                         │
                         ▼
                ┌─────────────────┐
                │   Arduino UNO   │
                │                 │
                │  ADC + Logic    │
                └────────┬────────┘
                         │
                  Sensor Processing
                         │
                         ▼
                ┌─────────────────┐
                │    Threshold    │
                │    Comparison   │
                └────────┬────────┘
                         │
                ┌────────┴────────┐
                │                 │
                ▼                 ▼
             NORMAL              ALERT
                │                 │
                ▼                 ▼
           Green LED          Red LED
           Buzzer OFF         Buzzer ON
                │
                └──────┐
                       ▼
                  OLED Display
```

---

## 3. Step 1 — Smoke/Gas Sensing

The MQ-2 is the primary sensing component of PyroSense V1.

The sensor contains a metal-oxide sensing material whose electrical resistance changes when exposed to certain gases and smoke.

The MQ-2 module provides an analog output that changes according to the sensor's response.

In our V1 circuit:

```text
MQ-2 AO → Arduino A0
```

The analog output is therefore used as the primary input for the detection algorithm.

> **Note:** The MQ-2 is a broad-response sensor. Its raw analog value should be treated as a sensor response rather than a direct measurement of a specific gas concentration.

---

## 4. Step 2 — Analog Signal Acquisition

The Arduino UNO reads the MQ-2 analog output through its **A0 analog input**.

The Arduino UNO contains a **10-bit ADC (Analog-to-Digital Converter)**.

Therefore, the analog input is represented by a digital value in the range:

```text
0 → 1023
```

Conceptually:

```text
MQ-2 Analog Voltage
        │
        ▼
   Arduino A0
        │
        ▼
      ADC
        │
        ▼
 Digital Reading
    0 — 1023
```

A higher or lower value indicates a change in the sensor's electrical response, depending on the module, wiring, sensor condition, and environmental conditions.

---

## 5. Step 3 — Sensor Data Processing

Once the Arduino obtains the analog reading, the program processes the value.

A simplified representation is:

```cpp
sensorValue = analogRead(A0);
```

The resulting value is then used by the detection logic.

For example:

```text
Sensor Value = 120
Sensor Value = 180
Sensor Value = 275
Sensor Value = 360
```

These values represent changes in the MQ-2's response.

They should not automatically be interpreted as:

```text
120 ppm
180 ppm
275 ppm
```

because the current V1 system has not been calibrated to provide certified gas concentration measurements.

---

## 6. Step 4 — Threshold Comparison

The current V1 uses a simple threshold-based detection method.

The sensor reading is compared against a predefined threshold:

```text
IF sensorValue < threshold
        ↓
     NORMAL

IF sensorValue >= threshold
        ↓
      ALERT
```

This is the fundamental decision-making mechanism of V1.

---

## 7. Step 5 — Normal Condition

When the sensor reading remains below the configured threshold, the system considers the environment to be within the current normal detection range.

The system responds by:

```text
Green LED → ON
Red LED   → OFF
Buzzer    → OFF
OLED      → NORMAL
```

Conceptually:

```text
              Sensor Reading
                    │
                    ▼
             Below Threshold
                    │
                    ▼
                 NORMAL
              ┌─────┼─────┐
              ▼     ▼     ▼
           Green   Red   Buzzer
            ON     OFF     OFF
```

---

## 8. Step 6 — Alert Condition

When the MQ-2 reading crosses the configured threshold, the system enters the alert state.

The response is:

```text
Green LED → OFF
Red LED   → ON
Buzzer    → ON
OLED      → ALERT
```

Flow:

```text
              Sensor Reading
                    │
                    ▼
             Threshold Crossed
                    │
                    ▼
                  ALERT
              ┌─────┼─────┐
              ▼     ▼     ▼
           Green   Red   Buzzer
            OFF     ON     ON
```

This provides both visual and audible indication of an abnormal sensor reading.

---

## 9. Step 7 — OLED Monitoring

The OLED provides real-time feedback to the user.

The display communicates with the Arduino through the **I2C interface**.

### OLED Connections

```text
OLED VCC → 5V
OLED GND → GND
OLED SDA → A4
OLED SCL → A5
```

The OLED uses the I2C address:

```text
0x3C
```

The display can show information such as:

```text
--------------------
    SMOKE DETECTOR

    VALUE:  XXX

    STATUS: NORMAL
--------------------
```

During an alert:

```text
--------------------
    SMOKE DETECTOR

    VALUE:  XXX

    STATUS: ALERT
--------------------
```

---

## 10. Complete V1 Signal Flow

The complete operation of PyroSense V1 can be represented as:

```text
                ENVIRONMENT
                     │
                     │
              Smoke / Gas
                     │
                     ▼
              ┌────────────┐
              │    MQ-2    │
              └─────┬──────┘
                    AO
                     │
                     ▼
              ┌────────────┐
              │ Arduino A0 │
              └─────┬──────┘
                    │
                    ▼
              ┌────────────┐
              │    ADC     │
              │ 0 — 1023   │
              └─────┬──────┘
                    │
                    ▼
             Sensor Processing
                    │
                    ▼
             Threshold Check
                    │
             ┌──────┴──────┐
             │             │
             ▼             ▼
          NORMAL          ALERT
             │             │
             ▼             ▼
         Green LED       Red LED
            ON              ON
                             +
                           Buzzer
                             ON
             │             │
             └──────┬───────┘
                    ▼
               OLED Display
```

---

## 11. Detection Logic in Simple Terms

The V1 system can be understood using five basic steps:

### 1. Sense

MQ-2 responds to changes in the surrounding atmosphere.

### 2. Read

Arduino reads the MQ-2 analog output through A0.

### 3. Process

The analog signal is converted into a digital value by the Arduino's ADC.

### 4. Decide

The reading is compared with the configured threshold.

### 5. Alert

Depending on the result, the system controls the LEDs, buzzer, and OLED.

```text
SENSE
  ↓
READ
  ↓
PROCESS
  ↓
COMPARE
  ↓
DISPLAY + ALERT
```

---

## 12. Why V1 Uses Threshold Detection

Threshold detection was selected for V1 because it provides:

- Simple implementation
- Fast response
- Easy debugging
- Easy visualization
- Low computational requirements
- A clear foundation for future development

It also makes it easier to experimentally observe how the MQ-2 behaves under different conditions.

---

## 13. Important Limitation

The V1 system detects an **abnormal MQ-2 sensor response**, not a confirmed fire.

For example:

```text
Incense Smoke
      ↓
MQ-2 Response ↑
      ↓
Threshold Crossed
      ↓
ALERT
```

This does not necessarily mean that an actual fire is present.

Similarly, environmental conditions, sensor warm-up, sensor aging, humidity, temperature, and other gases can influence the MQ-2 response.

Therefore:

> **V1 should be considered a smoke/gas detection prototype rather than a certified fire detection system.**

---

## 14. V1 Working Summary

The complete working principle is:

```text
Smoke / Gas
     ↓
    MQ-2
     ↓
Analog Signal
     ↓
Arduino A0
     ↓
10-bit ADC
     ↓
Sensor Value
     ↓
Threshold Comparison
     ↓
┌──────────────┐
│              │
▼              ▼
NORMAL        ALERT
│              │
▼              ▼
Green LED     Red LED
              +
            Buzzer
│              │
└──────┬───────┘
       ▼
   OLED Display
```

The V1 architecture establishes the fundamental sensing, processing, visualization, and alert pipeline that forms the core of the PyroSense project.