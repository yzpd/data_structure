#ifndef _GRAPH_H_
#define _GRAPH_H_


#define MaxVertexNum 100	//��󶥵���
#define INFINITY	 65535	//������Ϊ65535
typedef int Vertex;			//�����±�
typedef int WeightType;		//Ȩֵ
typedef char DataType;		//����洢����������


typedef struct GNode *PtrToGNode;
struct GNode {
	int Nv;	//������
	int Ne;	//����
	WeightType G[MaxVertexNum][MaxVertexNum];
	DataType   Data[MaxVertexNum];
};
typedef PtrToGNode MGraph;


#endif // !_GTAPH_H_
