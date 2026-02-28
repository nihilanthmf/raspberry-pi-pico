#include <stdio.h>
#include "pico/stdlib.h"
#include "hardware/sync.h"

int main() {
    stdio_init_all();

    const uint PIN = 4;
    const uint LED_PIN = 25;
    
    gpio_init(LED_PIN);
    gpio_init(PIN);

    gpio_set_dir(PIN, GPIO_IN);
    gpio_set_dir(LED_PIN, GPIO_OUT);

    gpio_pull_down(PIN);

    // warm up the sensor
    sleep_ms(61000);

    while (true) {
        const bool motion = gpio_get(PIN);

        gpio_put(LED_PIN, motion);

        // repeating it with a X ms delay
        sleep_ms(100);
    }
}
