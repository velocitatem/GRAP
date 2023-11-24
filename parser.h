#ifndef PROGRAMMING_LANGUAGE_IN_C_PARSER_H
#define PROGRAMMING_LANGUAGE_IN_C_PARSER_H

#include "tokens.h"
#include "lexer.h"

typedef struct Command {
    CustomTokens node_a;
    CustomTokens link;
    CoreTokens node_b;
} Command;

bool isCoreToken(Token token, CoreTokens coreToken);
bool isCustomToken(Token token, CustomTokens customToken);
void parseTokens(Lexer *lexer, Token *tokens, int tokenCount);

#endif // PROGRAMMING_LANGUAGE_IN_C_PARSER_H