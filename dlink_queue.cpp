#include <stdio.h>
#include "double_link.h"

/**
 *双向链表实现队列，能存储任意数据
 */

//创建队列
int create_dlink_queue()
{
	return create_dlink();
}

//销毁队列
int destroy_dlink_queue()
{
	return destroy_dlink();
}

//将p添加到队列尾
int add_queue(void* p)
{
	return dlink_insert_last(p);
}

//返回队列头部元素
void* front()
{
	return dlink_get_first();
}

//弹出队列头部元素并删除
void* pop()
{
	void *p = front();
	dlink_delete_first();
	return p;
}

//返回队列大小
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

	// 创建“队列”
	create_dlink_queue();

	// 将10, 20, 30 依次推入队列中
	int i = 0;
	for (i = 0; i<ARR_STU_SIZE - 1; i++)
	{
		add_queue(&arr_stu[i]);
	}

	// 将“队列开头的元素”赋值给pval，并删除“该元素”
	pval = (stu*)pop();
	print_stu(pval);

	// 只将“队列开头的元素”赋值给pval，不删除该元素.
	pval = (stu*)front();
	print_stu(pval);

	add_queue(&arr_stu[ARR_STU_SIZE - 1]);

	printf("is_empty()=%d\n", queue_is_empty());
	printf("size()=%d\n", size());
	// 打印队列中的所有元素
	while (!queue_is_empty())
	{
		pval = (stu*)pop();
		print_stu(pval);
	}

	// 销毁队列
	destroy_dlink_queue();

	getchar();
}