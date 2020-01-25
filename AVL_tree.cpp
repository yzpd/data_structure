#include <stdio.h>
#include "AVL_tree.h"
#include <stdlib.h>

#define Max(a, b)	((a) > (b) ? (a) : (b))

//递归求高
int Height(PtrToAVL tree)
{
	int HL, HR, MaxH;
	if (tree != NULL)
	{
		HL = Height(tree->left);
		HR = Height(tree->right);
		MaxH = Max(HL, HR) + 1;

		return MaxH;
	}

	else 
		return 0;
}

//获取树高,NULL为0层,叶子结点为1层
int Get_Height(PtrToAVL tree)
{
	if (tree == NULL)
		return 0;
	else
		return tree->height;
}

//左单旋
PtrToAVL SingleLeftRotation(PtrToAVL tree)
{
	PtrToAVL tmp = tree->left;
	tree->left = tmp->right;
	tmp->right = tree;
	tmp->height = Max(Get_Height(tmp->right), Get_Height(tmp->left)) + 1;
	tree->height = Max(Get_Height(tree->right), Get_Height(tree->left)) + 1;

	return tmp;
}

//右单旋
PtrToAVL SingleRightRotation(PtrToAVL tree)
{
	PtrToAVL tmp = tree->right;
	tree->right = tmp->left;
	tmp->left = tree;
	tmp->height = Max(Get_Height(tmp->right), Get_Height(tmp->left)) + 1;
	tree->height = Max(Get_Height(tree->right), Get_Height(tree->left)) + 1;

	return tmp;
}

//LR型(先后再前), 左右双旋,右单旋接左单旋
PtrToAVL DoubleLR_Rotation(PtrToAVL tree)
{
	tree->left = SingleLeftRotation(tree->left);
	return SingleRightRotation(tree);
}

//RL型, 右左双旋，左旋接右旋
PtrToAVL DoubleRL_Rotation(PtrToAVL tree)
{
	tree->right = SingleRightRotation(tree->right);
	return SingleLeftRotation(tree);
}

//查找最大值
PtrToAVL AVLtree_max(PtrToAVL tree)
{
	if (tree == NULL)
		return NULL;

	while (tree->right != NULL)
		tree = tree->right;
	return tree;
}

//查找最小值
PtrToAVL AVLtree_min(PtrToAVL tree)
{
	if (tree == NULL)
		return NULL;
	while (tree->left != NULL)
		tree = tree->left;
	return tree;
}

//插入结点
PtrToAVL AVL_insert(PtrToAVL tree, Type x)
{
	if (!tree)
	{
		tree = (PtrToAVL)malloc(sizeof(struct AVLTreeNode));
		tree->key = x;
		tree->left = tree->right = NULL;
		tree->height = 1;
	}

	else if ( x < tree->key )
	{
		tree->left = AVL_insert(tree->left, x);

		if ((Get_Height(tree->left) - Get_Height(tree->right)) == 2)
		{
			if ( x == tree->left->key )
				tree = SingleLeftRotation(tree);
			else
				tree = DoubleLR_Rotation(tree);
		}
	}

	else if ( x > tree->key )
	{
		tree->right = AVL_insert(tree->right, x);

		if ((Get_Height(tree->right) - Get_Height(tree->left)) == 2)
		{
			if (x == tree->right->key)
				tree = SingleRightRotation(tree);
			else
				tree = DoubleRL_Rotation(tree);
		}
	}

	/*else x == tree->key 无需插入*/

	tree->height = Max(Get_Height(tree->left), Get_Height(tree->right)) + 1;

	return tree;
}

//删除结点
PtrToAVL AVLtree_delete(Type x, PtrToAVL tree)
{
	PtrToAVL tmp = NULL;
	if (tree == NULL || x == NULL)
		printf("要删除的元素未找到");
	else
	{
		if (x < tree->key)
		{
			tree->left = AVLtree_delete(x, tree->left);

			if ((Get_Height(tree->right) - Get_Height(tree->left) == 2))
			{
				if (Get_Height(tree->right->right) > Get_Height(tree->right->left))
					tree = SingleRightRotation(tree);
				else
					tree = DoubleRL_Rotation(tree);
			}
		}			
		else if (x > tree->key)
		{
			tree->right = AVLtree_delete(x, tree->right);

			if ((Get_Height(tree->left) - Get_Height(tree->right)) == 2)
			{
				if (Get_Height(tree->left->left) > Get_Height(tree->left->right))
					tree = SingleLeftRotation(tree);
				else
					tree = DoubleLR_Rotation(tree);
			}
		}

		else
		{
			if (tree->left && tree->right)
			{
				/**
				 *如果左子树比右子树高
				 *采用左最大替换删除点的策略
				 *优点：删除后的树依旧平衡
				 */
				if (Get_Height(tree->left) > Get_Height(tree->right))
				{
					tmp = AVLtree_max(tree->left);
					tree->key = tmp->key;
					tree->left = AVLtree_delete(tree->key, tree->left);
				}
				/**
				*如果右子树比左子树高,或者一样高
				*采用右最小替换删除点的策略
				*优点：删除后的树依旧平衡
				*/
				else
				{
					tmp = AVLtree_min(tree->right);
					tree->key = tmp->key;
					tree->right = AVLtree_delete(tree->key, tree->right);
				}
			}
			else
			{
				tmp = tree;
				if (!tree->left)
					tree = tree->right;
				else
					tree = tree->left;
				free(tmp);
			}
		}
	}
	return tree;
}