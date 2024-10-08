#include <WiFi.h>
#include <AfricasTalking.h>

#define SOIL_MOISTURE_SENSOR_PIN A0
#define SOLENOID_VALVE_PIN 7

// Wi-Fi credentials
const char* ssid = "YOUR_SSID"; 
const char* password = "YOUR_PASSWORD"; 

// Africa's Talking credentials
static const char *apiKey = "<Africans Talking API>"; 
static const char *username = "sandbox"; //username remains sandox in simulation environment

AfricasTalking *AT;

void setup() {
    pinMode(SOLENOID_VALVE_PIN, OUTPUT);
    Serial.begin(115200);
    
    // Connect to Wi-Fi
    WiFi.begin(ssid, password);
    Serial.print("Connecting to WiFi");
    while (WiFi.status() != WL_CONNECTED) {
        delay(1000);
        Serial.print(".");
    }
    Serial.println("Connected to WiFi");

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
        String recipients = "+254790690288"; // Recipient number (sandbox will simulate this)

        // Send SMS using the sandbox environment
        bool success = AT->sms(recipients, "", message); // No sender ID needed in sandbox
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
