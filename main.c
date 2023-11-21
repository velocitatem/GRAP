//
// Created by velocitatem on 11/21/23.
//
#include <lexer.h>
#include <stdlib.h>
#include <string.h>

int main() {
    const char* source = "hello world 1299223";
    Lexer *lex = initLexer(source);

    Token  token;
    do {
        token = nextToken(lex);
        // Process the token, like printing it
    } while (token.coreToken != TOKEN_EOF);

    // Free token values and perform any necessary cleanup
    return 0;
}
