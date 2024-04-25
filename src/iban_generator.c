/*
================================================================================
File: iban_generator.c
Author: mlem 
Description: the methods of generating a unique IBAN. 
GitHub: https://https://github.com/ml3m
================================================================================
*/

#include <stdlib.h>
#include <string.h>
#include <stdio.h>
#include <time.h>

#include "../include/bank.h"
#include "../include/cli.h"

char* generateIBAN() {
    srand(time(NULL)); // this line is cool

    int r = rand() % 999999;
    r += 11000000;

    char* string_iban = (char*)malloc(10 * sizeof(char));
    if (string_iban == NULL) {
        printFAIL(10); 
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

int isUniqueIBAN(const char* newIBAN, const Account* accounts, const int numAccounts) {
    for (int i = 0; i < numAccounts; ++i) {
        if (cmpIBANS(accounts[i].IBAN, newIBAN) == 0) {
            return 0; 
        }
    }
    return 1; 
}

char* generateUniqueIBAN(const Account* accounts, const int numAccounts) {
    char* newIBAN;
    do {
        newIBAN = generateIBAN();
    } while (!isUniqueIBAN(newIBAN, accounts, numAccounts));

    return newIBAN;
}
