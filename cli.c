/*the command line interface ui goes here*/
#include "cli.h"
#include <stdio.h>

void printUserAccounts(char user_accounts[][9]){
    for (int i =0;user_accounts[i][0]!= '\0'; i++) {
        printf("\t%dAC:%s\n",i,user_accounts[i]); 
    }
}

void printMainMenu(char *name, char *surname){
    printf("\nWelcome %s %s !\n", name, surname);
    printf("\nBank Management System Menu:\n");
    printf("1. Edit Account\n");
    printf("2. Delete Account\n");
    printf("3. View Account\n");
    printf("4. Perform Transaction\n");
    printf("5. Exit\n");
    printf("6. Create Account\n");
    printf("Enter your choice: ");
}

void printEditAccount(char *iban){
    printf("Account found. Editing account: %s\n", iban);
    printf("1. Change owner's name\n");
    printf("2. Change owner's surname\n");
    printf("3. Change currency type\n");
    printf("Enter your choice: ");
}
