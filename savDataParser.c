#include <stdio.h>
#include <stdlib.h>

#include "structs.h"
#include "printHexFunctions.h"
#include "freqFunctions.h"

/**
 * Fills the player struct with hex values from the charcter savFile array.
 * 
 * @param player *p1
 * @param char *savFile
 * @return void
*/
void fillPlayer(struct player *p1, char *savFile) {
    int pIndex = 0;
    int index = 0x2598;
    char c = savFile[index];
    char check = (char)0x50;
    while (c != check) {
        p1->playerName[pIndex] = c;
        printf("%X ", c);
        pIndex++;
        index++;
        c = savFile[index];
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

    /* Allocate an array of 8kb to store .sav file length. */
    char *savFile = (char *)calloc(SAV_SIZE, sizeof(char));

    /* Check for proper allocation. */
    int sfCheck = cPtrCallocCheck(savFile);
    if (sfCheck == 0) {
        printf("Couldn't allocate memory for the .sav file\n");
        free(filePath);
        exit(1);
    }

    /* Open the file. */
    FILE *fPtr;
    fPtr = openFile(fPtr, filePath, "rb");

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

    formatArray(savFile, SAV_SIZE);

    /* Prompt user for a name for the output file. */
    char *outputFilePath = (char*)calloc(_MAX_PATH, sizeof(char));

    /* Check for proper allocation. */
    int ofpCheck = cPtrCallocCheck(outputFilePath);
    if (ofpCheck == 0) {
        printf("Couldn't allocate memory for the file path.\n");
        free(filePath);
        free(savFile);
        fclose(fPtr);
        exit(1);
    }

    /* Write to the output file the raw hex data. */
    FILE *ofPtr;

    printf("What if the name of your output file?\n");
    ofPtr = openFile(ofPtr, filePath, "w");
    printHexData(ofPtr, savFile, SAV_SIZE);
    printf("Finished writing to the file!\n");

    /* Create a structure to hold the player's profile. */
    struct player playerProfile;

    fillPlayer(&playerProfile, savFile);

    /* Free all the allocated memory. */
    free(filePath);
    fclose(fPtr);
    free(savFile);
    free(outputFilePath);
    fclose(ofPtr);

    /* Arbitrary return statement. */
    return 0;
}
