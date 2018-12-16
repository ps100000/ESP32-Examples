#include <stdio.h> 
#include <string.h> 
#include <stdlib.h> 
#include "freertos/FreeRTOS.h" 
#include "freertos/task.h" 
#include "freertos/queue.h" 
#include "driver/gpio.h" 
#include "esp_log.h"



void app_main(){
    PIN_FUNC_SELECT(GPIO_PIN_MUX_REG[13], PIN_FUNC_GPIO);//Pin 13 als GPIO setzen
    PIN_FUNC_SELECT(GPIO_PIN_MUX_REG[12], PIN_FUNC_GPIO);//Pin 12 als GPIO setzen
    gpio_set_direction(2,GPIO_MODE_OUTPUT);              //LED-Pin als Ausgang setzen
    gpio_set_level(2,0);                                 //LED aus
    gpio_set_direction(12,GPIO_MODE_INPUT);              //Pin 12 als Eingang setzen
    gpio_set_pull_mode(12,GPIO_PULLDOWN_ONLY);           //Pin 12 pulldown anschalten
    gpio_set_direction(13,GPIO_MODE_OUTPUT);             //Pin 13 als Ausgang setzen
    while(1!=0){                                         //Endlosschleife
        gpio_set_level(2,1);                             //LED an
        vTaskDelay(100 / portTICK_PERIOD_MS);            //warte 0.1s
        gpio_set_level(13,1);                            //Impuls an
        ets_delay_us(10);                                //warte 10us
        gpio_set_level(13,0);                            //Impuls aus
        while(gpio_get_level(12) == 0){                  //Überprüfe ob Echo Signal low
        }
        gpio_set_level(2,0);                             //LED aus
        uint32_t start = xthal_get_ccount();             //Startzeit in start speichern
        while(gpio_get_level(12) == 1){                  //Überprüfe ob Echo Signal high
        }
        uint32_t end = xthal_get_ccount();               //endzeit in end speichern
        int t = (end - start) / 160;                     //umrechnung in us
        ESP_LOGI("example","time:%d", t);                //Ausgabe Zeit
        vTaskDelay(100 / portTICK_PERIOD_MS);            //warte 0.1s
   }
}