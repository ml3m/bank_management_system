/*
================================================================================
File: cli.h
Author: mlem 
Description: cli header with some consts for cli beautify. 
GitHub: https://https://github.com/ml3m
================================================================================
*/
#ifndef CLI_H 
#define CLI_H

#define ANSI_COLOR_RED     "\x1b[31m"
#define ANSI_COLOR_GREEN   "\x1b[32m"
#define ANSI_COLOR_YELLOW  "\x1b[33m"
#define ANSI_COLOR_BLUE    "\x1b[34m"
#define ANSI_COLOR_MAGENTA "\x1b[35m"
#define ANSI_COLOR_CYAN    "\x1b[36m"
#define ANSI_COLOR_RESET   "\x1b[0m" 
#define ANSI_COLOR_BLACK   "\x1b[30m"

#define ANSI_UNDERLINE_START "\x1b[4m"
#define ANSI_ITALIC_START "\x1b[3m"  
#define ANSI_BOLD_START "\x1b[1m"

#define GREEN_BACKGROUND "\x1b[42m"
#define RED_BACKGROUND "\x1b[41m"

void printUserAccounts(const char user_accounts[][9]);
void printEditAccount(const char *iban);
void sayHello(const char *name, const char *surname);
void printFAIL(const int choice);
void printPASS(const int choice);
void printHeader();
void printMainMenu();
void editHeader();
void printChangeCurrency();
void printCreateCurrency();
void printDeleteAccountHeader();

#endif
