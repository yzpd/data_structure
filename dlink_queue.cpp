#include <stdio.h>
#include "double_link.h"

/**
 *˫������ʵ�ֶ��У��ܴ洢��������
 */

//��������
int create_dlink_queue()
{
	return create_dlink();
}

//���ٶ���
int destroy_dlink_queue()
{
	return destroy_dlink();
}

//��p��ӵ�����β
int add_queue(void* p)
{
	return dlink_insert_last(p);
}

//���ض���ͷ��Ԫ��
void* front()
{
	return dlink_get_first();
}

//��������ͷ��Ԫ�ز�ɾ��
void* pop()
{
	void *p = front();
	dlink_delete_first();
	return p;
}

//���ض��д�С
int size()
{
	return dlink_size();
}

int queue_is_empty()
{
	return dlink_is_empty();
}

typedef struct tag_stu
{
	int id;
	char name[20];
}stu;

static stu arr_stu[] =
{
	{ 10, "sky1"},
	{ 20, "sky2"},
	{ 30, "sky3"},
	{ 40, "sky4"},
};

#define ARR_STU_SIZE ( (sizeof(arr_stu)) / (sizeof(arr_stu[0])) )

static void print_stu(stu *p)
{
	if (!p)
		return;

	printf("id=%d, name=%s\n", p->id, p->name);
}

void main_queue()
{
	stu *pval = NULL;

	// ���������С�
	create_dlink_queue();

	// ��10, 20, 30 �������������
	int i = 0;
	for (i = 0; i<ARR_STU_SIZE - 1; i++)
	{
		add_queue(&arr_stu[i]);
	}

	// �������п�ͷ��Ԫ�ء���ֵ��pval����ɾ������Ԫ�ء�
	pval = (stu*)pop();
	print_stu(pval);

	// ֻ�������п�ͷ��Ԫ�ء���ֵ��pval����ɾ����Ԫ��.
	pval = (stu*)front();
	print_stu(pval);

	add_queue(&arr_stu[ARR_STU_SIZE - 1]);

	printf("is_empty()=%d\n", queue_is_empty());
	printf("size()=%d\n", size());
	// ��ӡ�����е�����Ԫ��
	while (!queue_is_empty())
	{
		pval = (stu*)pop();
		print_stu(pval);
	}

	// ���ٶ���
	destroy_dlink_queue();

	getchar();
}