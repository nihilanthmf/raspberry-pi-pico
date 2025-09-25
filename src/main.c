#include <stdio.h>
#include "pico/stdlib.h"

int main() {
    // Initialize stdio (USB or UART depending on build config)
    stdio_init_all();

    // Set onboard LED pin
    const uint LED_PIN = 25;
    gpio_init(LED_PIN);
    gpio_set_dir(LED_PIN, GPIO_OUT);

    char message;

    while (true) {
        scanf("%c", &message);

        printf("you typed %c\n", message);

        if (message == '1') {
            gpio_put(LED_PIN, 1);
        } else{
            gpio_put(LED_PIN, 0);
        }
    }
}
