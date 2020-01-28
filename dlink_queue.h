#ifndef _DLINK_LINK_H_
#define _DLINK_LINK_H_

//创建队列
int create_dlink_queue();
//销毁队列
int destroy_dlink_queue();

//将p添加到队列尾
int add_queue(void* p);
//弹出队列头部元素并删除
void* pop();

//返回队列头部元素
void* front();

//返回队列大小
int size();
int queue_is_empty();

#endif // !_DOUBLE_LINK_H_

