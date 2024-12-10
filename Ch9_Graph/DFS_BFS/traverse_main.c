#include "graph.h"
#include "traverse.h"

int main() {
    int mode = 0;
    Graph* g = createGraph();
    Vertex* v1 = createVertex(10);
    Vertex* v2 = createVertex(20);
    Vertex* v3 = createVertex(30);
    Vertex* v4 = createVertex(40);
    Vertex* v5 = createVertex(50);
    Vertex* v6 = createVertex(60);
    Vertex* v7 = createVertex(70);

    addVertex(g, v1);
    addVertex(g, v2);
    addVertex(g, v3);
    addVertex(g, v4);
    addVertex(g, v5);
    addVertex(g, v6);
    addVertex(g, v7);

    addEdge(v1, createEdge(v1, v2, 0));
    addEdge(v1, createEdge(v1, v3, 0));
    
    addEdge(v2, createEdge(v2, v4, 0));
    addEdge(v2, createEdge(v2, v5, 0));


    addEdge(v3, createEdge(v3, v4, 0));
    addEdge(v3, createEdge(v3, v6, 0));

    addEdge(v4, createEdge(v4, v5, 0));
    addEdge(v4, createEdge(v4, v7, 0));

    addEdge(v5, createEdge(v5, v7, 0));
    
    addEdge(v6, createEdge(v6, v7, 0));

    printf("Enter Traversal Mode (0: DFS, 1:BFS) >> ");
    scanf("%d", &mode);

    if (mode == 0) DFS(g->vertices);
    else {
        Queue* q = NULL;
        createQueue(&q);
        BFS(v1, q);
        destroyQueue(q);
    }
    destroyGraph(g);
    return 0;
}