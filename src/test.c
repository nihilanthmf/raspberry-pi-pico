#include <stdio.h>

char cmd_equal_check() { 
    return 23;
}

int main() {
    int res = cmd_equal_check();
    printf("%lu\n", sizeof(res));
    printf("%lu\n", res);
}
