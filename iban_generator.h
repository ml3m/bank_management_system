/*
================================================================================
File: iban_generator.h
Author: mlem 
GitHub: https://https://github.com/ml3m
================================================================================
*/
#include "bank.h"
#ifndef IBAN_GENERATOR 
#define IBAN_GENERATOR

char* generateIBAN();
int cmpIBANS(const char* iban1, const char* iban2);
int isUniqueIBAN(const char* newIBAN, Account* accounts, int numAccounts);
char* generateUniqueIBAN(Account* accounts, int numAccounts);

#endif 
