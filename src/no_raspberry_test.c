#include <stdio.h>
#include <math.h>

#define MAX_NUMBER_LENGTH 4
#define MAX_BINARY_LENGTH sizeof(num) * 8

void to_binary(int num) {
    char bin[MAX_BINARY_LENGTH] = {0};
    for (int i = 0; i < MAX_BINARY_LENGTH; i++) {
        int bit = (num >> i) & 1;
        bin[i] = bit;
        printf("%d\n", bit);
    }
    printf("%s\n", bin);
}

int char_to_num(char num) {
    return num - 48;
}

int main() {
    to_binary(123);
}
