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
    TOKEN_EOF,
    TOKEN_HEAD,
    TOKEN_TAIL,
    TOKEN_MAIN
} CoreTokens;


typedef enum ModuleTokens {
    TOKEN_MEM,
    TOKEN_IO
} ModuleTokens;

typedef enum ActionTokens {
    TOKEN_LINK,
    TOKEN_SAVE,
    TOKEN_GET,
    TOKEN_SAY,
} ActionTokens;

typedef enum TokenType {
    TOKEN_CORE,
    TOKEN_MODULE,
    TOKEN_ACTION
} TokenType;

typedef struct Token {
    TokenType type;
    union {
        CoreTokens coreToken;
        ActionTokens actionToken;
        ModuleTokens moduleToken;
    };
    char *value;
    int line;
} Token;

#endif //PROGRAMMING_LANGUAGE_IN_C_TOKENS_H
