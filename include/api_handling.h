#ifndef CURRENCY_H
#define CURRENCY_H

#include <stdio.h>
#include <curl/curl.h>
#include "cJSON.h"

typedef struct {
    double exEUR;
    double exRON;
    double exRONtoexEUR ,exRONtoexUSD, exEURtoexRON, exEURtoexUSD, exUSDtoexRON ,exUSDtoexEUR;
} CurrencyRates;

CurrencyRates fetch_currency_rates();
void print_test_api_handlingC();

#endif /* CURRENCY_H */
