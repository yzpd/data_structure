#ifndef _HUFFMAN_TREE_H_
#define _HUFFMAN_TREE_H_

typedef int Type;

typedef struct HuffmanTreeNode *PtrToHuffman;
struct HuffmanTreeNode {
	int weight;	//权值
	PtrToHuffman left;
	PtrToHuffman right;
};

typedef struct HuffmanMinHeapNode *PtrToHuffmanMinHeap;
struct HuffmanMinHeapNode {
	PtrToHuffman Data;		/*储存的Huffman类型的元素*/
	int size;				/*堆中当前元素的个数*/
	int capacity;			/*堆的最大容量*/
};



#endif