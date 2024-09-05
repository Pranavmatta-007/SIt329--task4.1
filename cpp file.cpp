// TemperatureHumidityControl.cpp

#include "temp.h"

const int DHT_PIN = 2;
const int LED1_PIN = 3;
const int LED2_PIN = 4;
const int LED3_PIN = 5;
const int TEMP_SAMPLING_INTERVAL = 5000;
const int HUMIDITY_SAMPLING_INTERVAL = 30000;
const int LED2_BLINK_INTERVAL = 1000;
const int LED3_BLINK_INTERVAL = 500;
const int ALL_LED_BLINK_INTERVAL = 2000;

float temperature;
float humidity;
unsigned long lastTempSampleTime;
unsigned long lastHumiditySampleTime;
unsigned long lastLED2BlinkTime;
unsigned long lastLED3BlinkTime;
unsigned long lastAllLEDBlinkTime;
bool led1State = false;
bool led2State = false;
bool led3State = false;
bool led2BlinkState = false;
bool led3BlinkState = false;
bool allLEDBlinkState = false;

DHT dht(DHT_PIN, DHT22);

void setupTemperatureHumidityControl() {
    pinMode(LED1_PIN, OUTPUT);
    pinMode(LED2_PIN, OUTPUT);
    pinMode(LED3_PIN, OUTPUT);

    dht.begin();

    lastTempSampleTime = millis();
    lastHumiditySampleTime = millis();
    lastLED2BlinkTime = millis();
    lastLED3BlinkTime = millis();
    lastAllLEDBlinkTime = millis();

    Serial.begin(9600);
}

void loopTemperatureHumidityControl() {
    unsigned long currentMillis = millis();

    if (currentMillis - lastTempSampleTime >= TEMP_SAMPLING_INTERVAL) {
        lastTempSampleTime = currentMillis;
        temperature = dht.readTemperature() +30;
        Serial.print("Temperature: ");
        Serial.print(temperature);
        Serial.println(" °C");

        if (temperature >= 20 && temperature <= 25) {
            led1State = true;
            led2State = false;
            led3State = false;
            Serial.println("Condition: Temperature between 20°C and 25°C, LED1 ON");
        } else if (temperature > 25 && temperature <= 30) {
            led1State = false;
            led3State = false;

            if (currentMillis - lastLED2BlinkTime >= LED2_BLINK_INTERVAL) {
                lastLED2BlinkTime = currentMillis;
                led2BlinkState = !led2BlinkState;
            }
            led2State = led2BlinkState;
            Serial.println("Condition: Temperature between 25°C and 30°C, LED2 blinking every 1 second");
        } else if (temperature > 30) {
            led1State = false;

            if (currentMillis - lastLED2BlinkTime >= LED2_BLINK_INTERVAL) {
                lastLED2BlinkTime = currentMillis;
                led2BlinkState = !led2BlinkState;
            }
            led2State = led2BlinkState;

            if (currentMillis - lastLED3BlinkTime >= LED3_BLINK_INTERVAL) {
                lastLED3BlinkTime = currentMillis;
                led3BlinkState = !led3BlinkState;
            }
            led3State = led3BlinkState;
            Serial.println("Condition: Temperature above 30°C, LED2 and LED3 blinking");
        } else if (temperature < 20) {
            if (currentMillis - lastAllLEDBlinkTime >= ALL_LED_BLINK_INTERVAL) {
                lastAllLEDBlinkTime = currentMillis;
                allLEDBlinkState = !allLEDBlinkState;
                led1State = allLEDBlinkState;
                led2State = allLEDBlinkState;
                led3State = allLEDBlinkState;
            }
            Serial.println("Condition: Temperature below 20°C, All LEDs blinking every 2 seconds");
        }
    }

    if (currentMillis - lastHumiditySampleTime >= HUMIDITY_SAMPLING_INTERVAL) {
        lastHumiditySampleTime = currentMillis;
        humidity = dht.readHumidity() + 40;
        Serial.print("Humidity: ");
        Serial.print(humidity);
        Serial.println(" %");

        if (humidity > 80) {
            led1State = true;
            led2State = true;
            led3State = true;
            Serial.println("Condition: Humidity above 80%, All LEDs ON");
        }
    }

    digitalWrite(LED1_PIN, led1State);
    digitalWrite(LED2_PIN, led2State);
    digitalWrite(LED3_PIN, led3State);

    delay(100);
}
