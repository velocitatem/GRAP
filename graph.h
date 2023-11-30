//
// Created by i-be-keggles on 2023-11-30.
//

#ifndef PROGRAMMING_LANGUAGE_IN_C_GRAPH_H
#define PROGRAMMING_LANGUAGE_IN_C_GRAPH_H

#include "tokens.h"
#include "lexer.h"
#include <stdlib.h>

typedef enum {
    NODE_MODULE,
    NODE_ACTION,
    NODE_ARGUMENT,
    NODE_SUBGRAPH,
    NODE_CORE
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


Edge *createEdge(Node *from, Node *to, Token action);
Node *createNode(NodeType type, Token token);
void addEdge(Node *from, Node *to, Token action);
int numEdges(Node *node);

#endif //PROGRAMMING_LANGUAGE_IN_C_GRAPH_H
