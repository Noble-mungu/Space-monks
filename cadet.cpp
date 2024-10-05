#include <Wire.h>
#define SOIL_MOISTURE_SENSOR_PIN A0
#define SOLENOID_VALVE_PIN 7

void setup() {
    pinMode(SOLENOID_VALVE_PIN, OUTPUT);
    Serial.begin(9600);
}

void loop() {
    int moistureLevel = analogRead(SOIL_MOISTURE_SENSOR_PIN);
    Serial.println(moistureLevel);

    if (moistureLevel < 300) { // Threshold value
        // Add AT logic for sms
        digitalWrite(SOLENOID_VALVE_PIN, HIGH); // Open valve
    } else {
        digitalWrite(SOLENOID_VALVE_PIN, LOW); // Close valve
    }
    delay(60000); // Check every minute
}