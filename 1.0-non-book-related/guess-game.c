#include <stdio.h>
#include <stdlib.h>

int main() {
  while (1) {
    system("clear");
    printf("Lets play a guessing game, I will choose number between 1-100, "
           "and you have to guess it!\nYou will have 5 tries, each try you "
           "will get a hint.\nGood luck!\n");

    int x = rand() % 100 + 1;
    x++;
    printf("%d", x);

    for (int tries = 4; tries > -1; tries--) {
      int guess;
      printf("\nGuess the number: ");
      scanf("%d", &guess);

      if (guess > x) {
        printf("%d > X", guess);
      }

      else if (guess < x) {
        printf("%d < X", guess);
      }

      else if (guess == x) {
        char replay;
        printf("\nYou win, wanna play again? (y/n): ");
        scanf(" %c", &replay);

        if (replay == 'y') {
          break;
        }

        else if (replay == 'n') {
          return 0;
        }
      }

      if (tries == 0) {
        char replay;
        printf("\nYou are out of guesses, want to play again? (y/n): ");
        scanf(" %c", &replay);

        if (replay == 'y') {
          break;
        }

        else if (replay == 'n') {
          return 0;
        }
      }
      printf("\nYou have %d tries left", tries);
    }
  }
}
