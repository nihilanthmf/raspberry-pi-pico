#include "pico/stdlib.h"
#include <stdio.h>
#include <string.h>
#include <math.h>

#define COMMAND_BUFFER_LENGTH 64

int char_to_int(char c){
    return c > 47 && c < 58 ? c - 48 : -1;
}

int string_to_int(char *c) {
    char current_char;
    int result = 0;

    int string_length = 0;

    for (; c[string_length] != '\0'; ++string_length) ;

    for (int i = 0; i < string_length; ++i) {
        int res = char_to_int(c[i]);

        if (res == -1) {
            printf("'%c' is not a number!\n", c[i]);
        } else {
            result += res * pow(10, string_length - i - 1);
        }
    }
    return result;
}

void cmd_read(char* cmd) {
    printf("> ");
    fflush(stdout);
    for (int cmd_index = 0; cmd_index < COMMAND_BUFFER_LENGTH - 1; ++cmd_index) {
        scanf("%c", cmd + cmd_index);
        printf("%c", cmd[cmd_index]);

        if (cmd[cmd_index] == '\r' || cmd[cmd_index] == '\n') {
            printf("\n");
            break;
        }
    }
}

char cmd_equal_check(char* user_cmd, char *check_cmd, int check_cmd_length) {
    for (int i = 0; i < check_cmd_length; ++i) {
        if (user_cmd[i] != check_cmd[i]) {
            return false;
        }
    }
    return true;
}

void calc(char* cmd) {
    int max_operand_cnt = 8;
    int max_operand_length = 10;
    char operands[max_operand_cnt][max_operand_length];
    memset(operands, 0, sizeof(operands));

    int operand_index = -1;
    int character_index = 0;
    for (int i = 0; i < COMMAND_BUFFER_LENGTH; ++i) {
        if (cmd[i] == ' ' || cmd[i] == '\n' || cmd[i] == '\r') {
            ++operand_index;
            character_index = 0;
            continue;
        }

        if (operand_index != -1 && operand_index < max_operand_cnt 
            && character_index < max_operand_length) {
            operands[operand_index][character_index] = cmd[i];
            ++character_index;
        }
    }

    int sum = 0;

    for (int i = 0; i < max_operand_cnt; ++i) {
        if (operands[i][0] != '\0') {
            sum += string_to_int(operands[i]);
        }
    }

    printf("the sum is %d\n", sum);
}

void cmd_execute(char* cmd) {
    if (cmd_equal_check(cmd, "calc", 4)) {
        calc(cmd);
    } else {
        printf("this command is unknown!\n");
        fflush(stdout);
    }
}

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
