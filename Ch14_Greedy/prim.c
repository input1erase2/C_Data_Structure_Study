#include <stdio.h>
#include <stdlib.h>
#include <string.h>


#define TRUE			1
#define FALSE			0
#define V_CNT			5
#define INF				1e9+1


void printMST(int* mst, int graph[][V_CNT]) {
	printf("Edge\tWeight\n");
	for (int i = 1; i < V_CNT; ++i)
		printf("%d - %d\t%d\n", mst[i], i, graph[i][mst[i]]);
	printf("\n\n");
}

// Find the vertex which has connected with edge has minimum weight
// and the vertex shouldn't include MST yet.
int findMinVertex(int* weights, int* verticeFlags) {
	int min = INF, minIdx = 0;
	for (int i = 0; i < V_CNT; ++i) {
		// If i'th vertex is not included MST and 'min' can be updated,
		if (verticeFlags[i] == FALSE && weights[i] < min) {
			min = weights[i];
			minIdx = i;
		}
	}
	return minIdx;
}

// MST - prim algorithm ( Time complexity = O(V²) or O(E + log(V)) )
// Construct MST for a graph represented using adjacency matrix
// This prim algorithm doesn't use priority queue(= heap) so O(V^2)
void prim(int graph[][V_CNT]) {
	int mst[V_CNT], weights[V_CNT], verticesFlag[V_CNT];
	
	// Initialize weights array and flag array which checks each vertice is in MST.
	for (int i = 0; i < V_CNT; ++i) {
		weights[i] = INF;
		verticesFlag[i] = FALSE;
	}
	// Pick first vertex and input to MST and initialize it to zero.
	weights[0] = 0;
	mst[0] = -1;
	
	for (int i = 0; i < V_CNT - 1; ++i) {
		// Pick the vertex which is connected edge has minimum weight
		// from vertices not yet included in MST
		int selected = findMinVertex(weights, verticesFlag);
		verticesFlag[selected] = TRUE;
		for (int j = 0; j < V_CNT; j++) {
			// 1. There are adjacent vertices from selected vertex,
			// 2. one of those adjacent vertices is not included in MST yet,
			// 3. update values if edge's weight is smaller than MST has.
			if (graph[selected][j] && verticesFlag[j] == FALSE && graph[selected][j] < weights[j]) {
				mst[j] = selected;
				weights[j] = graph[selected][j];
			}
		}
	}
	// Print the constructed MST graph.
	printMST(mst, graph);
}

int main() {
	int graph[V_CNT][V_CNT] = { 
		{ 0, 2, 0, 6, 0 },
		{ 2, 0, 3, 8, 5 },
		{ 0, 3, 0, 0, 7 },
		{ 6, 8, 0, 0, 9 },
		{ 0, 5, 7, 9, 0 } 
	};
	
	// Print the solution
	prim(graph);
	
	return 0;
}