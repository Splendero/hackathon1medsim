#include <Wire.h>
#include <SPI.h>
#include <Adafruit_LSM303_Accel.h>
#include <Adafruit_LSM303_U.h>

#define BUTTON_PIN 2  // Pin for the button
#define FORCE_SENSOR_PIN_1 A0  // Analog pin for force sensor 1
#define FORCE_SENSOR_PIN_2 A1  // Analog pin for force sensor 2

Adafruit_LSM303_Accel_Unified accel = Adafruit_LSM303_Accel_Unified(54321);

unsigned long sessionStartMillis;
bool isSessionActive = false;

void setup() {
  Serial.begin(9600);
  pinMode(BUTTON_PIN, INPUT_PULLUP);
  pinMode(FORCE_SENSOR_PIN_1, INPUT);
  pinMode(FORCE_SENSOR_PIN_2, INPUT);

  if (!accel.begin()) {
    Serial.println(F("Could not find a valid LSM303 accelerometer, check wiring!"));
    while (1);
  }
}

void loop() {
  if (digitalRead(BUTTON_PIN) == LOW && !isSessionActive) {
    // Start a new session
    isSessionActive = true;
    sessionStartMillis = millis();
    Serial.println("Session started.");
  }

  if (isSessionActive) {
    // Read sensor data
    sensors_event_t event;
    accel.getEvent(&event);
    float accelerometerX = event.acceleration.x;
    float accelerometerY = event.acceleration.y;
    float accelerometerZ = event.acceleration.z;

    int forceSensor1Value = analogRead(FORCE_SENSOR_PIN_1);
    int forceSensor2Value = analogRead(FORCE_SENSOR_PIN_2);

    // Calculate statistics
    float sessionDuration = (millis() - sessionStartMillis) / 1000.0; // Convert milliseconds to seconds

    // Perform any statistical operations you want here
    // For demonstration, let's calculate mean and standard deviation
    float meanForceSensor1 = forceSensor1Value;
    float meanForceSensor2 = forceSensor2Value;
    float stdDevForceSensor1 = 0.0; // Placeholder, replace with actual calculation
    float stdDevForceSensor2 = 0.0; // Placeholder, replace with actual calculation
    float meanAccelerometerX = accelerometerX;
    float meanAccelerometerY = accelerometerY;
    float meanAccelerometerZ = accelerometerZ;

    // Output the calculated statistics
    Serial.print("SessionDuration,");
    Serial.print(meanForceSensor1);
    Serial.print(",");
    Serial.print(meanForceSensor2);
    Serial.print(",");
    Serial.print(stdDevForceSensor1);
    Serial.print(",");
    Serial.print(stdDevForceSensor2);
    Serial.print(",");
    Serial.print(meanAccelerometerX);
    Serial.print(",");
    Serial.print(meanAccelerometerY);
    Serial.print(",");
    Serial.print(meanAccelerometerZ);
    Serial.print(",");
    Serial.println(0); // Placeholder for damage value

    // Check if button released to end session
    if (digitalRead(BUTTON_PIN) == HIGH) {
      isSessionActive = false;
      Serial.println("Session ended.");
    }

    delay(1000); // Adjust delay as needed for sampling rate
  }
}
