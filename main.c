#include "bank.h"
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

    // CLI args
    char *name = argv[1];
    char *surname = argv[2];
    
    loadUserAccounts(user_accounts, numAccounts, accounts, name, surname);
    login(name, surname, accounts, numAccounts);


//    for (int i =0;user_accounts[i][0]!= '\0'; i++) {
//        printf("\t%dAC:%s\n",i,user_accounts[i]); 
//    }
//    printf("MAN:%s",user_accounts[0]);
//    printf("MAN:%s",user_accounts[1]);
//
    int choice;
    do {
        // clear terminal
// messaged out for debugging purposes
        system("clear");

        for (int i =0;user_accounts[i][0]!= '\0'; i++) {
            printf("\t%dAC:%s\n",i,user_accounts[i]); 
        }
        printf("\nWelcome %s %s !\n", name, surname);
        printf("\nBank Management System Menu:\n");
        printf("1. Edit Account\n");
        printf("2. Delete Account\n");
        printf("3. View Account\n");
        printf("4. Perform Transaction\n");
        printf("5. Exit\n");
        printf("Enter your choice: ");
        scanf("%d", &choice);
        switch(choice) {
            case 1:
                editAccount(accounts, numAccounts);
                break;
            case 2:
                deleteAccount(accounts, numAccounts);
                break;
            case 3:
                viewAccount(accounts, numAccounts);
                break;
            case 4:
                performTransaction(accounts, numAccounts);
                break;
            case 5:
                printf("Exiting...\n");
                break;
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
