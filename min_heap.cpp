/**
*����С�ѵ���ʼ�±�Ϊ1
*/
#include <stdio.h>
#include <stdlib.h>

#define Length(a) ((sizeof(a)) / (sizeof(a[0])))

#define MAXDATA 1000

typedef int Type;
typedef struct MinHeapNode *PtrToMinHeap;

struct MinHeapNode {
	Type *Data;		/*���������*/
	int size;		/*���е�ǰԪ�صĸ���*/
	int capacity;	/*�ѵ��������*/
}MinHeap;



bool HeapIsEmpty(PtrToMinHeap heap)
{
	return (heap->size == 0);
}

bool HeapIsFull(PtrToMinHeap heap)
{
	return (heap->size == heap->capacity);
}

//��������ΪMAXDATA�Ŀյ���С��
PtrToMinHeap CreateMaxHeap(int MaxSize)
{
	PtrToMinHeap H = (PtrToMinHeap)malloc(sizeof(MinHeap));
	H->Data = (Type *)malloc((MAXDATA + 1) * sizeof(Type));
	H->size = 0;
	H->capacity = MaxSize;
	H->Data[0] = MAXDATA;

	return H;
}

//����data�ڶ��е�����
int get_index(int data, PtrToMinHeap heap)
{
	int i = 0;

	for (i = 0; i < heap->size; i++)
		if (heap->Data[i] == data)
			return i;

	return -1;
}

//��С�ѵ������㷨
//startΪ��ʼ�����ĸ����,endΪ���������Ľ��
static void minheap_filterdown(int start, int end, PtrToMinHeap heap)
{
	int Parent, Child;
	Type x;
	//end = heap->size;

	x = heap->Data[start];	//ȡ��������ֵ
	for (Parent = start; Parent * 2 <= end; Parent = Child)
	{
		Child = Parent * 2;
		if ((Child != end) && (heap->Data[Child] > heap->Data[Child + 1]))
			Child++;
		if (x <= heap->Data[Child]) break; //x������child���ֵ��ҪС��������Parentλ�ü�Ϊx��λ��
		else
			heap->Data[Parent] = heap->Data[Child];
	}
	heap->Data[Parent] = x;
}

//��С�ѵĽ���
void BuildMinHeap(PtrToMinHeap heap)
{
	/*����heap->Data[]�е�Ԫ��,ʹ������С�ѵ�������*/
	/*�����������heap->size��Ԫ�ض��Ѿ�������heap->Data[]��*/

	int i;

	/*�����һ�����ĸ���㿪ʼ,�������1*/
	for (i = heap->size / 2; i > 0; i--)
		minheap_filterdown(i, heap->size, heap);
}

//ɾ����С�ѵ�data
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

//��С�ѵ������㷨,Ĭ�ϵ�0λ����һ�����κ�Ԫ�ض�ҪС��ֵ����ʹheap->Data[i / 2] > x������������ѭ��
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


//��С�ѵĲ���
int maxheap_insert(int data, PtrToMinHeap heap)
{
	if (HeapIsFull(heap))
		return -1;

	heap->size += 1;
	heap->Data[heap->size] = data;
	minheap_filterup(heap->size, heap);
	//heap->size++;���˵��������0��ʼ

	return 0;
}
