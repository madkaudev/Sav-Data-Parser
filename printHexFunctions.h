#include <stdio.h>

/**
 * Outputs the header of the hex data file.
 * 
 * @param FILE *fPtr
 * @param char *savFile
 * @return void
*/
void printHeader(FILE *fPtr, char *savFile) {
    // Index variable
    int horizontalIndex = 0x00;   

    // Prints out the header. 
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
}

/**
 * Outputs the rows of the hex data file.
 * 
 * @param FILE *fPtr
 * @param char *savFile
 * @param int size
 * @return void
*/
void printRows(FILE *fPtr, char *savFile, int size) {
    //Index variables
    int index = 0;
    int verticalIndex = 0x0000;

    // Prints out the rows.
    for (int i = 0; i < size/16; i++) {
        fprintf(fPtr, "0x%04X   ", verticalIndex);
        for (int j = 0; j < 16; j++) {
            int tempHex = 0xFF & savFile[index];
            fprintf(fPtr, "%02X", tempHex);
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
 * Outputs the data of the .sav file in an external file.
 * 
 * @param FILE *fPtr
 * @param char *savFile
 * @param int size
 * @return void
*/
void printHexData(FILE *fPtr, char *savFile, int size) {
    // Print the header.
    printHeader(fPtr, savFile);

    // Prints out the rows
    printRows(fPtr, savFile, size);
}
