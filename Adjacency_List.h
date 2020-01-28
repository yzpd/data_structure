#ifndef _ADJACENCY_LIST_H_
#define _ADJACENCY_LIST_H_

#define MaxVertexNum 100	//��󶥵���
typedef int Vertex;			//�����±�
typedef int WeightType;		//Ȩֵ
typedef char DataType;		//����洢����������

/*�ߵĶ���*/
typedef struct ENode *PtrToENode;
struct ENode {
	Vertex v1, v2;
	WeightType Weight;
};
typedef PtrToENode Edge;

/*�ڽӵ�Ķ���*/
typedef struct AdjVNode *PtrToAdjVNode;
struct AdjVNode {
	Vertex AdjV;
	WeightType Weight;
	PtrToAdjVNode Next;			//ָ����һ���ڽӵ�
};

/*�����ͷ���Ķ���*/
typedef struct Vnode {
	PtrToAdjVNode FirstEdge;	//ָ��߱�ͷ
	DataType Data;
}AdjList[MaxVertexNum];

/*ͼ���Ķ���*/
typedef struct GNode *PtrToGNode;
struct GNode {
	int Nv;
	int Ne;
	AdjList G;
};
typedef PtrToGNode LGraph;

LGraph BuildLGraph();

#endif // !_ADJACENCY_LIST_H_

