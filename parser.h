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
    while (i < tokenCount) {
        Token token = tokens[i];
        printf("AA: %s\n", token.value);
        i++;
    }
}


#endif //PROGRAMMING_LANGUAGE_IN_C_PARSER_H
