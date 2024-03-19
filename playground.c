#include <stdio.h>
#include <string.h>


// function that compares the new generated IBAN - number and the IBANs in the db.
int main(){
    char string1[] = "XX123456";
    char string2[] = "123456";

    // Compare string1 starting from index 2 with string2
    int result = strncmp(string1 + 2, string2, strlen(string2));

    if (result == 0) {
        printf("The strings are equal up to %d characters.\n", (int)strlen(string2));
    } else {
        printf("The strings are not equal.\n");
    }
}
