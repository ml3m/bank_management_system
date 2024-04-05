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
#include <string.h>

int main(int argc, char *argv[]) {
    
    if (argc == 1 || argc >3){
        printf("Usage1: %s [NAME] [SURNAME]\n", argv[0]);
        printf("Usage2: %s -create/-c [NAME] [SURNAME]\n", argv[0]);
        return 1;
    } 

    char user_accounts[MAX_USER_ACCOUNTS][MAX_IBAN_LENGTH];
    Account accounts[MAX_ACCOUNTS];
    int numAccounts = loadAccountsFromFile(accounts); 
    char *name, *surname;
    int new_account_login_marker = 0;
    char *create_flag = argv[1];
    
    // -c / -create flag handling 
    if ((strcmp(create_flag, "-c")== 0 || strcmp(create_flag, "-create")==0)&& argc == 2) {
        new_account_login_marker = 1;
        createAccount(accounts, &numAccounts);
        printf("login in.. with created account...\n");
        char cli_user_choice;
        printf("do you want to log in with the created account? (y/n)\n>");
        scanf(" %c", &cli_user_choice);
        if(cli_user_choice == 'y' || cli_user_choice == 'Y'){
            printf("log in behaviour\n");
        }else {
            printf("finished!...\n");
            return 1;
        }
    }

    if(new_account_login_marker){
        name = accounts[numAccounts -1].owner.name;
        surname= accounts[numAccounts -1].owner.surname;

    }else {
        name = argv[1];
        surname = argv[2];
    }


    login(name, surname, accounts, numAccounts);
    int choice;
    do {
        loadUserAccounts(user_accounts, numAccounts, accounts, name, surname);
        system("clear");
        printHeader();
        printf("hello_debug\n");
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
                createAccount(accounts, &numAccounts);
            case 6:
                printf("Exiting...\n");
                saveAccountsToFile(accounts, &numAccounts);
                break;
            default:
                printFAIL(1);
        }
        if (choice != 6 && choice <6){
            saveAccountsToFile(accounts, &numAccounts);
        } 
        
        printf("Press Enter to continue...");
        getchar();
        getchar();

    } while(choice != 6);
    return 0;
}
    
