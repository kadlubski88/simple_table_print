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

int is_separator(char c);

int main(int argc, char *argv[]) {

    //###########################
    //# Variable initialisation #
    //###########################

    char buffer[BUFFER_SIZE];
    char *buffer_pointer = NULL;
    char *entry_pointer = NULL;
    int separator = 1;
    int line_to_read = 1; //default line to read
    int column_to_read = 1; //default column to read
    int actual_line = 1;
    int actual_column = 1;
    FILE *data_stream = stdin;

    //####################
    //# Argument parsing #
    //####################

    argc--;
    argv++;
    while (argc > 0 && argv[0][0] == '-' ) {
        switch (argv[0][1]) {
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
            if ((data_stream = fopen(*argv, "r")) == NULL) {
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
        argv++;
    }

    //################
    //# Text parsing #
    //################

    // line loop
    while ((fgets(buffer, BUFFER_SIZE, data_stream)) != NULL) {
        // ignore not needed lines
        if (actual_line != line_to_read) {
            actual_line++;
            continue;
        }
        // character loop
        buffer_pointer = buffer;
        while (*buffer_pointer != '\0') {
            if (*buffer_pointer == '\n'){
                *buffer_pointer = '\0';
                break;
            }
            if (is_separator(*buffer_pointer)) {
                *buffer_pointer = '\0';
                if (actual_column == 1) {
                    // ignore whitespace at beginning
                    buffer_pointer++;
                    continue;
                }
                if (entry_pointer != NULL) {
                    // entry is complete
                    break;
                } 
                separator = 1;
                buffer_pointer++;
            } else {
                if (separator) {
                    // first entry character after a separator or beginning of a line
                    if (column_to_read == actual_column) {
                        entry_pointer = buffer_pointer;
                    }
                    actual_column++;
                }
                buffer_pointer++;
                separator = 0;
            }
        }
        if (entry_pointer == NULL) {
            fclose(data_stream);
            exit(EXIT_FAILURE);
        }
        printf("%s\n", entry_pointer);
        break;
    }
    fclose(data_stream);
    exit(EXIT_SUCCESS);
}

int is_separator(char c) {
    // 32 -> space
    // 9 -> tab
    return((c == 32) || (c == 9));
    // LUT could be also a solution for very long lines
}
