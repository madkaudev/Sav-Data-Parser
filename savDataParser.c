#include <stdio.h>
#include <stdlib.h>
#include <ctype.h>

#include "structs.h"

void printHexData() {
    
}

int main() {
    /* Declare consts. */
    const int BANK_SIZE = 0x2000;
    const int SAV_SIZE = BANK_SIZE * 4;

    /* Prompt user for the file path. */
    char *filePath = (char*)calloc(_MAX_PATH, sizeof(char));
    printf("Enter the file path: ");
    scanf("%s", filePath);

    /* Attempt to open file. */
    FILE *fptr;
    fptr = fopen(filePath, "rb");
    while (fptr != 0) {
        printf("Error opening file at %s.\n", filePath);
        printf("Enter the file path: ");
        scanf("%s", filePath);
        fptr = fopen(filePath, "rb");
    }
    printf("Success opening file.\n");

    /* Read through binary file. */
    char savBinary[8000];
    int count = 0;
    while (feof(fptr) == 0 && count < 8000) {
        fread(savBinary, sizeof(char), 1, fptr);
        count++;
    }

    /* Allocate an array of 8kb to store .sav file length. */
    char *savFile = (char *)calloc(8000, sizeof(char));
    if (savFile == 0) {
        printf("Failed to allocate memory\n");
        exit(1);
    }

    /* Load char *savFile with hex data. */
    int index = 0;
    while (index < 8000) {
        *(savFile + index) = savBinary[index];
        index++;
    }

    /* Optionally print out hex data in a file. */
    char yesOrNo;
    printf("Do you want to print out the raw hex data?\n");
    printf("Y/N: ");
    scanf("%c", &yesOrNo);
    yesOrNo = tolower(yesOrNo);
    if (yesOrNo == 'y') {
        char *outputFile = (char *)calloc(_MAX_PATH, sizeof(char));
        printf("Enter a file path to write to: ");
        scanf("%s", outputFile);
    }

    struct savProfile s1;

    /* Free all the allocated memory. */

    /* Arbitrary return statement. */
    return 0;
}
