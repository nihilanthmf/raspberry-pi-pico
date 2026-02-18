#include "pico/stdlib.h"
#include <stdio.h>
#include <string.h>
#include <math.h>

int main() {
    stdio_init_all();

    sleep_ms(3000);

    printf("Welcome to tinyos\n");

    char cmd[COMMAND_BUFFER_LENGTH];
    while (true) {
        memset(cmd, 0, COMMAND_BUFFER_LENGTH * sizeof(cmd[0]));

        cmd_read(cmd);
        cmd_execute(cmd);
    }
}
