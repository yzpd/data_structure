#include <stdio.h>
#include <stdlib.h>
#include "HuffmanTree.h"

#define MAXDATA -1

static bool HeapIsEmpty(PtrToHuffmanMinHeap heap)
{
	return (heap->size == 0);
}
static bool HeapIsFull(PtrToHuffmanMinHeap heap)
{
	return (heap->size == heap->capacity);
}

static void swap_node(int i, int j, PtrToHuffmanMinHeap heap)
{
	HuffmanTreeNode tmp = heap->Data[i];
	heap->Data[i] = heap->Data[j];
	heap->Data[j] = tmp;
}

//创建容量为size的最小堆
PtrToHuffmanMinHeap CreateHuffmanMinHeap(Type* a,int size)
{
	int i;

	PtrToHuffmanMinHeap H = (PtrToHuffmanMinHeap)malloc(sizeof(struct HuffmanMinHeapNode));
	H->Data = (PtrToHuffman)malloc((size + 1) * sizeof(struct HuffmanTreeNode));	//data[0]为哨兵
	H->size = size ;	
	H->capacity = size ;
	H->Data[0].weight = MAXDATA;
	H->Data[0].right = H->Data[0].left = NULL;

	//初始化数组,特别注意数据的索引！！！
	for (i = 1; i < ( size+1 ); i++)
	{
		H->Data[i].weight = a[i-1];
		H->Data[i].right = H->Data[i].left = NULL;
	}

	return H;
}

//最小堆的下滤算法
//start为开始调整的根结点,end为结束调整的结点
static void minheap_filterdown(int start, int end, PtrToHuffmanMinHeap heap)
{
	int Parent, Child;
	PtrToHuffman x;
	x = (PtrToHuffman)malloc(sizeof(struct HuffmanTreeNode));

	*x = heap->Data[start];	//取出根结点的值
	for (Parent = start; Parent * 2 <= end; Parent = Child)
	{
		Child = Parent * 2;
		if ((Child != end) && (heap->Data[Child].weight > heap->Data[Child + 1].weight))
			Child++;
		if (x->weight <= heap->Data[Child].weight) break; //x比两个child结点值都要小，因此这个Parent位置即为x的位置
		else
			heap->Data[Parent] = heap->Data[Child];
	}
	heap->Data[Parent] = *x;
}

//最小堆的建立
void HuffmanBuildMinHeap(PtrToHuffmanMinHeap heap)
{
	/*调整heap->Data[]中的元素,使满足最小堆的有序性*/
	/*这里假设所有heap->size个元素都已经存在于heap->Data[]中*/

	int i;

	/*从最后一个结点的父结点开始,到根结点1*/
	for (i = heap->size / 2; i > 0; i--)
		minheap_filterdown(i, heap->size, heap);
}

//删除最小堆的最小值(即树根),即data[1]和data[size]的值互换,并返回
PtrToHuffman Delete_Heap_Min(PtrToHuffmanMinHeap heap)
{
	if (HeapIsEmpty(heap))
		return NULL;

	PtrToHuffman T;
	T = (PtrToHuffman)malloc(sizeof(struct HuffmanTreeNode));
	*T = heap->Data[1];
	swap_node(1, heap->size, heap);

	heap->size--;
	minheap_filterdown(1, heap->size, heap);

	return T;
}

//最小堆的上滤算法,默认第0位放着一个比任何元素都要小的值，来使heap->Data[i / 2] > x不成立而跳出循环
static void minheap_filterup(int start, PtrToHuffmanMinHeap heap)
{
	int i;
	PtrToHuffman x;
	x = (PtrToHuffman)malloc(sizeof(struct HuffmanTreeNode));

	*x = heap->Data[start];
	//i = heap->size;
	i = start;

	for (; heap->Data[i / 2].weight > x->weight; i /= 2)
		heap->Data[i] = heap->Data[i / 2];
	heap->Data[i] = *x;
}


//最小堆的插入
int minheap_insert(PtrToHuffman Huffman, PtrToHuffmanMinHeap heap)
{
	if (HeapIsFull(heap))
		return -1;

	heap->size += 1;
	heap->Data[heap->size] = *Huffman;

	minheap_filterup(heap->size, heap);
	//heap->size++;后加说明索引从0开始

	return 0;
}