#define _CRT_SECURE_NO_WARNINGS
#include <stdio.h>
#include <stdlib.h>
#include "Adjacency_List.h"

LGraph CreateLGraph(int VertexNum) {
	Vertex V;
	LGraph Graph;

	Graph = (LGraph)malloc(sizeof(struct GNode));
	Graph->Nv = VertexNum;
	Graph->Ne = 0;

	for (V = 0;V < Graph->Nv;V++)
		Graph->G[V].FirstEdge = NULL;

	return Graph;
}

void InsertLEdge(LGraph Graph, Edge E) {
	PtrToAdjVNode NewNode;
	/*插入边<V1,V2>*/
	NewNode = (PtrToAdjVNode)malloc(sizeof(struct AdjVNode));
	NewNode->AdjV = E->v2;
	NewNode->Weight = E->Weight;
	NewNode->Next = Graph->G[E->v1].FirstEdge;
	Graph->G[E->v1].FirstEdge = NewNode;
	Graph->G[E->v1].FirstEdge = NewNode;
	/*若是无向图*/
	/*还要插入边<V2,V1>*/
	NewNode = (PtrToAdjVNode)malloc(sizeof(struct AdjVNode));
	NewNode->AdjV = E->v1;
	NewNode->Weight = E->Weight;
	NewNode->Next = Graph->G[E->v2].FirstEdge;
	Graph->G[E->v2].FirstEdge = NewNode;
	Graph->G[E->v2].FirstEdge = NewNode;
}

LGraph BuildLGraph() {
	LGraph Graph;
	Edge E;
	Vertex V;
	int Nv, i;

	printf("请输入顶点的数量：");
	scanf("%d", &Nv);
	Graph = CreateLGraph(Nv);

	printf("请输入边的数量：");
	scanf("%d", &(Graph->Ne));
	if (Graph->Ne != 0) {
		E = (Edge)malloc(sizeof(struct ENode));
		for (i = 0;i < Graph->Ne;i++) {
			printf("请输入边的属性(最小的起点为0)，格式为：起点，终点，权重\n");
			scanf("%d %d %d", &E->v1, &E->v2, &E->Weight);	//输入格式为：起点，终点，权重
			InsertLEdge(Graph, E);
		}
	}

	/*输入顶点数据*/
	for (V = 0; V < Graph->Nv ;V++) {
		printf("请输入顶点数据：");
		getchar();
		scanf("%c", &(Graph->G[V].Data));	//%c为输入一个字符
	}
		
	return Graph;


}