#ifndef __GRAPH_H
#define __GRAPH_H

#include <stdio.h>
#include <stdlib.h>

enum visitMode { VISITED, NOTVISITED };

typedef char vElementType;

typedef struct _Vertex {
    vElementType data;
    int visited;
    int idx;
    struct _Vertex* next;
    struct _Edge*   connectedEdges;
} Vertex;

typedef struct _Edge {
    int weight;
    struct _Edge* next;
    Vertex* from;
    Vertex* to;
} Edge;

typedef struct _Graph {
    Vertex* vertices;
    int     verticeCount;
} Graph;

Graph*      createGraph();
void        destroyGraph(Graph* g);
Vertex*     createVertex(vElementType data);
void        destroyVertex(Vertex* v);
Edge*       createEdge(Vertex* from, Vertex* to, int weight);
void        destroyEdge(Edge* e);
void        addVertex(Graph* g, Vertex* v);
void        addEdge(Vertex* v, Edge* e);
void        printGraph (Graph* g);

#endif
