#include <stdio.h>
#include <stdlib.h>

struct User {
    char name[50];
    int account_number;
    float balance;
};

int main() {
    int a;
    FILE *fp;
    struct User user;

    do {
        printf("\n--- Bank Management System ---\n");
        printf("1. Add Account\n2. View Accounts\n3. Deposit/Withdraw\n4. Exit\n");
        printf("What do you want to do: ");
        scanf("%d", &a);

        switch (a) {
            case 1:
                fp = fopen("account.txt", "a+");
                if (fp == NULL) {
                    printf("Error opening file!\n");
                    exit(1);
                }
                printf("Enter account holder name: ");
                scanf("%s", user.name);
                printf("Enter account number: ");
                scanf("%d", &user.account_number);
                printf("Enter your balance: ");
                scanf("%f", &user.balance);
                fprintf(fp, "%s %d %.2f\n", user.name, user.account_number, user.balance);
                fclose(fp);
                printf("Account added successfully!\n");
                break;

            
               case 2: {
    // Ask for the account number to search
    printf("Enter account number: ");
    int search_account_num;
    scanf("%d", &search_account_num);

    // Open the file for reading
    fp = fopen("account.txt", "r");
    if (fp == NULL) {
        printf("No accounts found!\n");
        break;
    }

    int found = 0;
    // Search for the account by reading each line
    while (fscanf(fp, "%s %d %f", user.name, &user.account_number, &user.balance) != EOF) {
        if (user.account_number == search_account_num) {
            // Account found, display details
            printf("Account Details:\n");
            printf("Name: %s\n", user.name);
            printf("Account Number: %d\n", user.account_number);
            printf("Balance: %.2f\n", user.balance);
            found = 1; // Set flag to indicate the account was found
            break; // Exit the loop once the account is found
        }
    }
    fclose(fp);

    // If no account was found, notify the user
    if (!found) {
        printf("Account not found!\n");
    }
    break;
}


            case 3: {
                printf("Enter account number: ");
                int account_num;
                scanf("%d", &account_num);

                // Open accounts file for reading
                fp = fopen("account.txt", "r");
                if (fp == NULL) {
                    printf("No accounts found!\n");
                    break;
                }

                // Create a temporary file for updating balances
                FILE *temp_fp = fopen("temp.txt", "w");
                if (temp_fp == NULL) {
                    printf("Error creating temporary file!\n");
                    fclose(fp);
                    break;
                }

                int found = 0;
                int trans_choice;

                // Ask for deposit or withdrawal choice
                printf("1. Deposit\n2. Withdraw\n");
                printf("Enter your choice: ");
                scanf("%d", &trans_choice);

                // Read each account from the file
                while (fscanf(fp, "%s %d %f", user.name, &user.account_number, &user.balance) != EOF) {
                    if (user.account_number == account_num) {
                        found = 1;
                        printf("Account found: %s, Balance: %.2f\n", user.name, user.balance);

                        // Handle deposit
                        if (trans_choice == 1) { // Deposit
                            float amount;
                            printf("Enter deposit amount: ");
                            scanf("%f", &amount);
                            user.balance += amount;
                            printf("New Balance: %.2f\n", user.balance);
                        } 
                        // Handle withdrawal
                        else if (trans_choice == 2) { // Withdraw
                            float amount;
                            printf("Enter withdrawal amount: ");
                            scanf("%f", &amount);
                            if (user.balance >= amount) {
                                user.balance -= amount;
                                printf("New Balance: %.2f\n", user.balance);
                            } else {
                                printf("Insufficient funds!\n");
                            }
                        }
                    }
                    // Write updated account information to temporary file
                    fprintf(temp_fp, "%s %d %.2f\n", user.name, user.account_number, user.balance);
                }

                fclose(fp);
                fclose(temp_fp);

                // Check if account was found and update files
                if (!found) {
                    printf("Account not found!\n");
                    remove("temp.txt");
                } else {
                    remove("account.txt");
                    rename("temp.txt", "account.txt");
                    printf("Transaction completed successfully!\n");
                }
                break;
            }

            case 4:
                printf("Exiting...\n");
                break;

            default:
                printf("Invalid choice! Please try again.\n");
        }

    } while (a != 4);

    return 0;
}

