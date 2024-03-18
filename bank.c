#include "bank.h"
#include "cli.h"
#include <stdio.h>
#include <stdlib.h>
#include <string.h>

/*works like a charm*/
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


/* works properly, coin change -> iban label change */
void editAccount(Account *accounts, int numAccounts) {
    char iban[MAX_IBAN_LENGTH];
    printf("Enter the IBAN of the account you want to edit: ");
    scanf("%s", iban);

    int i;
    for (i = 0; i < numAccounts; ++i) {
        if (strcmp(iban, accounts[i].IBAN) == 0) {
            printEditAccount(iban); 

            /*bellow switch can be included in printEditAccount() CLI fun*/
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
                    int changed_coin;
                    scanf("%d", &changed_coin);
                    accounts[i].coin = changed_coin;
                    switch (changed_coin) {
                        case 1: 
                            accounts[i].IBAN[0]= 'R';
                            accounts[i].IBAN[1]= 'O';
                            break;
                        case 2:
                            accounts[i].IBAN[0]= 'E';
                            accounts[i].IBAN[1]= 'U';
                            break;
                        case 3:
                            accounts[i].IBAN[0]= 'U';
                            accounts[i].IBAN[1]= 'S';
                            break;
                        default:
                            printf("failed to change iban after coin conversion");
                    } 
                    printf("iban changed to:%s ",accounts[i].IBAN);
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


/*work in progress delete account doesn't work properly'*/
/*need to come up with a implementation for deleting an account*/
/*need to make sure the user doesn't have any money in the account'*/
/*prompt the user to transfer the money left and only then the account is available to be deleted*/
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


/*works properly*/
void viewAccount(Account *accounts, int numAccounts) {
    // UI/UX work needed here... make it beautiful, add colors
    //
    char iban[MAX_IBAN_LENGTH];
    printf("Enter the IBAN of account you want to see information: ");
    scanf("%s", iban);


    for (int i = 0; i< numAccounts; i++) {
        if(strcmp(accounts[i].IBAN,iban)== 0){
           printf("check000"); 
           printf("ac: %s", accounts[i].IBAN);

           printf(">Account Details:\n");
           printf("IBAN: %s\n", accounts[i].IBAN);
           printf("Owner: %s %s\n", accounts[i].owner.name, accounts[i].owner.surname);
           printf("Amount: %.2f\n", accounts[i].amount);
           switch(accounts[i].coin) {
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
        numAccounts++;
    }

    fclose(file);
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

/* doesn't work properly it sends the money to the next account'*/
/* for now we ignore the different currencies*/
/* implementation needed, source account from connected user -> destination account*/

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
