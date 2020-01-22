#ifndef _DOUBLE_LINK_H
#define _DOUBLE_LINK_H

//�½�˫������.�ɹ�,����0;����,����NULL
extern int create_dlink();
//����˫������,�ɹ�,����0;���򣬷���0
extern int destroy_dlink();

//����Ϊ��,����1;����,����0
extern int dlink_is_empty();

extern int dlink_size();

//��ȡ������indexλ�õ�Ԫ��.�ɹ�, ���ؽڵ�ָ��;����,����NULL
extern void* dlink_get(int index);
extern void* dlink_get_first();
extern void* dlink_get_last();

//��pval��Ԫ�ز��뵽indexλ��.�ɹ�������0;����,����-1
extern int dlink_insert(int index, void *pval);
//��pval��Ԫ�ز����ͷ.�ɹ�������0;����,����-1
extern int dlink_insert_first(void *pval);
//��pval��Ԫ�ز���ĩβ.�ɹ�������0;����,����-1
extern int dlink_insert_last(void *pval);

//ɾ��������indexλ�õĽڵ�.�ɹ�������0;����,����-1
extern int dlink_delete(int index);
extern int dlink_delete_first();
extern int dlink_delete_last();

#endif
