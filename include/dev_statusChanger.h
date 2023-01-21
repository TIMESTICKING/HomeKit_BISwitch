#pragma once

#include <Arduino.h>
#include "HomeSpan.h"
#include "dev_switch.h"

struct DEV_CHANGER : Service::LightBulb
{
    SpanCharacteristic *power;
    DEV_SWITCH *dev_switch;

    DEV_CHANGER(DEV_SWITCH *DevSwitch) : Service::LightBulb() {
        power = new Characteristic::On();
        dev_switch = DevSwitch;
    }

    boolean update(){
        dev_switch->flip = power->getNewVal();
        digitalWrite(dev_switch->LedPin, !digitalRead(dev_switch->LedPin));
        // dev_switch->power->setVal(!dev_switch->power->getVal());

        return true;
    }

};



