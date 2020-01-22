#ifndef _DOUBLE_LINK_H
#define _DOUBLE_LINK_H

//新建双向链表.成功,返回0;否则,返回NULL
extern int create_dlink();
//销毁双向链表,成功,返回0;否则，返回0
extern int destroy_dlink();

//链表为空,返回1;否则,返回0
extern int dlink_is_empty();

extern int dlink_size();

//获取链表中index位置的元素.成功, 返回节点指针;否则,返回NULL
extern void* dlink_get(int index);
extern void* dlink_get_first();
extern void* dlink_get_last();

//将pval的元素插入到index位置.成功，返回0;否则,返回-1
extern int dlink_insert(int index, void *pval);
//将pval的元素插入表头.成功，返回0;否则,返回-1
extern int dlink_insert_first(void *pval);
//将pval的元素插入末尾.成功，返回0;否则,返回-1
extern int dlink_insert_last(void *pval);

//删除链表中index位置的节点.成功，返回0;否则,返回-1
extern int dlink_delete(int index);
extern int dlink_delete_first();
extern int dlink_delete_last();

#endif
