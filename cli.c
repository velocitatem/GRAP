//
// Created by velocitatem on 12/8/23.
//

#include "cli.h"
#include "interpreter.h"
#include "parser.h"
#include <stdio.h>
#include <stdlib.h>
#include <string.h>

// this is an interactive CLI shell for the programming language
void handleCLI(int argc, char **argv) {
    Lexer *lex;
    while (1) {
        printf(">> ");
        char input[100];
        fgets(input, 100, stdin);
        if (strcmp(input, "exit\n") == 0) {
            break;
        }
        lex = initLexer(input);
        Token token;
        Token *tokens = malloc(sizeof(Token) * 100);
        int tokenCount = 0;
        do {
            token = nextToken(lex);
            // Process the token, like printing it
            //printf("Token: %s\n", token.value);
            tokens[tokenCount] = token;
            tokenCount++;
        } while (token.coreToken != TOKEN_EOF);
        Node *rt = parseTokensIntoGraph(tokens, tokenCount - 1);
        interpretGraph(rt);
    }
}


