#include <stdio.h>
#include "pico/stdlib.h"
#include "hardware/sync.h"

int main() {
    stdio_init_all();

    const uint PIN = 11;
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
        while (gpio_get(PIN) == 0);
        while (gpio_get(PIN) == 1);

        // processing sensor's data
        // every bit starts with 50us LOW
        // 0 = 26-28us HIGH
        // 1 = ~70us HIGH

        int result[40];

        char current_value = 0;
        char values[5];
        int value_index = 0;

        uint32_t status = save_and_disable_interrupts();

        for (int i = 0; i < 40; ++i) {
            int low_cnt = 0;
            while (gpio_get(PIN) == 0) {

            }

            int start_time = time_us_32();
            while (gpio_get(PIN) == 1);
            int high_duration = time_us_32() - start_time;

            if (high_duration > 50) {
                result[i] = 1;

                current_value <<= 1;
                current_value |= 1;
            } else {
                result[i] = 0;
                
                current_value <<= 1;
            }

            if ((i+1) % 8 == 0) {
                values[value_index] = current_value;
                current_value = 0;
                ++value_index;
            }
        }

        restore_interrupts(status);

        for (int i = 0; i < 5; ++i) {
            for (int j = 0; j < 8; ++j) {
                printf("%d", result[(i*8) + j]);
            }
            printf("   %d\n", values[i]);
        }
        printf("---\nTemperature (C): %d; Humidity: %d\n", values[2], values[0]);
        if (values[4] == (values[0] +  values[1] +  values[2] +  values[3])) {
            printf("Correct!\n");
        } else {
            printf("!!!! Incorrect !!!!\n");
        }
        printf("---\n");

        // repeating it with a X ms delay
        sleep_ms(1000);
    }
}
