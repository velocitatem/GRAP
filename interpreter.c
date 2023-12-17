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
#include <math.h>


char * handleCore(Node *root);
char * handleModule(Node *root);
void handleAction(Node *root);

// ------------------ MEMORY ------------------
#define MAX_MEMORY 100
#define MAX_MODULES 100

typedef struct
{
    char* variableName;
    char* variableValue;
}
Memory;

Memory memory[MAX_MEMORY];
int memoryIndex = 0;

void setMemory
(char* variableName, char* variableValue)
{
    if
    (memoryIndex >= MAX_MEMORY)
    {
        printf("Memory is full.\n");
        return;
    }
    memory[memoryIndex].variableName = variableName;
    memory[memoryIndex].variableValue = variableValue;
    memoryIndex++;
}

char*
getMemory
(char* variableName)
{
    for
    (int i = 0; i < memoryIndex; i++)
    {
        if
        (
            strcmp(memory[i].variableName, variableName)
            == 0
        )
        {
            return memory[i].variableValue;
        }
    }
    return NULL;
}

// ------------------ MEMORY ------------------


// ------------------ MODULES ------------------
typedef struct
{
    char *name;
    Node *exports;
    int exportCount;
    Token linker;
}
Module;

Module *moduleRegistry[MAX_MODULES];
int moduleRegistryCount = 0;

Module*
createModule
(char *name)
{
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

void
addExportToModule
(Module *module, Node *export)
{
    module->exportCount++;
    addEdge(module->exports, export, module->linker);
}

void
addModuleToRegistry
(Module *module)
{
    if
    (moduleRegistryCount >= MAX_MODULES)
    {
        printf("Module registry is full.\n");
        return;
    }
    moduleRegistry[moduleRegistryCount] = module;
    moduleRegistryCount++;
}

// ------------------ MODULES ------------------


// ------------------ STR Concat stack ------------------
typedef struct
{
    char *value;
    int index;
}
ConcatStack;

ConcatStack concatStack[100];
int concatStackIndex = 0;

void
pushConcatStack
(char *value)
{
    if
    (concatStackIndex >= 100)
    {
        printf("Concat stack is full.\n");
        return;
    }
    concatStack[concatStackIndex].value = value;
    concatStack[concatStackIndex].index = 0;
    concatStackIndex++;
}

char *
popConcatStack
()
{
    if
    (concatStackIndex <= 0)
    {
        printf("Concat stack is empty.\n");
        return NULL;
    }
    concatStackIndex--;
    return concatStack[concatStackIndex].value;
}

char * // return concatenated stack
concatStackToString
()
{
    char *result = malloc(sizeof(char) * 100);
    strcpy(result, "");
    for
    (int i = 0; i < concatStackIndex; i++)
    {
        strcat(result, concatStack[i].value);
    }
    // reset stack
    concatStackIndex = 0;
    for
    (int i = 0; i < 100; i++)
    {
        concatStack[i].value = NULL;
        concatStack[i].index = 0;
    }

    return result;
}




char*
handleCore
(Node *root)
{
    char* result = NULL;
    switch
    (root->token.coreToken)
    {
        case TOKEN_MAIN:
            for
            (int i = 0; i < root->edgeCount; i++)
            {
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

int evaluateMath(Node * child)
{
    // both are a type of TOKEN_CUSTOM_NODE and start with an N_
    if
    (child->edges[0].from->token.moduleToken == TOKEN_CUSTOM_NODE
    && child->edges[0].to->token.moduleToken== TOKEN_CUSTOM_NODE
    )
    {
        char * a = child->token.value; // N_{NUMBER}
        char * b = child->edges[0].to->token.value; // N_{NUMBER}
        a = (a + 2); // remove N_
        b = (b + 2); // remove N_
        switch (child->edges[0].action.actionToken)
        {
            case TOKEN_ADDITION:
                return atoi(a) + atoi(b);
            case TOKEN_SUBTRACTION:
                return atoi(a) - atoi(b);
            case TOKEN_MULTIPLICATION:
                return atoi(a) * atoi(b);
            case TOKEN_DIVISION:
                return atoi(a) / atoi(b);
            case TOKEN_MODULUS:
                return atoi(a) % atoi(b);
            default:
                return 0;
                break;
        }
    }
    else
    {
        // if not base case, then we have a subgraph
        // recursive call
        int a = evaluateMath(child->edges[0].to);
        int b = evaluateMath(child->edges[1].to);
        switch (child->edges[0].action.actionToken)
        {
            case TOKEN_ADDITION:
                return a + b;
            case TOKEN_SUBTRACTION:
                return a - b;
            case TOKEN_MULTIPLICATION:
                return a * b;
            case TOKEN_DIVISION:
                return a / b;
            case TOKEN_MODULUS:
                return a % b;
            default:
                return 0;
                break;
        }
    }
}

char*
handleModule
(Node *root)
{
    // go through edges
    switch
    (root->token.moduleToken)
    {
        case TOKEN_MATH:
            for
            (int i = 0; i < root->edgeCount; i++)
            {
                Edge edge = root->edges[i];
                Node *child = edge.to;

                //Parse arguments
                char * c;
                // resolve possible subgraph
                if
                (child->token.type == TOKEN_CORE
                && child->token.coreToken == TOKEN_MAIN)
                {
                    c = interpretGraph(child);
                }
                else
                {
                    c = child->token.value;
                }
                //strip " if present
                if (c[0] == '\"')
                {
                    c += 1;
                }
                if (c[strlen(c) - 1] == '\"')
                {
                    c[strlen(c) - 1] = '\0';
                }

                //parse
                c = strtok(c, " ");
                float a, b;
                for(int j = 0; j < 2 && c; j++){
                    char * ptr;
                    float n = strtof(c, &ptr);
                    if(strcmp(ptr, "") != 0){
                        if(strcmp(c, ptr) != 0){
                            printf("Syntax error.\n");
                            return 0;
                        }

                        //get value from memory
                        char * ptr2;
                        char * varname = (char*)malloc(100 * sizeof(char));
                        sprintf(varname, "\"%s\"", ptr);
                        char *d = getMemory(varname);

                        if(d == NULL){
                            printf("Unknown variable %s.\n", varname);
                            free(varname);
                            return 0;
                        }

                        free(varname);

                        //copy variable
                        char * m = malloc(strlen(d) + 1);
                        strcpy(m, d);

                        //strip "
                        m += 1;
                        m[strlen(m)-1] = '\0';

                        n = strtof(m, &ptr2);

                        if(strcmp(ptr2, "") != 0){
                            printf("Syntax error.\n");
                            free(m);
                            return 0;
                        }
                    }
                    if (j==0) a = n;
                    else b = n;
                    c = strtok(NULL, " ");
                }
                c = calloc(100, sizeof (char));


                if (edge.action.actionToken == TOKEN_EVAL)
                {
                    Node *child = root->edges[i].to;
                    // regularly we would call main recursively
                    // but in this case we want to evaluate the expression
                    // (NUMBER | +/-%*| NUMBER) where nubmer can be a subgraph
                    int result = evaluateMath(child->edges[0].to);
                    char *resultString = malloc(sizeof(char) * 100);
                    sprintf(resultString, "\"%d\"", result);
                    // HACK: TODO change all return types to a custom type
                    // that is a union of various types
                    return resultString;
                }
                switch
                (edge.action.actionToken)
                {
                    case TOKEN_ADDITION:
                        sprintf(c, "%g", a + b);
                        return c;
                    case TOKEN_SUBTRACTION:
                        sprintf(c, "%g", a - b);
                        return c;
                    case TOKEN_MULTIPLICATION:
                        sprintf(c, "%g", a * b);
                        return c;
                    case TOKEN_DIVISION:
                        sprintf(c, "%g", a / b);
                        return c;
                    case TOKEN_MODULUS:
                        sprintf(c, "%g", (float)((int)a % (int)b));
                        return c;
                    case TOKEN_POWER:
                        sprintf(c, "%g", pow(a,b));
                        return c;

                }
            }
            break;
        case TOKEN_BITS:
            for
            (int i = 0; i < root->edgeCount; i++)
            {
                Node *child = root->edges[i].to;
                // if is a root node, then we have a subgraph
                if
                (child->token.type == TOKEN_CORE
                && child->token.coreToken == TOKEN_MAIN)
                {
                    char *subgraphResult = interpretGraph(child);
                    if (subgraphResult != NULL) {
                        // turn from binary string to int
                        // result will be something like "101010" or "101"=5
                        int binary = 0;
                        for
                        (int i = 0; i < strlen(subgraphResult)-1; i++)
                        {
                            binary = binary << 1;
                            if (subgraphResult[i] == '1') {
                                binary = binary | 1;
                            }
                        }
                        int result = binary;
                        if
                        (root->edges->action.actionToken
                        == TOKEN_RIGHTSHIFT)
                        {
                            result = result >> 1;
                        }
                        else if
                        (root->edges->action.actionToken
                        == TOKEN_LEFTSHIFT)
                        {
                            result = result << 1;
                        }
                        char *resultString = malloc(sizeof(char) * 100);
                        sprintf(resultString, "%d", result);
                        return resultString;
                    }
                }
            }
            break;
        case TOKEN_IO:
            for
            (int i = 0; i < root->edgeCount; i++)
            {
                Edge edge = root->edges[i];
                Node *child = edge.to;
                // handle cases when we have a subgraph
                if
                (child->token.type == TOKEN_CORE
                && child->token.coreToken == TOKEN_MAIN)
                {
                    char *subgraphResult = interpretGraph(child);
                    if
                    (subgraphResult != NULL)
                    {
                        char *line = strtok(subgraphResult, "<n>");
                        while (line != NULL)
                        {
                            printf("%s\n", line);
                            line = strtok(NULL, "<n>");
                        }
                    }
                    break;
                }
                if
                (edge.action.actionToken == TOKEN_SAY)
                {
                    char *say = child->token.value;
                    // clear literal \" if present
                    if
                    (say[0] == '\"')
                    {
                        say = say + 1;
                    }
                    if
                    (say[strlen(say) - 1] == '\"')
                    {
                        say[strlen(say) - 1] = '\0';
                    }

                    // check if we have a newline inside the string
                    // if so, print each line separately
                    // split by \\n but make sure not to get just \n
                    char *line = strtok(say, "<N>");
                    while (line != NULL)
                    {
                        printf("%s\n", line);
                        line = strtok(NULL, "<N>");
                    }
                }
                if
                (edge.action.actionToken == TOKEN_ASK)
                {
                    printf("User input (%s): ", child->token.value);
                    char * in = calloc(100, sizeof(char));
                    scanf("%s", in);
                    return in;
                    //TODO: fix cli double ">>"
                }
            }
            break;
        case TOKEN_MEM:
            for
            (int i = 0; i < root->edgeCount; i++)
            {
                Edge edge = root->edges[i];
                if
                (edge.action.actionToken == TOKEN_SAVE)
                {
                    Node *child = edge.to;
                    Edge var = child->edges[0].to->edges[0];
                    char *varname = var.action.value;
                    char *varvalue = var.to->token.value;
                    // maybe var value is a subgraph
                    if (var.to->token.type == TOKEN_CORE
                        && var.to->token.coreToken == TOKEN_MAIN) {
                        varvalue = interpretGraph(var.to);
                    }
                    setMemory(varname, varvalue);
                    return NULL;
                }
                if
                (edge.action.actionToken == TOKEN_GET)
                {
                    // simple param extraction as in IO
                    Node *child = edge.to;
                    char *varname = child->token.value;
                    char *varvalue = getMemory(varname);
                    return varvalue;
                }
            }
            break;
        case TOKEN_CUSTOM_MODULE:
            for
            (int i = 0; i < root->edgeCount; i++)
            {
                Edge edge = root->edges[i];
                Node *child = edge.to;
                // possible actions declare,export,call
                if
                (edge.action.actionToken == TOKEN_DECLARE)
                {
                    // get the argument and add it to the module registry
                    char *export = child->token.value;
                    Module *module = createModule(export);
                    addModuleToRegistry(module);
                }
                if
                (edge.action.actionToken == TOKEN_EXPORT)
                {
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
            if
            (edge.action.actionToken == TOKEN_CALL)
            {
                char * moduleName = root->token.value;                // find the module in the registry
                Module *module = NULL;
                for
                (int j = 0; j < moduleRegistryCount; j++)
                {
                    if
                    (strcmp(moduleRegistry[j]->name, moduleName) == 0)
                    {
                        module = moduleRegistry[j];
                        break;
                    }
                }
                if
                (module == NULL)
                {
                    printf("Module %s not found.\n", moduleName);
                    break;
                }
                // go through the exports and execute them
                for
                (int j = 0; j < module->exportCount; j++)
                {
                    Node *export = &module->exports[j];
                    interpretGraph(export);
                }
            }
            break;

        case TOKEN_STR:
            for
            (int i = 0; i < root->edgeCount; i++)
            {
                Edge edge = root->edges[i];
                Node *child = edge.to;
                // handle cases when we have a subgraph
                // concat and concadd
                char *subgraphResult;
                if
                (child->token.type == TOKEN_CORE
                && child->token.coreToken == TOKEN_MAIN)
                {
                     subgraphResult= interpretGraph(child);
                }
                else
                {
                    subgraphResult = child->token.value;
                }
                if
                (edge.action.actionToken == TOKEN_CONCADD)
                {
                    // add to stack
                    // trim " at the beginning and end
                    if
                    (subgraphResult[0] == '\"')
                    {
                        subgraphResult = subgraphResult + 1;
                    }
                    if
                    (subgraphResult[strlen(subgraphResult) - 1] == '\"')
                    {
                        subgraphResult[strlen(subgraphResult) - 1] = '\0';
                    }
                    pushConcatStack(subgraphResult);
                }
                if
                (edge.action.actionToken == TOKEN_CONCAT)
                {
                    // pop from stack
                    char *result = concatStackToString();
                    // clear stack
                    return result;
                }
            }
            break;
        default:
            break;
    }
}

char *
interpretGraph
(Node *root)
{
    // go through edges
    switch
    (root->type)
    {
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