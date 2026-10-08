#include<stdio.h>

int main() {
    int num = 1024, reverse = 0;
    while(num != 0) {
        reverse = reverse * 10 + num % 10;
        num /= 10;
    }
    printf("Reversed number: %d\n", reverse);
    return 0;
}