#include <stdio.h>
#include <string.h>
#include <curl/curl.h>
#include "cJSON.h"

// Struct to hold currency rates
typedef struct {
    double exEUR;
    double exRON;
} CurrencyRates;

// Callback function to handle HTTP response
size_t write_callback(void *ptr, size_t size, size_t nmemb, char *data) {
    strcat(data, (char *)ptr);
    return size * nmemb;
}

// Function to fetch currency rates from API
CurrencyRates fetch_currency_rates() {
    CurrencyRates rates = {0}; // Initialize rates to 0

    // Initialize libcurl
    CURL *curl;
    CURLcode res;
    curl = curl_easy_init();
    if (curl) {
        char response[4096] = {0}; // Buffer to store API response
        curl_easy_setopt(curl, CURLOPT_URL, "https://api.freecurrencyapi.com/v1/latest?apikey=fca_live_HB3ZQDCbNB02SGeWii9BiQn53C8SZGGgSXiJ5l5v");
        curl_easy_setopt(curl, CURLOPT_WRITEFUNCTION, write_callback);
        curl_easy_setopt(curl, CURLOPT_WRITEDATA, response);
        res = curl_easy_perform(curl);

        if (res != CURLE_OK) {
            fprintf(stderr, "curl_easy_perform() failed: %s\n", curl_easy_strerror(res));
        } else {
            // Parse JSON response
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

    return rates;
}
/*
void print_test_api_handlindC() {
    CurrencyRates rates = fetch_currency_rates();
    //double  exRONtoexEUR ,exRONtoexUSD, exEURtoexRON, exEURtoexUSD, exUSDtoexRON ,exUSDtoexEUR;

    printf("exRON to exEUR rate: %.10f\n", rates.exEUR / rates.exRON);
    printf("exRON to exUSD rate: %.10f\n", 1/ rates.exRON);
    printf("exEUR to exRON rate: %.10f\n", rates.exRON / rates.exEUR);
    printf("exEUR to exUSD rate: %.10f\n", 1 / rates.exEUR);
    printf("exUSD to exRON rate: %.10f\n", rates.exRON);
    printf("exUSD to exEUR rate: %.10f\n", rates.exEUR);
}
*/
void print_test_api_handlingC() {
    CurrencyRates rates = fetch_currency_rates();
    printf("exRON to exEUR rate: %.10f\n", rates.exEUR / rates.exRON);
    printf("exRON to exUSD rate: %.10f\n", 1/ rates.exRON);
    printf("exEUR to exRON rate: %.10f\n", rates.exRON / rates.exEUR);
    printf("exEUR to exUSD rate: %.10f\n", 1 / rates.exEUR);
    printf("exUSD to exRON rate: %.10f\n", rates.exRON);
    printf("exUSD to exEUR rate: %.10f\n", rates.exEUR);
}

/*
int main(){
    CurrencyRates rates = fetch_currency_rates();
    printf("exRON to exEUR rate: %.10f\n", rates.exEUR / rates.exRON);
    printf("exRON to exUSD rate: %.10f\n", 1/ rates.exRON);
    printf("exEUR to exRON rate: %.10f\n", rates.exRON / rates.exEUR);
    printf("exEUR to exUSD rate: %.10f\n", 1 / rates.exEUR);
    printf("exUSD to exRON rate: %.10f\n", rates.exRON);
    printf("exUSD to exEUR rate: %.10f\n", rates.exEUR);
}

*/// for testing 
