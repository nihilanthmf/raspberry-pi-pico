#include <stdio.h>
#include "pico/stdlib.h"
#include "hardware/sync.h"

int main() {
    stdio_init_all();

    const uint PIN = 15;
    gpio_init(PIN);

    sleep_ms(4000);

    while (true) {
        // Singaling to the sensor that we're ready to accept its output
        gpio_set_dir(PIN, GPIO_OUT);
        gpio_put(PIN, 0);
        sleep_ms(18);
        gpio_put(PIN, 1);
        sleep_us(20);
        gpio_set_dir(PIN, GPIO_IN);
        gpio_pull_up(PIN);

        // handling handshake
        while (gpio_get(PIN) == 0) sleep_us(1);
        while (gpio_get(PIN) == 1) sleep_us(1);

        // processing sensor's data
        // every bit starts with 50us LOW
        // 0 = 26-28us HIGH
        // 1 = ~70us HIGH

        int result[40];

        for (int i = 0; i < 40; ++i) {
            while (gpio_get(PIN) == 0) sleep_us(1);

            int ones_cnt = 0;
            int time_before_ones = time_us_32();
            while (gpio_get(PIN) == 1) {
                ones_cnt = time_us_32() - time_before_ones;
                // sleep_us(1);
            }

            if (ones_cnt > 60) {
                // its a 1
                result[i] = 1;
            } else {
                // its a 0
                result[i] = 0;
            }
        }

        for (int i = 0; i < 40; ++i) {
            printf("%d", result[i]);
        }
        printf("\n\n");

        for (int i = 0; i < 40; ++i) {
            if (i % 8 == 0) {
                printf("\n");
            }
            printf("%d", result[i]);
        }
        printf("\n\n");

        // restore_interrupts(status);

        // repeating it with a X ms delay
        sleep_ms(1000);
    }
}
