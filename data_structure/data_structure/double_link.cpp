#include<stdio.h>
#include<malloc.h>

/**
 *C����˫��ѭ������,�ܴ洢��������
 *@author pannell
 *@data   2020-01-22
*/

//˫������ڵ�
typedef struct Node *PtrToNode;
typedef struct Node
{
	PtrToNode next;
	PtrToNode previous;
	void* p;
};

//�ձ�ͷ
static PtrToNode phead = NULL;
//�ڵ����
static int count = 0;

//�½��ڵ�,�ɹ�,���ؽڵ�ָ��;����,����NULL
static PtrToNode create_node(void *pval)
{
	PtrToNode pnode = (PtrToNode)malloc(sizeof(struct Node));
	if (!pnode)
	{
		printf("create node error!\n");
		return NULL;
	}
	pnode->next = pnode->previous = pnode;
	pnode->p = pval;

	return pnode;
}

//�½�˫������.�ɹ�,����0;����,����NULL
int create_dlink()
{
	phead = create_node(NULL);
	if (!phead)
		return -1;
	count = 0;

	return 0;
}

int dlink_is_empty()
{
	return count == 0;
}

int dlink_size()
{
	return count;
}

//��ȡ������indexλ�õ�Ԫ��.�ɹ�, ���ؽڵ�ָ��;����,����NULL
static PtrToNode get_node(int index)
{
	if (index < 0 || index >= count)
	{
		printf("%s failed! index out of bound!\n", __func__);
		return NULL;
	}

	//�������
	if (index <= (count / 2))
	{
		int i = 0;
		PtrToNode pnode = phead->next;
		while ((i++) < index)
			pnode = pnode->next;
		return pnode;
	}
	//�������
	else
	{
		int j = 0;
		int rindex = count - 1 - index;//count-1 ����Ϊ�ձ�ͷλ��Ϊ0,�ܳ�count,�������һλΪcount-1
		PtrToNode rnode = phead->previous;
		while ((j++) < rindex)
			rnode = rnode->previous;
		return rnode;
	}
}

static PtrToNode get_node_first()
{
	return get_node(0);
}

static PtrToNode get_node_last()
{
	return get_node(count - 1);
}

void* dlink_get(int index)
{
	PtrToNode pindex = get_node(index);
	if (!pindex)
	{
		printf("%s failed!\n", __func__);
		return NULL;
	}

	return pindex->p;
}

void* dlink_get_first()
{
	return dlink_get(0);
}

void* dlink_get_last()
{
	return dlink_get(count - 1);
}

int dlink_insert_first(void* pval)
{
	PtrToNode pnode = create_node(pval);
	if (!pnode)
		return -1;
	pnode->previous = phead;
	pnode->next = phead->next;
	phead->next->previous = pnode;
	phead->next = pnode;
	count++;

	return 0;
}


int dlink_insert(int index, void* pval)
{
	if (index == 0)
		return dlink_insert_first(pval);
	
	PtrToNode pnode = create_node(pval);
	if (!pnode)
		return -1;

	PtrToNode pindex = get_node(index);
	if (!pindex)
		return -1;

	pnode->next = pindex;
	pnode->previous = pindex->previous;
	pindex->previous->next = pnode;
	pindex->previous = pnode;
	count++;

	return 0;
}

int dlink_insert_last(void* pval)
{
	PtrToNode pnode = create_node(pval);
	if (!pnode)
		return -1;

	pnode->next = phead;
	pnode->previous = phead->previous;
	phead->previous->next = pnode;
	phead->previous = pnode;
	count++;

	return 0;
}

int dlink_delete(int index)
{
	PtrToNode pindex = get_node(index);
	if (!pindex)
	{
		printf("s failed! the index in out of bound\n", __func__);
		return -1;
	}

	pindex->next->previous = pindex->previous;
	pindex->previous->next = pindex->next;
	count--;

	return 0;
}

int dlink_delete_last()
{
	dlink_delete(count - 1);

	return 0;
}

int dlink_delete_first()
{
	dlink_delete(0);
	
	return 0;
}

int destroy_dlink()
{
	if (!phead)
	{
		printf("%s failed! dlink is null\n", __func__);
		return -1;
	}

	PtrToNode pnode = phead->next;
	PtrToNode ptmp = NULL;

	while (pnode != phead)
	{
		ptmp = pnode;
		pnode = pnode->next;
		free(ptmp);
	}

	free(phead);
	phead = NULL;
	count = 0;

	return 0;
}