#ifndef PROGRAMMING_LANGUAGE_IN_C_LEXER_H
#define PROGRAMMING_LANGUAGE_IN_C_LEXER_H

#include <stdbool.h>
#include "tokens.h"

// Lexer structure definition
typedef struct {
    const char* start;
    const char* current;
    int line;
} Lexer;

// Function declarations
Lexer* initLexer(const char* source);
void freeLexer(Lexer* lexer);
bool isAtEnd(Lexer* lexer);
char advance(Lexer* lexer);
void skipWhitespace(Lexer* lexer);
Token nextToken(Lexer* lexer);

#endif // PROGRAMMING_LANGUAGE_IN_C_LEXER_H
