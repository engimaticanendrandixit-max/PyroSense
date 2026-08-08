# 🧪 PyroSense V1 — Testing & Validation

## 1. Introduction

Testing is performed to verify that each component of PyroSense V1 works correctly and that the complete system responds appropriately to changes in the MQ-2 sensor output.

The testing process covers:

- MQ-2 sensor response
- Analog signal acquisition
- OLED display
- Green LED
- Red LED
- Buzzer
- Threshold detection
- Smoke response
- Recovery after smoke exposure
- Overall system behavior

The complete testing approach is:

```text
Component Test
      ↓
Sensor Test
      ↓
Threshold Test
      ↓
Smoke Test
      ↓
Alert Test
      ↓
Recovery Test
      ↓
System Validation
```

---

# 2. Testing Objectives

The main objectives of V1 testing are:

1. Verify that the MQ-2 produces a readable analog signal.
2. Verify that Arduino UNO correctly reads the sensor output.
3. Verify that the OLED displays sensor information.
4. Verify that the LEDs indicate the correct system state.
5. Verify that the buzzer activates during an alert.
6. Verify that the selected threshold works correctly.
7. Observe the sensor response to smoke.
8. Verify that the system returns toward NORMAL after smoke exposure is removed.

---

# 3. Test Environment

The basic V1 testing setup consists of:

| Parameter | Configuration |
|---|---|
| Microcontroller | Arduino UNO R3 |
| Gas/Smoke Sensor | MQ-2 |
| OLED | I2C OLED |
| OLED Address | 0x3C |
| Analog Input | A0 |
| Green LED | Digital Pin 8 |
| Red LED | Digital Pin 9 |
| Buzzer | Digital Pin 10 |
| LED Resistors | 220 Ω |
| Test Stimulus | Incense/Agarbatti Smoke |

> **Note:** Actual sensor readings depend on the environment, sensor condition, warm-up state, and test conditions.

---

# 4. Test 1 — Power Supply Verification

### Objective

Verify that all components receive power correctly.

### Procedure

1. Connect the Arduino UNO to the power source.
2. Verify that the MQ-2 heater becomes active.
3. Verify that the OLED powers on.
4. Verify that the LEDs and buzzer are connected correctly.
5. Check that no component becomes abnormally hot.

### Expected Result

```text
Arduino → Powered
MQ-2 → Heater Active
OLED → Powered
LEDs → Available
Buzzer → Available
```

### Result

**PASS / FAIL**

---

# 5. Test 2 — MQ-2 Analog Output Test

### Objective

Verify that the MQ-2 produces a readable analog signal.

### Procedure

1. Connect:

```text
MQ-2 AO → Arduino A0
```

2. Upload the basic analog-reading program.
3. Open the Serial Monitor.
4. Observe the sensor readings.
5. Allow the sensor to warm up.
6. Record the readings in relatively clean air.

### Expected Result

The Arduino should continuously display numerical values between:

```text
0 — 1023
```

Example:

```text
Sensor Value: 84
Sensor Value: 86
Sensor Value: 88
Sensor Value: 85
```

### Result

**PASS / FAIL**

---

# 6. Test 3 — Sensor Response to Smoke

### Objective

Verify that the MQ-2 responds to smoke.

### Procedure

1. Allow the MQ-2 to stabilize.
2. Record the clean-air reading.
3. Introduce a controlled amount of incense smoke near the sensor.
4. Observe the sensor value.
5. Record the maximum observed response.
6. Remove the smoke source.

### Expected Result

The sensor reading should show a noticeable change compared with the baseline.

Example:

```text
Clean Air
   ↓
~80–100
   ↓
Smoke Applied
   ↓
~150–300+
```

The exact values will vary depending on the test conditions.

### Result

**PASS / FAIL**

---

# 7. Test 4 — OLED Display Test

### Objective

Verify that the OLED correctly displays sensor information.

### Procedure

1. Connect the OLED using I2C.
2. Verify the I2C address:

```text
0x3C
```

3. Upload the PyroSense V1 program.
4. Observe the OLED.

### Expected Result

The OLED should display information similar to:

```text
--------------------
    SMOKE DETECTOR

    VALUE:  XXX

    STATUS: NORMAL
--------------------
```

When the threshold is crossed:

```text
--------------------
    SMOKE DETECTOR

    VALUE:  XXX

    STATUS: ALERT
--------------------
```

### Result

**PASS / FAIL**

---

# 8. Test 5 — Green LED Test

### Objective

Verify the NORMAL-state indicator.

### Procedure

1. Keep the MQ-2 reading below the configured threshold.
2. Observe the LEDs.

### Expected Result

```text
Green LED → ON
Red LED   → OFF
Buzzer    → OFF
```

### Result

**PASS / FAIL**

---

# 9. Test 6 — Red LED Test

### Objective

Verify the ALERT-state indicator.

### Procedure

1. Introduce smoke or use a controlled sensor value that crosses the threshold.
2. Observe the LEDs.

### Expected Result

```text
Green LED → OFF
Red LED   → ON
Buzzer    → ON
```

### Result

**PASS / FAIL**

---

# 10. Test 7 — Buzzer Test

### Objective

Verify that the buzzer activates during an alert.

### Procedure

1. Ensure the sensor reading crosses the configured threshold.
2. Observe the buzzer.

### Expected Result

```text
Threshold Crossed
       ↓
Buzzer → ON
```

When the sensor returns below the threshold:

```text
Buzzer → OFF
```

### Result

**PASS / FAIL**

---

# 11. Test 8 — Threshold Logic Test

### Objective

Verify the core decision-making logic of PyroSense V1.

Assume:

```text
Threshold = 150
```

### Test Cases

| Sensor Value | Expected State |
|---:|---|
| 50 | NORMAL |
| 100 | NORMAL |
| 149 | NORMAL |
| 150 | ALERT |
| 180 | ALERT |
| 250 | ALERT |
| 350 | ALERT |

### Expected Logic

```text
IF sensorValue < threshold
        ↓
     NORMAL

IF sensorValue >= threshold
        ↓
      ALERT
```

### Result

**PASS / FAIL**

---

# 12. Test 9 — NORMAL → ALERT Transition

### Objective

Verify that the system changes state correctly when smoke is introduced.

### Procedure

1. Start with the sensor in relatively clean air.
2. Confirm that the system shows NORMAL.
3. Introduce smoke.
4. Observe the sensor reading.
5. Wait until the reading crosses the threshold.

### Expected Transition

```text
NORMAL
  ↓
Smoke Introduced
  ↓
Sensor Reading Increases
  ↓
Threshold Crossed
  ↓
ALERT
```

Expected outputs:

```text
Green LED → OFF
Red LED   → ON
Buzzer    → ON
OLED      → ALERT
```

### Result

**PASS / FAIL**

---

# 13. Test 10 — ALERT → NORMAL Recovery

### Objective

Verify that the system can return to NORMAL after the smoke source is removed.

### Procedure

1. Trigger an alert using controlled smoke.
2. Confirm that the system enters ALERT.
3. Remove the smoke source.
4. Allow fresh air to reach the sensor.
5. Observe the sensor reading.

### Expected Behavior

```text
ALERT
  ↓
Smoke Removed
  ↓
Sensor Response Decreases
  ↓
Reading Falls Below Threshold
  ↓
NORMAL
```

Expected outputs:

```text
Green LED → ON
Red LED   → OFF
Buzzer    → OFF
OLED      → NORMAL
```

### Result

**PASS / FAIL**

---

# 14. Test 11 — Repeated Smoke Test

### Objective

Determine whether the MQ-2 produces a reasonably repeatable response.

### Procedure

Perform the same smoke exposure multiple times while keeping the test conditions approximately similar.

Record:

- Initial reading
- Maximum reading
- Threshold crossing
- Recovery reading

### Test Table

| Test | Initial | Maximum | Threshold Crossed | Recovery |
|---:|---:|---:|---|---:|
| 1 | ___ | ___ | YES / NO | ___ |
| 2 | ___ | ___ | YES / NO | ___ |
| 3 | ___ | ___ | YES / NO | ___ |
| 4 | ___ | ___ | YES / NO | ___ |
| 5 | ___ | ___ | YES / NO | ___ |

### Result

**PASS / FAIL**

---

# 15. Test 12 — Sensor Stability Test

### Objective

Determine how much the sensor reading fluctuates under relatively stable conditions.

### Procedure

1. Allow the sensor to warm up.
2. Keep it in clean air.
3. Record readings at regular intervals.

Example:

| Time | Sensor Reading |
|---:|---:|
| 0 min | ___ |
| 1 min | ___ |
| 2 min | ___ |
| 3 min | ___ |
| 4 min | ___ |
| 5 min | ___ |

### Observation

The readings should remain within a reasonable range under stable conditions.

Large fluctuations may indicate:

- Insufficient warm-up
- Environmental changes
- Sensor instability
- Wiring issues
- Power supply issues

### Result

**PASS / FAIL**

---

# 16. Test 13 — False Trigger Test

### Objective

Determine whether the system unnecessarily enters ALERT under normal conditions.

### Procedure

Operate the sensor without intentionally exposing it to smoke.

Observe whether the threshold is crossed.

### Expected Result

```text
Normal Environment
       ↓
Sensor Reading
       ↓
Below Threshold
       ↓
NORMAL
```

The system should not continuously trigger an alert due to small natural variations.

### Result

**PASS / FAIL**

---

# 17. Test 14 — Distance Variation Test

### Objective

Observe how the distance between the smoke source and MQ-2 affects the sensor response.

### Procedure

Perform smoke tests at different approximate distances.

Example:

| Distance | Sensor Response |
|---:|---:|
| 5 cm | ___ |
| 10 cm | ___ |
| 20 cm | ___ |
| 30 cm | ___ |
| 50 cm | ___ |

### Expected Observation

The sensor response may change with distance because the amount of smoke reaching the sensing surface changes.

This test demonstrates why test conditions must be controlled during calibration.

### Result

**PASS / FAIL**

---

# 18. Test 15 — Response Time

### Objective

Estimate how quickly the system responds after smoke reaches the sensor.

### Procedure

1. Start the system in NORMAL state.
2. Introduce smoke.
3. Record the time at which smoke exposure begins.
4. Record the time when the threshold is crossed.

Calculate:

\[
Response\ Time = Alert\ Time - Exposure\ Start\ Time
\]

### Test Record

```text
Exposure Start Time: ______

Threshold Crossed: ______

Response Time: ______
```

### Result

**PASS / FAIL**

---

# 19. Test 16 — Recovery Time

### Objective

Measure how long the sensor takes to return below the threshold after smoke is removed.

### Procedure

1. Trigger an ALERT.
2. Remove the smoke source.
3. Record the time.
4. Wait until the reading falls below the threshold.

Calculate:

\[
Recovery\ Time = Normal\ Time - Smoke\ Removal\ Time
\]

### Test Record

```text
Smoke Removed: ______

Returned to NORMAL: ______

Recovery Time: ______
```

### Result

**PASS / FAIL**

---

# 20. Complete System Test

After individual components have been tested, the complete PyroSense V1 system should be tested as one unit.

### Normal Condition

```text
Clean Air
   ↓
MQ-2
   ↓
Sensor Reading < Threshold
   ↓
NORMAL
   ├── Green LED → ON
   ├── Red LED   → OFF
   ├── Buzzer    → OFF
   └── OLED      → NORMAL
```

### Alert Condition

```text
Smoke
   ↓
MQ-2 Response
   ↓
Sensor Reading ≥ Threshold
   ↓
ALERT
   ├── Green LED → OFF
   ├── Red LED   → ON
   ├── Buzzer    → ON
   └── OLED      → ALERT
```

### Recovery Condition

```text
Smoke Removed
      ↓
Sensor Response Decreases
      ↓
Reading < Threshold
      ↓
NORMAL
```

---

# 21. V1 Testing Checklist

| Test | Status |
|---|---|
| Power Supply | ⬜ |
| MQ-2 Analog Reading | ⬜ |
| OLED Display | ⬜ |
| Green LED | ⬜ |
| Red LED | ⬜ |
| Buzzer | ⬜ |
| Threshold Logic | ⬜ |
| Smoke Response | ⬜ |
| NORMAL → ALERT | ⬜ |
| ALERT → NORMAL | ⬜ |
| Repeated Smoke Test | ⬜ |
| Sensor Stability | ⬜ |
| False Trigger Test | ⬜ |
| Distance Test | ⬜ |
| Response Time | ⬜ |
| Recovery Time | ⬜ |
| Complete System Test | ⬜ |

---

# 22. Observed V1 Test Results

The following section can be updated with actual measurements obtained from the physical prototype.

### Initial Sensor Behavior

```text
Clean-Air Reading Range:
________________________
```

### Maximum Observed Smoke Response

```text
Maximum Reading:
________________________
```

### Selected Threshold

```text
Threshold:
________________________
```

### Response Time

```text
Response Time:
________________________
```

### Recovery Time

```text
Recovery Time:
________________________
```

---

# 23. Testing Limitations

The testing performed on V1 is intended for prototype validation.

The results should not be interpreted as certified fire detection performance.

The MQ-2 response can vary due to:

- Temperature
- Humidity
- Sensor warm-up
- Sensor aging
- Smoke concentration
- Smoke source
- Distance
- Airflow
- Sensor history
- Power conditions

Therefore, identical readings should not be expected in every environment.

---

# 24. Safety Considerations

Testing should be performed carefully.

When using incense or another controlled smoke source:

- Keep the smoke source away from flammable materials.
- Avoid direct contact between flame and electronics.
- Do not intentionally expose the circuit to excessive heat.
- Ensure adequate ventilation.
- Do not use dangerous gas sources for experimentation.
- Do not treat the prototype as a certified fire alarm.

The purpose of testing is to characterize the sensor response safely, not to create an uncontrolled fire or hazardous gas environment.

---

# 25. Key Takeaway

Testing PyroSense V1 is not limited to checking whether the buzzer turns ON.

The objective is to understand the complete behavior of the system:

```text
Sensor
  ↓
Signal
  ↓
Processing
  ↓
Threshold
  ↓
Decision
  ↓
Alert
  ↓
Recovery
```

A successful V1 test should demonstrate that the system can:

> **Detect a change in MQ-2 response → compare it against a calibrated threshold → provide a visual and audible alert → and return toward normal operation after the stimulus is removed.**

These tests also provide the experimental foundation for improving PyroSense in future versions.