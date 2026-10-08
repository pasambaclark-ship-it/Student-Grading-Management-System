#include<stdio.h>

void seperator(int length) {
    for (int i = 0; i < length; i++) {
        putchar('-');
    }
    putchar('\n');
}


int main() {
    int upperlmt, lowerlmt;

    seperator(50);
    printf("Enter Upper Limit: ");
    scanf("%d", &upperlmt);
    printf("\n");
    seperator(50);

    printf("Enter Lower Limit: ");
    scanf("%d", &lowerlmt);
    printf("\n");
    seperator(50);

    if(lowerlmt < upperlmt) {

        for(int i = lowerlmt; i<=upperlmt; i+=2) {
            printf("%d \n", i);
        }
        printf("\n");
    seperator(50);

    } else {
        printf("Invalid Input.");

    }
return 0;
}