#include <stdio.h>
#include <string.h>
#include "pico/stdlib.h"
#include "hardware/flash.h"
#include "hardware/sync.h"

#define FLASH_TARGET_OFFSET (1 * 1024 * 1024)
#define LED_PIN 25
#define PICO_FLASH_BLOCK 256

void write_to_flash(char* message, int count) {
    uint32_t ints = save_and_disable_interrupts();
    flash_range_erase(FLASH_TARGET_OFFSET, FLASH_SECTOR_SIZE); // erase 4KB of flash memory
    restore_interrupts(ints);

    ints = save_and_disable_interrupts();
    flash_range_program(FLASH_TARGET_OFFSET, message, count); // write to the erased memory
    restore_interrupts(ints);
}

void read_from_flash() {
    char message_buffer[PICO_FLASH_BLOCK];
    memset(message_buffer, 0, sizeof(message_buffer));

    char* message_start_pointer = (char *)(XIP_BASE + FLASH_TARGET_OFFSET);
    int i;
    for (i = 0; 
        i < PICO_FLASH_BLOCK - 1 && *message_start_pointer != '\0';
        i++, message_start_pointer++) {
        message_buffer[i] = *message_start_pointer;
    }
    message_start_pointer[i] = '\0';

    printf("%s\n", message_buffer);
}

int main() {
    stdio_init_all();

    char message[PICO_FLASH_BLOCK]; // must be multiples of 256 (pico block)
    int message_index = 0;

    sleep_ms(5000);

    read_from_flash();

    while (true) {
        scanf("%c", &message[message_index]);
        printf("%c", message[message_index]); // echoing the input in the console

        if (message[message_index] == '\n' || message[message_index] == '\r') {
            message[message_index] = '\0';
            printf("\n");
            write_to_flash(message, sizeof(message));
            break;
        }

        message_index++;
    }

    read_from_flash();
}
