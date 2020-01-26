#ifndef _HASH_H_
#define _HASH_H_

#define MAXTABLESIZE 10000				//允许开辟的最大散列表长度

#define KEYLENGTH 15					//关键词字符串的最大长度
typedef char Type[KEYLENGTH + 1];		//关键词类型
typedef int Index;						//散列地址

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
	int TableSize;	//散列表最大长度
	List Heads;		//指向链表头结点的数组
};
#endif