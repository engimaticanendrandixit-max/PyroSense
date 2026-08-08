#include <Wire.h>
#include <Adafruit_GFX.h>
#include <Adafruit_SH110X.h>

// ================= OLED =================
#define SCREEN_WIDTH 128
#define SCREEN_HEIGHT 64

Adafruit_SH1106G display(128, 64, &Wire, -1);

// ================= PINS =================
#define MQ2_PIN A0
#define GREEN_LED 8
#define RED_LED 9
#define BUZZER 10

// ================= SETTINGS =================
#define SMOKE_THRESHOLD 150

void setup() {

  Serial.begin(9600);

  // LEDs and buzzer
  pinMode(GREEN_LED, OUTPUT);
  pinMode(RED_LED, OUTPUT);
  pinMode(BUZZER, OUTPUT);

  // ================= OLED =================
  Wire.begin();

  if (!display.begin(0x3C, true)) {
    Serial.println("OLED NOT FOUND");

    while (1);
  }

  display.clearDisplay();
  display.setTextColor(SH110X_WHITE);

  // Startup screen
  display.setTextSize(2);
  display.setCursor(10, 5);
  display.println("SMOKE");
  display.setCursor(20, 28);
  display.println("DETECTOR");

  display.display();

  delay(2000);
}


void loop() {

  // Read MQ-2
  int smokeValue = analogRead(MQ2_PIN);

  Serial.print("Smoke Value: ");
  Serial.println(smokeValue);


  // ==================================================
  // 🚨 SMOKE DETECTED
  // ==================================================

  if (smokeValue > SMOKE_THRESHOLD) {

    digitalWrite(GREEN_LED, LOW);
    digitalWrite(RED_LED, HIGH);
    digitalWrite(BUZZER, HIGH);

    display.clearDisplay();

    display.setTextColor(SH110X_WHITE);

    // ALERT
    display.setTextSize(2);
    display.setCursor(5, 0);
    display.println("!! ALERT !!");

    // Smoke value
    display.setTextSize(1);
    display.setCursor(5, 28);
    display.print("Smoke Level: ");
    display.println(smokeValue);

    // Message
    display.setCursor(5, 45);
    display.println("SMOKE DETECTED!");

    display.display();
  }


  // ==================================================
  // ✅ NORMAL AIR
  // ==================================================

  else {

    digitalWrite(GREEN_LED, HIGH);
    digitalWrite(RED_LED, LOW);
    digitalWrite(BUZZER, LOW);

    display.clearDisplay();

    display.setTextColor(SH110X_WHITE);

    // SAFE
    display.setTextSize(2);
    display.setCursor(20, 0);
    display.println("SAFE");

    // Smoke value
    display.setTextSize(1);
    display.setCursor(5, 30);
    display.print("Smoke Level: ");
    display.println(smokeValue);

    // Status
    display.setCursor(5, 48);
    display.println("Air is Normal");

    display.display();
  }

  delay(500);
}