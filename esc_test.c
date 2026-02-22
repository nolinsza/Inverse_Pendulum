#include <stdio.h>
#include "driver/ledc.h"
#include "esp_err.h"
#include "freertos/FreeRTOS.h"
#include "freertos/task.h"

void app_main(void)
{


  //Delay 10 seconds before doing anything 
  vTaskDelay(pdMS_TO_TICKS(10000));

  //Define Struct for timer configuration
  ledc_timer_config_t ledc_timer = {
      .speed_mode       = LEDC_HIGH_SPEED_MODE, // Timer mode
      .timer_num        = LEDC_TIMER_0,        // Timer index
      .duty_resolution  = LEDC_TIMER_10_BIT,   // 10-bit resolution for duty cycle
      .freq_hz          = 2000,                // 2kHz frequency
      .clk_cfg          = LEDC_AUTO_CLK         // Auto select the source clock
  };

  
  //Define Struct for channel configuration
  int period_us = 500;
  int duty_counts = 250 * 1023 / period_us; // Convert pulse width to duty counts (10-bit resolution)
  ledc_channel_config_t ledc_channel = {
    .gpio_num       = 18,                     // GPIO18 output
    .speed_mode     = LEDC_HIGH_SPEED_MODE,   // Channel mode
    .channel        = LEDC_CHANNEL_0,         // Channel index 
    .timer_sel      = LEDC_TIMER_0,          // Select the timer source
    .duty           = duty_counts,           // Initial pulse width (minimum ESC pulse)
    .hpoint         = 0                     // Start at beggining of the period 
  };


  //Configure timer using struct 
  esp_err_t err = ledc_timer_config(&ledc_timer);
  //Can check for errors here (blinking LED or something)

  //Configure channel using struct
  err = ledc_channel_config(&ledc_channel);
  //Can check for errors here (blinking LED or something)

  //Output max throttle for 10 seconds to calibrate ESC 
  vTaskDelay(pdMS_TO_TICKS(10000));

  //Output min throttle for 10 seconds to calibrate ESC
  int new_duty_counts = 125 * 1023 / 500; 
  ledc_set_duty(LEDC_HIGH_SPEED_MODE, LEDC_CHANNEL_0, new_duty_counts); // Update the duty cycle
  ledc_update_duty(LEDC_HIGH_SPEED_MODE, LEDC_CHANNEL_0); // Apply the updated duty cycle
  vTaskDelay(pdMS_TO_TICKS(10000));

  //Update throttle to input 
  int throttle_input = 25; //Number between 0 and 125 for 0% to 100% throttle
  new_duty_counts = (125+throttle_input) * 1023 / 500; // Convert throttle input to duty counts
  ledc_set_duty(LEDC_HIGH_SPEED_MODE, LEDC_CHANNEL_0, new_duty_counts); // Update the duty cycle
  ledc_update_duty(LEDC_HIGH_SPEED_MODE, LEDC_CHANNEL_0); // Apply the updated duty cycle
  vTaskDelay(pdMS_TO_TICKS(10000));

  //Update throttle to input 
  throttle_input = 50; //Number between 0 and 125 for 0% to 100% throttle
  new_duty_counts = (125+throttle_input) * 1023 / 500; // Convert throttle input to duty counts
  ledc_set_duty(LEDC_HIGH_SPEED_MODE, LEDC_CHANNEL_0, new_duty_counts); // Update the duty cycle
  ledc_update_duty(LEDC_HIGH_SPEED_MODE, LEDC_CHANNEL_0); // Apply the updated duty cycle
  vTaskDelay(pdMS_TO_TICKS(10000));

  //Update throttle to input 
  throttle_input = 75; //Number between 0 and 125 for 0% to 100% throttle
  new_duty_counts = (125+throttle_input) * 1023 / 500; // Convert throttle input to duty counts
  ledc_set_duty(LEDC_HIGH_SPEED_MODE, LEDC_CHANNEL_0, new_duty_counts); // Update the duty cycle
  ledc_update_duty(LEDC_HIGH_SPEED_MODE, LEDC_CHANNEL_0); // Apply the updated duty cycle
  vTaskDelay(pdMS_TO_TICKS(10000));

  throttle_input = 100; //Number between 0 and 125 for 0% to 100% throttle
  new_duty_counts = (125+throttle_input) * 1023 / 500; // Convert throttle input to duty counts
  ledc_set_duty(LEDC_HIGH_SPEED_MODE, LEDC_CHANNEL_0, new_duty_counts); // Update the duty cycle
  ledc_update_duty(LEDC_HIGH_SPEED_MODE, LEDC_CHANNEL_0); // Apply the updated duty cycle
  vTaskDelay(pdMS_TO_TICKS(10000));

  throttle_input = 125; //Number between 0 and 125 for 0% to 100% throttle
  new_duty_counts = (125+throttle_input) * 1023 / 500; // Convert throttle input to duty counts
  ledc_set_duty(LEDC_HIGH_SPEED_MODE, LEDC_CHANNEL_0, new_duty_counts); // Update the duty cycle
  ledc_update_duty(LEDC_HIGH_SPEED_MODE, LEDC_CHANNEL_0); // Apply the updated duty cycle

}
