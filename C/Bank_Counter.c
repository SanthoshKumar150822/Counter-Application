#include <stdio.h>
#include <conio.h>

int main() {
    int a = 0;
    long int token = 0, current_token = 0;
    int counter1 = 0, counter2 = 0, counter3 = 0, counter4 = 0;

    while (1) {
        printf("1. Enter 1 for Counter1.\n");
        printf("2. Enter 2 for Counter2.\n");
        printf("3. Enter 3 for Counter3.\n");
        printf("4. Enter 4 for Counter4.\n");
        printf("5. Enter 5 to generate a Token.\n");
        printf("Enter your choice: ");
        scanf("%d", &a);

        // Validate user input
        while (a > 5 || a < 1) {
            printf("Invalid choice!\nEnter your choice: ");
            scanf("%d", &a);
        }

        switch (a) {
            case 1:
                if (token > current_token) {
                    current_token++;
                    counter1 = current_token;
                } else {
                    counter1 = 0; // No tokens available
                }
                break;

            case 2:
                if (token > current_token) {
                    current_token++;
                    counter2 = current_token;
                } else {
                    counter2 = 0; // No tokens available
                }
                break;

            case 3:
                if (token > current_token) {
                    current_token++;
                    counter3 = current_token;
                } else {
                    counter3 = 0; // No tokens available
                }
                break;

            case 4:
                if (token > current_token) {
                    current_token++;
                    counter4 = current_token;
                } else {
                    counter4 = 0; // No tokens available
                }
                break;

            case 5:
                token++;
                printf("Your Token number: %ld\n", token);
                break;
        }

        // Display current state of counters
        printf("Counter1: %d\tCounter2: %d\n", counter1, counter2);
        printf("Counter3: %d\tCounter4: %d\n", counter3, counter4);
        printf("\n\n");
    }

    return 0;
}
