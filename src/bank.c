/*
================================================================================
File: bank.c
Author: mlem 
Description: bank main functions that provide the core functionality. 
GitHub: https://https://github.com/ml3m
================================================================================
*/
#include <stdlib.h>
#include <string.h>
#include <stdio.h>
#include <time.h>

#include "../include/iban_generator.h"
#include "../include/api_handling.h"
#include "../include/paths.h"
#include "../include/bank.h"
#include "../include/cli.h"


/*works like a charm*/
void login(const char *name, const char *surname, const Account *accounts, const int numAccounts) {
    for (int i = 0; i< numAccounts; ++i){
        if (strcmp(name, accounts[i].owner.name) == 0 && 
            strcmp(surname, accounts[i].owner.surname) == 0){
            printf("Logged in as %s %s\n", name, surname);
            return;
        }
    }
    printFAIL(9);
    exit(1);
}

void createAccount(Account *accounts, int *numAccounts){
    
    int chosen_coin;
    char* uniqueIBAN = generateUniqueIBAN(accounts, *numAccounts);

    printf("\nAccount Creation\n");
    printf("Enter the required data down bellow:\n");
    printf("account name\n> "); 
    scanf("%s",accounts[*numAccounts].owner.name);
    printf("account surname\n> "); 
    scanf("%s",accounts[*numAccounts].owner.surname);
    printCreateCurrency();
    scanf("%d", &chosen_coin);

    system("clear");
    

    accounts[*numAccounts].coin = chosen_coin - 1;
    accounts[*numAccounts].amount = 0.00;
    
    switch (chosen_coin) {
        case 1: 
            uniqueIBAN[0] = 'R';
            uniqueIBAN[1] = 'O';
            break;
        case 2:
            uniqueIBAN[0] = 'E';
            uniqueIBAN[1] = 'U';
            break;
        case 3:
            uniqueIBAN[0] = 'U';
            uniqueIBAN[1] = 'S';
            break;
        default:
            printFAIL(0);
            break;
    } 

    /* printing is messed up here*/ 
    system("clear");
    strcpy(accounts[*numAccounts].IBAN, uniqueIBAN);
    printf("iban: %s",uniqueIBAN);
    (*numAccounts)++;
    /*
    printf("+-----------------------------------------+\n");
    printf("|             Bank Account Details        |\n");
    printf("+-----------------------------------------+\n");
    printf("| Owner's Name:          %-20s |\n", accounts[*numAccounts].owner.name);
    printf("| Owner's Surname:       %-20s |\n", accounts[*numAccounts].owner.surname);
    printf("| Account Balance (Coins): %-14d |\n", accounts[*numAccounts].coin);
    printf("| Account Balance (Amount): %.2f          |\n", accounts[*numAccounts].amount);
    printf("+-----------------------------------------+\n");
    */
    printPASS(5);
    free(uniqueIBAN);    
    saveAccountsToFile(accounts, numAccounts);
}

/* works properly, currency exchange UPDATE in on*/ 
void editAccount(Account *accounts, const int numAccounts) {
    char iban[MAX_IBAN_LENGTH];

    /***********fetch rates here************/
    CurrencyRates rates = fetch_currency_rates();

    editHeader();
    scanf("%s", iban);

    int i;
    int choice;
    for (i = 0; i < numAccounts; ++i) {
        if (strcmp(iban, accounts[i].IBAN) == 0) {
            printEditAccount(iban); 
            scanf("%d", &choice);

            switch (choice) {
                case 1:
                    printf("Enter new name: ");
                    scanf("%s", accounts[i].owner.name);
                    printPASS(3);
                    break;
                case 2:
                    printf("Enter new surname: ");
                    scanf("%s", accounts[i].owner.surname);
                    printPASS(4);
                    break;
                case 3:
                    printChangeCurrency();
                    int changed_coin;
                    scanf("%d", &changed_coin);
                    switch (accounts[i].coin) {
                        case 0:
                            //changing from ron
                            if (changed_coin - 1 == accounts[i].coin) {
                                break;//nothing happens ron ron 
                            }
                            if (changed_coin - 1 == 1) {
                                //exRONtoexEUR;
                                accounts[i].amount *= rates.exRONtoexEUR;
                                break;
                            }
                            if (changed_coin - 1 == 2){
                                //exRONtoexUSD;
                                accounts[i].amount *= rates.exRONtoexUSD;
                                break;
                            }
                            break;
                        case 1:
                            if (changed_coin - 1 == accounts[i].coin) {
                                break;//nothing happens eur eur
                            }
                            if (changed_coin - 1 == 0) {
                                //exEURtoexRON;
                                accounts[i].amount *= rates.exEURtoexRON;
                                break;
                            }
                            if (changed_coin - 1 == 2){
                                //exEURtoexUSD;
                                accounts[i].amount *= rates.exEURtoexUSD;
                                break;
                            }
                            break;
                        case 2:
                            if (changed_coin - 1 == accounts[i].coin) {
                                break;//nothing happens usd usd 
                            }
                            if (changed_coin - 1 == 1) {
                                //exUSDtoexEUR;
                                accounts[i].amount *= rates.exUSDtoexEUR;
                                break;
                            }
                            if (changed_coin - 1 == 0){
                                //exUSDtoexRON;
                                accounts[i].amount *= rates.exUSDtoexRON;
                                break;
                            }
                            break;
                    }
                    accounts[i].coin = changed_coin - 1;

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
                            printFAIL(0);
                    } 
                    printPASS(0);
                    break;
                case 4:
                    printf("Select balance option:\n");
                    printf("┌───────────────┐\n");
                    printf("│ 1. Withdraw   │\n");
                    printf("│ 2. Deposit    │\n");
                    printf("└───────────────┘\n\n");
                    int option;
                    int option_amount;
                    scanf("%d", &option);
                    switch (option) {
                        case 1:
                            printf("Withdrawal amount: ");
                            scanf("%d", &option_amount);
                            accounts[i].amount -= option_amount;
                            printPASS(1);
                            break;
                        case 2:
                            printf("Deposit amount: ");
                            scanf("%d", &option_amount);
                            accounts[i].amount += option_amount;
                            printPASS(1);
                            break;
                        default:
                            //more handling here
                            printf("Fail?");
                            break;
                    }
                    break;
                case 5:
                    printf("\n\nOld IBAN: %s\n", accounts[i].IBAN);
                    char *newuniqueIBAN = generateUniqueIBAN(accounts, numAccounts);
                    printf("New IBAN generating...\n");
                    printf("generated IBAN: %s\n", newuniqueIBAN);
                    strcpy(accounts[i].IBAN, newuniqueIBAN);
                    if (accounts[i].coin == 0) {
                        accounts[i].IBAN[0]= 'R';
                        accounts[i].IBAN[1]= 'O';
                    }
                    if (accounts[i].coin == 1) {
                        accounts[i].IBAN[0]= 'E';
                        accounts[i].IBAN[1]= 'U';
                    }
                    if (accounts[i].coin == 2) {
                        accounts[i].IBAN[0]= 'U';
                        accounts[i].IBAN[1]= 'S';
                    }
                    printf("New IBAN: ");
                    printf(ANSI_BOLD_START"%s\n"ANSI_COLOR_RESET, accounts[i].IBAN);
                    break;
                
                default:
                    printFAIL(1);
            }
            return;
        }
    }
    printFAIL(2);
}

/*works properly, the enter key confirmation doesn't idk how to fix it*/
void deleteAccount(Account *accounts, int *numAccounts) {
    char iban[MAX_IBAN_LENGTH];
    printDeleteAccountHeader();
    scanf("%s", iban);

    int i;
    for (i = 0; i < *numAccounts; ++i) {
        if (strcmp(iban, accounts[i].IBAN) == 0) {
            printf("Account %s found!\n", iban);
            if (accounts[i].amount != 0) {
                printFAIL(8);
                return;
            } else {
                char response;
                printf("Are you sure you want to delete account %s ? (y/n): ", iban);
                scanf(" %c", &response); 

                if (response == 'y' || response == 'Y' || response == '\n') {
                    for (int j = i; j < *numAccounts - 1; ++j) {
                        accounts[j] = accounts[j + 1];
                    }
                    (*numAccounts)--;
                    printPASS(2);
                    return;
                } else {
                    printFAIL(7);
                    return;
                }
            }
        }
    }
    printFAIL(2);
}

void viewAccount(const Account *accounts, const int numAccounts) {
    char iban[MAX_IBAN_LENGTH];
    printf("Enter the IBAN of account you want to see information: ");
    scanf("%s", iban);
    int found = 0;

    for (int i = 0; i< numAccounts; i++) {
        if(strcmp(accounts[i].IBAN,iban)== 0){
           found = 1; 

         printf("\n┌──────────────────────────┐\n");
           printf("│     AC: %s                    \n", accounts[i].IBAN);
           printf("│     >Account Details:         \n");
           printf("│     IBAN: %s                  \n", accounts[i].IBAN);
           printf("│     Owner: %s %s              \n", accounts[i].owner.name, accounts[i].owner.surname);
           printf("│     Amount: %.2f              \n", accounts[i].amount);
           switch(accounts[i].coin) {
               case RON:
           printf("│     Currency: RON             \n");
                   break;
               case EUR:
           printf("│     Currency: EUR             \n");
                   break;
               case USD:
           printf("│     Currency: USD             \n");
                   break;
               default:
           printf("│     Currency: Unknown         \n");
           }
         printf  ("└──────────────────────────┘\n\n");
        }
    }
    if(!found)printFAIL(11);
}

void saveAccountsToFile(const Account *accounts, const int *numAccounts) {
    FILE *file = fopen(ACCOUNTS_FILE_PATH, "w");
    if (file == NULL) {
        printFAIL(6); 
        return;
    }

    for (int i = 0; i < *numAccounts; ++i) {
        fprintf(file, "%s %s %s %d %.2f\n", 
                accounts[i].IBAN, 
                accounts[i].owner.name, 
                accounts[i].owner.surname, 
                accounts[i].coin, 
                accounts[i].amount
        );
    }

    fclose(file);
}

int loadAccountsFromFile(Account *accounts) {
    FILE *file = fopen(ACCOUNTS_FILE_PATH, "r");
    if (file == NULL) {
        printFAIL(5);
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

void loadUserAccounts(char user_accounts[][9], 
                      const int numAccounts, 
                      const Account *accounts, 
                      const char *sysuser, 
                      const char *syssurname) {
    int k = 0;
    for (int i = 0; i < numAccounts; i++) {
        if (strcmp(accounts[i].owner.name, sysuser) == 0 && 
            strcmp(accounts[i].owner.surname, syssurname) == 0) {
                printf("account found: %s\n", accounts[i].IBAN);
                strcpy(user_accounts[k], accounts[i].IBAN); 
                k++;
        }
    }
    user_accounts[k][0] = '\0'; 
}


/*works properly, currency conversion wansn't implemented YETTT*/
void performTransaction(
        Account *accounts, 
        const int numAccounts, 
        const char *sysuser, 
        const char *syssurname)
{
    float amount;
    char dest_iban[MAX_IBAN_LENGTH]; 
    char source_iban[MAX_IBAN_LENGTH]; 
    int successfully = 0;

    // in work !
    CurrencyRates rates = fetch_currency_rates();

    printf("Enter source account IBAN: ");
    scanf("%s", source_iban);
    printf("Enter amount to transfer: ");
    scanf("%f", &amount);
    printf("Enter destination IBAN: ");
    scanf("%s", dest_iban);
    printf("you entered iban: %s\n", dest_iban);

    for (int i = 0; i< numAccounts; i++) {
        if (successfully) {
            break;
        }
        if (strcmp(accounts[i].IBAN, source_iban) == 0 && 
                strcmp(accounts[i].owner.name, sysuser) == 0 &&
                strcmp(accounts[i].owner.surname, syssurname) == 0){
            if (accounts[i].amount >= amount) {
                for (int j = 0; j< numAccounts; j++) {
                    /*********************** inplement here transactions between different coins exchange ***********************/
                    /*if (strcmp(accounts[j].IBAN, dest_iban) == 0) {
                      successfully = 1;
                      if (accounts[i].coin == accounts[j].coin) {
                      accounts[i].amount -= amount;
                      accounts[j].amount += amount;
                      }

                      break;
                      }*/
                    if (strcmp(accounts[j].IBAN, dest_iban) == 0) {
                        successfully = 1;
                        printf("Ammount: %f was converted to:", amount);
                        // Check if currency conversion is needed
                        int source_coin = accounts[i].coin;
                        int dest_coin = accounts[j].coin;
                        double used_rate;
                        /*for beauty info printing*/

                        char source_coin_symbol[4];
                        char destination_coin_symbol[4];

                        accounts[i].amount -= amount;

                        // not touching this 
                        switch (source_coin) {
                            case 0:
                                strcpy(source_coin_symbol,"RON");
                                switch (dest_coin) {
                                    case 1:
                                        strcpy(destination_coin_symbol,"EUR");
                                        // Convert from RON to EUR
                                        amount *= rates.exRONtoexEUR;
                                        used_rate = rates.exRONtoexEUR;
                                        break;
                                    case 2:
                                        strcpy(destination_coin_symbol,"USD");
                                        // Convert from RON to USD
                                        amount *= rates.exRONtoexUSD;
                                        used_rate = rates.exRONtoexUSD;
                                        break;
                                    default:
                                        strcpy(destination_coin_symbol,"RON");
                                        break;
                                }
                                break;
                            case 1:
                                strcpy(source_coin_symbol,"EUR");
                                switch (dest_coin) {
                                    case 0:
                                        strcpy(destination_coin_symbol,"RON");
                                        // Convert from EUR to RON
                                        amount *= rates.exEURtoexRON;
                                        used_rate = rates.exEURtoexRON;
                                        break;
                                    case 2:
                                        strcpy(destination_coin_symbol,"USD");
                                        // Convert from EUR to USD
                                        amount *= rates.exEURtoexUSD;
                                        used_rate = rates.exEURtoexUSD;
                                        break;
                                    default:
                                        strcpy(destination_coin_symbol,"EUR");
                                        break;
                                }
                                break;
                            case 2:
                                strcpy(source_coin_symbol,"USD");
                                switch (dest_coin) {
                                    case 0:
                                        strcpy(destination_coin_symbol,"RON");
                                        // Convert from USD to RON
                                        amount *= rates.exUSDtoexRON;
                                        used_rate = rates.exUSDtoexRON;
                                        break;
                                    case 1:
                                        strcpy(destination_coin_symbol,"EUR");
                                        // Convert from USD to EUR
                                        amount *= rates.exUSDtoexEUR;
                                        used_rate = rates.exUSDtoexEUR;
                                        break;
                                    default:
                                        strcpy(destination_coin_symbol,"USD");
                                        break;
                                }
                                break;
                            default:
                                // Handle other cases if necessary
                                break;
                        }
                        printf("%f\n", amount);
                        printf("Using the following Exchange Rate: \n%s/%s  = ",source_coin_symbol, destination_coin_symbol);
                        printf("%.6f\n",used_rate);

                        accounts[j].amount += amount;
                        break;
                    }
                }
            }else{
                printFAIL(4);
                break;
            }
        } 
    }

    if (successfully) { printPASS(1);
    }else { printFAIL(3);}
}
