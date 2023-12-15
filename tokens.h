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
    TOKEN_MAIN,
} CoreTokens;


typedef enum ModuleTokens {
    TOKEN_CUSTOM_NODE,
    TOKEN_MATH,
    TOKEN_MEM,
    TOKEN_IO,
    TOKEN_VAR,
    TOKEN_INT,
    TOKEN_BIN,
    TOKEN_LIST,
    TOKEN_CUSTOM_MODULE,
    TOKEN_CUSTOM_MODULE_NAME,
    TOKEN_BITS
} ModuleTokens;

typedef enum ActionTokens {
    TOKEN_EVAL,
    TOKEN_CUSTOM_ACTION,
    TOKEN_ADDITION,
    TOKEN_SUBTRACTION,
    TOKEN_MULTIPLICATION,
    TOKEN_DIVISION,
    TOKEN_MODULUS,
    TOKEN_LINK,
    TOKEN_SAVE,
    TOKEN_GET,
    TOKEN_SAY,
    TOKEN_ASK,
    TOKEN_DECLARE,
    TOKEN_EXPORT,
    TOKEN_CALL,
    TOKEN_RIGHTSHIFT,
    TOKEN_LEFTSHIFT,
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
    bool isFinal;
} Token;

#endif //PROGRAMMING_LANGUAGE_IN_C_TOKENS_H
