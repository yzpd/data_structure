/**
 *此最大堆的起始下标为1
 */
#include <stdio.h>
#include <stdlib.h>

#define Length(a) ((sizeof(a)) / (sizeof(a[0])))

#define MAXDATA 1000

typedef int Type;
typedef struct HeapNode *PtrToHeap;

struct HeapNode {
	Type *Data;		/*储存的数组*/
	int size;		/*堆中当前元素的个数*/
	int capacity;	/*堆的最大容量*/
}MaxHeap;



bool HeapIsEmpty(PtrToHeap heap)
{
	return (heap->size == 0);
}

bool HeapIsFull(PtrToHeap heap)
{
	return (heap->size == heap->capacity);
}

//创建容量为MAXDATA的空的最大堆
PtrToHeap CreateMaxHeap(int MaxSize)
{
	PtrToHeap H = (PtrToHeap)malloc(sizeof(MaxHeap));
	H->Data = (Type *)malloc((MAXDATA + 1) * sizeof(Type));
	H->size = 0;
	H->capacity = MaxSize;
	H->Data[0] = MAXDATA;

	return H;
}

//返回data在堆中的索引
int get_index(int data, PtrToHeap heap)
{
	int i = 0;

	for (i = 0; i < heap->size; i++)
		if (heap->Data[i] == data)
			return i;

	return -1;
}	

//最大堆的下滤算法
//start为开始调整的根结点,end为结束调整的结点
static void maxheap_filterdown(int start, int end, PtrToHeap heap)
{
	int Parent, Child;
	Type x;
	//end = heap->size;

	x = heap->Data[start];	//取出根结点的值
	for (Parent = start; Parent * 2 <= end; Parent = Child)
	{
		Child = Parent * 2;
		if ((Child != end) && (heap->Data[Child] < heap->Data[Child + 1]))
			Child++;
		if (x >= heap->Data[Child]) break; //x比两个child结点值都要大，因此这个Parent位置即为x的位置
		else
			heap->Data[Parent] = heap->Data[Child];
	}
	heap->Data[Parent] = x;
}

//最大堆的建立
void BuildMaxHeap(PtrToHeap heap)
{
	/*调整heap->Data[]中的元素,使满足最大堆的有序性*/
	/*这里假设所有heap->size个元素都已经存在于heap->Data[]中*/

	int i;

	/*从最后一个结点的父结点开始,到根结点1*/
	for (i = heap->size / 2; i > 0; i--)
		maxheap_filterdown(i, heap->size, heap);
}

//删除最大堆中的data
int Delete_Heap(Type data, PtrToHeap heap)
{
	int index;

	if (HeapIsEmpty(heap))
		return -1;

	index = get_index(data, heap);
	if (index == -1)
		return -1;

	heap->Data[index] = heap->Data[heap->size--];
	maxheap_filterdown(heap->Data[index], heap->size, heap);

	return 0;
}

//最大堆的上滤算法,默认第0位放着一个比任何元素都要大的值，来使heap->Data[i / 2] < x不成立而跳出循环
static void maxheap_filterup(int start, PtrToHeap heap)
{
	int i;
	Type x;

	x = heap->Data[start];
	//i = heap->size;
	i = start;

	for (; heap->Data[i / 2] < x; i /= 2)
		heap->Data[i] = heap->Data[ i/2 ];
	heap->Data[i] = x;
}


//最大堆的插入
int maxheap_insert(int data, PtrToHeap heap)
{
	if (HeapIsFull(heap))
		return -1;

	heap->size += 1;
	heap->Data[heap->size] = data;
	maxheap_filterup(heap->size, heap);

	return 0;
}
