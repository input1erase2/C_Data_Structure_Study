#include "traverse.h"

// DFS - 방문(및 출력) -> 연결된 간선들로 갈 수 있는 정점들 중 방문하지 않은 정점으로 이동
void DFS(Vertex* v) {
    printf("  %d", v->data);
    v->visited = VISITED;
    Edge* e = v->connectedEdges;
    while (e) {
        if (e->to->visited == NOTVISITED) DFS(e->to);
        e = e->next;
    }
}
// BFS - 방문(및 출력) -> 연결된 간선들로 갈 수 있는 모든 정점을 큐에 enqueue
// 큐가 빌 때까지 이 과정을 반복, 큐가 빌 때 탐색이 종료.
void BFS(Vertex* v, Queue* q) {
    printf("  %d", v->data);
    v->visited = VISITED;

    Edge* e = v->connectedEdges;
    enqueue(q, createNode(v));

    while (!isQueueEmpty(q)) {
        Node* popped = dequeue(q);
        v = popped->data;
        e = popped->data->connectedEdges;
        while (e) {
            v = e->to;
            if (v->visited != VISITED) {
                printf("  %d", v->data);
                v->visited = VISITED;
                enqueue(q, createNode(v));
            }
            e = e->next;
        }
    }
}