#include <Wire.h>
#include <AfricasTalking.h>

#define SOIL_MOISTURE_SENSOR_PIN A0
#define SOLENOID_VALVE_PIN 7

// Africa's Talking credentials
static const char *apiKey = "YOUR_API_KEY"; // Replace with your API key
static const char *username = "YOUR_USERNAME"; // Replace with your username
AfricasTalking *AT;

void setup() {
    pinMode(SOLENOID_VALVE_PIN, OUTPUT);
    Serial.begin(9600);
    
    // Initialize Africa's Talking client
    AT = new AfricasTalking(apiKey, username);
}

void loop() {
    int moistureLevel = analogRead(SOIL_MOISTURE_SENSOR_PIN);
    Serial.println(moistureLevel);

    if (moistureLevel < 300) { // Threshold value
        digitalWrite(SOLENOID_VALVE_PIN, HIGH); // Open valve
        
        // Send SMS notification to farmers
        String message = "Alert: Soil moisture is low and the sprinkler is now open.";
        String recipients[] = { "+254XXXXXXXXX" }; // Replace with actual recipient numbers
        
        bool success = AT->sms(recipients[0], "Your_Sender_ID", message); // Replace 'Your_Sender_ID' with your sender ID
        if (success) {
            Serial.println("SMS sent successfully.");
        } else {
            Serial.println("Failed to send SMS.");
        }
    } else {
        digitalWrite(SOLENOID_VALVE_PIN, LOW); // Close valve
    }
    
    delay(60000); // Check every minute
}