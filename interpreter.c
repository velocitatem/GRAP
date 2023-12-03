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


void handleCore(Node *root);
void handleModule(Node *root);
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
                if (edge.action.actionToken == TOKEN_SAVE) {
                    // todo wrap in try
                    Node *child = edge.to;
                    Edge var = child->edges[0].to->edges[0];
                    char *varname = var.action.value;
                    char *varvalue = var.to->token.value;
                    setMemory(varname, varvalue);
                }
                if (edge.action.actionToken == TOKEN_GET) {
                    // simple param extraction as in IO
                    Node *child = edge.to;
                    char *varname = child->token.value;
                    char *varvalue = getMemory(varname);
                    printf("\t%s = %s\n", varname, varvalue);
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
