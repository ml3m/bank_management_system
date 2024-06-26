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

int cmpIBANS(const char* iban1, const char* iban2);
int isUniqueIBAN(const char* newIBAN, const Account* accounts, const int numAccounts);
char* generateIBAN();
char* generateUniqueIBAN(const Account* accounts, const int numAccounts);

#endif 
