# 🔬 MQ-2 Sensor — Working Principle

## 1. Introduction

The **MQ-2** is a metal-oxide semiconductor (MOS) gas sensor commonly used for detecting the presence of smoke and several combustible or reducing gases.

In PyroSense V1, the MQ-2 is the primary sensing element used to detect changes in the surrounding atmosphere.

The sensor provides an analog output that can be read by the Arduino UNO.

```text
MQ-2 AO → Arduino A0
```

The MQ-2 is not a gas analyzer. It has a broad response to multiple gases, meaning that its output can be influenced by different gases and environmental conditions.

---

# 2. Internal Structure of MQ-2

The MQ-2 sensing element mainly consists of:

- **SnO₂ (Tin Oxide) sensing layer**
- **Heater coil**
- **Electrodes**
- **Ceramic substrate**
- **Metal mesh / protective structure**

A simplified representation is:

```text
                 MQ-2 SENSOR
        ┌─────────────────────────┐
        │      Protective Mesh    │
        │           ↓             │
        │    ┌───────────────┐    │
        │    │   SnO₂ Layer  │    │
        │    │ Sensing Layer │    │
        │    └───────────────┘    │
        │       Electrodes        │
        │           │             │
        │      Heater Coil        │
        │           │             │
        │     Ceramic Body        │
        └─────────────────────────┘
```

The **SnO₂ layer** is responsible for the gas-sensitive behavior, while the heater maintains the sensing material at an elevated operating temperature.

---

# 3. Why Does the MQ-2 Need a Heater?

The MQ-2 is a **heated metal-oxide semiconductor sensor**.

The heater raises the temperature of the sensing element so that chemical reactions between the sensor surface, oxygen, and surrounding gases can occur effectively.

Without sufficient heating, the sensing material would not provide its intended response characteristics.

The heater therefore plays a critical role in sensor operation.

```text
Power Supply
     │
     ▼
 Heater Coil
     │
     ▼
Raises Sensor Temperature
     │
     ▼
SnO₂ Surface Becomes Reactive
```

The heater does **not directly detect smoke**.

Instead, it creates the temperature conditions required for the sensing mechanism to work.

---

# 4. The SnO₂ Sensing Layer

The sensing material used in MQ-series sensors is primarily **tin oxide (SnO₂)**.

SnO₂ is a semiconductor whose electrical conductivity can change when gases interact with its surface.

This change in conductivity is the fundamental phenomenon used for gas detection.

In simplified form:

```text
Gas Interaction
      ↓
SnO₂ Surface Properties Change
      ↓
Electrical Resistance Changes
      ↓
Sensor Output Changes
```

Therefore, the MQ-2 does not "see" smoke like a camera.

It detects a **change in electrical resistance caused by chemical interactions at the sensing surface**.

---

# 5. Oxygen Adsorption — The Key Mechanism

When the MQ-2 is heated in normal air, oxygen molecules from the surrounding atmosphere interact with the SnO₂ surface.

Oxygen becomes adsorbed onto the surface and captures electrons from the semiconductor.

Conceptually:

```text
O₂ from Air
     ↓
Adsorbs on SnO₂ Surface
     ↓
Captures Electrons
     ↓
Electron Concentration Changes
     ↓
Electrical Resistance Changes
```

This creates a surface region where the electrical properties of SnO₂ are different from the bulk material.

This surface chemistry is the foundation of the sensor's gas response.

---

# 6. What Happens When Reducing/Combustible Gas Arrives?

When a reducing or combustible gas interacts with the oxygen species adsorbed on the SnO₂ surface, a chemical reaction can occur.

The gas interacts with the adsorbed oxygen and releases electrons back into the sensing material.

Simplified:

```text
Reducing Gas
     +
Adsorbed Oxygen
     ↓
Surface Reaction
     ↓
Electrons Released
     ↓
SnO₂ Conductivity Changes
     ↓
Resistance Changes
```

For an n-type metal-oxide semiconductor such as SnO₂, this generally results in an **increase in conductivity and decrease in resistance** when exposed to reducing gases.

However, the exact response depends on:

- Gas type
- Gas concentration
- Temperature
- Humidity
- Sensor condition
- Sensor history
- Operating conditions

---

# 7. Resistance Change

The most important electrical effect can be summarized as:

```text
Gas Exposure
     ↓
Surface Chemical Reaction
     ↓
Electron Concentration Changes
     ↓
SnO₂ Resistance Changes
```

For many reducing gases:

```text
Reducing Gas ↑
      ↓
SnO₂ Resistance ↓
      ↓
Conductivity ↑
```

This resistance change is what the external circuit converts into a measurable voltage.

---

# 8. How Does Resistance Become a Voltage?

The MQ-2 module generally uses the sensing resistance together with a **load resistor (RL)** to form a voltage divider.

A simplified circuit is:

```text
              VCC
               │
               │
              RL
               │
               ├────────── AO
               │
              Rs
        MQ-2 Sensing
         Resistance
               │
              GND
```

Where:

- **Rs** = sensor resistance
- **RL** = load resistance
- **AO** = analog output

The output voltage depends on the relationship between Rs and RL.

For the simplified voltage-divider arrangement:

\[
V_{out}=V_C\frac{R_L}{R_S+R_L}
\]

where:

- \(V_{out}\) = analog output voltage
- \(V_C\) = circuit supply voltage
- \(R_L\) = load resistance
- \(R_S\) = sensor resistance

Therefore, when the gas changes \(R_S\), the output voltage changes as well.

```text
Gas Concentration / Exposure
            ↓
       Changes Rs
            ↓
      Voltage Divider
            ↓
        Changes Vout
            ↓
          AO Signal
```

---

# 9. AO — Analog Output

The **AO (Analog Output)** provides a continuously varying voltage corresponding to the sensor's electrical response.

In PyroSense V1:

```text
MQ-2 AO
   │
   ▼
Arduino A0
   │
   ▼
10-bit ADC
   │
   ▼
Digital Value
0 — 1023
```

The Arduino therefore does not directly receive "smoke" or "gas".

It receives an **electrical voltage**.

The software then interprets changes in that voltage as changes in the sensor response.

---

# 10. DO — Digital Output

Many MQ-2 modules also provide a **DO (Digital Output)**.

The digital output is usually controlled by a comparator circuit on the sensor module.

A potentiometer on the module is commonly used to adjust the comparator threshold.

Conceptually:

```text
                MQ-2 Sensor
                     │
                     ▼
                Analog Signal
                     │
            ┌────────┴────────┐
            │                 │
            ▼                 ▼
           AO              Comparator
            │                 │
            │                 ▼
            │                 DO
            │
            ▼
        Arduino A0
```

### AO vs DO

| Output | Type | Function |
|---|---|---|
| AO | Analog | Provides continuously varying sensor response |
| DO | Digital | Provides ON/OFF threshold indication |

PyroSense V1 uses **AO** because we want access to the sensor's continuous reading rather than only a binary signal.

```text
AO → A0
DO → Not Used
```

---

# 11. Why We Use AO Instead of DO in V1

Using AO provides significantly more information than a simple digital output.

With AO, we can observe:

```text
100
150
200
250
300
350
...
```

Instead of only:

```text
LOW
HIGH
```

This allows us to:

- Observe sensor behavior
- Record readings
- Experiment with thresholds
- Study sensor response
- Perform calibration experiments
- Analyze changes over time

Therefore, AO is more useful for developing future versions of PyroSense.

---

# 12. What Gases Can MQ-2 Respond To?

The MQ-2 is designed to respond to several gases, including commonly listed gases such as:

- Smoke
- LPG
- Propane
- Methane
- Hydrogen
- Carbon monoxide
- Alcohol vapors

However, this list should **not** be interpreted as meaning that MQ-2 can independently identify each gas.

The sensor has a **broad and overlapping response** to multiple gases.

---

# 13. Can MQ-2 Identify Which Gas Is Present?

### No — not reliably by itself.

This is one of the most important concepts to understand about MQ-2.

Suppose the sensor produces a reading of:

```text
300
```

The Arduino cannot simply conclude:

```text
300 = Smoke
```

or:

```text
300 = CO
```

because the same sensor response can potentially be influenced by different gases and environmental conditions.

The MQ-2 essentially tells us:

> **"My sensing element has experienced a change in its electrical response."**

It does not inherently tell us:

> **"This exact gas is present at this exact concentration."**

---

# 14. Why Can't MQ-2 Identify a Specific Gas?

The main reason is **cross-sensitivity**.

The sensing material responds to multiple gases.

Therefore:

```text
Gas A ─────┐
Gas B ─────┤
Gas C ─────┼──→ MQ-2 → Sensor Response
Gas D ─────┤
Smoke ─────┘
```

Different gases can produce overlapping responses.

Additionally, the output can be affected by:

- Temperature
- Humidity
- Sensor aging
- Sensor warm-up
- Gas concentration
- Exposure duration
- Previous exposure history

Therefore, a single MQ-2 sensor cannot reliably distinguish between all possible gases.

---

# 15. Why Does the Sensor Need Warm-Up?

The MQ-2 contains a heater and requires time to reach stable operating conditions.

When the sensor is powered:

```text
Power ON
   ↓
Heater warms sensing element
   ↓
Sensor chemistry stabilizes
   ↓
Baseline becomes more stable
   ↓
Measurement
```

Immediately after powering the sensor, readings can fluctuate significantly.

Therefore, calibration and meaningful measurements should be performed after allowing the sensor to stabilize according to the intended operating procedure.

---

# 16. Sensor Resistance and Gas Concentration

The relationship between sensor resistance and gas concentration is not simply linear.

A typical metal-oxide gas sensor response is often represented using a relationship such as:

\[
\frac{R_S}{R_0}
\]

where:

- \(R_S\) = sensor resistance under the current gas condition
- \(R_0\) = reference resistance under a defined calibration condition

Sensor datasheets commonly provide characteristic curves showing how \(R_S/R_0\) changes with gas concentration.

Conceptually:

```text
Gas Concentration
        ↓
      Rs/R0
        ↓
Sensor Response
```

This is why simply converting an Arduino ADC value directly into ppm is not scientifically valid without proper calibration.

---

# 17. Why Raw ADC Value Is Not PPM

In PyroSense V1:

```text
MQ-2
  ↓
Analog Voltage
  ↓
Arduino ADC
  ↓
0 — 1023
```

The value `300`, for example, is simply an ADC reading.

It does **not** inherently mean:

```text
300 ppm
```

To estimate gas concentration, a much more rigorous process would be required:

```text
ADC Reading
     ↓
Voltage
     ↓
Sensor Resistance Rs
     ↓
Rs/R0
     ↓
Calibration Curve
     ↓
Estimated Gas Concentration
```

Even then, the accuracy depends heavily on sensor calibration, environmental conditions, and the target gas.

---

# 18. MQ-2 in PyroSense V1

The role of MQ-2 in PyroSense V1 can be summarized as:

```text
              ENVIRONMENT
                   │
                   ▼
             Gas / Smoke
                   │
                   ▼
              ┌─────────┐
              │  MQ-2   │
              │         │
              │ Heater  │
              │  +      │
              │  SnO₂   │
              └────┬────┘
                   │
             Resistance
                Change
                   │
                   ▼
             Voltage Divider
                   │
                   ▼
                  AO
                   │
                   ▼
              Arduino A0
                   │
                   ▼
                  ADC
                   │
                   ▼
             Sensor Reading
                   │
                   ▼
            Threshold Logic
```

---

# 19. Why MQ-2 Was Selected for V1

MQ-2 was selected for the first prototype because it provides:

- Low-cost gas/smoke sensing
- Simple analog interface
- Easy integration with Arduino
- Easy experimentation
- Broad sensitivity to smoke and combustible gases
- A useful platform for understanding gas sensing

Its simplicity makes it suitable for establishing the first working version of PyroSense.

---

# 20. Limitations of MQ-2

Despite being useful for prototyping, MQ-2 has several limitations.

### 20.1 Broad Gas Response

It responds to multiple gases rather than one specific gas.

### 20.2 Cross-Sensitivity

Different gases can produce similar sensor responses.

### 20.3 Environmental Dependence

Temperature and humidity can influence the sensor response.

### 20.4 Warm-Up Requirement

The sensor requires time to reach stable operating conditions.

### 20.5 Sensor Aging

The sensing characteristics can change over time.

### 20.6 Calibration Requirement

Accurate gas concentration estimation requires proper calibration.

### 20.7 Not a Fire Detector by Itself

A high MQ-2 reading does not automatically prove that a fire is present.

---

# 21. MQ-2 Working in One Flow

The complete sensing mechanism can be summarized as:

```text
             GAS / SMOKE
                  │
                  ▼
          ┌───────────────┐
          │   MQ-2        │
          │               │
          │ Heater warms  │
          │ sensing layer │
          └───────┬───────┘
                  │
                  ▼
              SnO₂ Layer
                  │
                  ▼
        Oxygen Adsorption
                  │
                  ▼
       Gas-Surface Reaction
                  │
                  ▼
       Electron Concentration
             Changes
                  │
                  ▼
       Sensor Resistance Rs
             Changes
                  │
                  ▼
         Voltage Divider
                  │
                  ▼
             Analog AO
                  │
                  ▼
            Arduino A0
                  │
                  ▼
             ADC Reading
                  │
                  ▼
         PyroSense V1 Logic
```

---

# 22. Key Takeaway

The MQ-2 does not directly detect "fire".

It detects changes in the electrical properties of a heated metal-oxide sensing layer caused by interactions between gases and the sensor surface.

The fundamental chain is:

> **Gas → Surface Reaction → Resistance Change → Voltage Change → ADC Reading → Detection Logic**

Understanding this mechanism is important because it explains both the usefulness and the limitations of MQ-2 in PyroSense V1.