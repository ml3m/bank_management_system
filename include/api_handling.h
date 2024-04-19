#ifndef API_HANDLING_H
#define API_HANDLING_H
#include <stdio.h>

typedef struct {
    double exEUR;
    double exRON;
} CurrencyRates;

CurrencyRates fetch_currency_rates();
void print_test_api_handlingC();
#endif /* API_HANDLING_H */
