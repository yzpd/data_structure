#include <stdio.h>
#include <stdlib.h>
#include "HuffmanTree.h"

extern PtrToHuffmanMinHeap CreateHuffmanMinHeap(Type* a, int size);
extern void HuffmanBuildMinHeap(PtrToHuffmanMinHeap heap);
//最小堆的插入
int minheap_insert(PtrToHuffman Huffman, PtrToHuffmanMinHeap heap);
//删除最小堆的最小值(即树根),即data[1]和data[size]的,并返回
extern PtrToHuffman Delete_Heap_Min(PtrToHuffmanMinHeap heap);

//中序遍历
static void inorder_HuffmanTree(PtrToHuffman tree)
{
	if (tree != NULL)
	{
		inorder_HuffmanTree(tree->left);
		printf("%d ", tree->weight);
		inorder_HuffmanTree(tree->right);
	}
}

static void print_HuffmanTree(PtrToHuffman tree, Type key, int direction)
{
	if (tree != NULL)
	{
		if (direction == 0)    // tree是根节点
			printf("\n%2d is root\n", tree->weight);
		else                // tree是分支节点
			printf("%2d is %2d's %6s child\n", tree->weight, key, direction == 1 ? "right" : "left");

		print_HuffmanTree(tree->left, tree->weight, -1);
		print_HuffmanTree(tree->right, tree->weight, 1);
	}
}

PtrToHuffman Huffman(Type* a, int size) {
	int i;

	PtrToHuffmanMinHeap MinHeap = CreateHuffmanMinHeap(a, size);
	HuffmanBuildMinHeap(MinHeap);

	PtrToHuffman T;

	for (i = 1; i < size; i++)
	{		
		T = (PtrToHuffman)malloc(sizeof(struct HuffmanTreeNode));
		T->left = Delete_Heap_Min(MinHeap);
		T->right = Delete_Heap_Min(MinHeap);
		T->weight = T->left->weight + T->right->weight;
		minheap_insert(T, MinHeap);
		//printf("%d, %d, %d, %d, %d", MinHeap->Data[1].weight, MinHeap->Data[2].weight, MinHeap->Data[3].weight, MinHeap->Data[4].weight, MinHeap->Data[5].weight);
	}
	PtrToHuffman root = Delete_Heap_Min(MinHeap);
	free(MinHeap);	//回收原最小树
	return root;
}

void main_Huffman() {
	int a[] = { 1, 2, 3, 4, 5 };
	int i, ilen = 5;
	PtrToHuffman root = NULL;
	
	printf("== 添加数组：");
	for (i = 0;i < ilen;i++)
		printf("%d ", a[i]);

	root = Huffman(a, ilen);
	printf("\n== 中序遍历: ");
	inorder_HuffmanTree(root);
	print_HuffmanTree(root, root->weight, 0);
	
	getchar();
}