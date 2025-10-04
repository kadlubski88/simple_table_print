/*
Simple table print(stp): A simple command to get one entry from a certain line of a file.
https://github.com/kadlubski88/simple_table_print

The MIT License (MIT)
Copyright © 2025 Georges Kadlubski
URL: https://mit-license.org/
*/



#include <stdio.h>
#include <unistd.h>
#include <stdlib.h>
#include <string.h>

#define BUFFER_SIZE 4096

int
main(int argc, char *argv[]) {
    char buffer[BUFFER_SIZE];
    int text_offset = 0;
    int buffer_index = 0;
    int separator = 0;
    int first_entry = 1;
    int line = 1;
    int line_to_read = 1;
    int column_to_read = 1;
    int actual_column = 1;
    FILE *file_stream = NULL;

    // parse arguments
    if (--argc == 0) {
        fprintf(stderr, "Argument missing\n");
        exit(EXIT_FAILURE);
    }
    while (argc > 0) {
        argv++;
        if (argv[0][0] != '-') {
            fprintf(stderr, "Wrong option %s\n", *argv);
            exit(EXIT_FAILURE);
        }
        switch (argv[0][1])
        {
        case 'c':
            argv++;
            if ((column_to_read = atoi(*argv)) == 0) {
                fprintf(stderr, "\"%s\" is not a valid column number\n", *argv);
                exit(EXIT_FAILURE);
            }
            argc -= 2;
            break;
        case 'l':
            argv++;
            if ((line_to_read = atoi(*argv)) == 0) {
                fprintf(stderr, "\"%s\" is not a valid line number\n", *argv);
                exit(EXIT_FAILURE);
            }
            argc -= 2;
            break;
        case 'f':
            argv++;
            if ((file_stream = fopen(*argv, "r")) == NULL) {
                fprintf(stderr, "file \"%s\" doesn\'t exists\n", *argv);
                exit(EXIT_FAILURE);
            }
            argc -= 2;
            break;
        default:
            fprintf(stderr, "\"%s\" is not a valid option\n", *argv);
            exit(EXIT_FAILURE);
            break;
        }
    }

    // parsing the text file
    while ((fgets(buffer, BUFFER_SIZE, file_stream)) != NULL) {
        if (line != line_to_read) {
            line++;
            continue;
        }
        if (buffer[strlen(buffer) - 1] == '\n') {
            buffer[strlen(buffer) - 1] = '\0';
        }
        while (buffer[buffer_index] != '\0') {
            if (first_entry) {
                if (buffer[buffer_index] == 32 || buffer[buffer_index] == 9) {
                    text_offset++;
                    buffer_index++;
                    continue;
                }
            }
            if (buffer[buffer_index] == 32 || buffer[buffer_index] == 9) {
                buffer[buffer_index] = '\0';
                if (column_to_read == actual_column) {
                    break;
                } 
                separator = 1;
                buffer_index++;
            } else {
                first_entry = 0;
                if (separator) {
                    actual_column++;
                }
                buffer_index++;
                separator = 0;
            }
            if (column_to_read > actual_column ) {
                text_offset++;
            }
        }
        if (actual_column < column_to_read) {
            fclose(file_stream);
            exit(EXIT_FAILURE);
        }
        printf("%s\n", &buffer[text_offset]);
        break;
    }
    fclose(file_stream);
    if (first_entry) {
        exit(EXIT_FAILURE);
    }
    exit(EXIT_SUCCESS);
}
