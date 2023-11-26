//
// Created by velocitatem on 11/21/23.
//
#include <lexer.h>
#include <stdlib.h>
#include <string.h>
#include <stdio.h>
#include <ctype.h>
#include <parser.h>


// load file thats the first argument
// if no argument, load from stdin
int main(int argc, char** argv) {

    // chekc if file is in .rem extension
    FILE *fp;
    char *line = NULL;
    size_t len = 0;
    ssize_t read;
    char *filename = argv[1];
    fp = fopen(filename, "r");
    if (fp == NULL) {
        printf("Error: File not found\n");
        exit(EXIT_FAILURE);
    }
    // read all lines save full contents
    char *source = malloc(sizeof(char) * 1000);
    while ((read = getline(&line, &len, fp)) != -1) {
        strcat(source, line);
    }
    fclose(fp);

    Lexer *lex = initLexer(source);

    Token  token;
    Token *tokens = malloc(sizeof(Token) * 100);
    int tokenCount = 0;
    do {
        token = nextToken(lex);
        // Process the token, like printing it
        printf("Token: %s\n", token.value);
        tokens[tokenCount] = token;
        tokenCount++;
    } while (token.coreToken != TOKEN_EOF);
    parseTokens(lex, tokens, tokenCount - 1);




    freeLexer(lex);
    free(line);
    // Free token values and perform any necessary cleanup
    return 0;
}
