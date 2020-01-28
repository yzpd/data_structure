#ifndef _GRAPH_H_
#define _GRAPH_H_


#define MaxVertexNum 100	//最大顶点数
#define INFINITY	 65535	//设无穷为65535
typedef int Vertex;			//顶点下标
typedef int WeightType;		//权值
typedef char DataType;		//顶点存储的数据类型


typedef struct GNode *PtrToGNode;
struct GNode {
	int Nv;	//顶点数
	int Ne;	//边数
	WeightType G[MaxVertexNum][MaxVertexNum];
	DataType   Data[MaxVertexNum];
};
typedef PtrToGNode MGraph;


#endif // !_GTAPH_H_
