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


/*����һ��û�бߵ�ͼ*/
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

/*�����*/
void InsertEdge(MGraph Graph, Edge E) {
	Graph->G[E->v1][E->v2] = E->weight;
	/*����ͼ*/
	Graph->G[E->v2][E->v1] = E->weight;
}

/*����ͼ*/
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
			scanf("%d %d %d", &E->v1, &E->v2, &E->weight);	//�����ʽΪ����㣬�յ㣬Ȩ��
			InsertEdge(Graph, E);
		}
	}

	/*���붥������*/
	for (v = 0; v < Graph->Nv;v++)
		scanf("%c", &(Graph->Data[v]));

	return Graph;
}

