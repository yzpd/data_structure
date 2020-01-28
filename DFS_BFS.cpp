#include <stdio.h>
#include <stdlib.h>
#include "Adjacency_List.h"
#include "dlink_queue.h"
#include "double_link.h"

bool Visited[MaxVertexNum] = { 0 };

void Visit(Vertex V) {
	printf("正在访问顶点%d\n", V);
}

void DFS(LGraph Graph, Vertex V, void(*Visit)(Vertex)) {
	PtrToAdjVNode W;
	//W = (PtrToAdjVNode)malloc(sizeof(struct AdjVNode));

	Visit(V);
	Visited[V] = true;

	for (W = Graph->G[V].FirstEdge; W != NULL; W = W->Next)
		if (!Visited[W->AdjV])
			DFS(Graph, W->AdjV, Visit);
}

void BFS(LGraph Graph, Vertex S, void(*Visit)(Vertex)) {
	PtrToAdjVNode W;
	Vertex* V;
	
	create_dlink_queue();
	Visit(S);
	Visited[S] = true;
	add_queue(&S);

	while (!queue_is_empty())
	{
		V = (Vertex*)pop();
		for (W = Graph->G[*V].FirstEdge; W ; W = W->Next)
			if (!Visited[W->AdjV]) {
				Visit(W->AdjV);
				Visited[W->AdjV] = true;
				add_queue(&(W->AdjV));
			}
	}

}

void main_DFS_BFS() {
	LGraph Graph;
	Graph = BuildLGraph();

	//DFS(Graph, 0, Visit);
	BFS(Graph, 0, Visit);
	getchar();
	getchar();
}