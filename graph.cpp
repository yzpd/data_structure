#define _CRT_SECURE_NO_WARNINGS
#include <stdio.h>
#include <stdlib.h>
#include "graph.h"


typedef struct ENode *PtrToENode;
struct ENode {
	Vertex v1, v2;
	WeightType weight;
};
typedef PtrToENode Edge;


/*创建一个没有边的图*/
MGraph CreateGraph(int VertexNum) {
	Vertex v, w;
	MGraph Graph;

	Graph = (MGraph)malloc(sizeof(GNode));
	Graph->Ne = VertexNum;
	Graph->Nv = 0;

	for (v = 0;v < VertexNum;v++)
		for (w = 0;w < VertexNum;w++)
			Graph->G[v][w] = INFINITY;

	return Graph;
}

/*插入边*/
void InsertEdge(MGraph Graph, Edge E) {
	Graph->G[E->v1][E->v2] = E->weight;
	/*无向图*/
	Graph->G[E->v2][E->v1] = E->weight;
}

/*创建图*/
MGraph BuildGraph() {
	MGraph Graph;
	Edge E;
	Vertex v;
	int Nv, i;

	scanf("%d", &Nv);	
	Graph = CreateGraph(Nv);
	scanf("%d", &(Graph->Ne));
	if (Graph->Ne != 0) {
		E = (Edge)malloc(sizeof(struct ENode));
		for (i = 0;i < Graph->Ne;i++) {
			scanf("%d %d %d", &E->v1, &E->v2, &E->weight);	//输入格式为：起点，终点，权重
			InsertEdge(Graph, E);
		}
	}

	/*输入顶点数据*/
	for (v = 0; v < Graph->Nv;v++)
		scanf("%c", &(Graph->Data[v]));

	return Graph;
}

