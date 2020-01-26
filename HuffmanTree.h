#ifndef _HUFFMAN_TREE_H_
#define _HUFFMAN_TREE_H_

typedef int Type;

typedef struct HuffmanTreeNode *PtrToHuffman;
struct HuffmanTreeNode {
	int weight;	//Ȩֵ
	PtrToHuffman left;
	PtrToHuffman right;
};

typedef struct HuffmanMinHeapNode *PtrToHuffmanMinHeap;
struct HuffmanMinHeapNode {
	PtrToHuffman Data;		/*�����Huffman���͵�Ԫ��*/
	int size;				/*���е�ǰԪ�صĸ���*/
	int capacity;			/*�ѵ��������*/
};



#endif