# 🤖 PyroSense — TinyML & Edge Intelligence

## 1. Introduction

TinyML is the concept of running machine-learning models on resource-constrained embedded devices such as microcontrollers.

For PyroSense, TinyML represents a future transition from manually defined detection rules toward **data-driven pattern recognition**.

The development path is:

```text
V1
Single Sensor + Threshold
        ↓
V2
Multi-Sensor + Rule-Based Fusion
        ↓
V3
Feature Extraction + Dataset
        ↓
V4
TinyML Classification
        ↓
Future
Predictive Edge Intelligence
```

The objective is not to replace the sensing hardware with AI.

Instead:

> **Sensors provide the evidence. TinyML learns how to interpret the evidence.**

---

# 2. Why TinyML?

A traditional V1 system uses a fixed rule:

```text
IF sensorValue >= threshold
        ↓
      ALERT
```

This approach is simple but has limitations.

A future TinyML system can consider multiple parameters simultaneously.

For example:

```text
MQ-2
MQ-7
Temperature
Humidity
PM
Rate of Change
Exposure Duration
        ↓
      TinyML
        ↓
  Pattern Recognition
        ↓
 Risk Classification
```

This can potentially help distinguish between different environmental patterns.

---

# 3. What TinyML Will Do in PyroSense

TinyML will not directly measure smoke or gas.

The sensors will still perform the physical sensing.

The TinyML model will analyze the sensor data and classify patterns.

Conceptually:

```text
Physical Environment
        ↓
      Sensors
        ↓
   Raw Sensor Data
        ↓
 Data Preprocessing
        ↓
 Feature Extraction
        ↓
    TinyML Model
        ↓
 Classification
        ↓
 Risk Assessment
```

---

# 4. Proposed ML Classes

The exact classes will be determined after collecting experimental data.

A possible initial classification system is:

```text
CLASS 0 → NORMAL
CLASS 1 → SMOKE EVENT
CLASS 2 → GAS EVENT
CLASS 3 → HIGH-RISK EVENT
CLASS 4 → UNKNOWN / ANOMALY
```

Another possibility is a simpler risk-oriented model:

```text
NORMAL
CAUTION
WARNING
HIGH RISK
CRITICAL
```

The final classification structure will depend on the quality and quantity of collected data.

---

# 5. Dataset Creation

A reliable TinyML model requires a dataset.

Therefore, a major future development step will be systematic data collection.

The system can continuously record:

```text
Timestamp
MQ-2
MQ-7
Temperature
Humidity
PM
Rate of Change
Exposure Duration
System State
Event Label
```

Example:

```text
Timestamp   MQ2   MQ7   Temp   Humidity   PM   Label
--------------------------------------------------------
10:00:01    90    60    30.1      51      10   NORMAL
10:00:02    92    61    30.1      51      11   NORMAL
10:00:03   110    65    30.2      51      15   SMOKE
10:00:04   145    72    30.4      50      22   SMOKE
10:00:05   190    85    31.0      50      35   HIGH_RISK
```

> These values are illustrative only. Actual values must come from real measurements.

---

# 6. Data Collection Strategy

The dataset should contain multiple environmental conditions.

Possible experimental categories:

```text
1. Clean Air
2. Incense Smoke
3. Different Smoke Sources
4. Controlled Gas Events
5. Temperature Variation
6. Humidity Variation
7. Short Sensor Spikes
8. Long Sensor Exposure
9. Recovery Period
10. Sensor Fault Conditions
```

The purpose is to prevent the model from simply memorizing one specific test environment.

---

# 7. Importance of Dataset Diversity

A model trained only on one type of smoke may perform poorly in another environment.

For example:

```text
Training:
Incense Smoke
      ↓
Model learns pattern
```

does not guarantee:

```text
Wood Smoke
Cooking Smoke
Electrical Smoke
Other Environmental Events
```

will produce the same pattern.

Therefore, dataset diversity is one of the most important parts of the TinyML development process.

---

# 8. Feature Engineering

Raw sensor readings may not always be sufficient.

Additional features can be extracted from the sensor signals.

Potential features include:

### Instantaneous Value

```text
Current Sensor Reading
```

### Moving Average

```text
Average of Recent Readings
```

### Rate of Change

\[
Rate = \frac{\Delta X}{\Delta t}
\]

### Maximum Value

```text
Maximum value within a time window
```

### Minimum Value

```text
Minimum value within a time window
```

### Variance

Measures how much the signal fluctuates.

### Exposure Duration

Measures how long abnormal conditions persist.

### Recovery Rate

Measures how quickly the sensor response returns toward baseline.

---

# 9. Example Feature Vector

A future model input could look like:

```text
[
  MQ2_normalized,
  MQ7_normalized,
  Temperature,
  Humidity,
  PM_normalized,
  MQ2_rate,
  MQ7_rate,
  PM_rate,
  MQ2_average,
  PM_average,
  Exposure_duration
]
```

This creates a multi-dimensional representation of the environment.

---

# 10. Data Preprocessing

Before training, the collected data will need preprocessing.

Possible steps:

```text
Raw Data
   ↓
Remove Invalid Samples
   ↓
Handle Missing Values
   ↓
Filter Noise
   ↓
Normalize Features
   ↓
Create Time Windows
   ↓
Assign Labels
   ↓
Training Dataset
```

This step is critical because poor-quality data can result in a poor model.

---

# 11. Time-Window Based Analysis

Sensor events occur over time.

Instead of feeding one sensor reading to the model, future PyroSense versions can provide a short sequence of measurements.

For example:

```text
Time Window = 5 seconds

t0 → Sensor values
t1 → Sensor values
t2 → Sensor values
t3 → Sensor values
t4 → Sensor values
```

The model can then learn the pattern across the complete window.

Conceptually:

```text
Sensor Signal
     ↓
┌──────────────────────┐
│ Time Window           │
│ t0 t1 t2 t3 t4       │
└──────────┬───────────┘
           ↓
       ML Model
```

This can provide more information than a single instantaneous reading.

---

# 12. Candidate Machine Learning Models

The first model should remain lightweight.

Potential algorithms include:

- Decision Tree
- Random Forest
- Logistic Regression
- K-Nearest Neighbors
- Support Vector Machine
- Small Neural Network

For embedded deployment, the final model should be selected based on:

- Accuracy
- Model size
- RAM requirements
- Flash requirements
- Inference time
- Power consumption

The most accurate model is not necessarily the best embedded model.

---

# 13. Model Development Pipeline

The proposed development pipeline is:

```text
Data Collection
      ↓
Data Cleaning
      ↓
Feature Engineering
      ↓
Dataset Preparation
      ↓
Train / Validation / Test Split
      ↓
Model Training
      ↓
Model Evaluation
      ↓
Model Optimization
      ↓
Quantization
      ↓
Embedded Deployment
```

---

# 14. Training, Validation and Testing

The dataset should be separated into different subsets.

A possible structure is:

```text
Dataset
   │
   ├── Training Data
   │
   ├── Validation Data
   │
   └── Test Data
```

### Training Data

Used to train the model.

### Validation Data

Used to tune model parameters and compare approaches.

### Test Data

Used for final evaluation on previously unseen data.

The exact split ratio will depend on the final dataset size.

---

# 15. Preventing Data Leakage

Care must be taken when creating the dataset.

Measurements collected from the exact same test session should not automatically be split randomly across training and testing sets.

Otherwise, the model may see extremely similar samples during training and testing.

A better approach can be:

```text
Experiment Session A
        ↓
Training

Experiment Session B
        ↓
Validation

Experiment Session C
        ↓
Testing
```

This provides a more realistic evaluation.

---

# 16. Model Evaluation

Accuracy alone is not enough.

Future PyroSense models should be evaluated using:

- Accuracy
- Precision
- Recall
- F1-score
- Confusion matrix
- False-positive rate
- False-negative rate
- Inference time
- Memory usage

For a safety-oriented application, false negatives are particularly important to investigate.

---

# 17. Confusion Matrix

A confusion matrix can help understand model behavior.

Example:

```text
                 Predicted
              Normal  Smoke  Risk
Actual Normal    90      5      0
       Smoke      4     85      6
       Risk       0      5     95
```

This allows us to identify which classes the model confuses.

---

# 18. Model Quantization

Machine-learning models can be computationally expensive.

Quantization can reduce model size and computational requirements.

For example:

```text
Floating Point Model
        ↓
Quantization
        ↓
Smaller Integer Model
        ↓
Embedded Deployment
```

A common approach for TinyML is converting model parameters to lower-precision representations such as 8-bit integers.

The impact on model accuracy must be evaluated after quantization.

---

# 19. Edge Inference

Once deployed, the model should perform inference locally.

The complete process becomes:

```text
Sensors
   ↓
ESP32
   ↓
Preprocessing
   ↓
Feature Extraction
   ↓
TinyML Model
   ↓
Prediction
   ↓
Risk Engine
   ↓
Alert
```

The cloud does not need to perform the primary detection decision.

---

# 20. Why Edge AI?

Running the model locally provides several advantages.

### Low Latency

The decision does not have to wait for a remote server.

### Offline Operation

Basic detection can continue even without internet connectivity.

### Reduced Network Dependency

Continuous raw sensor streaming is not required for local inference.

### Privacy

Sensor data can remain on the device unless the user explicitly chooses to transmit it.

### Reliability

Local detection can continue even when network services are unavailable.

---

# 21. TinyML Hardware

The initial TinyML target can be an ESP32-class microcontroller.

Possible future hardware:

```text
Arduino UNO
     ↓
ESP32
     ↓
ESP32 + Optimized ML
     ↓
More Capable Edge Hardware
```

The hardware choice will depend on:

- RAM
- Flash
- CPU performance
- Power requirements
- Number of sensors
- Model complexity

---

# 22. Inference Pipeline

A future PyroSense inference loop may look like:

```text
START
  ↓
Read Sensors
  ↓
Validate Measurements
  ↓
Filter Noise
  ↓
Normalize Data
  ↓
Update Time Window
  ↓
Extract Features
  ↓
Run TinyML Inference
  ↓
Calculate Risk
  ↓
Apply Safety Rules
  ↓
Display Result
  ↓
Trigger Alert if Required
  ↓
Repeat
```

---

# 23. Hybrid AI + Rule-Based Safety

TinyML should not necessarily control the entire safety system by itself.

A hybrid architecture can be used.

```text
                 Sensor Data
                     ↓
              ┌──────────────┐
              │   TinyML     │
              │ Classification│
              └──────┬───────┘
                     │
                     ▼
                Risk Score
                     │
          ┌──────────┴──────────┐
          │                     │
          ▼                     ▼
      ML Decision         Safety Rules
          │                     │
          └──────────┬──────────┘
                     ▼
                Final Decision
                     ↓
                  Alarm
```

This provides a deterministic safety layer alongside the ML model.

---

# 24. Unknown Event Detection

One important future capability is detecting events that do not match known training classes.

For example:

```text
Known Classes:
NORMAL
SMOKE
GAS
HIGH_RISK
```

But the environment may produce something completely different.

The system should ideally be able to indicate:

```text
UNKNOWN / ANOMALOUS EVENT
```

instead of confidently assigning an incorrect known class.

This area can be explored through anomaly-detection techniques in future research.

---

# 25. Model Updating

As more experimental data is collected, the model can potentially be retrained.

```text
Initial Dataset
      ↓
Model V1
      ↓
New Experimental Data
      ↓
Expanded Dataset
      ↓
Model V2
      ↓
Improved Evaluation
```

However, new models should be validated before deployment.

A model should never be updated blindly using unverified sensor data.

---

# 26. Continuous Improvement Loop

The long-term TinyML development cycle is:

```text
Deploy
  ↓
Collect Data
  ↓
Analyze Errors
  ↓
Improve Dataset
  ↓
Retrain
  ↓
Evaluate
  ↓
Optimize
  ↓
Redeploy
```

This creates a controlled development loop.

---

# 27. Example Future Scenario

Consider a future PyroSense system.

### Initial Condition

```text
MQ-2       → Normal
MQ-7       → Normal
Temperature → Normal
PM         → Normal
```

TinyML output:

```text
NORMAL
Confidence: High
```

Then:

```text
MQ-2 ↑
PM ↑
Temperature → Stable
```

Model output:

```text
SMOKE-LIKE EVENT
Confidence: Medium
```

Later:

```text
MQ-2 ↑↑
MQ-7 ↑
Temperature ↑
PM ↑↑
```

Model output:

```text
HIGH-RISK EVENT
Confidence: High
```

The rule-based safety layer then determines the final alarm response.

---

# 28. TinyML Limitations

TinyML will introduce new challenges.

These include:

- Limited training data
- Sensor drift
- Dataset bias
- Environmental variability
- Overfitting
- False positives
- False negatives
- Limited microcontroller resources
- Model quantization effects
- Distribution shift
- Unknown environmental events

Therefore, TinyML should be treated as an experimental enhancement rather than an automatic guarantee of reliability.

---

# 29. Research Questions

Future PyroSense development can investigate questions such as:

### Question 1

Can multi-sensor data distinguish smoke-related events from other environmental changes better than a single MQ-2 threshold?

### Question 2

Does adding temperature and humidity improve model robustness?

### Question 3

Does particulate matter data improve smoke-event classification?

### Question 4

Can temporal features improve detection compared with instantaneous values?

### Question 5

Can a lightweight model run reliably on an ESP32?

### Question 6

How much accuracy is lost after model quantization?

### Question 7

Can the system detect unknown environmental events?

### Question 8

Can the model reduce false alarms without increasing dangerous missed detections?

---

# 30. Development Roadmap

```text
Phase 1
───────
V1 Threshold Detection
        ↓
Phase 2
───────
Multi-Sensor Hardware
        ↓
Phase 3
───────
Data Logging
        ↓
Phase 4
───────
Dataset Creation
        ↓
Phase 5
───────
Feature Engineering
        ↓
Phase 6
───────
Classical ML Experiments
        ↓
Phase 7
───────
TinyML Model Selection
        ↓
Phase 8
───────
Quantization
        ↓
Phase 9
───────
ESP32 Deployment
        ↓
Phase 10
────────
Real-World Validation
        ↓
Phase 11
────────
Predictive Edge Intelligence
```

---

# 31. Final Architecture

The long-term PyroSense AI architecture is envisioned as:

```text
                 ENVIRONMENT
                      │
                      ▼
              ┌───────────────┐
              │    Sensors    │
              │               │
              │ MQ-2          │
              │ MQ-7          │
              │ Temperature   │
              │ Humidity      │
              │ PM            │
              └───────┬───────┘
                      │
                      ▼
                ESP32 / MCU
                      │
                      ▼
              Data Processing
                      │
                      ▼
             Feature Extraction
                      │
                      ▼
                TinyML Model
                      │
                      ▼
              Pattern Detection
                      │
                      ▼
                Risk Engine
                      │
              ┌───────┼────────┐
              ▼       ▼        ▼
           NORMAL   WARNING   CRITICAL
              │       │        │
              └───────┼────────┘
                      ▼
               Local Response
                      │
             ┌────────┼────────┐
             ▼        ▼        ▼
           OLED     Buzzer     LED
                      │
                      ▼
                Optional IoT
                      │
                      ▼
                  Dashboard
```

---

# 32. Final Objective

The long-term goal of TinyML in PyroSense is to enable the system to move beyond fixed thresholds and learn meaningful patterns from multi-sensor environmental data.

The evolution can be summarized as:

```text
Fixed Threshold
      ↓
Rule-Based Logic
      ↓
Sensor Fusion
      ↓
Feature Engineering
      ↓
Machine Learning
      ↓
TinyML
      ↓
Edge Intelligence
      ↓
Predictive Risk Assessment
```

> **PyroSense aims to use TinyML not merely to make the project "AI-powered", but to investigate whether lightweight edge intelligence can make low-cost environmental sensing more adaptive, explainable, and reliable.**