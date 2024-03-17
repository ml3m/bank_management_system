#include <stdio.h>
#include <stdlib.h>
#include <string.h>

// Define constants for currency types
#define RON 0
#define EUR 1
#define USD 2

// Define maximum length for name, surname, and IBAN
#define MAX_NAME_LENGTH 50
#define MAX_ACCOUNTS 100
#define MAX_IBAN_LENGTH 20

#define EXCHANGE_RATE_EUR_RON // Define structure for a person
typedef struct {
    char name[MAX_NAME_LENGTH];
    char surname[MAX_NAME_LENGTH];
} Person;

// Define structure for an account
typedef struct {
    char IBAN[MAX_IBAN_LENGTH];
    Person owner;
    int coin;
    double amount;
} Account;

// Function prototypes
int loadAccountsFromFile(Account *accounts);
void saveAccountsToFile(Account *accounts, int numAccounts);
void login(char *name, char *surname, Account *accounts, int numAccounts);
void editAccount(Account *accounts, int numAccounts);
void deleteAccount(Account *accounts, int *numAccounts);
void viewAccount(Account *accounts, int numAccounts);
void performTransaction(Account *accounts, int numAccounts);

int main(int argc, char *argv[]) {

    Account accounts[MAX_ACCOUNTS];
    int numAccounts = loadAccountsFromFile(accounts); 

    // Check if correct number of arguments provided
    if (argc != 3) {
        printf("Usage: %s [NAME] [SURNAME]\n", argv[0]);
        return 1;
    }

    // Get name and surname from command-line arguments
    char *name = argv[1];
    char *surname = argv[2];

    // Perform login
    login(name, surname, accounts, numAccounts);

    // Sample menu-driven interface
    int choice;
    do {
        // clear terminal
        system("clear");
        printf("\nBank Management System Menu:\n");
        printf("1. Edit Account\n");
        printf("2. Delete Account\n");
        printf("3. View Account\n");
        printf("4. Perform Transaction\n");
        printf("5. Exit\n");
        printf("Enter your choice: ");
        scanf("%d", &choice);
        switch(choice) {
            case 1:
                editAccount(accounts, numAccounts);
                break;
            case 2:
                deleteAccount(accounts, numAccounts);
                break;
            case 3:
                viewAccount(accounts, numAccounts);
                break;
            case 4:
                performTransaction(accounts, numAccounts);
                break;
            case 5:
                printf("Exiting...\n");
                break;
            default:
                printf("Invalid choice! Please enter again.\n");
        }
        printf("Press Enter to continue...");
        getchar();
        getchar();

    } while(choice != 5);
    
    saveAccountsToFile(accounts, numAccounts);
    return 0;
}

void login(char *name, char *surname, Account *accounts, int numAccounts) {
    int i;
    for (i = 0; i< numAccounts; ++i){
        if (strcmp(name, accounts[i].owner.name) == 0 && 
            strcmp(surname, accounts[i].owner.surname) == 0){
            printf("Logged in as %s %s\n", name, surname);
            return;
        }
    }
    // not found in db
    printf("Login failed. Name and Surname not found in db.\n");
    exit(1);
}

void editAccount(Account *accounts, int numAccounts) {
    char iban[MAX_IBAN_LENGTH];
    printf("Enter the IBAN of the account you want to edit: ");
    scanf("%s", iban);

    // Find the account with the given IBAN
    int i;
    for (i = 0; i < numAccounts; ++i) {
        if (strcmp(iban, accounts[i].IBAN) == 0) {
            // Account found, allow editing
            printf("Account found. Editing account: %s\n", iban);
            printf("1. Change owner's name\n");
            printf("2. Change owner's surname\n");
            printf("3. Change currency type\n");
            printf("Enter your choice: ");
            int choice;
            scanf("%d", &choice);
            switch (choice) {
                case 1:
                    printf("Enter new name: ");
                    scanf("%s", accounts[i].owner.name);
                    printf("Owner's name updated successfully.\n");
                    break;
                case 2:
                    printf("Enter new surname: ");
                    scanf("%s", accounts[i].owner.surname);
                    printf("Owner's surname updated successfully.\n");
                    break;
                case 3:
                    printf("Select new currency type:\n");
                    printf("1. RON\n");
                    printf("2. EUR\n");
                    printf("3. USD\n");
                    printf("Enter your choice: ");
                    scanf("%d", &accounts[i].coin);
                    printf("Currency type updated successfully.\n");
                    break;
                default:
                    printf("Invalid choice.\n");
            }
            return;
        }
    }
    printf("Account not found with the given IBAN.\n");
}

void deleteAccount(Account *accounts, int *numAccounts) {
    char iban[MAX_IBAN_LENGTH];
    printf("Enter the IBAN of the account you want to delete: ");
    scanf("%s", iban);

    // Find the account with the given IBAN
    int i;
    for (i = 0; i < *numAccounts; ++i) {
        if (strcmp(iban, accounts[i].IBAN) == 0) {
            // Account found, delete it
            printf("Account found. Deleting account: %s\n", iban);
            // Shift elements to overwrite the deleted account
            for (int j = i; j < *numAccounts - 1; ++j) {
                accounts[j] = accounts[j + 1];
            }
            (*numAccounts)--;
            printf("Account deleted successfully.\n");
            return;
        }
    }
    printf("Account not found with the given IBAN.\n");
}
//void editAccount(Account *accounts, int numAccounts) {
//    // Sample implementation of editing account
//    // For simplicity, assume the user edits the first account
//    printf("Editing account: %s\n", accounts[0].IBAN);
//    // Sample edit: Increase amount by 100
//    accounts[0].amount += 100.0;
//    printf("Account edited successfully.\n");
//}
//
//void deleteAccount(Account *accounts, int numAccounts) {
//    // Sample implementation of deleting account
//    // For simplicity, assume the user deletes the last account
//    printf("Deleting account: %s\n", accounts[numAccounts - 1].IBAN);
//    // Sample deletion: Remove the last account from the list
//    numAccounts--;
//    printf("Account deleted successfully.\n");
//}

void viewAccount(Account *accounts, int numAccounts) {
    // Sample implementation of viewing account
    // For simplicity, view details of the first account
    printf("Account Details:\n");
    printf("IBAN: %s\n", accounts[0].IBAN);
    printf("Owner: %s %s\n", accounts[0].owner.name, accounts[0].owner.surname);
    printf("Amount: %.2f\n", accounts[0].amount);
    switch(accounts[0].coin) {
        case RON:
            printf("Currency: RON\n");
            break;
        case EUR:
            printf("Currency: EUR\n");
            break;
        case USD:
            printf("Currency: USD\n");
            break;
        default:
            printf("Currency: Unknown\n");
    }
}

void saveAccountsToFile(Account *accounts, int numAccounts) {
    FILE *file = fopen("accounts.txt", "w");
    if (file == NULL) {
        printf("Error opening file for writing.\n");
        return;
    }

    for (int i = 0; i < numAccounts; ++i) {
        fprintf(file, "%s %s %s %d %.2f\n", accounts[i].IBAN, accounts[i].owner.name, accounts[i].owner.surname, accounts[i].coin, accounts[i].amount);
    }

    fclose(file);
    printf("Accounts data saved to file.\n");
}

int loadAccountsFromFile(Account *accounts) {
    FILE *file = fopen("accounts.txt", "r");
    if (file == NULL) {
        printf("Error opening file for reading.\n");
        return 0;
    }

    int numAccounts = 0;
    while (fscanf(file, "%s %s %s %d %lf", accounts[numAccounts].IBAN, accounts[numAccounts].owner.name, accounts[numAccounts].owner.surname, &accounts[numAccounts].coin, &accounts[numAccounts].amount) == 5) {
        numAccounts++;
    }

    fclose(file);
    printf("Accounts data loaded from file.\n");
    return numAccounts;
}

void performTransaction(Account *accounts, int numAccounts) {
    // Sample implementation of performing transaction
    // For simplicity, assume a transfer between the first two accounts
    printf("Performing transaction...\n");
    double amount;
    char iban[MAX_IBAN_LENGTH]; 
    printf("Enter amount to transfer: ");
    scanf("%lf", &amount);
    printf("Enter destination IBAN...");
    scanf("%s", iban);
    printf("you entered iban: %s", iban);

    if (amount <= accounts[0].amount) {
        accounts[0].amount -= amount;
        accounts[1].amount += amount;
        printf("Transaction successful.\n");
    } else {
        printf("Insufficient funds.\n");
    }
}
