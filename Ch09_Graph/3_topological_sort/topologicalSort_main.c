#include "topologicalSort.h"

int main() {
    List* list;
    makeList(list);

    Graph* graph = createGraph();

    Vertex* a = createVertex('A');
    Vertex* b = createVertex('B');
    Vertex* c = createVertex('C');
    Vertex* d = createVertex('D');
    Vertex* e = createVertex('E');
    Vertex* f = createVertex('F');
    Vertex* g = createVertex('G');
    Vertex* h = createVertex('H');

    addVertex(graph, a);
    addVertex(graph, b);
    addVertex(graph, c);
    addVertex(graph, d);
    addVertex(graph, e);
    addVertex(graph, f);
    addVertex(graph, g);

    addEdge(a, createEdge(a, c, 0));
    addEdge(a, createEdge(a, d, 0));
    
    addEdge(b, createEdge(b, c, 0));
    addEdge(b, createEdge(b, e, 0));

    addEdge(c, createEdge(c, f, 0));

    addEdge(d, createEdge(d, f, 0));
    addEdge(d, createEdge(d, g, 0));

    addEdge(e, createEdge(e, g, 0));

    addEdge(f, createEdge(f, h, 0));
    
    addEdge(g, createEdge(g, h, 0));


    topologicalSort(graph->vertices, list);

    printf("Topological Sort Result: ");
    
    Node* temp = list->head->next;
    while (temp) {
        printf("%c  ", temp->data->data);
        temp = temp->next;
    }
    printf("\n");

    removeList(list);
    destroyGraph(graph);

    return 0;
}