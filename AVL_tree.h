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


//递归求高
int Height(PtrToAVL tree);
//获取树高,NULL为0层,叶子结点为1层
int Get_Height(PtrToAVL tree);


//左单旋
PtrToAVL SingleLeftRotation(PtrToAVL tree);
//右单旋
PtrToAVL SingleRightRotation(PtrToAVL tree);


//查找最大值
PtrToAVL AVLtree_max(PtrToAVL tree);
//查找最小值
PtrToAVL AVLtree_min(PtrToAVL tree);


//LR型(先后再前), 左右双旋,右单旋接左单旋
PtrToAVL DoubleLR_Rotation(PtrToAVL tree);
//RL型, 右左双旋，左旋接右旋
PtrToAVL DoubleRL_Rotation(PtrToAVL tree);


//插入结点
PtrToAVL AVL_insert(PtrToAVL tree, Type x);
//删除结点
PtrToAVL AVLtree_delete(Type x, PtrToAVL tree);
#endif