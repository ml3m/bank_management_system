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
#include <string.h>
#include <stdlib.h>
#include <stdio.h>

#include "../include/api_handling.h"
#include "../include/bank.h"
#include "../include/cli.h"

int main(int argc, char *argv[]) {
    
    if (argc == 1 || argc >4 || argc == 3){
        printf("Usage1: %s -login/-l [NAME] [SURNAME]\n", argv[0]);
        printf("Usage2: %s -create/-c\n", argv[0]);
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
        if (strcmp(argv[1],"-l")==0 || strcmp(argv[1],"-login")==0) {
            name = argv[2];
            surname = argv[3];
        }else {
            printf("Usage1: %s -login/-l [NAME] [SURNAME]\n", argv[0]);
            printf("Usage2: %s -create/-c\n", argv[0]);
            return 1;
        }
    }

    /********** just some very serious testing here *************************
     *
     * api can be accesed via rates struct - > CurrencyRates and the fetch function accordingly
     * 
     *
    // hahahhahhahahahahah
    //print_test_api_handlingC();
    //preparing_exCOIN();
    
    CurrencyRates rates = fetch_currency_rates();

    printf("exUSD to exEUR rate: %.10f\n", rates.exEUR);

    // Print test API results
    //print_test_api_handlingC();
    //
    CurrencyRates rates
    return 0;

    CurrencyRates rates = fetch_currency_rates();
    printf("exUSD to exEUR rate: %.10f\n", rates.exUSDtoexEUR);
    return 0;
    */ /********** just some very serious testing here *************************/
    

    login(name, surname, accounts, numAccounts);
    int choice;
    do {
        loadUserAccounts(user_accounts, numAccounts, accounts, name, surname);
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
                createAccount(accounts, &numAccounts);
                break;
            case 6:
                //working accordingly
                print_test_api_handlingC();
                break;
            case 7:
                printf("Exiting...\n");
                saveAccountsToFile(accounts, &numAccounts);
                break;
            default:
                printFAIL(1);
        }
        if (choice != 7 && choice <7){
            saveAccountsToFile(accounts, &numAccounts);
        } 
        
        printf("Press Enter to continue...");
        getchar();
        getchar();

    } while(choice != 7);
    return 0;
}
    
