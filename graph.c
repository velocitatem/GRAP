//
// Created by i-be-keggles on 2023-11-30.
//

#include "graph.h"
#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include "parser.h"


Node* createNode(NodeType type, Token token) {
    Node* node = (Node*) malloc(sizeof(Node));
    node->type = type;
    node->token = token;
    node->edges = NULL;
    node->subgraph = NULL;
    return node;
}

Edge* createEdge(Node* from, Node* to, Token action) {
    Edge* edge = (Edge*) malloc(sizeof(Edge));
    edge->from = from;
    edge->to = to;
    edge->action = action;
    return edge;
}

void addEdge(Node* from, Node* to, Token action) {
    Edge* edge = createEdge(from, to, action);
    int i = numEdges(from);
    from->edges = realloc(to->edges, sizeof(from->edges) + sizeof(struct Edge));
    from->edges[i] = *edge;
}

int numEdges(Node* node){
    int i = 0;
    while(node->edges != NULL){
        i ++;
    }
    return i;
}