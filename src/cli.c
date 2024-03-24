/*
, ================================================================================
File: cli.c
Author: mlem 
Description: this file provides the required cli printing.
GitHub: https://https://github.com/ml3m
================================================================================
*/
#include "cli.h"
#include <stdio.h>

void printUserAccounts(const char user_accounts[][9]){
    printf(ANSI_BOLD_START "Owned Accounts:\n\n" ANSI_COLOR_RESET);
    for (int i =0;user_accounts[i][0]!= '\0'; i++) {
        printf("\t%dAC:", i); 
        printf(ANSI_UNDERLINE_START"%s\n"ANSI_COLOR_RESET, user_accounts[i]); 
    }
}

void printHeader() {
    //idea: change stars with equal type symbol
    printf(ANSI_BOLD_START "\t=============================================\n");
    //printf(ANSI_BOLD_START ANSI_COLOR_BLUE "\t*********************************************\n");
    printf("\t|          "ANSI_COLOR_RESET);
    printf(ANSI_COLOR_MAGENTA ANSI_BOLD_START "MlemBank - Banking App"ANSI_COLOR_RESET);
    printf(ANSI_BOLD_START "           |\n");
    printf("\t=============================================\n" ANSI_COLOR_RESET);
    //printf("\t*********************************************\n" ANSI_COLOR_RESET);
}

void sayHello(const char *name, const char *surname){
    printf(ANSI_COLOR_MAGENTA"\nWelcome "ANSI_COLOR_RESET);
    printf(ANSI_COLOR_MAGENTA ANSI_BOLD_START"%s %s !\n"ANSI_COLOR_RESET, name, surname);
}

void printMainMenu(){
    printf(ANSI_BOLD_START"\n1. Edit Account\n");
    printf("2. Delete Account\n");
    printf("3. View Account\n");
    printf("4. Perform Transaction\n");
    printf("5. Exit\n");
    printf("6. Create Account\n"ANSI_COLOR_RESET);
    printf(ANSI_COLOR_MAGENTA"Enter your choice: "ANSI_COLOR_RESET);
}

void printEditAccount(const char *iban){
    printf(ANSI_COLOR_BLACK GREEN_BACKGROUND "Account found "ANSI_COLOR_RESET);
    printf("Editing account: ");
    printf(ANSI_BOLD_START "%s\n", iban);
    printf("\n1. Change owner's name\n");
    printf("2. Change owner's surname\n");
    printf("3. Change currency type\n");
    printf("4. Change currency ammount\n");
    printf("5. Renew IBAN\n"ANSI_COLOR_RESET);
    printf(ANSI_COLOR_MAGENTA"Enter your choice: "ANSI_COLOR_RESET);
}

void editHeader(){
    printf("Enter the ");
    printf(ANSI_ITALIC_START ANSI_BOLD_START "IBAN "ANSI_COLOR_RESET);
    printf("of the account you want to edit: ");
}

void printFAIL(const int choice){
    switch (choice) {
        case 0:
            printf(ANSI_COLOR_BLACK RED_BACKGROUND "Failed to change iban after coin conversion\n"ANSI_COLOR_RESET);
            break;
        case 1:
            printf(ANSI_COLOR_BLACK RED_BACKGROUND "Invalid choice.\n"ANSI_COLOR_RESET);
            break;
        case 2:
            printf(ANSI_COLOR_BLACK RED_BACKGROUND "Account not found with the given IBAN.\n"ANSI_COLOR_RESET);
            break;
        case 3:
            printf(ANSI_COLOR_BLACK RED_BACKGROUND "Destination IBAN doesn't exit!\n" ANSI_COLOR_RESET);
            break;
        case 4:
            printf(ANSI_COLOR_BLACK RED_BACKGROUND "Insuficient Funds...\n" ANSI_COLOR_RESET);
            break;
        case 5:
            printf(ANSI_COLOR_BLACK RED_BACKGROUND "Error opening file for reading.\n" ANSI_COLOR_RESET);
            break;
        case 6:
            printf(ANSI_COLOR_BLACK RED_BACKGROUND "Error opening file for writing.\n" ANSI_COLOR_RESET);
            break;
        case 7:
            printf(ANSI_COLOR_BLACK RED_BACKGROUND "Account deletion canceled!\n" ANSI_COLOR_RESET);
            break;
        case 8:
            printf(ANSI_COLOR_BLACK RED_BACKGROUND "ERROR: account has funds, remove funds and try again!\n" ANSI_COLOR_RESET);
            break;
        case 9:
            printf(ANSI_COLOR_BLACK RED_BACKGROUND "Login failed. Name and Surname not found in data base.\n" ANSI_COLOR_RESET);
            break;
        case 10:
            printf(ANSI_COLOR_BLACK RED_BACKGROUND "Memory allocation failed.\n" ANSI_COLOR_RESET);
            break;
    }
}

void printPASS(const int choice){
    switch (choice) {
        case 0:
            printf(ANSI_COLOR_BLACK GREEN_BACKGROUND "Currency type updated successfully!\n"ANSI_COLOR_RESET);
            break;
        case 1:
            printf(ANSI_COLOR_BLACK GREEN_BACKGROUND "Transaction Successfully Processed!\n"ANSI_COLOR_RESET);
            break;
        case 2:
            printf(ANSI_COLOR_BLACK GREEN_BACKGROUND "Account deleted successfully!\n" ANSI_COLOR_RESET);
            break;
        case 3:
            printf(ANSI_COLOR_BLACK GREEN_BACKGROUND "Owner's name updated successfully!\n" ANSI_COLOR_RESET);
            break;
        case 4:
            printf(ANSI_COLOR_BLACK GREEN_BACKGROUND "Owner's surname updated successfully!\n" ANSI_COLOR_RESET);
            break;
    }
}

void printChangeCurrency(){
    printf("Select new currency type:\n");
    printf(ANSI_BOLD_START"1. RON\n");
    printf("2. EUR\n");
    printf("3. USD\n"ANSI_COLOR_RESET);
    printf("Enter your choice: ");
}

void printCreateCurrency(){
    printf("Chose your Account Currency:\n");
    printf(ANSI_BOLD_START"1. RON\n");
    printf("2. EUR\n");
    printf("3. USD\n"ANSI_COLOR_RESET);
    printf("Enter your choice: ");
}

void printDeleteAccountHeader(){
    printf("Enter the ");
    printf(ANSI_BOLD_START"IBAN "ANSI_COLOR_RESET);
    printf("of the account you want to delete: ");
}
