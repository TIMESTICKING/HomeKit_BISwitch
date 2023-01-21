#pragma once

#include <Arduino.h>
#include "HomeSpan.h"

#define TOUCH_PIN   4

struct DEV_SWITCH : Service::LightBulb
{
    int LedPin;
    int flip = 0;
    SpanCharacteristic *power;

    DEV_SWITCH(int ledpin) : Service::LightBulb() {
        power = new Characteristic::On();

        LedPin = ledpin;
        pinMode(ledpin, OUTPUT);
        LOG0("LED init on Pin: ");LOG0(ledpin);
    }

    int power_NewVal(){
        return flip ^ power->getNewVal();
    }

    boolean update(){
        digitalWrite(LedPin, power_NewVal());

        return true;
    }

};


extern DEV_SWITCH *dev_switch;

