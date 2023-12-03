//
// Created by velocitatem on 12/3/23.
//

#include "interpreter.h"
#include "tokens.h"
#include "lexer.h"
#include "graph.h"
#include <stdio.h>

typedef struct Memmory {
    char *key;
    char *value;
} Memmory;

int memmorySize = 100;
Memmory *memmory;

void handleCore(Node *root);
void handleModule(Node *root);
void handleAction(Node *root);


void initMemmory() {
    memmory = malloc(memmorySize * sizeof(Memmory));
}

void handleCore(Node *root) {
    switch (root->token.coreToken) {
        case TOKEN_MAIN:
            for (int i = 0; i < root->edgeCount; i++) {
                // maybe sort by module types
                Node *child = root->edges[i].to;
                handleModule(child);
            }
            break;

        default:
            printf("UNKNOWN CORE\n");
            break;
    }
}

void handleModule(Node *root) {
    // go through edges
    switch (root->token.moduleToken) {
        case TOKEN_IO:
            for (int i = 0; i < root->edgeCount; i++) {
                Edge edge = root->edges[i];
                Node *child = edge.to;
                if (edge.action.actionToken == TOKEN_SAY) {
                    printf("~ %s\n", child->token.value);
                }
            }
            break;
        case TOKEN_MEM:
            for (int i = 0; i < root->edgeCount; i++) {
                Edge edge = root->edges[i];
                Node *child = edge.to;
                if (edge.action.actionToken == TOKEN_SAVE) {
                    // TODO save to memmory
                }
            }
        default:
            break;
    }
}


void interpretGraph(Node *root) {
    if (root == NULL) {
        return;
    }
    switch (root->token.type) { // CORE, MODULE, ACTION, ARGUMENT, SUBGRAPH
        case TOKEN_CORE:
            handleCore(root);
            break;
        case TOKEN_MODULE:
            break;
        case TOKEN_ACTION:
            break;
        default:
            break;

    }
}
