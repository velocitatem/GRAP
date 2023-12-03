#ifndef PROGRAMMING_LANGUAGE_IN_C_PARSER_H
#define PROGRAMMING_LANGUAGE_IN_C_PARSER_H

#include "tokens.h"
#include "lexer.h"
#include "graph.h"


Node * parseTokensIntoGraph(Token tokens[], int tokenCount);
Node *parseTokenAsNode(Token token);



#endif // PROGRAMMING_LANGUAGE_IN_C_PARSER_H