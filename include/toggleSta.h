#pragma once

#include <Arduino.h>
#include "HomeSpan.h"
#include "dev_switch.h"
#include "globalVars.h"

#define time_gap_thresh 16   //total time gap = time_gap_thresh * 50 (ms)
#define toggle_times    3

static u8_t sta = 0;
static int t = 0;
static int t_last = -1000;

void init_state_machine(){
    sta = 0;
    t_last = -1000;
    t = -1;
}

void toggle_scan(void *para){
    u8_t power_sta_last = dev_switch->power->getVal();
    u8_t power_sta_cur = power_sta_last;
    while (1)
    {
        power_sta_cur = dev_switch->power->getVal(); // request for new value

        if (t - t_last > time_gap_thresh && sta != 0){
            //out of time
            init_state_machine();
        }else if (power_sta_cur != power_sta_last){
            if (t_last < 0){
                //first time
                t_last = t;
                sta++;
            }else if (sta < toggle_times - 1){
                sta++; //into next state
                t_last = t;
                LOG1("next state\n");
            }else if (sta = toggle_times - 1){
                // into trigger! Do something!
                dev_switch->flip = !dev_switch->flip;
                digitalWrite(dev_switch->LedPin, !digitalRead(dev_switch->LedPin));
                init_state_machine();

                #if HSP_LED_ME_USE
                    blink_led(1, 1500);
                #endif

                LOG0("switch status!");
            }else{
                // dont know what happened
                init_state_machine();
                LOG1("dont know...reset...\n");
            }
        }

        t++;
        power_sta_last = power_sta_cur;
        vTaskDelay(pdMS_TO_TICKS(50));
    }
}
