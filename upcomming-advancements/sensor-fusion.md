# 🔬 PyroSense — Sensor Fusion

## 1. Introduction

PyroSense V1 relies primarily on a single MQ-2 sensor and a fixed threshold to detect abnormal smoke/gas responses.

Although this approach is simple and effective for a basic prototype, a single sensor cannot provide enough information to reliably distinguish between different environmental events.

For future versions, PyroSense will investigate **multi-sensor fusion**.

The basic idea is:

> **Instead of trusting one sensor, combine information from multiple independent sensors to make a stronger decision.**

---

# 2. Why Sensor Fusion?

The MQ-2 is a broad-response gas sensor.

It can respond to multiple gases and smoke-producing substances.

Therefore:

```text
MQ-2 Response ↑
      ↓
Something changed
```

does not necessarily mean:

```text
Fire detected
```

The change could be caused by:

- Smoke
- Combustible gases
- Vapors
- Environmental changes
- Temperature
- Humidity
- Sensor drift

Sensor fusion attempts to reduce this uncertainty.

Instead of:

```text
MQ-2 → ALERT
```

the future system can evaluate:

```text
MQ-2
Temperature
Humidity
CO
Particulate Matter
Rate of Change
Exposure Duration
       ↓
Sensor Fusion
       ↓
Risk Estimation
```

---

# 3. Proposed Sensor Set

The future PyroSense architecture can use several sensing mechanisms.

| Sensor | Primary Information | Role |
|---|---|---|
| MQ-2 | Smoke / combustible gas response | Gas/smoke indication |
| MQ-7 | CO response | Combustion-related evidence |
| Temperature Sensor | Temperature | Thermal evidence |
| Humidity Sensor | Relative humidity | Environmental compensation |
| PM Sensor | Particulate matter | Particle/smoke evidence |

The exact sensor combination may change during development depending on cost, availability, accuracy, and experimental results.

---

# 4. Sensor Roles

## 4.1 MQ-2

The MQ-2 acts as the primary broad-response gas/smoke sensor.

Its output can provide information about changes in the surrounding atmosphere.

```text
MQ-2
  ↓
Broad Gas/Smoke Response
```

However, the MQ-2 should not be treated as a standalone fire detector.

---

## 4.2 MQ-7

MQ-7 can provide additional information related to carbon monoxide.

CO can be an important indicator of combustion.

The important distinction is:

```text
MQ-2 → Broad response
MQ-7 → CO-focused response
```

Combining both can provide more information than using MQ-2 alone.

---

## 4.3 Temperature Sensor

A temperature sensor provides thermal information.

Example:

```text
Smoke ↑
Temperature stable
```

is different from:

```text
Smoke ↑
Temperature rapidly increasing
```

Temperature therefore becomes an additional feature in the risk model.

---

## 4.4 Humidity Sensor

Humidity can affect the behavior of some gas and particulate sensors.

Therefore, humidity can be used for:

- Environmental monitoring
- Sensor compensation
- Data analysis
- Improving model robustness

Example:

```text
MQ-2 Response
      +
Humidity
      ↓
Environmental Context
```

---

## 4.5 Particulate Matter Sensor

A particulate matter sensor can provide information about airborne particles.

This is fundamentally different from the MQ-2's gas-sensitive response.

Therefore:

```text
MQ-2
Gas/Smoke Response
        +
PM Sensor
Particle Concentration
        ↓
Independent Evidence
```

This sensor diversity can potentially improve confidence in smoke-related events.

---

# 5. Sensor Fusion Architecture

The proposed architecture is:

```text
                   ┌─────────────┐
                   │    MQ-2     │
                   └──────┬──────┘
                          │
                   ┌──────▼──────┐
                   │    MQ-7     │
                   └──────┬──────┘
                          │
                   ┌──────▼──────┐
                   │ Temperature │
                   └──────┬──────┘
                          │
                   ┌──────▼──────┐
                   │   Humidity  │
                   └──────┬──────┘
                          │
                   ┌──────▼──────┐
                   │ PM Sensor   │
                   └──────┬──────┘
                          │
                          ▼
                 ┌─────────────────┐
                 │ Data Processing  │
                 └────────┬────────┘
                          │
                          ▼
                 ┌─────────────────┐
                 │ Feature         │
                 │ Extraction      │
                 └────────┬────────┘
                          │
                          ▼
                 ┌─────────────────┐
                 │ Sensor Fusion   │
                 │ Engine          │
                 └────────┬────────┘
                          │
                          ▼
                 ┌─────────────────┐
                 │ Risk Estimation │
                 └────────┬────────┘
                          │
              ┌───────────┼───────────┐
              ▼           ▼           ▼
           NORMAL       WARNING     CRITICAL
```

---

# 6. Data Acquisition

All sensors will provide measurements to the main controller.

A future ESP32-based implementation can act as the central processing unit.

Conceptually:

```text
Sensors
   ↓
ESP32
   ↓
Timestamped Measurements
   ↓
Processing
```

Each measurement should ideally contain:

```text
Timestamp
Sensor ID
Sensor Value
Sensor Status
```

Example:

```text
Time: 10:32:15

MQ-2: 182
MQ-7: 74
Temperature: 31.4°C
Humidity: 52%
PM: 18 µg/m³
```

---

# 7. Data Normalization

Different sensors produce values in different units and ranges.

For example:

```text
MQ-2       → ADC value
MQ-7       → sensor response
Temperature → °C
Humidity    → %
PM          → µg/m³
```

These values cannot be directly combined without preprocessing.

A normalization step is therefore required.

A simple normalization approach is:

\[
X_{norm} = \frac{X-X_{min}}{X_{max}-X_{min}}
\]

This maps the measurement approximately into:

```text
0 → 1
```

Example:

```text
Raw Value
   ↓
Normalization
   ↓
0.0 — 1.0
```

The exact normalization method will depend on sensor calibration and collected experimental data.

---

# 8. Baseline Estimation

Before fusion, the system should understand what is considered normal for the environment.

The system can collect baseline measurements during relatively clean conditions.

Example:

```text
MQ-2 baseline = 90
MQ-7 baseline = 60
Temperature = 30°C
Humidity = 50%
PM = 10 µg/m³
```

These values form part of the environmental baseline.

The system can then monitor deviations from that baseline.

---

# 9. Sensor Deviation

Instead of looking only at absolute values, future versions can calculate deviation from baseline.

Conceptually:

\[
Deviation = Current\ Value - Baseline
\]

For normalized data:

\[
Deviation_{norm}
\]

can be used as a feature for the fusion engine.

Example:

```text
Baseline MQ-2 = 90
Current MQ-2  = 180

Deviation = 90
```

This can be more useful than using a universal threshold for every environment.

---

# 10. Rate of Change

Sensor magnitude alone is not enough.

The system can also evaluate how quickly a value is changing.

\[
Rate\ of\ Change = \frac{X_t-X_{t-1}}{t-t_{prev}}
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

over a short period indicates a much faster change.

This can become an important feature in future risk estimation.

---

# 11. Persistence

A sensor event should not necessarily be considered dangerous just because it crosses a threshold for one instant.

The system can measure how long the abnormal condition persists.

```text
Threshold Crossed
       ↓
Start Timer
       ↓
Condition Still Present?
       │
      YES
       ↓
Continue
       ↓
Required Duration Reached
       ↓
Increase Risk
```

This can reduce false triggers caused by short-lived fluctuations.

---

# 12. Weighted Sensor Fusion

One simple fusion approach is a weighted score.

Each sensor contributes to an overall risk score.

For example:

\[
Risk =
w_1S_{MQ2}
+
w_2S_{MQ7}
+
w_3S_{Temp}
+
w_4S_{PM}
\]

where:

- \(S\) = normalized sensor contribution
- \(w\) = weight assigned to that sensor

The weights should not be chosen arbitrarily in the final system.

They should be experimentally evaluated using collected data.

---

# 13. Example Risk Score

Suppose the system uses:

```text
MQ-2 contribution     = 0.35
MQ-7 contribution     = 0.30
Temperature           = 0.15
PM                    = 0.20
```

Then:

\[
Risk =
0.35S_{MQ2}
+
0.30S_{MQ7}
+
0.15S_{Temp}
+
0.20S_{PM}
\]

The resulting value can be mapped to a risk category.

Example:

```text
0.00 — 0.30 → NORMAL
0.30 — 0.50 → CAUTION
0.50 — 0.70 → WARNING
0.70 — 0.85 → HIGH RISK
0.85 — 1.00 → CRITICAL
```

> These values are illustrative. They must be experimentally validated before being used in a real system.

---

# 14. Evidence-Based Decision Making

The future system should avoid treating every sensor equally in every situation.

For example:

### Scenario A

```text
MQ-2 ↑
MQ-7 → Normal
Temperature → Normal
PM → Normal
```

Possible interpretation:

```text
Gas/smoke sensor response detected
but insufficient independent evidence
```

The system may classify this as:

```text
CAUTION
```

rather than immediately declaring a critical fire event.

---

### Scenario B

```text
MQ-2 ↑
MQ-7 ↑
Temperature ↑
PM ↑
```

Now multiple independent measurements indicate an abnormal event.

The system could produce:

```text
HIGH RISK
```

or:

```text
CRITICAL
```

depending on the magnitude and persistence.

---

# 15. Temporal Sensor Fusion

Sensor fusion should not only consider multiple sensors at one instant.

It should also consider their behavior over time.

Example:

```text
Time →
────────────────────────────────────

MQ-2
100 → 120 → 160 → 220 → 300

MQ-7
 60 →  62 →  70 →  90 → 120

Temperature
30 → 30 → 31 → 32 → 34

PM
10 → 15 → 30 → 50 → 80
```

All four parameters are increasing.

This creates a much stronger pattern than a single isolated spike.

---

# 16. Sensor Agreement

An important concept in fusion is **sensor agreement**.

If multiple sensors independently indicate abnormal conditions:

```text
MQ-2       → Abnormal
MQ-7       → Abnormal
Temperature → Abnormal
PM         → Abnormal
```

confidence can increase.

If only one sensor changes:

```text
MQ-2       → Abnormal
MQ-7       → Normal
Temperature → Normal
PM         → Normal
```

the system can treat the event differently.

This does not mean that disagreement proves a false alarm.

It simply provides additional context for the decision.

---

# 17. False Alarm Reduction

Sensor fusion can potentially reduce false alarms by requiring stronger evidence.

### Single Sensor

```text
MQ-2 Spike
    ↓
ALERT
```

### Multi-Sensor

```text
MQ-2 Spike
    ↓
Check MQ-7
    ↓
Check Temperature
    ↓
Check PM
    ↓
Analyze Duration
    ↓
Risk Decision
```

This provides a more robust decision-making pipeline.

---

# 18. Fault Tolerance

Sensor fusion also introduces the possibility of detecting sensor failures.

For example:

```text
MQ-2
Reading = 0 continuously
```

could indicate:

- Sensor disconnected
- Wiring problem
- Sensor failure
- Invalid measurement

The system should distinguish:

```text
Environmental Event
```

from:

```text
Sensor Fault
```

Future versions can therefore maintain a sensor-health state.

---

# 19. Proposed Decision Engine

The future decision engine can follow:

```text
             Sensor Data
                  ↓
          Data Validation
                  ↓
          Noise Filtering
                  ↓
          Normalization
                  ↓
         Baseline Comparison
                  ↓
          Feature Extraction
                  ↓
        ┌───────────────────┐
        │   Sensor Fusion   │
        └─────────┬─────────┘
                  ↓
           Risk Estimation
                  ↓
         Persistence Check
                  ↓
            Final State
                  ↓
       ┌──────────┼──────────┐
       ▼          ▼          ▼
    NORMAL     WARNING    CRITICAL
```

---

# 20. Filtering

Raw sensor readings may contain noise.

Future versions can investigate filtering techniques such as:

- Moving average
- Exponential moving average
- Median filtering
- Low-pass filtering

Example moving average:

\[
Average =
\frac{x_1+x_2+\cdots+x_n}{n}
\]

Instead of reacting to one raw measurement:

```text
150
```

the system can consider a recent window:

```text
145
150
152
148
151
```

This can provide a more stable signal.

---

# 21. Sensor Fusion and Machine Learning

The rule-based fusion system will also provide the foundation for future TinyML development.

The pipeline can eventually become:

```text
Multiple Sensors
       ↓
Data Collection
       ↓
Feature Extraction
       ↓
Dataset
       ↓
Machine Learning
       ↓
Pattern Classification
       ↓
Risk Estimation
```

Possible input features:

```text
MQ-2 value
MQ-7 value
Temperature
Humidity
PM
Rate of change
Moving average
Variance
Exposure duration
Recovery rate
```

---

# 22. Transition from Rules to AI

The development path is intentionally gradual.

### Stage 1

```text
Single Threshold
```

### Stage 2

```text
Multiple Thresholds
```

### Stage 3

```text
Weighted Sensor Fusion
```

### Stage 4

```text
Feature-Based Classification
```

### Stage 5

```text
TinyML Model
```

This allows each stage to be tested and compared with the previous one.

---

# 23. Example Future Scenario

Consider the following event:

```text
Initial State

MQ-2 = Normal
MQ-7 = Normal
Temperature = Normal
PM = Normal
```

Then:

```text
MQ-2 begins increasing
```

The system enters:

```text
CAUTION
```

After several seconds:

```text
MQ-2 ↑
MQ-7 ↑
PM ↑
Temperature ↑
```

The system now has multiple independent indicators.

The risk score increases:

```text
NORMAL
   ↓
CAUTION
   ↓
WARNING
   ↓
HIGH RISK
```

If the evidence continues to increase:

```text
CRITICAL
```

The system can then trigger:

```text
Buzzer
+
Red LED
+
OLED Warning
+
IoT Notification
```

---

# 24. Important Limitations

Sensor fusion does not automatically guarantee accurate fire detection.

Possible limitations include:

- Sensor cross-sensitivity
- Sensor drift
- Calibration errors
- Environmental effects
- Poor sensor placement
- Correlated sensor errors
- Limited training data
- False positives
- False negatives
- Hardware limitations

Therefore, every fusion strategy must be experimentally validated.

---

# 25. Experimental Validation

Future sensor-fusion development should include controlled experiments.

Potential test conditions:

```text
Clean Air
Smoke
Different Smoke Sources
Temperature Variation
Humidity Variation
Non-fire Gas Events
Sensor Fault
Short Sensor Spike
Long Sensor Exposure
```

For every experiment, the system should record:

```text
Timestamp
Sensor Values
Environmental Conditions
Event Type
System Decision
```

This dataset can later be used for algorithm evaluation and TinyML development.

---

# 26. Performance Metrics

Future versions should evaluate the fusion system using measurable metrics.

Important metrics include:

### Detection Rate

\[
Detection\ Rate =
\frac{True\ Positives}
{Actual\ Positive\ Events}
\]

### False Alarm Rate

\[
False\ Alarm\ Rate =
\frac{False\ Positives}
{Total\ Negative\ Events}
\]

### Response Time

\[
Response\ Time =
Alert\ Time - Event\ Start
\]

### Recovery Time

\[
Recovery\ Time =
Normal\ Time - Event\ End
\]

These metrics will help compare:

```text
V1 Threshold
        vs
V2 Sensor Fusion
        vs
Future TinyML
```

---

# 27. Long-Term Goal

The ultimate goal of sensor fusion in PyroSense is to move from:

```text
"What does one sensor say?"
```

to:

```text
"What does the complete environment indicate?"
```

The future system will combine:

```text
Gas Information
       +
Thermal Information
       +
Particle Information
       +
Environmental Information
       +
Temporal Information
       ↓
     Sensor Fusion
       ↓
   Risk Estimation
```

---

# 28. Development Path

```text
             PyroSense V1
                  │
                  ▼
          Single Sensor
          MQ-2 Detection
                  │
                  ▼
             PyroSense V2
                  │
                  ▼
        Multiple Sensors
                  │
                  ▼
          Data Processing
                  │
                  ▼
        Baseline + Filtering
                  │
                  ▼
          Weighted Fusion
                  │
                  ▼
             PyroSense V3
                  │
                  ▼
        Feature Extraction
                  │
                  ▼
          Dataset Creation
                  │
                  ▼
             TinyML
                  │
                  ▼
        Intelligent Risk Model
```

---

# 29. Final Objective

Sensor fusion is one of the most important planned upgrades for PyroSense.

The objective is not simply to increase the number of sensors.

The objective is to use **different types of evidence** to make the system's decision more reliable.

> **More sensors do not automatically mean a smarter system. Better interpretation of sensor information does.**