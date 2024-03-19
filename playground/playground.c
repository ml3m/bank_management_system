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

    printf("\x1b[1mBold text\x1b[0m\n");
    // dim looks good
    printf("\x1b[2mDim text\x1b[0m\n");
    printf("\x1b[3mItalic text\x1b[0m\n");
    printf("\x1b[4mUnderlined text\x1b[0m\n");
    printf("\x1b[5mBlinking text\x1b[0m\n");
    // inverse too
    printf("\x1b[7mInverse text\x1b[0m\n");
    printf("\x1b[8mHidden text\x1b[0m\n");
    printf("\x1b[9mStrikethrough text\x1b[0m\n");

    printf("\x1b[31mRed text\x1b[0m\n");
    printf("\x1b[32mGreen text\x1b[0m\n");
    printf("\x1b[33mYellow text\x1b[0m\n");
    printf("\x1b[34mBlue text\x1b[0m\n");
    printf("\x1b[35mMagenta text\x1b[0m\n");
    printf("\x1b[36mCyan text\x1b[0m\n");
    printf("\x1b[37mWhite text\x1b[0m\n");

    printf("\x1b[41mRed background\x1b[0m\n");
    printf("\x1b[42mGreen background\x1b[0m\n");
    printf("\x1b[43mYellow background\x1b[0m\n");
    printf("\x1b[44mBlue background\x1b[0m\n");
    printf("\x1b[45mMagenta background\x1b[0m\n");
    printf("\x1b[46mCyan background\x1b[0m\n");
    printf("\x1b[47mWhite background\x1b[0m\n");

    return 0;
}
