#include <stdio.h>

int main () {
    int number, rem;
    char choice;

   
    while (1) {
        printf("\nEnter a Number: ");
        scanf("%d", &number);
        
        rem = number % 2; 
        
        if (number > 0 && rem == 0) {
            printf("The number %d is positive even...\n", number);
        } 
        else if (number > 0 && rem != 0) { 
            printf("The number %d is positive odd...\n", number);
        } 
        else if (number < 0 && rem == 0) {
            printf("The number %d is negative even...\n", number);

        } else if (number < 0 && rem !=0) {
            printf("The number %d is negative odd...\n", number);
        } 
        else {
            printf("The number is zero...\n", number);
        }
        
        
        printf("Do you want to enter another number? (y/n): ");
        scanf(" %c", &choice); 
        
        if (choice == 'n' || choice == 'N') {
            printf("Exiting program. Goodbye!\n");
            break; 
        }
    }
    
    return 0;
}