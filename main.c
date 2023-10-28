#include "freertos/FreeRTOS.h"
#include "freertos/task.h"
#include "driver/gpio.h"

#define LED_PIN 2      // GPIO pin connected to the LED
#define BUTTON_PIN 15  // GPIO pin connected to the button

void init_gpio() {
    // Configure LED_PIN as an output
    gpio_pad_select_gpio(LED_PIN);
    gpio_set_direction(LED_PIN, GPIO_MODE_OUTPUT);

    // Configure BUTTON_PIN as an input
    gpio_pad_select_gpio(BUTTON_PIN);
    gpio_set_direction(BUTTON_PIN, GPIO_MODE_INPUT);
    gpio_set_pull_mode(BUTTON_PIN, GPIO_PULLUP_ONLY);  // Use an external pull-up resistor
}

void toggle_led_task(void* pvParameter) {
    while (1) {
        if (gpio_get_level(BUTTON_PIN) == 0) {
            // Button is pressed (active low)
            gpio_set_level(LED_PIN, 1);  // Turn on the LED
        } else {
            gpio_set_level(LED_PIN, 0);  // Turn off the LED
        }
        vTaskDelay(10 / portTICK_PERIOD_MS);  // Add a small delay to debounce the button
    }
}

void app_main() {
    init_gpio();
    xTaskCreate(toggle_led_task, "toggle_led_task", 2048, NULL, 5, NULL);
}
