#ifndef _ADJACENCY_LIST_H_
#define _ADJACENCY_LIST_H_

#define MaxVertexNum 100	//最大顶点数
typedef int Vertex;			//顶点下标
typedef int WeightType;		//权值
typedef char DataType;		//顶点存储的数据类型

/*边的定义*/
typedef struct ENode *PtrToENode;
struct ENode {
	Vertex v1, v2;
	WeightType Weight;
};
typedef PtrToENode Edge;

/*邻接点的定义*/
typedef struct AdjVNode *PtrToAdjVNode;
struct AdjVNode {
	Vertex AdjV;
	WeightType Weight;
	PtrToAdjVNode Next;			//指向下一个邻接点
};

/*顶点表头结点的定义*/
typedef struct Vnode {
	PtrToAdjVNode FirstEdge;	//指向边表头
	DataType Data;
}AdjList[MaxVertexNum];

/*图结点的定义*/
typedef struct GNode *PtrToGNode;
struct GNode {
	int Nv;
	int Ne;
	AdjList G;
};
typedef PtrToGNode LGraph;

LGraph BuildLGraph();

#endif // !_ADJACENCY_LIST_H_

