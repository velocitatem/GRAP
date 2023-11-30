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
    // Add the edge to the graph
}

Node* parseTokenAsNode(Token token) {
    if (token.isCoreToken) {

    }
    // For example, if token is a known module name, create a NODE_MODULE type node
    // You'll need some logic here to decide the type based on your language's rules
}

void parseTokensIntoGraph(Token tokens[], int tokenCount) {
    for (int i = 0; i < tokenCount; i++) {
        Token token = tokens[i];
        Node* node = parseTokenAsNode(token);
        // Add the node to the graph
        // You'll need a function for this
    }

}
