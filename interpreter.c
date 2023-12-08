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
#define MAX_MODULES 100

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


// ------------------ MODULES ------------------
typedef struct {
    char *name;
    Node *exports;
    int exportCount;
    Token linker;
} Module;

Module *moduleRegistry[MAX_MODULES];
int moduleRegistryCount = 0;

Module *createModule(char *name) {
    Module *module = malloc(sizeof(Module));
    module->name = name;
    Token * rootToken = malloc(sizeof(Token));
        rootToken->value = "root";
        rootToken->type = TOKEN_CORE;
        rootToken->coreToken= TOKEN_MAIN;
    Node *exports = createNode(NODE_CORE, *rootToken);
    Token *mainLinker = malloc(sizeof(Token));
        mainLinker->value = "linker";
        mainLinker->type = TOKEN_ACTION;
        mainLinker->actionToken= TOKEN_LINK;
    module->exports = exports;
    module->linker = *mainLinker;
    module->exportCount = 0;
    return module;
}

void addExportToModule(Module *module, Node *export) {
    module->exportCount++;
    addEdge(module->exports, export, module->linker);
}

void addModuleToRegistry(Module *module) {
    if (moduleRegistryCount >= MAX_MODULES) {
        printf("Module registry is full.\n");
        return;
    }
    moduleRegistry[moduleRegistryCount] = module;
    moduleRegistryCount++;
}

// ------------------ MODULES ------------------



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
            printf("UNKNOWN CORE: %d\n", root->token.coreToken);
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
            break;
        case TOKEN_CUSTOM_MODULE:
            for (int i = 0; i < root->edgeCount; i++) {
                Edge edge = root->edges[i];
                Node *child = edge.to;
                // possible actions declare,export,call
                if (edge.action.actionToken == TOKEN_DECLARE) {
                    // get the argument and add it to the module registry
                    char *export = child->token.value;
                    Module *module = createModule(export);
                    addModuleToRegistry(module);
                }
                if (edge.action.actionToken == TOKEN_EXPORT) {
                    // add an export to the last module in the registry
                    Node *export = child->edges[0].to;
                    Module *module = moduleRegistry[moduleRegistryCount - 1];
                    addExportToModule(module, export);
                }

            }
            break;
        case TOKEN_CUSTOM_MODULE_NAME:
            1+1;
            Edge edge = root->edges[0];
            if (edge.action.actionToken == TOKEN_CALL) {
                char * moduleName = root->token.value;                // find the module in the registry
                Module *module = NULL;
                for (int j = 0; j < moduleRegistryCount; j++) {
                    if (strcmp(moduleRegistry[j]->name, moduleName) == 0) {
                        module = moduleRegistry[j];
                        break;
                    }
                }
                if (module == NULL) {
                    printf("Module %s not found.\n", moduleName);
                    break;
                }
                // go through the exports and execute them
                for (int j = 0; j < module->exportCount; j++) {
                    Node *export = &module->exports[j];
                    interpretGraph(export);
                }

            }
            break;
        default:
            break;
    }
}

char * interpretGraph(Node *root) {
    // go through edges
    switch (root->type) {
        case NODE_CORE:
            return handleCore(root);
        case NODE_MODULE:
            return handleModule(root);
        case NODE_ACTION:
            break;
        default:
            break;
    }
    return NULL;
}