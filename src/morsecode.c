#include <stdio.h>
#include "pico/stdlib.h"

#define MORSE_CODE_LETTER_CNT 26

typedef struct {
    char character;
    int code[4];
} MorseCodeSymbol;

MorseCodeSymbol morse_codes[MORSE_CODE_LETTER_CNT] = {
    {'a', {1,3,0,0}},  // · –
    {'b', {3,1,1,1}},  // – · · ·
    {'c', {3,1,3,1}},  // – · – ·
    {'d', {3,1,1,0}},  // – · ·
    {'e', {1,0,0,0}},  // ·
    {'f', {1,1,3,1}},  // · · – ·
    {'g', {3,3,1,0}},  // – – ·
    {'h', {1,1,1,1}},  // · · · ·
    {'i', {1,1,0,0}},  // · ·
    {'j', {1,3,3,3}},  // · – – –
    {'k', {3,1,3,0}},  // – · –
    {'l', {1,3,1,1}},  // · – · ·
    {'m', {3,3,0,0}},  // – –
    {'n', {3,1,0,0}},  // – ·
    {'o', {3,3,3,0}},  // – – –
    {'p', {1,3,3,1}},  // · – – ·
    {'q', {3,3,1,3}},  // – – · –
    {'r', {1,3,1,0}},  // · – ·
    {'s', {1,1,1,0}},  // · · ·
    {'t', {3,0,0,0}},  // –
    {'u', {1,1,3,0}},  // · · –
    {'v', {1,1,1,3}},  // · · · –
    {'w', {1,3,3,0}},  // · – –
    {'x', {3,1,1,3}},  // – · · –
    {'y', {3,1,3,3}},  // – · – –
    {'z', {3,3,1,1}}   // – – · ·
};

MorseCodeSymbol default_morse_code = {0, {0,0,0,0}};

int* morse_code_conversion(char input) {
    for (int i = 0; i < MORSE_CODE_LETTER_CNT; ++i) {
        if (morse_codes[i].character == input) {
            return morse_codes[i].code;
        }
    }

    return default_morse_code.code;
}

int main() {
    // Initialize stdio (USB or UART depending on build config)
    stdio_init_all();

    // Set onboard LED pin
    const uint LED_PIN = 25;
    gpio_init(LED_PIN);
    gpio_set_dir(LED_PIN, GPIO_OUT);

    char message[512];
    char symbol = 0;
    int message_i = 0;
    while (symbol != 13) {
        scanf("%c", &symbol);
        printf("%c", symbol);
        message[message_i] = symbol;
        message_i++;
    }
    message[message_i] = 0;
    printf("\n%s\n", message);

    while (true) {
        for (int letter_i = 0; letter_i < message_i; ++letter_i) {
            int* morse_code = morse_code_conversion(message[letter_i]);
            for (int i = 0; i < 4; ++i) {
                sleep_ms(1 * 100); // a gap between the letter's signals (== 1 dot)
                gpio_put(LED_PIN, 1);
                sleep_ms(morse_code[i] * 100);
                gpio_put(LED_PIN, 0);
            }
            sleep_ms(700);
        }
        sleep_ms(3000);
    }
}
