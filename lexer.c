//
// Created by velocitatem on 11/24/23.
//

#include "lexer.h"
#include "tokens.h"
#include <stdlib.h>
#include <string.h>
#include <stdio.h>
#include <ctype.h>


Lexer* initLexer(const char* source) {
    Lexer* lexer = malloc(sizeof(Lexer));
    lexer->start = source;
    lexer->current = source;
    lexer->line = 1;
    return lexer;
}

void freeLexer(Lexer* lexer) {
    free(lexer);
}

bool isAtEnd(Lexer* lexer) {
    return *lexer->current == '\0';
}

char advance(Lexer* lexer) {
    lexer->current++;
    return lexer->current[-1];
}

static char peek(Lexer* lexer) {
    return *lexer->current;
}

static bool match(Lexer* lexer, char expected) {
    if (*lexer->current == expected) {
        lexer->current++;
        return true;
    }
    return false;
}

void skipWhitespace(Lexer* lexer) {
    for (;;) {
        char c = peek(lexer);
        switch (c) {
            case ' ':
            case '\r':
            case '\t':
                advance(lexer);
                break;
            case '\n':
                lexer->line++;
                advance(lexer);
                break;
            default:
                return;
        }
    }
}


static Token* makeToken(Lexer* lexer, TokenType tokenType, CoreTokens coreToken, ActionTokens customToken) {
    Token* token = malloc(sizeof(Token));
    token->type = tokenType;
    switch (tokenType) {
        case TOKEN_CORE:
            token->coreToken = coreToken;
            break;
        case TOKEN_ACTION:
            token->actionToken = customToken;
            break;
        case TOKEN_MODULE:
            token->moduleToken = customToken;
            break;
        default:
            break;
    }

    token->value = malloc(sizeof(char) * (lexer->current - lexer->start + 1));
    memcpy(token->value, lexer->start, lexer->current - lexer->start);
    token->value[lexer->current - lexer->start] = '\0';
    token->line = lexer->line;
    return token;
}


Token nextToken(Lexer* lexer) {

    skipWhitespace(lexer);

    lexer->start = lexer->current;

    if (isAtEnd(lexer)) return *makeToken(lexer, TOKEN_CORE, TOKEN_EOF, TOKEN_EOF);

    char c = advance(lexer);

    // Handle different characters and token types
    switch (c) {
        // Add cases for different characters
        // Example for 'hello;'
        case 'm':
            if (strncmp(lexer->current, "odule", 5) == 0) {
                lexer->current += 5;
                return *makeToken(lexer, TOKEN_MODULE, TOKEN_CUSTOM_MODULE, TOKEN_CUSTOM_MODULE);
            }
            if (strncmp(lexer->current, "em", 2) == 0) {
                lexer->current += 2;
                return *makeToken(lexer, TOKEN_MODULE, TOKEN_MEM, TOKEN_MEM);
            }
            break;
        case '|':
            return *makeToken(lexer, TOKEN_CORE, TOKEN_LINK, TOKEN_LINK);
            // Add cases for different characters

        case 's':
            if (strncmp(lexer->current, "ave", 3) == 0) {
                lexer->current += 3;
                return *makeToken(lexer, TOKEN_MODULE, TOKEN_SAVE, TOKEN_SAVE);
            }
            // say
            if (strncmp(lexer->current, "ay", 2) == 0) {
                lexer->current += 2;
                return *makeToken(lexer, TOKEN_ACTION, TOKEN_SAY, TOKEN_SAY);
            }
            break;
        case 'v':
            if (strncmp(lexer->current, "ar", 2) == 0) {
                lexer->current += 2;
                return *makeToken(lexer, TOKEN_MODULE, TOKEN_VAR, TOKEN_VAR);
            }
            break;
        case 'i': // io
            if (strncmp(lexer->current, "o", 1) == 0) {
                lexer->current += 1;
                return *makeToken(lexer, TOKEN_MODULE, TOKEN_IO, TOKEN_IO);
            }
            // int
            if (strncmp(lexer->current, "nt", 2) == 0) {
                lexer->current += 2;
                return *makeToken(lexer, TOKEN_MODULE, TOKEN_INT, TOKEN_INT);
            }
            break;

            // get
        case 'g':
            if (strncmp(lexer->current, "et", 2) == 0) {
                lexer->current += 2;
                return *makeToken(lexer, TOKEN_ACTION, TOKEN_GET, TOKEN_GET);
            }
            break;

        case 'd':
            if (strncmp(lexer->current, "eclare", 6) == 0) {
                lexer->current += 6;
                return *makeToken(lexer, TOKEN_ACTION, TOKEN_DECLARE, TOKEN_DECLARE);
            }
            break;
        case 'e':
            if (strncmp(lexer->current, "xport", 5) == 0) {
                lexer->current += 5;
                return *makeToken(lexer, TOKEN_ACTION, TOKEN_EXPORT, TOKEN_EXPORT);
            }
            break;
        case 'c':
            if (strncmp(lexer->current, "all", 3) == 0) {
                lexer->current += 3;
                return *makeToken(lexer, TOKEN_ACTION, TOKEN_CALL, TOKEN_CALL);
            }
            break;

        case 'b': // binary
            if (strncmp(lexer->current, "in", 2) == 0) {
                lexer->current += 2;
                return *makeToken(lexer, TOKEN_MODULE, TOKEN_BIN, TOKEN_BIN);
            }
            if (strncmp(lexer->current, "its", 3) == 0) {
                lexer->current += 3;
                return *makeToken(lexer, TOKEN_MODULE, TOKEN_BITS, TOKEN_BITS);
            }
            break;

        case '>':
            return *makeToken(lexer, TOKEN_ACTION, TOKEN_RIGHTSHIFT, TOKEN_RIGHTSHIFT);
            break;
        case '<':
            return *makeToken(lexer, TOKEN_ACTION, TOKEN_LEFTSHIFT, TOKEN_LEFTSHIFT);
            break;



        // -------------- CORE TOKENS ----------------

        case '\@':
            while (isalnum(peek(lexer)) && !isAtEnd(lexer)) advance(lexer);
            return *makeToken(lexer, TOKEN_CORE, TOKEN_CUSTOM_MODULE_NAME, TOKEN_CUSTOM_MODULE_NAME);
            break;


            // ( TOKEN_HEAD
        case '(':
            return *makeToken(lexer, TOKEN_CORE, TOKEN_HEAD, TOKEN_HEAD);
            break;
            // ) TOKEN_TAIL
        case ')':
            return *makeToken(lexer, TOKEN_CORE, TOKEN_TAIL, TOKEN_TAIL);
            break;


            // allow for any word/string
        case '"':
            while (peek(lexer) != '"' && !isAtEnd(lexer)) advance(lexer);
            if (isAtEnd(lexer)) {
                printf("Error: Unterminated string at line %d\n", lexer->line);
                exit(EXIT_FAILURE);
            }
            advance(lexer); // The closing "
            return *makeToken(lexer, TOKEN_CORE, TOKEN_STRING, TOKEN_STRING);
            break;
        default:
            return *makeToken(lexer, TOKEN_CORE, TOKEN_IDENTIFIER, TOKEN_IDENTIFIER);
            break;

    }

}
