#include <stdio.h>

#include "checkFunctions.h"

/**
 * Opens the file stream at a file path and returns a pointer to a FILE variable.
 * 
 * @param FILE *fptr
 * @param char *filePath
 * @param char *mode
 * @return FILE
*/
FILE *openFile(FILE *fptr, char *filePath, char *mode) {
    printf("Enter the file path: ");
    scanf("%s", filePath);
    int fpValid = checkFilePath(filePath, mode);
    while (fpValid == 0) {
        printf("Error opening file at: %s\n", filePath);
        printf("Enter the file path: ");
        scanf("%s", filePath);
        fpValid = checkFilePath(filePath, mode);
    }
    printf("Successfully opened file.\n");
    fptr = fopen(filePath, mode);

    return fptr;
}

/**
 * Reformats all characters in .sav file array to two digits.
 * 
 * @param char *savFile
 * @param in size
 * @return void
*/
void formatArray(char *savFile, int size) {
    for (int i = 0; i < size; i++) {
        int tempHex = 0xFF & savFile[i];
        *(savFile + i) = tempHex;
    }
}
