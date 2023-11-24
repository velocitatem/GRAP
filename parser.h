//
// Created by velocitatem on 11/22/23.
//
/*
 * Graph like parser
 * goes over each 5 tokens and checks if it matches a pattern
 * CustomToken LINK CustomToken LINK CoreToken
 */

#include <stdbool.h>
#include <stdio.h>
#include <tokens.h>
#include <lexer.h>

#ifndef PROGRAMMING_LANGUAGE_IN_C_PARSER_H
#define PROGRAMMING_LANGUAGE_IN_C_PARSER_H

typedef struct Command {
    CustomTokens node_a;
    CustomTokens link;
    CoreTokens node_b;
} Command;

void parseTokens(Lexer *lexer, Token *tokens, int tokenCount) {
    int i = 0;
    if (tokenCount % 5 != 0) {
        printf("Error: Invalid number of tokens\n");
        exit(EXIT_FAILURE);
    }
    // go over number of commands
    int commands = tokenCount / 5;
    for (int i = 0; i < commands; i += 1) {
        // check if the first token is a custom token
        if (tokens[i * 5].isCoreToken) {
            printf("Error: Expected custom token\n");
            exit(EXIT_FAILURE);
        }
        // check if the second token is a custom token
        if (tokens[i * 5 + 1].isCoreToken) {
            printf("Error: Expected custom token\n");
            exit(EXIT_FAILURE);
        }
        // check if the third token is a core token
        if (!tokens[i * 5 + 2].isCoreToken) {
            printf("Error: Expected core token\n");
            exit(EXIT_FAILURE);
        }
        // check if the fourth token is a custom token
        if (tokens[i * 5 + 3].isCoreToken) {
            printf("Error: Expected custom token\n");
            exit(EXIT_FAILURE);
        }
        // check if the fifth token is a custom token
        if (!tokens[i * 5 + 4].isCoreToken) {
            printf("Error: Expected core token\n");
            exit(EXIT_FAILURE);
        }
        // check if the first token is a custom token
        if (tokens[i * 5].customToken != TOKEN_HELLO_COMMAND) {
            printf("Error: Expected hello command\n");
            exit(EXIT_FAILURE);
        }
        // check if the second token is a custom token
        if (tokens[i * 5 + 1].customToken != TOKEN_HELLO_WORLD) {
            printf("Error: Expected hello world\n");
            exit(EXIT_FAILURE);
        }
        // check if the third token is a core token
        if (tokens[i * 5 + 2].coreToken != TOKEN_IDENTIFIER) {
            printf("Error: Expected identifier\n");
            exit(EXIT_FAILURE);
        }
        // check if the fourth token is a custom token
        if (tokens[i * 5 + 3].customToken != TOKEN_LINK) {
            printf("Error: Expected link\n");
            exit(EXIT_FAILURE);
        }
        // check if the fifth token is a custom token
        if (tokens[i * 5 + 4].coreToken != TOKEN_IDENTIFIER) {
            printf("Error: Expected identifier\n");
            exit(EXIT_FAILURE);
        }
        // print the command
        printf("Command: %s %s %s %s %s\n", tokens[i * 5].value, tokens[i * 5 + 1].value, tokens[i * 5 + 2].value,
               tokens[i * 5 + 3].value, tokens[i * 5 + 4].value);
    }
}


#endif //PROGRAMMING_LANGUAGE_IN_C_PARSER_H
