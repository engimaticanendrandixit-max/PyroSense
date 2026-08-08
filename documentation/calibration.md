# 🎯 PyroSense V1 — MQ-2 Calibration

## 1. Introduction

Calibration is an important step in using the MQ-2 sensor because its raw output is influenced by several factors, including:

- Sensor warm-up time
- Temperature
- Humidity
- Gas concentration
- Sensor aging
- Previous exposure to gases
- Supply voltage
- Sensor-to-smoke distance

PyroSense V1 does not attempt to convert the MQ-2 reading directly into ppm.

Instead, calibration is used to understand the sensor's normal response and select a practical detection threshold for the prototype.

The V1 calibration process can be summarized as:

```text
Warm-Up
   ↓
Clean-Air Baseline
   ↓
Repeated Measurements
   ↓
Observe Sensor Variation
   ↓
Controlled Smoke Exposure
   ↓
Observe Response
   ↓
Select Threshold
   ↓
Validate Threshold
```

---

# 2. Why Calibration Is Required

The raw MQ-2 output is not a universal value.

For example, a reading of:

```text
250
```

does not always represent the same physical condition.

The reading can change depending on:

- Sensor warm-up state
- Ambient conditions
- Sensor module characteristics
- Distance from the smoke source
- Duration of exposure
- Sensor history

Therefore, using an arbitrary threshold without observing the sensor's behavior can result in:

- False alarms
- Missed detection
- Unstable output
- Excessive sensitivity

Calibration helps establish a more meaningful operating range for the prototype.

---

# 3. Important Concept — Baseline

The **baseline** is the sensor response observed when the system is operating in a relatively clean and stable environment.

A simplified representation is:

```text
Clean Environment
       ↓
MQ-2 Reading
       ↓
Repeated Measurements
       ↓
Baseline Range
```

For example:

```text
Reading 1 → 82
Reading 2 → 85
Reading 3 → 87
Reading 4 → 84
Reading 5 → 86
```

The exact values are environment- and sensor-dependent.

The purpose is not to find one magical "normal" MQ-2 value, but to understand the sensor's normal variation.

---

# 4. Step 1 — Sensor Warm-Up

The MQ-2 contains an internal heater that must reach its operating condition before meaningful measurements can be taken.

After powering the system:

```text
Power ON
   ↓
Heater Starts
   ↓
Sensing Layer Heats
   ↓
Sensor Response Stabilizes
   ↓
Calibration / Measurement
```

During the initial period, the sensor reading may change considerably.

Therefore:

> **Calibration should not be based on the first few readings immediately after power-up.**

For experimental work, allow the sensor to stabilize before collecting baseline data.

The required stabilization time depends on the sensor's condition, operating procedure, and whether the sensor is being used for initial burn-in or routine measurements.

---

# 5. Step 2 — Clean-Air Baseline

After warm-up, place the sensor in a relatively clean and well-ventilated environment.

Avoid intentionally exposing the sensor to:

- Incense smoke
- Cooking fumes
- Alcohol vapors
- LPG
- Aerosols
- Vehicle exhaust
- Other strong vapors

Then record multiple sensor readings.

Example:

| Sample | MQ-2 Reading |
|---:|---:|
| 1 | 85 |
| 2 | 87 |
| 3 | 84 |
| 4 | 86 |
| 5 | 88 |
| 6 | 85 |
| 7 | 87 |
| 8 | 86 |

These values are only an example.

Actual values should be recorded from the physical PyroSense V1 prototype.

---

# 6. Step 3 — Calculate the Baseline

A simple baseline estimate can be obtained using the average of multiple readings.

\[
Baseline = \frac{\sum_{i=1}^{N} Reading_i}{N}
\]

For example:

```text
Readings:

85, 87, 84, 86, 88
```

The average is:

```text
Baseline = (85 + 87 + 84 + 86 + 88) / 5

Baseline = 86
```

This gives an approximate reference point for the sensor's normal response.

However, the baseline should not be treated as a permanent constant.

---

# 7. Step 4 — Observe Sensor Variation

A good calibration process should examine how much the sensor naturally fluctuates.

For example:

```text
Minimum Reading → 82
Maximum Reading → 91
```

Therefore:

```text
Normal Range ≈ 82 — 91
```

A threshold placed too close to this range may cause unwanted alerts.

Conceptually:

```text
Sensor Reading
      │
      │        Normal Variation
      │       ┌──────────────┐
      ▼       ▼              ▼
──────82──────91────────────────────
                       │
                       │
                  Detection
                   Threshold
```

The threshold should therefore provide enough separation between normal variation and the response produced by the intended test stimulus.

---

# 8. Step 5 — Controlled Smoke Exposure

After establishing the clean-air baseline, the sensor can be exposed to a controlled smoke source.

For the initial PyroSense V1 prototype, incense/agarbatti smoke can be used as an experimental test stimulus.

The test should be performed consistently.

Try to keep the following approximately constant:

- Distance between smoke source and sensor
- Exposure duration
- Smoke source
- Sensor orientation
- Environmental conditions

Example:

```text
Smoke Source
     │
     │ Controlled Distance
     ▼
   ┌─────┐
   │ MQ-2│
   └─────┘
```

---

# 9. Step 6 — Record the Sensor Response

During smoke exposure, record the sensor readings.

Example:

| Time | Sensor Reading | Condition |
|---:|---:|---|
| 0 s | 86 | Clean |
| 5 s | 95 | Smoke approaching |
| 10 s | 125 | Smoke exposure |
| 15 s | 170 | Increased exposure |
| 20 s | 210 | Strong response |
| 25 s | 240 | Strong response |

These values are illustrative.

Actual experimental values should be recorded from the PyroSense prototype.

The important observation is the **change in sensor response**, rather than a specific universal value.

---

# 10. Step 7 — Determine the Detection Threshold

The threshold should be selected after observing both:

1. Normal sensor variation
2. Sensor response during the intended test condition

Conceptually:

```text
Normal Range
     │
     │
     ▼
───────────────┬──────────────────────
               │
               │ Detection Threshold
               ▼
──────────────────────────────────────
               │
               │
               ▼
        Smoke Response
```

The threshold should be high enough to avoid triggering from normal fluctuations but low enough to detect the intended smoke response.

In V1, the threshold is implemented in software.

Example:

```cpp
#define SMOKE_THRESHOLD 150
```

The actual threshold should be adjusted based on experimental measurements rather than blindly copying a fixed value.

---

# 11. Threshold Selection Logic

The basic V1 decision logic is:

```text
IF sensorValue < threshold
        ↓
     NORMAL

IF sensorValue >= threshold
        ↓
      ALERT
```

For example, if:

```text
Threshold = 150
```

then:

```text
Sensor = 100
       ↓
NORMAL
```

while:

```text
Sensor = 200
       ↓
ALERT
```

This is a simple prototype-level detection strategy.

---

# 12. Avoid Setting the Threshold Too Close to Baseline

Suppose the clean-air readings fluctuate between:

```text
80 — 100
```

Setting the threshold at:

```text
105
```

may result in unstable behavior if environmental conditions cause the sensor to fluctuate.

A better approach is to observe the normal operating range and provide a suitable margin.

```text
          Normal Range
        ┌───────────────┐
        │               │
80 ─────┴───────────────┴──── 100

                              Threshold
                                  │
                                  ▼
──────────────────────────────────150────
```

The exact margin should be determined experimentally.

---

# 13. Repeated Calibration Tests

A single test is not sufficient to establish reliable behavior.

The same experiment should ideally be repeated multiple times.

For example:

```text
Test 1 → Smoke Response
Test 2 → Smoke Response
Test 3 → Smoke Response
Test 4 → Smoke Response
Test 5 → Smoke Response
```

Compare:

- Initial reading
- Maximum reading
- Time to threshold
- Recovery behavior
- Reading after smoke is removed

This helps determine whether the response is reasonably repeatable.

---

# 14. Recovery Test

Calibration should also consider what happens after the smoke source is removed.

Example:

```text
Smoke Applied
     ↓
Sensor Reading ↑
     ↓
Threshold Crossed
     ↓
ALERT
     ↓
Smoke Removed
     ↓
Sensor Reading ↓
     ↓
Returns Toward Baseline
```

A recovery test helps determine whether the sensor returns toward its previous operating range.

It also demonstrates that the sensor response is dynamic rather than a permanent change.

---

# 15. Hysteresis Consideration

A simple threshold system can sometimes repeatedly switch between NORMAL and ALERT when the sensor value fluctuates around the threshold.

For example:

```text
Threshold = 150

149 → NORMAL
151 → ALERT
149 → NORMAL
152 → ALERT
148 → NORMAL
```

This can cause unstable alert behavior.

A future improvement could use **hysteresis**, where different thresholds are used for entering and leaving the alert state.

Example:

```text
Enter ALERT  → ≥ 160
Return NORMAL → ≤ 140
```

Conceptually:

```text
             ALERT
              ▲
              │
            160
──────────────┼────────────
              │
            140
──────────────┼────────────
              │
              ▼
            NORMAL
```

This feature is not required for the basic V1 implementation but is an important consideration for improving detection stability.

---

# 16. Factors Affecting Calibration

MQ-2 calibration can be affected by several environmental and operational factors.

### Temperature

Changes in temperature can affect sensor response.

### Humidity

Humidity can influence the interaction between gases and the sensing surface.

### Sensor Aging

The characteristics of the sensing material can change over time.

### Warm-Up State

A recently powered sensor may produce unstable readings.

### Gas Exposure History

Previous exposure can influence subsequent readings.

### Distance

The distance between the smoke source and sensor affects the amount of gas reaching the sensing surface.

### Airflow

Moving air can change how quickly smoke reaches and leaves the sensor.

### Supply Conditions

Changes in supply voltage or heater conditions can affect sensor behavior.

---

# 17. Calibration Does Not Mean Gas Identification

Calibration of the V1 system does **not** make the MQ-2 capable of identifying a specific gas.

For example:

```text
Calibration
     ↓
Better understanding of sensor response
```

It does not mean:

```text
Calibration
     ↓
MQ-2 can identify every gas
```

The MQ-2 remains a broad-response sensor.

---

# 18. Calibration vs PPM Measurement

These two concepts should not be confused.

### V1 Calibration

Used to determine:

- Normal sensor range
- Sensor variation
- Practical detection threshold
- Response to controlled smoke

### Gas Concentration Measurement

Would require:

- Appropriate calibration standards
- Sensor characterization
- Reference gas concentrations
- Rs/R0 analysis
- Calibration curves
- Controlled environmental conditions

Therefore, PyroSense V1 focuses on **relative sensor response and threshold-based detection**, not certified ppm measurement.

---

# 19. Recommended V1 Calibration Procedure

The complete practical procedure is:

```text
1. Power ON
      ↓
2. Allow MQ-2 to warm up
      ↓
3. Place sensor in clean air
      ↓
4. Record multiple readings
      ↓
5. Determine normal operating range
      ↓
6. Introduce controlled smoke
      ↓
7. Record sensor response
      ↓
8. Repeat the test
      ↓
9. Select a threshold with suitable margin
      ↓
10. Test NORMAL → ALERT → NORMAL transition
```

---

# 20. Calibration Data Sheet

The following table can be used to record actual PyroSense V1 measurements:

| Parameter | Value |
|---|---|
| Sensor | MQ-2 |
| Controller | Arduino UNO R3 |
| Analog Pin | A0 |
| Warm-up Time | ______ |
| Clean-Air Minimum | ______ |
| Clean-Air Maximum | ______ |
| Clean-Air Average | ______ |
| Smoke Test Minimum | ______ |
| Smoke Test Maximum | ______ |
| Selected Threshold | ______ |
| Time to Alert | ______ |
| Recovery Time | ______ |

---

# 21. V1 Calibration Philosophy

The goal of calibration in PyroSense V1 is not to find a universal MQ-2 value.

Instead, the goal is to understand:

```text
What does NORMAL look like?
           ↓
How much does the sensor fluctuate?
           ↓
How does it respond to smoke?
           ↓
Where should ALERT begin?
```

This approach makes the threshold more meaningful for the specific prototype and testing environment.

---

# 22. Key Takeaway

The MQ-2 should be calibrated based on **observed sensor behavior**, not an arbitrary ADC value.

The fundamental calibration process is:

> **Warm-Up → Baseline → Controlled Exposure → Response Analysis → Threshold Selection → Validation**

For PyroSense V1, calibration establishes the foundation for reliable threshold-based smoke detection while recognizing that the MQ-2 is a broad-response sensor and not a certified gas concentration instrument.