//
// Created by velocitatem on 12/3/23.
//

#include "interpreter.h"
#include "tokens.h"
#include "lexer.h"
#include "graph.h"
#include <stdio.h>
#include <stdlib.h>
#include <string.h>


char * handleCore(Node *root);
char * handleModule(Node *root);
void handleAction(Node *root);

// ------------------ MEMORY ------------------
#define MAX_MEMORY 100

typedef struct {
    char* variableName;
    char* variableValue;
} Memory;

Memory memory[MAX_MEMORY];
int memoryIndex = 0;

void setMemory(char* variableName, char* variableValue) {
    if(memoryIndex >= MAX_MEMORY) {
        printf("Memory is full.\n");
        return;
    }
    memory[memoryIndex].variableName = variableName;
    memory[memoryIndex].variableValue = variableValue;
    memoryIndex++;
}

char* getMemory(char* variableName) {
    for(int i = 0; i < memoryIndex; i++) {
        if(strcmp(memory[i].variableName, variableName) == 0) {
            return memory[i].variableValue;
        }
    }
    return NULL;
}

// ------------------ MEMORY ------------------



char* handleCore(Node *root) {
    char* result = NULL;
    switch (root->token.coreToken) {
        case TOKEN_MAIN:
            for (int i = 0; i < root->edgeCount; i++) {
                Node *child = root->edges[i].to;
                result = handleModule(child);
            }
            break;
        default:
            printf("UNKNOWN CORE\n");
            break;
    }
    return result;
}


char* handleModule(Node *root) {
    // go through edges
    switch (root->token.moduleToken) {
        case TOKEN_IO:
            for (int i = 0; i < root->edgeCount; i++) {
                Edge edge = root->edges[i];
                Node *child = edge.to;
                // handle cases when we have a subgraph
                if (child->token.type == TOKEN_CORE && child->token.coreToken == TOKEN_MAIN) {
                    char *subgraphResult = interpretGraph(child);
                    if (subgraphResult != NULL) {
                        printf("%s\n", subgraphResult);
                    }
                    break;
                }
                if (edge.action.actionToken == TOKEN_SAY) {
                    printf("%s\n", child->token.value);
                }
            }
            break;
        case TOKEN_MEM:
            for (int i = 0; i < root->edgeCount; i++) {
                Edge edge = root->edges[i];
                if (edge.action.actionToken == TOKEN_SAVE) {
                    // todo wrap in try
                    Node *child = edge.to;
                    Edge var = child->edges[0].to->edges[0];
                    char *varname = var.action.value;
                    char *varvalue = var.to->token.value;
                    setMemory(varname, varvalue);
                    return NULL;
                }
                if (edge.action.actionToken == TOKEN_GET) {
                    // simple param extraction as in IO
                    Node *child = edge.to;
                    char *varname = child->token.value;
                    char *varvalue = getMemory(varname);
                    return varvalue;
                }
            }
        default:
            break;
    }
}

char * interpretGraph(Node *root) {
    // go through edges
    switch (root->type) {
        case NODE_CORE:
            return handleCore(root);
            break;
        case NODE_MODULE:
            return handleModule(root);
        case NODE_ACTION:
            break;
        default:
            break;
    }
    return NULL;
}