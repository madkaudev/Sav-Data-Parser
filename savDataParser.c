#include <stdio.h>
#include <stdlib.h>

#include "structs.h"
#include "freqFunctions.h"

/**
 * Outputs the data of the .sav file in an external file.
 * 
 * @param FILE *fPtr
 * @param char *savFile
 * @param int size
 * @return void
*/
void printHexData(FILE *fPtr, char *savFile, int size) {
    //Index variables
    int index = 0;
    int verticalIndex = 0x0000;
    int horizontalIndex = 0x00;

    // Prints out the header
    fprintf(fPtr, "         ");
    for (int i = 0; i < 16; i++) {
        fprintf(fPtr, "%02X", horizontalIndex);
        if (horizontalIndex == 15) {
            fprintf(fPtr, "\n");
        }
        else {
            fprintf(fPtr, "  ");
        }
        horizontalIndex++;
        
    }
    // Prints out the rows
    for (int i = 0; i < size/16; i++) {
        fprintf(fPtr, "0x%04X   ", verticalIndex);
        for (int j = 0; j < 16; j++) {
            fprintf(fPtr, "%.*X", 2, savFile[index]);
            if (j == 15) {
                fprintf(fPtr, "\n");
            }
            else {
                fprintf(fPtr, "  ");
            }
            index++;
        }
        verticalIndex += 16;
    }
}

/**
 * The main method.
 * 
 * @return int
*/
int main() {
    /* Declare consts. */
    const int BANK_SIZE = 0x2000;
    const int SAV_SIZE = BANK_SIZE * 4;

    /* Create variable to store file path. */
    char *filePath = (char*)calloc(_MAX_PATH, sizeof(char));

    /* Check for proper allocation. */
    int fpCheck = cPtrCallocCheck(filePath);
    if (fpCheck == 0) {
        printf("Couldn't allocate memory for the file path.\n");
        exit(1);
    }

    /* Open the file. */
    FILE *fPtr;
    fPtr = openFile(fPtr, filePath, "rb");

    /* Allocate an array of 8kb to store .sav file length. */
    char *savFile = (char *)calloc(SAV_SIZE, sizeof(char));

    /* Check for proper allocation. */
    int sfCheck = cPtrCallocCheck(savFile);
    if (sfCheck == 0) {
        printf("Couldn't allocate memory for the .sav file\n");
        free(filePath);
        exit(1);
    }

    /* Fill array with hex bytes. */
    const size_t freadSize = fread(savFile, sizeof(char), SAV_SIZE, fPtr);

    /* Check if the file was read properly. */
    int check = freadCheck(freadSize, SAV_SIZE);
    if (check == 0) {
        free(filePath);
        free(savFile);
        exit(1);
    }
    printf("File was properly read.\n");

    /* Prompt user for a name for the output file. */
    char *outputFilePath = (char*)calloc(_MAX_PATH, sizeof(char));

    /* Check for proper allocation. */
    int ofpCheck = cPtrCallocCheck(outputFilePath);
    if (ofpCheck == 0) {
        printf("Couldn't allocate memory for the file path.\n");
        exit(1);
    }

    /* Write to the output file the raw hex data. */
    FILE *ofPtr;

    printf("What if the name of your output file?\n");
    ofPtr = openFile(ofPtr, filePath, "w");
    printHexData(ofPtr, savFile, SAV_SIZE);
    printf("Finished writing to the file!\n");

    /* Free all the allocated memory. */
    free(filePath);
    fclose(fPtr);
    free(savFile);
    free(outputFilePath);
    fclose(ofPtr);

    /* Arbitrary return statement. */
    return 0;
}
