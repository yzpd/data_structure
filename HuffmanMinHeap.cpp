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

//��������Ϊsize����С��
PtrToHuffmanMinHeap CreateHuffmanMinHeap(Type* a,int size)
{
	int i;

	PtrToHuffmanMinHeap H = (PtrToHuffmanMinHeap)malloc(sizeof(struct HuffmanMinHeapNode));
	H->Data = (PtrToHuffman)malloc((size + 1) * sizeof(struct HuffmanTreeNode));	//data[0]Ϊ�ڱ�
	H->size = size ;	
	H->capacity = size ;
	H->Data[0].weight = MAXDATA;
	H->Data[0].right = H->Data[0].left = NULL;

	//��ʼ������,�ر�ע�����ݵ�����������
	for (i = 1; i < ( size+1 ); i++)
	{
		H->Data[i].weight = a[i-1];
		H->Data[i].right = H->Data[i].left = NULL;
	}

	return H;
}

//��С�ѵ������㷨
//startΪ��ʼ�����ĸ����,endΪ���������Ľ��
static void minheap_filterdown(int start, int end, PtrToHuffmanMinHeap heap)
{
	int Parent, Child;
	PtrToHuffman x;
	x = (PtrToHuffman)malloc(sizeof(struct HuffmanTreeNode));

	*x = heap->Data[start];	//ȡ��������ֵ
	for (Parent = start; Parent * 2 <= end; Parent = Child)
	{
		Child = Parent * 2;
		if ((Child != end) && (heap->Data[Child].weight > heap->Data[Child + 1].weight))
			Child++;
		if (x->weight <= heap->Data[Child].weight) break; //x������child���ֵ��ҪС��������Parentλ�ü�Ϊx��λ��
		else
			heap->Data[Parent] = heap->Data[Child];
	}
	heap->Data[Parent] = *x;
}

//��С�ѵĽ���
void HuffmanBuildMinHeap(PtrToHuffmanMinHeap heap)
{
	/*����heap->Data[]�е�Ԫ��,ʹ������С�ѵ�������*/
	/*�����������heap->size��Ԫ�ض��Ѿ�������heap->Data[]��*/

	int i;

	/*�����һ�����ĸ���㿪ʼ,�������1*/
	for (i = heap->size / 2; i > 0; i--)
		minheap_filterdown(i, heap->size, heap);
}

//ɾ����С�ѵ���Сֵ(������),��data[1]��data[size]��ֵ����,������
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

//��С�ѵ������㷨,Ĭ�ϵ�0λ����һ�����κ�Ԫ�ض�ҪС��ֵ����ʹheap->Data[i / 2] > x������������ѭ��
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


//��С�ѵĲ���
int minheap_insert(PtrToHuffman Huffman, PtrToHuffmanMinHeap heap)
{
	if (HeapIsFull(heap))
		return -1;

	heap->size += 1;
	heap->Data[heap->size] = *Huffman;

	minheap_filterup(heap->size, heap);
	//heap->size++;���˵��������0��ʼ

	return 0;
}