#include "topologicalSort.h"

void topologicalSort(Vertex* v, List* list) {
    while (v && v->visited == NOTVISITED) {
        topologicalDFS(v, list);
        v = v->next;
    }
}

void topologicalDFS(Vertex* v, List* list) {
    v->visited = VISITED;

    Edge* e = v->connectedEdges;
    while (e != NULL) {     // 연결된 간선 모두 탐색
        if (e->to->visited == NOTVISITED)
            topologicalDFS(e->to, list);
        e = e->next;
    }
    printf("%c  ", v->data);
    addNode(list, v);
}

