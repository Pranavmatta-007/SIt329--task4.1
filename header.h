// TemperatureHumidityControl.h

#ifndef TEMPERATURE_HUMIDITY_CONTROL_H
#define TEMPERATURE_HUMIDITY_CONTROL_H

#include <Arduino.h>
#include <DHT.h>

extern const int DHT_PIN;
extern const int LED1_PIN;
extern const int LED2_PIN;
extern const int LED3_PIN;
extern const int TEMP_SAMPLING_INTERVAL;
extern const int HUMIDITY_SAMPLING_INTERVAL;
extern const int LED2_BLINK_INTERVAL;
extern const int LED3_BLINK_INTERVAL;
extern const int ALL_LED_BLINK_INTERVAL;

extern float temperature;
extern float humidity;
extern unsigned long lastTempSampleTime;
extern unsigned long lastHumiditySampleTime;
extern unsigned long lastLED2BlinkTime;
extern unsigned long lastLED3BlinkTime;
extern unsigned long lastAllLEDBlinkTime;
extern bool led1State;
extern bool led2State;
extern bool led3State;
extern bool led2BlinkState;
extern bool led3BlinkState;
extern bool allLEDBlinkState;

extern DHT dht;

void setupTemperatureHumidityControl();
void loopTemperatureHumidityControl();

#endif // TEMPERATURE_HUMIDITY_CONTROL_H
