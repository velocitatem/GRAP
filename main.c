//
// Created by velocitatem on 11/21/23.
//
#include "lexer.h"
#include <stdlib.h>
#include <string.h>
#include <stdio.h>
#include <ctype.h>


// load file thats the first argument
// if no argument, load from stdin
int main(int argc, char** argv) {

    // chekc if file is in .rem extension
    FILE *fp;
    char *line = NULL;
    size_t len = 0;
    ssize_t read;
    char *filename = argv[1];
    const char* source;
    fp = fopen(filename, "r");
    if (fp == NULL) {
        printf("Error: File not found\n");
        exit(EXIT_FAILURE);
    }
    // read file line by line
    while ((read = getline(&line, &len, fp)) != -1) {
        source = line;
    }
    fclose(fp);

int main() {
    const char* source = "wtest world 1299223";

    Lexer *lex = initLexer(source);

    Token  token;
    do {
        token = nextToken(lex);
        // Process the token, like printing it
    } while (token.coreToken != TOKEN_EOF);

    freeLexer(lex);
    free(line);
    // Free token values and perform any necessary cleanup
    return 0;
}
