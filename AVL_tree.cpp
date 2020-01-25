#include <stdio.h>
#include "AVL_tree.h"
#include <stdlib.h>

#define Max(a, b)	((a) > (b) ? (a) : (b))

//�ݹ����
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

//��ȡ����,NULLΪ0��,Ҷ�ӽ��Ϊ1��
int Get_Height(PtrToAVL tree)
{
	if (tree == NULL)
		return 0;
	else
		return tree->height;
}

//����
PtrToAVL SingleLeftRotation(PtrToAVL tree)
{
	PtrToAVL tmp = tree->left;
	tree->left = tmp->right;
	tmp->right = tree;
	tmp->height = Max(Get_Height(tmp->right), Get_Height(tmp->left)) + 1;
	tree->height = Max(Get_Height(tree->right), Get_Height(tree->left)) + 1;

	return tmp;
}

//�ҵ���
PtrToAVL SingleRightRotation(PtrToAVL tree)
{
	PtrToAVL tmp = tree->right;
	tree->right = tmp->left;
	tmp->left = tree;
	tmp->height = Max(Get_Height(tmp->right), Get_Height(tmp->left)) + 1;
	tree->height = Max(Get_Height(tree->right), Get_Height(tree->left)) + 1;

	return tmp;
}

//LR��(�Ⱥ���ǰ), ����˫��,�ҵ���������
PtrToAVL DoubleLR_Rotation(PtrToAVL tree)
{
	tree->left = SingleLeftRotation(tree->left);
	return SingleRightRotation(tree);
}

//RL��, ����˫��������������
PtrToAVL DoubleRL_Rotation(PtrToAVL tree)
{
	tree->right = SingleRightRotation(tree->right);
	return SingleLeftRotation(tree);
}

//�������ֵ
PtrToAVL AVLtree_max(PtrToAVL tree)
{
	if (tree == NULL)
		return NULL;

	while (tree->right != NULL)
		tree = tree->right;
	return tree;
}

//������Сֵ
PtrToAVL AVLtree_min(PtrToAVL tree)
{
	if (tree == NULL)
		return NULL;
	while (tree->left != NULL)
		tree = tree->left;
	return tree;
}

//������
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

	/*else x == tree->key �������*/

	tree->height = Max(Get_Height(tree->left), Get_Height(tree->right)) + 1;

	return tree;
}

//ɾ�����
PtrToAVL AVLtree_delete(Type x, PtrToAVL tree)
{
	PtrToAVL tmp = NULL;
	if (tree == NULL || x == NULL)
		printf("Ҫɾ����Ԫ��δ�ҵ�");
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
				 *�������������������
				 *����������滻ɾ����Ĳ���
				 *�ŵ㣺ɾ�����������ƽ��
				 */
				if (Get_Height(tree->left) > Get_Height(tree->right))
				{
					tmp = AVLtree_max(tree->left);
					tree->key = tmp->key;
					tree->left = AVLtree_delete(tree->key, tree->left);
				}
				/**
				*�������������������,����һ����
				*��������С�滻ɾ����Ĳ���
				*�ŵ㣺ɾ�����������ƽ��
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