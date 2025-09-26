#include <stdio.h>
#include "pico/stdlib.h"
#include "hardware/flash.h"
#include "hardware/sync.h"

#define FLASH_TARGET_OFFSET (1 * 1024 * 1024)
#define LED_PIN 25

void write_to_flash(char* message, int count) {
    uint32_t ints = save_and_disable_interrupts();
    flash_range_erase(FLASH_TARGET_OFFSET, FLASH_SECTOR_SIZE); // erase 4KB of flash memory
    restore_interrupts(ints);

    ints = save_and_disable_interrupts();
    flash_range_program(FLASH_TARGET_OFFSET, message, count); // write to the erased memory
    restore_interrupts(ints);
}

int main() {
    stdio_init_all();

    char message[256]; // must be multiples of 256 (pico block)

    while (true) {
        scanf("%c", &message);

        write_to_flash(message, sizeof(message));

        char read_message = *(int *)(XIP_BASE + FLASH_TARGET_OFFSET);
        printf("%d\n", read_message);
    }
}
