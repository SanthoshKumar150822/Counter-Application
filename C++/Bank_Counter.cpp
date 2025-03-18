#include<iostream>
using namespace std;

long token = 0, current_token = 0;

int main() {
    int choice = 0;
    int counter1 = 0, counter2 = 0, counter3 = 0, counter4 = 0;

    while (true) {
        cout << "1. Enter 1 for Window Operator1\n";
        cout << "2. Enter 2 for Window Operator2\n";
        cout << "3. Enter 3 for Window Operator3\n";
        cout << "4. Enter 4 for Window Operator4\n";
        cout << "5. Enter 5 to get a token for access to a Window Operator.\n\n";
        cout << "Enter your choice: ";
        cin >> choice;

        while (choice < 1 || choice > 5) {
            cout << "Invalid choice!!\n";
            cout << "Enter your choice: ";
            cin >> choice;
        }

        switch (choice) {
            case 1:
                if (token > 0 && current_token < token) {
                    current_token++;
                    counter1 = current_token;
                } else {
                    counter1 = 0;
                }
                break;

            case 2:
                if (token > 0 && current_token < token) {
                    current_token++;
                    counter2 = current_token;
                } else {
                    counter2 = 0;
                }
                break;

            case 3:
                if (token > 0 && current_token < token) {
                    current_token++;
                    counter3 = current_token;
                } else {
                    counter3 = 0;
                }
                break;

            case 4:
                if (token > 0 && current_token < token) {
                    current_token++;
                    counter4 = current_token;
                } else {
                    counter4 = 0;
                }
                break;

            case 5:
                token++;
                cout << "Your Token number: " << token << "\n";
                break;
        }

        cout << "\n\n";
        cout << "Counter1: " << counter1 << "\tCounter2: " << counter2 << "\n";
        cout << "Counter3: " << counter3 << "\tCounter4: " << counter4 << "\n";
        cout << "\n\n";
    }

    return 0;
}
