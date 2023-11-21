//
// Created by velocitatem on 11/21/23.
//
#include <lexer.h>
#include <stdlib.h>
#include <string.h>

int main() {
    const char* source = "hello\nworld";
    Lexer *lex = initLexer(source);

    Token  token;
    do {
        printf("Token: %s\n", token.value);
        token = nextToken(lex);
        // Process the token, like printing it
        printf("Token: %s\n", token.value);
        printf("Lexer: %d\n", *lex->current);
    } while (token.isCoreToken && token.coreToken != TOKEN_EOF);

    // Free token values and perform any necessary cleanup
    return 0;
}
