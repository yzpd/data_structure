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
	/*�����<V1,V2>*/
	NewNode = (PtrToAdjVNode)malloc(sizeof(struct AdjVNode));
	NewNode->AdjV = E->v2;
	NewNode->Weight = E->Weight;
	NewNode->Next = Graph->G[E->v1].FirstEdge;
	Graph->G[E->v1].FirstEdge = NewNode;
	Graph->G[E->v1].FirstEdge = NewNode;
	/*��������ͼ*/
	/*��Ҫ�����<V2,V1>*/
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

	printf("�����붥���������");
	scanf("%d", &Nv);
	Graph = CreateLGraph(Nv);

	printf("������ߵ�������");
	scanf("%d", &(Graph->Ne));
	if (Graph->Ne != 0) {
		E = (Edge)malloc(sizeof(struct ENode));
		for (i = 0;i < Graph->Ne;i++) {
			printf("������ߵ�����(��С�����Ϊ0)����ʽΪ����㣬�յ㣬Ȩ��\n");
			scanf("%d %d %d", &E->v1, &E->v2, &E->Weight);	//�����ʽΪ����㣬�յ㣬Ȩ��
			InsertLEdge(Graph, E);
		}
	}

	/*���붥������*/
	for (V = 0; V < Graph->Nv ;V++) {
		printf("�����붥�����ݣ�");
		getchar();
		scanf("%c", &(Graph->G[V].Data));	//%cΪ����һ���ַ�
	}
		
	return Graph;


}