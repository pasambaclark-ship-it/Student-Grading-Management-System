#include<stdio.h>

int main() {
    int num, factorial = 1, i = 1;

    printf("Give a Number: ");
    scanf("%d", &num);

    for(; i <= num; i++) {
        factorial *= i;
    }

    printf("The %d! is %d\n", num, factorial);
    return 0;
}