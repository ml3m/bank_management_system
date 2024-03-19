#ifndef BANK_H 
#define BANK_H

#define RON 0
#define EUR 1
#define USD 2

#define MAX_USER_ACCOUNTS 5
#define MAX_NAME_LENGTH 50
#define MAX_ACCOUNTS 100
#define MAX_IBAN_LENGTH 20

typedef struct {
    char name[MAX_NAME_LENGTH];
    char surname[MAX_NAME_LENGTH];
} Person;

typedef struct {
    char IBAN[MAX_IBAN_LENGTH];
    Person owner;
    int coin;
    double amount;
} Account;

int loadAccountsFromFile(Account *accounts);
void saveAccountsToFile(Account *accounts, int numAccounts);
void login(char *name, char *surname, Account *accounts, int numAccounts);
void editAccount(Account *accounts, int numAccounts);
void deleteAccount(Account *accounts, int *numAccounts);
void viewAccount(Account *accounts, int numAccounts);
void performTransaction(Account *accounts, int numAccounts);
void loadUserAccounts(char  user_accounts[][9], int numAccounts, Account *accounts, char *sysuser, char *syssurname);
#endif /* BANK_H */
