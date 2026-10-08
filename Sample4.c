#include<stdio.h>

int main() {
    int password;
    do{
        printf("Enter the correct password: ");
        scanf("%d",&password);
    } while(password != 1234);
    printf("ACCESS GRANTED...\n");
    return 0;

}