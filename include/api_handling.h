#ifndef CURRENCY_H
#define CURRENCY_H

// Include necessary headers
#include <stdio.h>
#include <curl/curl.h>
#include "cJSON.h"

// Struct to hold currency rates
typedef struct {
    double exEUR;
    double exRON;
    double exRONtoexEUR ,exRONtoexUSD, exEURtoexRON, exEURtoexUSD, exUSDtoexRON ,exUSDtoexEUR;
} CurrencyRates;

// Function prototypes
CurrencyRates fetch_currency_rates();
void print_test_api_handlingC();

#endif /* CURRENCY_H */
