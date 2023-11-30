#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include "parser.h"


Node* parseTokenAsNode(Token token) {
    NodeType t;

    //TODO: better node type assignment
    if (token.isCoreToken) {
        t = NODE_CORE;
    }
    else if (token.isActionToken){
        t = NODE_ACTION;
    }
    else if (token.isModuleToken){
        t = NODE_MODULE;
    }
    else {
        t = NODE_ARGUMENT;
    }

    return createNode(t, token);
}

void parseTokensIntoGraph(Token tokens[], int tokenCount) {
    for (int i = 0; i < tokenCount; i+=5) {
        printf("%s", tokens[i]);
        // check if pattern is ACTON
        if (tokens[i].isCoreToken && tokens[i].coreToken == TOKEN_HEAD) {
            int ogi = i;
            Token *sub = malloc(sizeof(Token) + 1);
            do {
                sub[i-ogi] = tokens[i];
                i+=1;
            } while
            (tokens[i].isCoreToken && tokens[i].coreToken != TOKEN_TAIL);
            parseTokensIntoGraph(sub, i-ogi);
        }
        Token module = tokens[i];
        Token action = tokens[i+2];
        Token param = tokens[i+4];
        printf("%s, %s, %s\n", module.value, action.value, param.value);
//        Node* node = parseTokenAsNode(token);
//        addEdge(biggus, maliggus);
    }

}
