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
    node->edgeCount = 0;
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
    // append to graph.graph file the edge just txt: from,to,action
    FILE *file = fopen("graph.txt", "a");
    if (file == NULL) {
        printf("Error opening file!\n");
        return;
    }
    fclose(file);
    Edge* edge = createEdge(from, to, action);
    from->edges = realloc(from->edges, (from->edgeCount + 1) * sizeof(Edge) + sizeof(edge));
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

void exportNode(Node* node, FILE* file) {
    for (int i = 0; i < node->edgeCount; i++) {
        fprintf(file, "%s,link,%s\n", node->token.value, node->edges[i].to->token.value);
        if (node->edges[i].to->subgraph != NULL) {
            exportNode(node->edges[i].to->subgraph, file);
        }
    }
}
void exportGraph(Node* root) {
    FILE *file = fopen("graph.txt", "w");
    if (file == NULL) {
        printf("Error opening file!\n");
        return;
    }

    exportNode(root, file);

    fclose(file);
}

void printGraph(Node* root) {
    levelTraversal(root, 0);
}
