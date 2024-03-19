#include "bank.h"
#include "cli.h"
#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <time.h>

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

/* functions to be moved to generative_engine.c*/
char* generateIBAN() {
    srand(time(NULL));

    int r = rand() % 999999;
    r += 11000000;

    char* string_iban = (char*)malloc(10 * sizeof(char));
    if (string_iban == NULL) {
        printf("Memory allocation failed.\n");
        exit(1);
    }

    sprintf(string_iban, "%d", r);
    string_iban[0] = 'X';
    string_iban[1] = 'X';

    return string_iban;
}

int cmpIBANS(const char* iban1, const char* iban2) {
    return strncmp(iban1 + 2, iban2, strlen(iban2));
}

int isUniqueIBAN(const char* newIBAN, Account* accounts, int numAccounts) {
    for (int i = 0; i < numAccounts; ++i) {
        if (cmpIBANS(accounts[i].IBAN, newIBAN) == 0) {
            return 0; 
        }
    }
    return 1; 
}

char* generateUniqueIBAN(Account* accounts, int numAccounts) {
    char* newIBAN;
    do {
        newIBAN = generateIBAN();
    } while (!isUniqueIBAN(newIBAN, accounts, numAccounts));
    return newIBAN;
}

void createAccount(Account *accounts, int *numAccounts){
    
    char *name, *surname;
    int chosen_coin;
    char* uniqueIBAN = generateUniqueIBAN(accounts, *numAccounts);
    //debug
    printf("uniqueIBAN_generated: %s\n",uniqueIBAN);

    printf("\nAccount Creation\n");
    printf("Enter the required data down bellow:\n");
    printf("account name\n> "); 
    scanf("%s",accounts[*numAccounts].owner.name);
    printf("account surname\n> "); 
    scanf("%s",accounts[*numAccounts].owner.surname);

    printf("Chose your Account Currency:\n");
    printf("1. RON\n");
    printf("2. EUR\n");
    printf("3. USD\n");
    printf("Enter your choice: ");

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
            printf("failed to change iban after coin conversion\n");
            break;
    } 

    strcpy(accounts[*numAccounts].IBAN, uniqueIBAN);
    printf("iban: %s",uniqueIBAN);
    (*numAccounts)++;
    printf("data entered:\n");
    printf("name:%s\n",accounts[*numAccounts].owner.name);
    printf("surname:%s\n",accounts[*numAccounts].owner.surname);
    printf("coin:%d\n", accounts[*numAccounts].coin);
    printf("ammount:%f\n", accounts[*numAccounts].amount);
    free(uniqueIBAN);    
    saveAccountsToFile(accounts, numAccounts);
}


/* works properly, coin change -> iban label change, currency conversion ignored for now 
 #ToDo : feature: modify ammount, replace IBAN(random generate verify existance)*/
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
                            printf("failed to change iban after coin conversion\n");
                    } 
                    printf("iban changed to:%s\n",accounts[i].IBAN);
                    printf("Currency type updated successfully.\n");
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
                            break;
                        case 2:
                            printf("Deposit ammount: ");
                            scanf("%d", &option_ammount);
                            accounts[i].amount += option_ammount;
                            break;
                        default:
                            printf("Fail?");
                            break;
                    }

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
void saveAccountsToFile(Account *accounts, int *numAccounts) {
    FILE *file = fopen("accounts.txt", "w");
    if (file == NULL) {
        printf("Error opening file for writing.\n");
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
