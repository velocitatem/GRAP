#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include "parser.h"
#include "tokens.h"


Node*
parseTokenAsNode
(Token token)
{
    NodeType t;

    //TODO: better node type assignment
    switch
    ( token.type)
    {
        case TOKEN_CORE:
            t = NODE_CORE;
            break;
        case TOKEN_MODULE:
            t = NODE_MODULE;
            break;
        case TOKEN_ACTION:
            t = NODE_ACTION;
            break;
        default:
            t = NODE_ARGUMENT;
            break;

    }

    return createNode(t, token);
}

Node *
parseTokensIntoGraph
(Token tokens[], int tokenCount)
{
    // create new token
    Token * rootToken = malloc(sizeof(Token));
    rootToken->value = "root";
    rootToken->type = TOKEN_CORE;
    rootToken->coreToken = TOKEN_MAIN;


    Token *mainLinker = malloc(sizeof(Token));
    mainLinker->value = "linker";
    mainLinker->type = TOKEN_ACTION;
    mainLinker->actionToken= TOKEN_LINK;

    Node *root = createNode(NODE_CORE, *rootToken);
    for
    (int i = 0; i < tokenCount; i+=5)
    {
        Token module = tokens[i];
        Token action = tokens[i+2];
        Token param = tokens[i+4];
        bool isSubGraph = false;
        Node *subGraph = NULL;
        if
        (param.type == TOKEN_CORE
        && param.coreToken == TOKEN_HEAD)
        {
            // user opened sub-graph by (module | action | core)
            // core could be another sub-graph (module | action | ( module | action | core))
            // find the end of the sub-graph, encapsulating other sub graphs
            int subGraphStart = i+4;
            int subGraphEnd = subGraphStart;
            int openSubSubGraphs = 0;
            for
            (int j = subGraphStart; j < tokenCount; j++)
            {
                if
                (tokens[j].type == TOKEN_CORE
                && tokens[j].coreToken == TOKEN_HEAD)
                {
                    openSubSubGraphs++;
                }
                if
                (tokens[j].type == TOKEN_CORE
                && tokens[j].coreToken == TOKEN_TAIL)
                {
                    if
                    (openSubSubGraphs == 0)
                    {
                        subGraphEnd = j;
                        break;
                    }
                    else
                    {
                        openSubSubGraphs--;
                        if
                        (openSubSubGraphs == 0)
                        {
                            subGraphEnd = j;
                            break;
                        }
                    }
                }
            }
            // first token and last token:
            // parse sub-graph
            Token *subGraphTokens = malloc(sizeof(Token) * (subGraphEnd - subGraphStart ));
            int k = 0;
            for
            (int j = subGraphStart+1; j < subGraphEnd; j++)
            {
                subGraphTokens[k] = tokens[j];
                k++;
            }
            subGraph = parseTokensIntoGraph(subGraphTokens, subGraphEnd - subGraphStart - 1);
            //printGraph(subGraph);
            // add sub-graph to root
            // skip to end of sub-graph
            isSubGraph = true;
            // re-shift because of sub-graph but wathc for +=5 in the loop
            i = subGraphEnd - 4;
        }
        Node* a = parseTokenAsNode(module);
        Node* b;
        // a, b
        if
        (!isSubGraph)
        {
            b = parseTokenAsNode(param);
        }
        else
        {
            b = subGraph;
        }
        // print both a and b
        addEdge(root, a, *mainLinker);
        addEdge(a, b, action);

    }
    return root;

}
