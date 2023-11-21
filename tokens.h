//
// Created by velocitatem on 11/21/23.
//
// Here we define the tokens for the lexer
// for our programming language

#include <stdbool.h>
#ifndef PROGRAMMING_LANGUAGE_IN_C_TOKENS_H
#define PROGRAMMING_LANGUAGE_IN_C_TOKENS_H

// Token types
typedef enum CoreTokens {
    TOKEN_IDENTIFIER,
    TOKEN_NUMBER,
    TOKEN_STRING,
    TOKEN_CHAR,
    TOKEN_KEYWORD,
    TOKEN_OPERATOR,
    TOKEN_PUNCTUATOR,
    TOKEN_COMMENT,
    TOKEN_WHITESPACE,
    TOKEN_NEWLINE,
    TOKEN_EOF
} CoreTokens;

typedef enum CustomTokens {
    TOKEN_HELLO_COMMAND,
    TOKEN_HELLO_WORLD,
} CustomTokens;

typedef struct Token {
    bool isCoreToken;
    union {
        CoreTokens coreToken;
        CustomTokens customToken;
    };
    char *value;
    int line;
} Token;

#endif //PROGRAMMING_LANGUAGE_IN_C_TOKENS_H
