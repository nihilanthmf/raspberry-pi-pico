#include <stdio.h>
#include "pico/stdlib.h"

int main() {
    // Initialize stdio (USB or UART depending on build config)
    stdio_init_all();

    // Set onboard LED pin
    const uint LED_PIN = 25;
    gpio_init(LED_PIN);
    gpio_set_dir(LED_PIN, GPIO_OUT);

    while (true) {
        printf("Hello from Raspberry Pi Pico!\n");

        // Turn LED on
        gpio_put(LED_PIN, 1);
        sleep_ms(500);

        // Turn LED off
        gpio_put(LED_PIN, 0);
        sleep_ms(500);
    }
}
