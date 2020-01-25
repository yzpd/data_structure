/**
*此最小堆的起始下标为1
*/
#include <stdio.h>
#include <stdlib.h>

#define Length(a) ((sizeof(a)) / (sizeof(a[0])))

#define MAXDATA 1000

typedef int Type;
typedef struct MinHeapNode *PtrToMinHeap;

struct MinHeapNode {
	Type *Data;		/*储存的数组*/
	int size;		/*堆中当前元素的个数*/
	int capacity;	/*堆的最大容量*/
}MinHeap;



bool HeapIsEmpty(PtrToMinHeap heap)
{
	return (heap->size == 0);
}

bool HeapIsFull(PtrToMinHeap heap)
{
	return (heap->size == heap->capacity);
}

//创建容量为MAXDATA的空的最小堆
PtrToMinHeap CreateMaxHeap(int MaxSize)
{
	PtrToMinHeap H = (PtrToMinHeap)malloc(sizeof(MinHeap));
	H->Data = (Type *)malloc((MAXDATA + 1) * sizeof(Type));
	H->size = 0;
	H->capacity = MaxSize;
	H->Data[0] = MAXDATA;

	return H;
}

//返回data在堆中的索引
int get_index(int data, PtrToMinHeap heap)
{
	int i = 0;

	for (i = 0; i < heap->size; i++)
		if (heap->Data[i] == data)
			return i;

	return -1;
}

//最小堆的下滤算法
//start为开始调整的根结点,end为结束调整的结点
static void minheap_filterdown(int start, int end, PtrToMinHeap heap)
{
	int Parent, Child;
	Type x;
	//end = heap->size;

	x = heap->Data[start];	//取出根结点的值
	for (Parent = start; Parent * 2 <= end; Parent = Child)
	{
		Child = Parent * 2;
		if ((Child != end) && (heap->Data[Child] > heap->Data[Child + 1]))
			Child++;
		if (x <= heap->Data[Child]) break; //x比两个child结点值都要小，因此这个Parent位置即为x的位置
		else
			heap->Data[Parent] = heap->Data[Child];
	}
	heap->Data[Parent] = x;
}

//最小堆的建立
void BuildMinHeap(PtrToMinHeap heap)
{
	/*调整heap->Data[]中的元素,使满足最小堆的有序性*/
	/*这里假设所有heap->size个元素都已经存在于heap->Data[]中*/

	int i;

	/*从最后一个结点的父结点开始,到根结点1*/
	for (i = heap->size / 2; i > 0; i--)
		minheap_filterdown(i, heap->size, heap);
}

//删除最小堆的data
int Delete_Heap(Type data, PtrToMinHeap heap)
{
	int index;

	if (HeapIsEmpty(heap))
		return -1;

	index = get_index(data, heap);
	if (index == -1)
		return -1;

	heap->Data[index] = heap->Data[heap->size--];
	minheap_filterdown(heap->Data[index], heap->size, heap);

	return 0;
}

//最小堆的上滤算法,默认第0位放着一个比任何元素都要小的值，来使heap->Data[i / 2] > x不成立而跳出循环
static void minheap_filterup(int start, PtrToMinHeap heap)
{
	int i;
	Type x;

	x = heap->Data[start];
	//i = heap->size;
	i = start;

	for (; heap->Data[i / 2] > x; i /= 2)
		heap->Data[i] = heap->Data[i / 2];
	heap->Data[i] = x;
}


//最小堆的插入
int maxheap_insert(int data, PtrToMinHeap heap)
{
	if (HeapIsFull(heap))
		return -1;

	heap->size += 1;
	heap->Data[heap->size] = data;
	minheap_filterup(heap->size, heap);
	//heap->size++;后加说明索引从0开始

	return 0;
}
