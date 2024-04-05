/*
================================================================================
File: bank.c
Author: mlem 
Description: bank main functions that provide the core functionality. 
GitHub: https://https://github.com/ml3m
================================================================================
*/
#include "bank.h"
#include "cli.h"
#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <time.h>
#include "iban_generator.h"

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

/*printing and console clear work here*/
void createAccount(Account *accounts, int *numAccounts){
    
    int chosen_coin;
    char* uniqueIBAN = generateUniqueIBAN(accounts, *numAccounts);

    printf("\nAccount Creation\n");
    printf("Enter the required data down bellow:\n");
    printf("account name\n> "); 
    scanf("%s",accounts[*numAccounts].owner.name);
    printf("account surname\n> "); 
    scanf("%s",accounts[*numAccounts].owner.surname);

    system("clear");
    printCreateCurrency();

    scanf("%d", &chosen_coin);
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
    printf("data entered:\n");
    printf("name:%s\n",accounts[*numAccounts].owner.name);
    printf("surname:%s\n",accounts[*numAccounts].owner.surname);
    printf("coin:%d\n", accounts[*numAccounts].coin);
    printf("ammount:%f\n", accounts[*numAccounts].amount);
    */
    printPASS(5);
    free(uniqueIBAN);    
    saveAccountsToFile(accounts, numAccounts);
}

/* works properly, currency exchange ignored for now */ 
void editAccount(Account *accounts, const int numAccounts) {
    char iban[MAX_IBAN_LENGTH];

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
                    printf("1. Withdraw\n");
                    printf("2. Deposit\n");
                    int option;
                    int option_ammount;
                    scanf("%d", &option);
                    switch (option) {
                        case 1:
                            printf("Withdrawal ammount: ");
                            scanf("%d", &option_ammount);
                            accounts[i].amount -= option_ammount;
                            printPASS(1);
                            break;
                        case 2:
                            printf("Deposit ammount: ");
                            scanf("%d", &option_ammount);
                            accounts[i].amount += option_ammount;
                            printPASS(1);
                            break;
                        default:
                            //more handling here
                            printf("Fail?");
                            break;
                    }
                    break;
                case 5:
                    printf("Old IBAN: %s\n", accounts[i].IBAN);
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
                    printf("New IBAN: %s\n", accounts[i].IBAN);
                    break;
                
                default:
                    printFAIL(1);
            }
            return;
        }
    }
    printFAIL(2);
}

/*works properly, the enter key confirmation doesn't*/
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
           printf("AC: %s", accounts[i].IBAN);
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
    if(!found)printFAIL(11);
}

void saveAccountsToFile(const Account *accounts, const int *numAccounts) {
    FILE *file = fopen("accounts.txt", "w");
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
    FILE *file = fopen("accounts.txt", "r");
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


/*works properly, currency conversion wansn't implemented yet*/
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
                        // see accounts being compared i think I don't 
                        // remember when this was written D:
                        // printf("accounts[%d]=%s\n",i,accounts[j].IBAN);
                        // printf("dest_iban=%s",dest_iban);
                        if (strcmp(accounts[j].IBAN, dest_iban) == 0) {
                            successfully = 1;
                            accounts[i].amount -= amount;
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
