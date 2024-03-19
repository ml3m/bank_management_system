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

/*account Creation -> work in progress*/
void createAccount(Account *accounts, int *numAccounts){
    
    printf("\nAccount Creation\n");
    /*ask for data 
     * numAccounts+
     * save data to file maybe?
     * restriction of <= 5 max accounts per accounts[i].owner.name/surname
     * make sure the struct accounts[]. has more space -> segfag
     */
    printf("Enter the required data down bellow:\n");
    printf("account name> "); 
    int r = rand() % 999999;
    r += 11000000;
    printf("random gen number = %d\n",r);

    char string_iban[9]; 
    sprintf(string_iban, "%d", r);
    string_iban[0] = 'X';
    string_iban[1] = 'X';

    printf("stringwithlabel: %s\n", string_iban);
  


            /*must be a function */
// comparing ibans type XX123123 & 123123
// makes sure there isn't  identical IBANs in the data base.
    for (int i = 0; i< *numAccounts; i++) {
        for (int j = 2; accounts[i].IBAN[j]; j++) {
            if (string_iban[j] == accounts[i].IBAN[j]) {
                printf("equal:%c",string_iban[j]);
           }else {
                printf("equal found... generate new random IBAN");
                //end idk ..
           } 
        }
    
    }

/*_____good_part_____*/

    for (int i = 0; i < *numAccounts; ++i) {
        if (accounts->IBAN) {
            //idk 
            break;
        } 
    }

    printf("Chose your Account Currency: ");

    printf("1. RON\n");
    printf("2. EUR\n");
    printf("3. USD\n");
    printf("Enter your choice: ");

    int chosen_coin;
    scanf("%d", &chosen_coin);
    switch (chosen_coin) {
        case 1: 
            string_iban[0] = 'R';
            string_iban[1] = 'O';
            break;
        case 2:
            string_iban[0] = 'E';
            string_iban[1] = 'U';
            break;
        case 3:
            string_iban[0] = 'U';
            string_iban[1] = 'S';
            break;
        default:
            printf("failed to change iban after coin conversion\n");
            break;
    } 



}



/* works properly, coin change -> iban label change, currency conversion ignored for now */
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
                            printf("failed to change iban after coin conversion\n");
                    } 
                    printf("iban changed to:%s\n",accounts[i].IBAN);
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

/*works properly, the enter key confirmation doesn't
 * more testing required*/
void deleteAccount(Account *accounts, int *numAccounts) {
    char iban[MAX_IBAN_LENGTH];
    printf("Enter the IBAN of the account you want to delete: ");
    scanf("%s", iban);

    int i;
    for (i = 0; i < *numAccounts; ++i) {
        if (strcmp(iban, accounts[i].IBAN) == 0) {
            printf("Account %s found!\n", iban);
            if (accounts[i].amount != 0) {
                printf("ERROR: account has funds, remove funds and try again!\n");
                return;
            } else {
                char response;
                printf("Are you sure you want to delete account %s ? (y/n): ", iban);
                scanf(" %c", &response); 

                if (response == 'y' || response == 'Y' || response == '\n') {
                    printf("Deleting account...\n");
                    for (int j = i; j < *numAccounts - 1; ++j) {
                        accounts[j] = accounts[j + 1];
                    }
                    (*numAccounts)--;
                    printf("Account deleted successfully.\n");
                    return;
                } else {
                    printf("Account deletion canceled!\n");
                    return;
                }
            }
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
}

/*works properly*/
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

/*works properly*/
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

/*works properly*/
void loadUserAccounts(char  user_accounts[][9], int numAccounts, Account *accounts, char *sysuser, char *syssurname) {
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
void performTransaction(Account *accounts, int numAccounts, char *sysuser, char *syssurname) {
    printf("Performing transaction...\n");
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
                        printf("dubug111");
                        printf("accounts[%d]=%s\n",i,accounts[j].IBAN);
                        printf("dest_iban=%s",dest_iban);
                        if (strcmp(accounts[j].IBAN, dest_iban) == 0) {
                            successfully = 1;
                            accounts[i].amount -= amount;
                            accounts[j].amount += amount;
                            break;
                        }
                    }
               }else{
                   printf("Insuficient Funds...\n");
                   break;
               }
        } 
    }
    if (successfully) {
        printf("Transaction Successfully Processed!\n");
    }else {
        printf("Destination IBAN doesn't exit!\n");
    }
}
