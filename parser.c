#include "parser.h"
#include "lexer.h"
#include "tokens.h"
#include <stdio.h>
#include <stdlib.h>

bool isCoreToken(Token token, CoreTokens coreToken) {
    return token.coreToken == coreToken;
}

bool isCustomToken(Token token, CustomTokens customToken) {
    return token.customToken == customToken;
}


void parseTokens(Lexer *lexer, Token *tokens, int tokenCount) {
    int i = 0;
    if (tokenCount % 5 != 0) {
        printf("Error: Invalid number of tokens\n");
        exit(EXIT_FAILURE);
    }
    while (i < tokenCount) {
        if (tokens[i].coreToken == TOKEN_EOF) {
            break;
        }
        // check if is of type CustomTokesn
        if (!tokens[i].isCoreToken)  {
            if (tokens[i + 1].coreToken == TOKEN_LINK) {
                if (!tokens[i + 2].isCoreToken) {
                    if (tokens[i + 3].coreToken == TOKEN_LINK) {
                        if (tokens[i + 4].isCoreToken) {
                            printf("Command: %s %s %s\n", tokens[i].value, tokens[i + 1].value, tokens[i + 2].value);
                            printf("Command: %s %s %s\n", tokens[i + 2].value, tokens[i + 3].value, tokens[i + 4].value);

                            i += 5;
                        } else {
                            printf("Error: Expected identifier\n");
                            exit(EXIT_FAILURE);
                        }
                    } else {
                        printf("Error: Expected link\n");
                        exit(EXIT_FAILURE);
                    }
                } else {
                    printf("Error: Expected identifier\n");
                    exit(EXIT_FAILURE);
                }
            } else {
                printf("Error: Expected link\n");
                exit(EXIT_FAILURE);
            }
        } else {
            printf("Error: Expected identifier\n");
            exit(EXIT_FAILURE);
        }
    }
}
