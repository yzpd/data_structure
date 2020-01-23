#include <stdio.h>
#include "double_link.h"

/**
 *˫������ʵ��ջ,�ܴ洢��������
 *��ͷΪջ�����,����ͷΪջ��,push �� pop �������ı�ͷ
 */

//����ջ
int create_dlink_stack()
{
	return create_dlink();
}

//����ջ
int destroy_dlink_stack()
{
	return destroy_dlink();
}

//ѹ��ջ
int push(void *p)
{
	return dlink_insert_first(p);
}

//����ջ��Ԫ��
void* peek()
{
	return dlink_get_first();
}


//����ջ��
static void* pop()
{
	void *p = peek();
	dlink_delete_first();
	return p;
}

//����ջ�Ĵ�С
static int size()
{
	return dlink_size();
}

int stack_is_empty()
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
	{ 10, "sky" },
	{ 20, "jody" },
	{ 30, "vic" },
	{ 40, "dan" },
};
#define ARR_STU_SIZE ( (sizeof(arr_stu)) / (sizeof(arr_stu[0])) )

static void print_stu(stu *p)
{
	if (!p)
		return;

	printf("id=%d, name=%s\n", p->id, p->name);
}

void main_stack()
{
	stu *pval = NULL;

	// ������ջ��
	create_dlink_stack();

	// ��10, 20, 30 ��������ջ��
	int i = 0;
	for (i = 0; i<ARR_STU_SIZE - 1; i++)
	{
		push(&arr_stu[i]);
	}

	// ����ջ��Ԫ�ء���ֵ��pval����ɾ����ջ��Ԫ�ء�
	pval = (stu*)pop();
	//print_stu(pval) ;

	// ֻ����ջ������ֵ��pval����ɾ����Ԫ��.
	pval = (stu*)peek();
	//print_stu(pval) ;

	push(&arr_stu[ARR_STU_SIZE - 1]);


	// ��ӡջ�е�����Ԫ��
	while (!stack_is_empty())
	{
		pval = (stu*)pop();
		print_stu(pval);
	}

	// ����ջ
	destroy_dlink_stack();
	getchar();
}