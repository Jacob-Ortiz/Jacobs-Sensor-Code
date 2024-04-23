//Help from embedded tutorials intro to GPIO and ADC Basics and Espressif website

#include <stdio.h>              //Allows for external users to input their own commands in different means
#include "freertos/FreeRTOS.h"  //Freetos allows for the inclusion of external C support
#include "freertos/task.h"  //Freetos allows for the inclusion of external C support
#include "driver/gpio.h"   //Immplements GPIO support for esp32
#include "driver/adc.h"    //Commands for the adc commands
#include "sdkconfig.h" // import libraries


#define ANALOG_PIN GPIO_NUM_35 // GPIO Pin we choose to use


#ifndef CONFIG_FREERTOS_HZ      //Checks if macro is defined
#define CONFIG_FREERTOS_HZ 1000 // Default value of 1000 Hz - frequency we work with
#endif


void init_adc() { // Function to initialize ADC values for sensor readings
    adc1_config_width(ADC_WIDTH_BIT_12);    
    adc1_config_channel_atten(ADC1_CHANNEL_7, ADC_ATTEN_DB_0);
}

// function to read and classify soil moisture level
void soil_moisture_task(void *pvParameter) {  //Pointer set in our parameter 
    while (1) { // While loop Always true and runs continuously 
        // Read analog input
        uint32_t adc_reading = adc1_get_raw(ADC1_CHANNEL_7); //sets variable with numerical type that gauruntees 32 bits 
        
        // Print the analog reading and classify soil moisture level
        printf("ADC Reading: %lu - ", adc_reading);
        if (adc_reading == 0) {
            printf("No Rainfall\n");
        } else if (adc_reading <= 3000) {//Prints from a range if there is light rain based off of a medium ADC reading
            printf("Light Rain\n");
        } else {
            printf("HEAVY RAINFALL\n");//Prints from a range if there is light rain based off of a medium ADC reading
        }

        vTaskDelay(pdMS_TO_TICKS(1000)); // Delay 1 second
    }
}

extern "C" void app_main() { // Used so when building, the it is able to compile and be compatable with other external programming languages.
   
    init_adc();  // Initialize ADC variable 

    // Create task to read and classify soil moisture level
    xTaskCreate(soil_moisture_task, "soil_moisture_task", 2048, NULL, 5, NULL); // Continuosly reads our soil moisture levels
}
