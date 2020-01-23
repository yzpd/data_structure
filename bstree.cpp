#include <stdio.h>
#include <stdlib.h>
#include "bstree.h"

//�������
static PtrToBST create_bstree_node(Type key, PtrToBST parent, PtrToBST left, PtrToBST right)
{
	PtrToBST p;

	if ((p = (PtrToBST)malloc(sizeof(struct BSTreeNode))) == NULL)
		return NULL;
	p->key = key;
	p->left = left;
	p->right = right;
	p->parent = parent;

	return p;
}

//����Ϊ��,�򷵻�1;���ǿ�,����NULL
int BST_is_empty(PtrToBST tree)
{
	if (!tree)
		return 1;
	return NULL;
}

//ǰ�����
void preorder_bstree(PtrToBST tree)
{
	if (!BST_is_empty(tree))
	{
		printf("%d ", tree->key);
		preorder_bstree(tree->left);
		preorder_bstree(tree->right);
	}
}

//�������
void inorder_bstree(PtrToBST tree)
{
	if (!BST_is_empty(tree))
	{
		inorder_bstree(tree->left);
		printf("%d ", tree->key);
		inorder_bstree(tree->right);
	}
}

//�������
void postorder_bstree(PtrToBST tree)
{
	if (!BST_is_empty(tree))
	{
		postorder_bstree(tree->left);
		postorder_bstree(tree->right);
		printf("%d ", tree->key);
	}
}

//����,�ݹ�汾
PtrToBST bstree_search(Type x, PtrToBST tree)
{
	if (BST_is_empty(tree) || tree->key == x)
		return tree;

	if (x < tree->key)
		return bstree_search(x, tree->left);
	else
		return bstree_search(x, tree->right);
}

//����,�����汾
PtrToBST iterative_bstree_search(Type x, PtrToBST tree)
{
	while (!BST_is_empty(tree))
	{
		if (x < tree->key)
			tree = tree->left;
		else
			tree = tree->right;
	}

	return tree;
}

//�������ֵ
PtrToBST bstree_max(PtrToBST tree)
{
	if (BST_is_empty(tree))
		return NULL;

	while (tree->right != NULL)
		tree = tree->right;
	return tree;
}

//������Сֵ
PtrToBST bstree_min(PtrToBST tree)
{
	if (BST_is_empty(tree))
		return NULL;
	while (tree->left != NULL)
		tree = tree->left;
	return tree;
}

//������
PtrToBST bstree_insert(Type x, PtrToBST tree)
{
	if (BST_is_empty(tree))
	{
		tree = (PtrToBST)malloc(sizeof(struct BSTreeNode));
		tree->key = x;
		tree->left = tree->right = NULL;
	}

	else
	{
		if (x < tree->key)
			tree->left = bstree_insert(x, tree->left);
		else
			tree->right = bstree_insert(x, tree->right);
	}

	return tree;
}

//ɾ�����,������������СԪ�ص�ɾ���������
PtrToBST bstree_delete(Type x, PtrToBST tree)
{
	PtrToBST tmp = NULL;
	if (BST_is_empty(tree))
		printf("Ҫɾ����Ԫ��δ�ҵ�");
	else
	{
		if (x < tree->key)
			tree->left = bstree_delete(x, tree->left);
		else if (x > tree->key)
			tree->right = bstree_delete(x, tree->right);
		else
		{
			if (tree->left && tree->right)
			{
				tmp = bstree_min(tree->right);
				tree->key = tmp->key;
				tree->right = bstree_delete(tree->key, tree->right);
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


/**
 *print_bstree(tree, key, direction)�������Ǵ�ӡ���Ŷ�����(tree)�����У�tree�Ƕ������ڵ㣬key�Ƕ������ļ�ֵ����direction��ʾ�ýڵ�����ͣ�
 *directionΪ 0����ʾ�ýڵ��Ǹ��ڵ�;
 *directionΪ-1����ʾ�ýڵ������ĸ���������;
 *directionΪ 1����ʾ�ýڵ������ĸ������Һ���.
 */
void print_bstree(PtrToBST tree, Type key, int direction)
{
	if (tree != NULL)
	{
		if (direction == 0)    // tree�Ǹ��ڵ�
			printf("%2d is root\n", tree->key);
		else                // tree�Ƿ�֧�ڵ�
			printf("%2d is %2d's %6s child\n", tree->key, key, direction == 1 ? "right" : "left");

		print_bstree(tree->left, tree->key, -1);
		print_bstree(tree->right, tree->key, 1);
	}
}

//���ٶ�����
void destroy_bstree(PtrToBST tree)
{
	if (tree == NULL)
		return;
	if (tree->left != NULL)
		destroy_bstree(tree->left);
	if (tree->right != NULL)
		destroy_bstree(tree->right);

	free(tree);
}