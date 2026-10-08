#include <stdio.h>

void seperator(int length) {
    for (int i = 0; i < length; i++) {
        putchar('-');
    }
    putchar('\n');
}

struct account{
    int id;
    char name[50];
    float balance;
};

int main () {

struct account acc;
int menu;
seperator(80);
    printf("--- Simple Bank Account Simulator --- \n");

    printf("Enter your name: ");
    scanf("%49s", acc.name);

    printf("Enter starting balance: ");
    scanf("%f", &acc.balance);

    printf("\n");
seperator(80);
    printf("Menu \n");
        printf("1. Deposit \n");
        printf("2. Withdraw \n");
        printf("3. Check Balance \n");
        printf("4. Exit \n");
seperator(80);

    do {
        printf("Enter you choice: ");
        scanf("%d", &menu);
        clearerr(stdin); 
        int c;
        while ((c = getchar()) != '\n' && c != EOF);
        printf("\n");

    switch(menu){
        case 1: {
           float amount;
            printf("Enter amount to deposit: ");
            scanf("%f", &amount);
            printf("\n");

                if(amount > 0) {
                    acc.balance += amount;
                     printf("Deposit successful! New balance: %.2f \n", acc.balance);
                     seperator(80);
                } else {
                    printf("Invalid Input. \n");
                    seperator(80);
                }
                break;
            }

            case 2: {
                float amount;
            printf("Enter amount to withdraw: ");
            scanf("%f", &amount);
            printf("\n");

                if(amount <= acc.balance && amount < 0) {
                    acc.balance -= amount;
                     printf("Withdraw successful! New balance: %.2f \n", acc.balance);
                     seperator(80);
                } else {
                    printf("Invalid Input, exceed balance. \n");
                    seperator(80);
                }
                break;
            }

            case 3: {
                printf("Your current balance is: %.2f \n", acc.balance);
                seperator(80);
                break;
            }

            case 4: {
                printf("Exiting program... thank you. \n");
                seperator(80);
                break;
            }
            default:
                printf("Invalid Input. Try again.");
                seperator(80);
        }
    }while (menu !=4);
    return 0;
}