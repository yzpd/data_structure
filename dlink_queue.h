#ifndef _DLINK_LINK_H_
#define _DLINK_LINK_H_

//��������
int create_dlink_queue();
//���ٶ���
int destroy_dlink_queue();

//��p��ӵ�����β
int add_queue(void* p);
//��������ͷ��Ԫ�ز�ɾ��
void* pop();

//���ض���ͷ��Ԫ��
void* front();

//���ض��д�С
int size();
int queue_is_empty();

#endif // !_DOUBLE_LINK_H_

