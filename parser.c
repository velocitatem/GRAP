#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include "parser.h"
#include "tokens.h"


Node* parseTokenAsNode(Token token) {
    NodeType t;

    //TODO: better node type assignment
    switch ( token.type) {
        case TOKEN_CORE:
            t = NODE_CORE;
            break;
        case TOKEN_MODULE:
            t = NODE_MODULE;
            break;
        case TOKEN_ACTION:
            t = NODE_ACTION;
            break;
        default:
            t = NODE_ARGUMENT;
            break;

    }

    return createNode(t, token);
}

Node * parseTokensIntoGraph(Token tokens[], int tokenCount) {
    // create new token
    Token * rootToken = malloc(sizeof(Token));
        rootToken->value = "root";
        rootToken->type = TOKEN_CORE;
        rootToken->coreToken = TOKEN_MAIN;


    Token *mainLinker = malloc(sizeof(Token));
        mainLinker->value = "linker";
        mainLinker->type = TOKEN_ACTION;
        mainLinker->actionToken= TOKEN_LINK;

    Node *root = createNode(NODE_CORE, *rootToken);
    for (int i = 0; i < tokenCount; i+=5) {
        //printf("%s", tokens[i]);
        // check if pattern is ACTON
        Token module = tokens[i];
        Token action = tokens[i+2];
        Token param = tokens[i+4];
        Node* a = parseTokenAsNode(module);
        Node* b = parseTokenAsNode(param);
        addEdge(root, a, *mainLinker);
        addEdge(a, b, action);

    }
    return root;

}
