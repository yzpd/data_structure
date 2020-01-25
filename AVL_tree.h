#ifndef _AVL_TREE_H_
#define _AVL_TREE_H_

typedef int Type;
typedef struct AVLTreeNode *PtrToAVL;
typedef struct AVLTreeNode
{
	Type key;
	int height;
	PtrToAVL left;
	PtrToAVL right;
};


//�ݹ����
int Height(PtrToAVL tree);
//��ȡ����,NULLΪ0��,Ҷ�ӽ��Ϊ1��
int Get_Height(PtrToAVL tree);


//����
PtrToAVL SingleLeftRotation(PtrToAVL tree);
//�ҵ���
PtrToAVL SingleRightRotation(PtrToAVL tree);


//�������ֵ
PtrToAVL AVLtree_max(PtrToAVL tree);
//������Сֵ
PtrToAVL AVLtree_min(PtrToAVL tree);


//LR��(�Ⱥ���ǰ), ����˫��,�ҵ���������
PtrToAVL DoubleLR_Rotation(PtrToAVL tree);
//RL��, ����˫��������������
PtrToAVL DoubleRL_Rotation(PtrToAVL tree);


//������
PtrToAVL AVL_insert(PtrToAVL tree, Type x);
//ɾ�����
PtrToAVL AVLtree_delete(Type x, PtrToAVL tree);
#endif