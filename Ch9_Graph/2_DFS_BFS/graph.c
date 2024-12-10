#include "graph.h"

Graph* createGraph() {
    Graph* newGraph = (Graph*)malloc(sizeof(Graph));

    newGraph->verticeCount  = 0;
    newGraph->vertices      = NULL;
    
    return newGraph;
}

void destroyGraph(Graph* g) {
    while (g->vertices != NULL) {
        Vertex* v = g->vertices->next;
        destroyVertex(g->vertices);
        g->vertices = v;
    }
    free(g);
}

Vertex* createVertex(ElementType data) {
    Vertex* newVertex = (Vertex*)malloc(sizeof(Vertex));

    newVertex->data             = data;
    newVertex->next             = NULL;
    newVertex->connectedEdges   = NULL;
    newVertex->idx              = -1;
    newVertex->visited          = NOTVISITED;
    
    return newVertex;
}

void destroyVertex(Vertex* v) {
    while (v->connectedEdges != NULL) {
        Edge* e = v->connectedEdges->next;
        destroyEdge(v->connectedEdges);
        v->connectedEdges = e;
    }
    free(v);
}

Edge* createEdge(Vertex* from, Vertex* to, int weight) {
    Edge* newEdge = (Edge*)malloc(sizeof(Edge));
    
    newEdge->from       = from;
    newEdge->to         = to;
    newEdge->weight     = weight;
    newEdge->next       = NULL;
    
    return newEdge;
}

void destroyEdge(Edge* e) {
    free(e);
}

void addVertex(Graph* g, Vertex* newVertex) {
    Vertex* v = g->vertices;
    // 현재 그래프에 아무런 정점이 없다면, 새로운 정점 추가
    if (v == NULL) g->vertices = newVertex;
    else {
    // 정점 리스트 중 제일 끝에 새로운 정점 추가
        while (v->next != NULL) v = v->next;
        v->next = newVertex;
    }
    newVertex->idx = ++(g->verticeCount);
}

void addEdge(Vertex* v, Edge* newEdge) {
    if (v->connectedEdges == NULL)
        v->connectedEdges = newEdge;
    else {
        Edge* e = v->connectedEdges;
        while (e->next != NULL) e = e->next;
        e->next = newEdge;
    }
}

void printGraph (Graph* g) {
    Vertex* v = g->vertices;
    Edge* e = NULL;

    while (v != NULL) {
        printf("Vertex data [%c] : \n\t", v->data);
        e = v->connectedEdges;
        while (e != NULL) {
            printf("Edge( [%d], to [%c])  ", e->weight, e->to->data);
            e = e->next;
        }
        printf("\n");
        v = v->next;
    }
    printf("\n");
}
