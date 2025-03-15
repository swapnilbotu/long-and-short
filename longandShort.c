#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <ctype.h>

int main(int argc, char *argv[]) {
    // makes sure that exactly three arguments are provided.
    if (argc != 4) {
        fprintf(stderr, "Usage: %s <source_file> <short_dest_file> <long_dest_file>\n", argv[0]);
        return 1;
    }

    // Open the source file for reading.
    FILE *source = fopen(argv[1], "r");
    if (source == NULL) {
        fprintf(stderr, "Error: could not open source file %s\n", argv[1]);
        return 1;
    }

    //this is the first destination file for writing (the short lines).
    FILE *shortFile = fopen(argv[2], "w");
    if (shortFile == NULL) {
        fprintf(stderr, "Error: could not open destination file %s\n", argv[2]);
        fclose(source);
        return 1;
    }

    // this iss the second destination file for writing (long lines).
    FILE *longFile = fopen(argv[3], "w");
    if (longFile == NULL) {
        fprintf(stderr, "Error: could not open destination file %s\n", argv[3]);
        fclose(source);
        fclose(shortFile);
        return 1;
    }

    int shortCount = 0;  // keeps track of the amount of lines wrriten to the first file(short lines)
    int longCount = 0;   // keeps track of the amount of lines wrriten to the second file(long lines)
    char line[256];      

    // iterating through the source file, one line at a time
    while (fgets(line, sizeof(line), source) != NULL) {
        size_t len = strlen(line);

        // make a copy of the line to hold the converted text.
        char converted[256];
        strcpy(converted, line);

        // If the line is shorter than 20 characters, make the letters into uppercase.
        if (len < 20) {
            for (size_t i = 0; i < len; i++) {
                converted[i] = toupper((unsigned char)converted[i]);
            }
            fputs(converted, shortFile);
            shortCount++;
        } else {  // or else, convert letters to lowercase.
            for (size_t i = 0; i < len; i++) {
                converted[i] = tolower((unsigned char)converted[i]);
            }
            fputs(converted, longFile);
            longCount++;
        }
    }

    fclose(source);
    fclose(shortFile);
    fclose(longFile);

    // final print statement to show the number of lines written to each destination file.
    printf("%d lines written to %s\n", shortCount, argv[2]);
    printf("%d lines written to %s\n", longCount, argv[3]);

    return 0;
}
