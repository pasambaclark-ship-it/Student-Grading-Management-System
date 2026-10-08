#include <stdio.h>

void seperator(int length) {
    for (int i = 0; i < length; i++) {
        putchar('-');
    }
    putchar('\n');
}

int main() {
    float ticketClass, weight, fee;
    fee = 0; 

    while(1){
 printf("\n");
 seperator(80);
   printf("Welcome to SkyHigh Airlines!\n");
    printf("We have the following classes:\n");
    printf("1. First Class Passenger\n");
    printf("2. Economy Class Passenger\n\n");

    printf("What Ticket Class would you prefer? ");
    scanf("%f", &ticketClass);
     seperator(80);
    printf("\n");

    printf("What is the weight of your suitcase (in kg)? ");
    scanf("%f", &weight);
     seperator(80);
    printf("\n");

    if (ticketClass == 1) {
        printf("Thank you, your bags fly free regardless of the weight.\n");
         seperator(80);
        fee = 1000;
    } else if (ticketClass == 2) {
        if (weight < 23) {
            fee = 1000;
            fee +=30;
        } else if (weight >= 23 && weight <= 32) {
            fee = 1000;
            fee +=75;
        } else {
            printf("The weight of the bag is over the safety limits.\n");
            printf("Your bag is rejected and cannot fly.\n");
             seperator(80);
            return 0;
        }

    } else {
        printf("Invalid input.\n");
         seperator(80);
        return 0;
    }

    if (ticketClass == 1) {
        printf("You chose First Class Passenger.\n");
         
    } else {
        printf("You chose Economy Class Passenger.\n");
        printf("Your Bag weight: %.2f kg\n", weight);
         
    }

    printf("Your Flight Fee is: $%.2f\n", fee);
     seperator(80);

     printf("Do you want to enter another response? (y/n): ");
     int choice;
        scanf(" %c", &choice); 
        seperator(80);
        
        if (choice == 'n' || choice == 'N') {
            printf("Exiting program. Goodbye!\n");
            break; 
        }

    }
    return 0;
}
