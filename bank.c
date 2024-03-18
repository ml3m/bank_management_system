#include "bank.h"
#include <stdio.h>
#include <stdlib.h>
#include <string.h>

void login(char *name, char *surname, Account *accounts, int numAccounts) {
    int i;
    int user_accounts[5];
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

    int i;
    for (i = 0; i < numAccounts; ++i) {
        if (strcmp(iban, accounts[i].IBAN) == 0) {

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

void deleteAccount(Account *accounts, int numAccounts) {
    char iban[MAX_IBAN_LENGTH];
    printf("Enter the IBAN of the account you want to delete: ");
    scanf("%s", iban);

    int i;
    for (i = 0; i < numAccounts; ++i) {
        if (strcmp(iban, accounts[i].IBAN) == 0) {
            printf("Account found. Deleting account: %s\n", iban);
            // Shift elements to overwrite the deleted account
            // work needed here...
            for (int j = i; j < numAccounts - 1; ++j) {
                accounts[j] = accounts[j + 1];
            }
            numAccounts--;
            printf("Account deleted successfully.\n");
            return;
        }
    }
    printf("Account not found with the given IBAN.\n");
}

void viewAccount(Account *accounts, int numAccounts) {
    // UI/UX work needed here... make it beautiful, add colors
    //
    char iban[MAX_IBAN_LENGTH];
    printf("Enter the IBAN of account you want to see information: ");
    scanf("%s", iban);

    // #ToDo make it print information of account after the specific iban

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
        fprintf(file, "%s %s %s %d %.2f\n", 
                accounts[i].IBAN, 
                accounts[i].owner.name, 
                accounts[i].owner.surname, 
                accounts[i].coin, 
                accounts[i].amount
        );
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
    while (fscanf(file, "%s %s %s %d %lf", 
                accounts[numAccounts].IBAN, 
                accounts[numAccounts].owner.name, 
                accounts[numAccounts].owner.surname, 
                &accounts[numAccounts].coin, 
                &accounts[numAccounts].amount) == 5
            ){
        //debug
        //printf("account names:%s",accounts[numAccounts].owner.name);
        numAccounts++;
    }

    fclose(file);
    printf("Accounts data loaded from file.\n");
    return numAccounts;
}

void loadUserAccounts(char  user_accounts[][9], int numAccounts, Account *accounts, char *sysuser, char *syssurname) {
    int k = 0;
    for (int i = 0; i < numAccounts; i++) {
        if (strcmp(accounts[i].owner.name, sysuser) == 0 && strcmp(accounts[i].owner.surname, syssurname) == 0) {
            printf("account found: %s\n", accounts[i].IBAN);
            strcpy(user_accounts[k], accounts[i].IBAN); 
            printf("debug121: %s\n", user_accounts[k]);
            k++;
        }
    }
    user_accounts[k][0] = '\0'; 
}

    // Sample implementation of performing transaction
void performTransaction(Account *accounts, int numAccounts) {
    // For simplicity, assume a transfer between the first two accounts
    printf("Performing transaction...\n");
    double amount;
    char iban[MAX_IBAN_LENGTH]; 
    printf("Enter amount to transfer: ");
    scanf("%lf", &amount);
    printf("Enter destination IBAN...");
    scanf("%s", iban);
    printf("you entered iban: %s", iban);

/*doesn't work porperly '*/

    if (amount <= accounts[0].amount) {
        accounts[0].amount -= amount;
        accounts[1].amount += amount;
        printf("Transaction successful.\n");
    } else {
        printf("Insufficient funds.\n");
    }
}
