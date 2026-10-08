#include <stdio.h>
#include <stdlib.h>
#include <time.h>

void playgame() {
    int secret, guess, attempts = 0;
    int guesses[100];

    srand(time(0));
    secret = rand() % 100 + 1;

    printf("Guess the number (1 to 100): \n");

    do{
        scanf("%d", &guess);
        guesses[attempts++] = guess;

        if(guess > secret){
            printf("Too high! \n");
        } else if(guess < secret) {
            printf("Too Low! \n");
        } else {
            printf("Congrats! You've have %d guessed attempts. \n", attempts);
        }

    }while(guess != secret);

     printf("Your Guesses: ");
        for (int i=0; i < attempts; i++) {
            printf("%d ", guesses[i]);
}

        printf("\n");
}

int main() {
    playgame();
    return 0;
}

