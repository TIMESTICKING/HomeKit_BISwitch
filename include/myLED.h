#pragma once

#include <Arduino.h>
#include "extras/PwmPin.h"


#define HSP_LED 32
#define LOWLED  digitalWrite(HSP_LED, LOW);
#define HIGHLED digitalWrite(HSP_LED, HIGH);
#define TOGGLELED   digitalWrite(HSP_LED, !digitalRead(HSP_LED));


void blink_led(int blinktime = 3, int delay_ms = 500){
    for (int i=0; i < blinktime; i++){
        HIGHLED;
        delay(delay_ms);
        LOWLED;
        delay(100);
    }
}

void setup_led(){
    pinMode(HSP_LED, OUTPUT);
    LOWLED;

    blink_led(5, 200);
}


void LED_loop(void *para){
    LedPin *led = new LedPin(HSP_LED);
    while (1){
        for (int i = 0; i < 50; i++)
        {
            led->set(i);
            vTaskDelay(pdMS_TO_TICKS(80));
        }
        vTaskDelay(pdMS_TO_TICKS(200));
        for (int i = 50; i > 0; i--)
        {
            led->set(i);
            vTaskDelay(pdMS_TO_TICKS(80));
        }
        vTaskDelay(pdMS_TO_TICKS(200));
    }
}

