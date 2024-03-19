#include "bank.h"
#include "cli.h"
#include <stdio.h>
#include <stdlib.h>

int main(int argc, char *argv[]) {

    char user_accounts[5][9];
    Account accounts[MAX_ACCOUNTS];
    int numAccounts = loadAccountsFromFile(accounts); 
    if (argc != 3) {
        printf("Usage: %s [NAME] [SURNAME]\n", argv[0]);
        return 1;
    }

    char *name = argv[1];
    char *surname = argv[2];
    
    loadUserAccounts(user_accounts, numAccounts, accounts, name, surname);
    login(name, surname, accounts, numAccounts);

    int choice;
    do {
        system("clear");
        printUserAccounts(user_accounts);
        printMainMenu(name, surname);

        scanf("%d", &choice);
        switch(choice) {
            case 1:
                editAccount(accounts, numAccounts);
                break;
            case 2:
                deleteAccount(accounts, &numAccounts);
                break;
            case 3:
                viewAccount(accounts, numAccounts);
                break;
            case 4:
                performTransaction(accounts, numAccounts, name, surname);
                break;
            case 5:
                printf("Exiting...\n");
                break;
            case 6:
                //createaAccount();
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
