/*
================================================================================
File: bank.h
Author: mlem 
Description: bank header, where the main structs are bedded. 
GitHub: https://https://github.com/ml3m
================================================================================
*/
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

void login(const char *name, const char *surname,const Account *accounts, const int numAccounts);
void createAccount(Account *accounts, int *numAccounts);
void editAccount(Account *accounts, const int numAccounts);
void deleteAccount(Account *accounts, int *numAccounts);
void viewAccount(const Account *accounts, const int numAccounts);
void saveAccountsToFile(const Account *accounts, const int *numAccounts);
int loadAccountsFromFile(Account *accounts);
void loadUserAccounts(char user_accounts[][9], const int numAccounts, const Account *accounts, const char *sysuser, const char *syssurname);
void performTransaction(Account *accounts, const int numAccounts, const char *sysuser, const char *syssurname);

#endif 
