#ifndef PROGRAMMING_LANGUAGE_IN_C_PARSER_H
#define PROGRAMMING_LANGUAGE_IN_C_PARSER_H

#include "tokens.h"
#include "lexer.h"

typedef enum {
    NODE_MODULE,
    NODE_ACTION,
    NODE_ARGUMENT,
    NODE_SUBGRAPH
} NodeType;

typedef struct Node {
    NodeType type;
    Token token;
    struct Edge* edges; // Edges to other nodes
    struct Node* subgraph; // Points to a subgraph if this node is of type NODE_SUBGRAPH
} Node;

typedef struct Edge {
    struct Node* from;
    struct Node* to;
    Token action;
} Edge;


void parseTokensIntoGraph(Token tokens[], int tokenCount);
Edge *createEdge(Node *from, Node *to, Token action);
Node *createNode(NodeType type, Token token);
void addEdge(Node *from, Node *to, Token action);
Node *parseTokenAsNode(Token token);



#endif // PROGRAMMING_LANGUAGE_IN_C_PARSER_H