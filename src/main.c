/*            _______           ____              _    
 _ __ ___    / /___ / _ __ ___ | __ )  __ _ _ __ | | __
| '_ ` _ \  / /  |_ \| '_ ` _ \|  _ \ / _` | '_ \| |/ /
| | | | | |/ /  ___) | | | | | | |_) | (_| | | | |   < 
|_| |_| |_/_/  |____/|_| |_| |_|____/ \__,_|_| |_|_|\_\
================================================================================
File: main.c
Author: mlem 
Description: main function :) 
GitHub: https://https://github.com/ml3m
================================================================================
*/
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
        printHeader();
        sayHello(name, surname);
        printUserAccounts(user_accounts);
        printMainMenu();

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
                saveAccountsToFile(accounts, &numAccounts);
                break;
            case 6:
                createAccount(accounts, &numAccounts);
            default:
                printFAIL(1);
        }
        if (choice != 5 && choice <=6){
            saveAccountsToFile(accounts, &numAccounts);
        } 
        
        printf("Press Enter to continue...");
        getchar();
        getchar();

    } while(choice != 5);
    return 0;
}
    
