#include <curl/curl.h>
#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <time.h>

#include "../include/api_handling.h"
#include "../include/cJSON.h"


// HTTP  
size_t write_callback(void *ptr, size_t size, size_t nmemb, char *data) {
    strcat(data, (char *)ptr);
    return size * nmemb;
}

CurrencyRates fetch_currency_rates() {
    CurrencyRates rates = {0};

    // this if for init libcurl
    CURL *curl;
    CURLcode res;
    curl = curl_easy_init();
    if (curl) {
        char response[4096] = {0}; 
        curl_easy_setopt(curl, CURLOPT_URL, "https://api.freecurrencyapi.com/v1/latest?apikey=fca_live_HB3ZQDCbNB02SGeWii9BiQn53C8SZGGgSXiJ5l5v");
        curl_easy_setopt(curl, CURLOPT_WRITEFUNCTION, write_callback);
        curl_easy_setopt(curl, CURLOPT_WRITEDATA, response);
        res = curl_easy_perform(curl);

        if (res != CURLE_OK) {
            fprintf(stderr, "curl_easy_perform() failed: %s\n", curl_easy_strerror(res));
        } else {
            cJSON *json = cJSON_Parse(response);
            if (json) {
                cJSON *data = cJSON_GetObjectItem(json, "data");
                if (data) {
                    cJSON *eur = cJSON_GetObjectItem(data, "EUR");
                    if (cJSON_IsNumber(eur)) {
                        rates.exEUR = eur->valuedouble;
                    }
                    cJSON *ron = cJSON_GetObjectItem(data, "RON");
                    if (cJSON_IsNumber(ron)) {
                        rates.exRON = ron->valuedouble;
                    }
                }
                cJSON_Delete(json);
            } else {
                fprintf(stderr, "Error parsing JSON: %s\n", cJSON_GetErrorPtr());
            }
        }
        curl_easy_cleanup(curl);
    } else {
        fprintf(stderr, "Failed to initialize libcurl\n");
    }

    rates.exRONtoexEUR =  rates.exEUR / rates.exRON;
    rates.exRONtoexUSD = 1/ rates.exRON;
    rates.exEURtoexRON = rates.exRON / rates.exEUR;
    rates.exEURtoexUSD = 1 / rates.exEUR;
    rates.exUSDtoexRON = rates.exRON;
    rates.exUSDtoexEUR = rates.exEUR; 
    return rates;
}

void print_test_api_handlingC() {
    CurrencyRates rates = fetch_currency_rates();

    time_t rawtime;
    struct tm *timeinfo;

    time(&rawtime);
    timeinfo = localtime(&rawtime);

    /*
    // cause of os clock being -2 lol 
    timeinfo->tm_hour -= 2;
    if (timeinfo->tm_hour < 0) {
        timeinfo->tm_hour += 24; 
    }
    */
    system("clear");

    //printf("%s",asctime(timeinfo)); // default 

    printf("\n\t┌────────────────────────────────────────────────┐\n");
    printf("\t│ Exchange Rate:   │   %.*s  │\n", (int)(strlen(asctime(timeinfo)) - 1), asctime(timeinfo));
    printf("\t└────────────────────────────────────────────────┘\n\n");

    printf("\t\t┌──────────┬──────────┬──────────┐\n");
    printf("\t\t│   RON    │   EUR    │ %.6f │\n", rates.exRONtoexEUR);
    printf("\t\t├──────────┼──────────┼──────────┤\n");
    printf("\t\t│   RON    │   USD    │ %.6f │\n", rates.exRONtoexUSD);
    printf("\t\t├──────────┼──────────┼──────────┤\n");
    printf("\t\t│   EUR    │   RON    │ %.6f │\n", rates.exEURtoexRON);
    printf("\t\t├──────────┼──────────┼──────────┤\n");
    printf("\t\t│   EUR    │   USD    │ %.6f │\n", rates.exEURtoexUSD);
    printf("\t\t├──────────┼──────────┼──────────┤\n");
    printf("\t\t│   USD    │   RON    │ %.6f │\n", rates.exUSDtoexRON);
    printf("\t\t├──────────┼──────────┼──────────┤\n");
    printf("\t\t│   USD    │   EUR    │ %.6f │\n", rates.exUSDtoexEUR);
    printf("\t\t└──────────┴──────────┴──────────┘\n\n");
}
