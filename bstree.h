#ifndef _BSTREE_H_
#define _BSTREE_H_

typedef int Type;

typedef struct BSTreeNode *PtrToBST;
typedef struct BSTreeNode {
	Type key;
	PtrToBST left;
	PtrToBST right;
	PtrToBST parent;
};

int BST_is_empty(PtrToBST tree);


//ǰ�����
void preorder_bstree(PtrToBST tree);
//�������
void inorder_bstree(PtrToBST tree);
//�������
void postorder_bstree(PtrToBST tree);


//����,�ݹ�汾
PtrToBST bstree_search(Type x, PtrToBST tree);
//����,�����汾
PtrToBST iterative_bstree_search(Type x, PtrToBST tree);


//�������ֵ
PtrToBST bstree_max(PtrToBST tree);
//������Сֵ
PtrToBST bstree_min(PtrToBST tree);


//������
PtrToBST bstree_insert(Type x, PtrToBST tree);
//ɾ�����,������������СԪ�ص�ɾ���������
PtrToBST bstree_delete(Type x, PtrToBST tree);

/**
*print_bstree(tree, key, direction)�������Ǵ�ӡ���Ŷ�����(tree)�����У�tree�Ƕ������ڵ㣬key�Ƕ������ļ�ֵ����direction��ʾ�ýڵ�����ͣ�
*directionΪ 0����ʾ�ýڵ��Ǹ��ڵ�;
*directionΪ-1����ʾ�ýڵ������ĸ���������;
*directionΪ 1����ʾ�ýڵ������ĸ������Һ���.
*/
void print_bstree(PtrToBST tree, Type key, int direction);

//���ٶ�����
void destroy_bstree(PtrToBST tree);

#endif
