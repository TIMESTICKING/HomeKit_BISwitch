#include <Arduino.h>
#include "HomeSpan.h"
#include "dev_switch.h"
// #include "dev_statusChanger.h"
#include "touch.h"
#include "toggleSta.h"

xTaskHandle touch_scan_handle;
xTaskHandle toggle_stat_handle;
DEV_SWITCH *dev_switch;


void homespan_init(){
  homeSpan.enableOTA();
  homeSpan.begin(Category::Bridges, "homekit bridge", "mylight");
  homeSpan.setHostNameSuffix("");
  // homeSpan.setControlPin(35);
  homeSpan.setStatusPin(32);
  homeSpan.setWifiCredentials("Xiaomi_0A9C", "ljx70051400");
}


void setup() {
  // put your setup code here, to run once:
  Serial.begin(115200);
  homespan_init();

  new SpanAccessory(); // bridge
    new Service::AccessoryInformation();
      new Characteristic::Identify();


  new SpanAccessory();
    new Service::AccessoryInformation();
      new Characteristic::Identify();
      new Characteristic::Name("BiSwitch");
    dev_switch = new DEV_SWITCH(2);
    // new DEV_CHANGER(dev_switch);

  xTaskCreate(touch_scan, "touch_scan", 1024, NULL, 0, &touch_scan_handle);
  xTaskCreate(toggle_scan, "toggle_scan", 1024, NULL, 0, &toggle_stat_handle);
}

void loop() {
  // put your main code here, to run repeatedly:
  homeSpan.poll();
}