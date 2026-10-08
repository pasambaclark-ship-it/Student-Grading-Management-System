#include<stdio.h>

int main() {

    int i, sum = 0;

    for(i=0; i<=100; i++) {
        sum+=i;
    }
    printf("The Sum of the Numbers from 1-100 is %d.", sum);
return 0;
}