#ifndef _HASH_H_
#define _HASH_H_

#define MAXTABLESIZE 10000				//�����ٵ����ɢ�б���

#define KEYLENGTH 15					//�ؼ����ַ�������󳤶�
typedef char Type[KEYLENGTH + 1];		//�ؼ�������
typedef int Index;						//ɢ�е�ַ

typedef struct LNode *PtrToLNode;
struct LNode {
	Type data;
	int count;
	PtrToLNode next;
};

typedef PtrToLNode Position;
typedef PtrToLNode List;

typedef struct TblNode *HashTable;
struct TblNode {
	int TableSize;	//ɢ�б���󳤶�
	List Heads;		//ָ������ͷ��������
};
#endif