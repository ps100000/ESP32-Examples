#include <stdio.h> 
#include <string.h> 
#include <stdlib.h> 
#include "freertos/FreeRTOS.h" 
#include "freertos/task.h" 
#include "freertos/queue.h" 
#include "driver/gpio.h" 
#include "esp_log.h"



void app_main(){
   gpio_set_direction(2,GPIO_MODE_OUTPUT);              //LED-Pin als Ausgang setzen
   gpio_set_level(2,0);                                 //LED aus
   gpio_set_direction(12,GPIO_MODE_INPUT);              //Pin 12 als Eingang setzen
   gpio_set_pull_mode(12,GPIO_PULLUP_ONLY);             //Pin 12 pullup anschalten
   while(1!=0){                                         //Endlosschleife
       gpio_set_level(2,1);                             //LED an
        while(gpio_get_level(12) == 0){                 //Überprüfe ob Kabel verbunden
            ESP_LOGI("example","waiting1");             //Logausgabe
            vTaskDelay(20 / portTICK_PERIOD_MS);        //warte 20ms
        }
        gpio_set_level(2,0);                            //LED aus
        uint32_t start = xthal_get_ccount();            //Startzeit in start speichern
        while(gpio_get_level(12) == 1){                 //Überprüfe ob Kabel abgezogen
            ESP_LOGI("example","waiting2");             //Logausgabe
            vTaskDelay(20 / portTICK_PERIOD_MS);        //warte 20ms
        }
        uint32_t end = xthal_get_ccount();              //endzeit in end speichern
        int t = (end - start) / 160000;                 //umrechnung in ms
        ESP_LOGI("example","time:%d", t);               //Ausgabe Zeit
        vTaskDelay(2000 / portTICK_PERIOD_MS);          //warte 2s
   }
}