#include <stdio.h>

/**
 * Takes in a string representing the path to a file and returns an integer
 * representing whether or not the file can be opened with a 0 meaning no and
 * a 1 meaning yes.
 * 
 * @param char *filePath
 * @return int
*/
int checkFilePath(char *filePath, char *mode) {
    int valid = 1;

    FILE *tempFptr = fopen(filePath, mode);
    if (!tempFptr) {
        valid = 0;
    }      
    fclose(tempFptr);

    return valid;
}

/**
 * Checks if a pointer to a string of characters was properly allocated memory. Returns a 0 if the memory wasn't
 * properly allocated, or a 1 if the memory was read allocated properly.
 * 
 * @param char *cPtr
 * @return int
*/
int cPtrCallocCheck(char *cPtr) {
    int check = 1;

    if (!cPtr) {
        printf("Failed to allocate memory\n");
        check = 0;
    }

    return check;
}

/**
 * Checks if a file was properly read through. Returns a 0 if the file wasn't read
 * properly, or a 1 if the file was read through properly.
 * 
 * @param size_t freadSize
 * @param int size
 * @return int
*/
int freadCheck(size_t freadSize, int size) {
    int check = 1;

    if ((size_t)size != freadSize) {
        printf("This is not a valid Gen 1 .sav file.\n");
        check = 0;
    }

    return check;
}
