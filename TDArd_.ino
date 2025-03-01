#include <Wire.h>
#include <MPU6050_light.h>

MPU6050 mpu(Wire);
unsigned long timer = 0;
const float tapThreshold = 2.0; // Adjust based on testing

void setup() {
    Serial.begin(115200);
    Wire.begin();
    delay(1000);

    byte status = mpu.begin();
    if (status != 0) {
        Serial.print("MPU6050 initialization failed! Error Code: ");
        Serial.println(status);
        Serial.println("Check wiring and power supply.");
    } else {
        Serial.println("MPU6050 initialized successfully!");
        mpu.calcOffsets();
        Serial.println("Calibration done!");
    }
}

void loop() {
    if (mpu.begin() != 0) {  // If sensor is disconnected
        Serial.println("⚠ MPU6050 Disconnected! Check Wiring.");
        delay(500);
        return;  // Continue execution without stopping
    }

    mpu.update();
    
    // Read accelerometer values
    float ax = mpu.getAccX();
    float ay = mpu.getAccY();
    float az = mpu.getAccZ();
    
    float acceleration = sqrt(ax * ax + ay * ay + az * az);

    // Print accelerometer values always
    Serial.print("AccX: ");
    Serial.print(ax);
    Serial.print(" | AccY: ");
    Serial.print(ay);
    Serial.print(" | AccZ: ");
    Serial.print(az);

    // Tap Detection
    if (acceleration > tapThreshold) {
        Serial.println(" Tap Detected!");
    } else {
        Serial.println(" No Tap Detected.");
    }

    // Print and log data every 1 second
    if (millis() - timer > 1000) {
        Serial.print("SAVE_CSV,");
        Serial.print(millis());
        Serial.print(",");
        Serial.print(ax);
        Serial.print(",");
        Serial.print(ay);
        Serial.print(",");
        Serial.println(az);

        timer = millis();
    }
}