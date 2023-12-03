//
// Created by i-be-keggles on 2023-11-30.
//

#include "graph.h"
#include <stdio.h>
#include <stdlib.h>
#include <string.h>


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
    // print edge
    //printf("%s -[%s]-> %s\n", from->token.value, action.value, to->token.value);
    Edge* edge = createEdge(from, to, action);
    from->edges = realloc(from->edges, (from->edgeCount + 1) * sizeof(Edge));
    from->edges[from->edgeCount] = *edge;
    from->edgeCount++;
}

int numEdges(Node* node){
    return node->edgeCount;
}

void levelTraversal(Node* root, int level) {
    // visually print graph
    // use indentation to show level
    // print root
    printf("%s\n", root->token.value);
    // print edges
    for (int i = 0; i < root->edgeCount; i++) {
        // print indentation
        for (int j = 0; j < level; j++) {
            printf("  ");
        }
        // print edge
        printf("-> %s\n", root->edges[i].to->token.value);
        // print subgraph
        if (root->edges[i].to->subgraph != NULL) {
            levelTraversal(root->edges[i].to->subgraph, level + 1);
        }
    }

}

void printGraph(Node* root) {
    levelTraversal(root, 0);
}
