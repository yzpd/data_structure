/**
 *�����ѵ���ʼ�±�Ϊ1
 */
#include <stdio.h>
#include <stdlib.h>

#define Length(a) ((sizeof(a)) / (sizeof(a[0])))

#define MAXDATA 1000

typedef int Type;
typedef struct HeapNode *PtrToHeap;

struct HeapNode {
	Type *Data;		/*���������*/
	int size;		/*���е�ǰԪ�صĸ���*/
	int capacity;	/*�ѵ��������*/
}MaxHeap;



bool HeapIsEmpty(PtrToHeap heap)
{
	return (heap->size == 0);
}

bool HeapIsFull(PtrToHeap heap)
{
	return (heap->size == heap->capacity);
}

//��������ΪMAXDATA�Ŀյ�����
PtrToHeap CreateMaxHeap(int MaxSize)
{
	PtrToHeap H = (PtrToHeap)malloc(sizeof(MaxHeap));
	H->Data = (Type *)malloc((MAXDATA + 1) * sizeof(Type));
	H->size = 0;
	H->capacity = MaxSize;
	H->Data[0] = MAXDATA;

	return H;
}

//����data�ڶ��е�����
int get_index(int data, PtrToHeap heap)
{
	int i = 0;

	for (i = 0; i < heap->size; i++)
		if (heap->Data[i] == data)
			return i;

	return -1;
}	

//���ѵ������㷨
//startΪ��ʼ�����ĸ����,endΪ���������Ľ��
static void maxheap_filterdown(int start, int end, PtrToHeap heap)
{
	int Parent, Child;
	Type x;
	//end = heap->size;

	x = heap->Data[start];	//ȡ��������ֵ
	for (Parent = start; Parent * 2 <= end; Parent = Child)
	{
		Child = Parent * 2;
		if ((Child != end) && (heap->Data[Child] < heap->Data[Child + 1]))
			Child++;
		if (x >= heap->Data[Child]) break; //x������child���ֵ��Ҫ��������Parentλ�ü�Ϊx��λ��
		else
			heap->Data[Parent] = heap->Data[Child];
	}
	heap->Data[Parent] = x;
}

//���ѵĽ���
void BuildMaxHeap(PtrToHeap heap)
{
	/*����heap->Data[]�е�Ԫ��,ʹ�������ѵ�������*/
	/*�����������heap->size��Ԫ�ض��Ѿ�������heap->Data[]��*/

	int i;

	/*�����һ�����ĸ���㿪ʼ,�������1*/
	for (i = heap->size / 2; i > 0; i--)
		maxheap_filterdown(i, heap->size, heap);
}

//ɾ�������е�data
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

//���ѵ������㷨,Ĭ�ϵ�0λ����һ�����κ�Ԫ�ض�Ҫ���ֵ����ʹheap->Data[i / 2] < x������������ѭ��
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


//���ѵĲ���
int maxheap_insert(int data, PtrToHeap heap)
{
	if (HeapIsFull(heap))
		return -1;

	heap->size += 1;
	heap->Data[heap->size] = data;
	maxheap_filterup(heap->size, heap);

	return 0;
}
