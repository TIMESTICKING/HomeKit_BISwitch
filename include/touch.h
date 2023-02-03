#pragma once

#include "dev_switch.h"
#include "globalVars.h"

boolean if_touch(){
  int thresh = 60;
  if (touchRead(TOUCH_PIN) < thresh){
    return true;
  }
  return false;
}

void touch_scan(void *para){
  uint32_t i = 0;
  u8_t sta = 0;
  while (1)
  {
    if (sta == 0 && if_touch()){
      sta = 1; //刚触发
      i = 0; //重新计数
    }else if (sta == 1 && i == 10){
      // 200ms 再次检查
      if (if_touch()){
        digitalWrite(dev_switch->LedPin, !digitalRead(dev_switch->LedPin));
        dev_switch->power->setVal(!dev_switch->power->getVal());
        sta = 2; //第一次触发完成

        #if HSP_LED_ME_USE
          blink_led(2, 300);
        #endif

        LOG0("touched!\n");
      }else{
        sta = 0;
      }
    }else if (sta == 2){
      if (!if_touch()){
        sta = 0;
      }
    }

    i++;
    vTaskDelay(pdMS_TO_TICKS(20));
  }
  
}

