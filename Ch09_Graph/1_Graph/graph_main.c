#include "graph.h"

int main() {
    Graph* g = createGraph();
    Vertex* v1 = createVertex('A');
    Vertex* v2 = createVertex('B');
    Vertex* v3 = createVertex('C');
    Vertex* v4 = createVertex('D');
    Vertex* v5 = createVertex('E');

    addVertex(g, v1);
    addVertex(g, v2);
    addVertex(g, v3);
    addVertex(g, v4);
    addVertex(g, v5);

    addEdge(v1, createEdge(v1, v2, 0));
    addEdge(v1, createEdge(v1, v3, 0));
    addEdge(v1, createEdge(v1, v4, 0));
    addEdge(v1, createEdge(v1, v5, 0));
    
    addEdge(v2, createEdge(v2, v1, 0));
    addEdge(v2, createEdge(v2, v3, 0));
    addEdge(v2, createEdge(v2, v5, 0));


    addEdge(v3, createEdge(v3, v1, 0));
    addEdge(v3, createEdge(v3, v2, 0));

    addEdge(v4, createEdge(v4, v1, 0));
    addEdge(v4, createEdge(v4, v5, 0));

    addEdge(v5, createEdge(v5, v1, 0));
    addEdge(v5, createEdge(v5, v2, 0));
    addEdge(v5, createEdge(v5, v4, 0));

    printGraph(g);

    destroyGraph(g);

    return 0;
}

/*

Vertex data [A] : 
        Edge( [0], to [B])  Edge( [0], to [C])  Edge( [0], to [D])  Edge( [0], to [E])  
Vertex data [B] :
        Edge( [0], to [A])  Edge( [0], to [C])  Edge( [0], to [E])
Vertex data [C] :
        Edge( [0], to [A])  Edge( [0], to [B])
Vertex data [D] :
        Edge( [0], to [A])  Edge( [0], to [E])
Vertex data [E] :
        Edge( [0], to [A])  Edge( [0], to [B])  Edge( [0], to [D])

*/