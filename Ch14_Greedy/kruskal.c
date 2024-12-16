#include <stdio.h>
#include <stdlib.h>

#define V_CNT 5


int comparator(const void* lhs, const void* rhs) {
	// 2d array pointer, x,y are const pointer of int[3].
	const int(*x)[3] = lhs;
	const int(*y)[3] = rhs;
	
	return (*x)[2] - (*y)[2];
}

void initSet(int* parent, int* rank, int n) {
	for (int i = 0; i < n; ++i) {
		parent[i] = i;		// Initialize each vertex to it's own parent.
		rank[i] = 0;		// They are all rank 0 at first.
	}
}

int findParent(int* parent, int vertex) {
	if (parent[vertex] == vertex) return vertex;
	return parent[vertex] = findParent(parent, parent[vertex]);
}

void unionSet(int v1, int v2, int* parent, int* rank, int n) {
	v1 = findParent(parent, v1);
	v2 = findParent(parent, v2);
	
	if (rank[v1] < rank[v2])
		parent[v1] = v2;
	else if (rank[v1] > rank[v2])
		parent[v2] = v1;
	else { // rand[v1] == rank[v2]
		parent[v2] = v1;
		rank[v1]++;			// Increase v1's rank
	}
}

void kruskal(int n, int edge[n][3]) {
	// Because Kruskal is subset of greedy algorithm,
	// We should sort edge with ascending order to pick minimum weight edge.
	qsort(edge, n, sizeof(edge[0]), comparator);
	
	// Instead using naive union-find algotihm which has potential O(n) in worst case,
	// We can use union-by-rank which can check graph's cycle in almost constant time. 
	int mstCost = 0;
	int parent[n], rank[n];
	initSet(parent, rank, n);
	
	printf("Following are the edges in the constructed MST\n");
	for (int i = 0; i < n; ++i) {
		int v1 = findParent(parent, edge[i][0]);
		int v2 = findParent(parent, edge[i][1]);
		int cost = edge[i][2];
		
		if (v1 != v2) {
			unionSet(v1, v2, parent, rank, n);	// make them union-set
			mstCost += cost;
			printf("%d ---- %d => %d\n", edge[i][0], edge[i][1], cost);
		}
	}
	printf("Minimum Cost Spanning Tree: %d\n", mstCost);
}

int main() {
	int edge[V_CNT][3] = {
		{0, 1, 10},
		{0, 2, 6},
		{0, 3, 5},
		{1, 3, 15},
		{2, 3, 4}
	};
	
	kruskal(V_CNT, edge);
	
	return 0;
}