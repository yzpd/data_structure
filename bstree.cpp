#include <stdio.h>
#include <stdlib.h>
#include "bstree.h"

//创建结点
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

//若树为空,则返回1;树非空,返回NULL
int BST_is_empty(PtrToBST tree)
{
	if (!tree)
		return 1;
	return NULL;
}

//前序遍历
void preorder_bstree(PtrToBST tree)
{
	if (!BST_is_empty(tree))
	{
		printf("%d ", tree->key);
		preorder_bstree(tree->left);
		preorder_bstree(tree->right);
	}
}

//中序遍历
void inorder_bstree(PtrToBST tree)
{
	if (!BST_is_empty(tree))
	{
		inorder_bstree(tree->left);
		printf("%d ", tree->key);
		inorder_bstree(tree->right);
	}
}

//后序遍历
void postorder_bstree(PtrToBST tree)
{
	if (!BST_is_empty(tree))
	{
		postorder_bstree(tree->left);
		postorder_bstree(tree->right);
		printf("%d ", tree->key);
	}
}

//查找,递归版本
PtrToBST bstree_search(Type x, PtrToBST tree)
{
	if (BST_is_empty(tree) || tree->key == x)
		return tree;

	if (x < tree->key)
		return bstree_search(x, tree->left);
	else
		return bstree_search(x, tree->right);
}

//查找,迭代版本
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

//查找最大值
PtrToBST bstree_max(PtrToBST tree)
{
	if (BST_is_empty(tree))
		return NULL;

	while (tree->right != NULL)
		tree = tree->right;
	return tree;
}

//查找最小值
PtrToBST bstree_min(PtrToBST tree)
{
	if (BST_is_empty(tree))
		return NULL;
	while (tree->left != NULL)
		tree = tree->left;
	return tree;
}

//插入结点
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

//删除结点,采用右子树最小元素的删除代替策略
PtrToBST bstree_delete(Type x, PtrToBST tree)
{
	PtrToBST tmp = NULL;
	if (BST_is_empty(tree))
		printf("要删除的元素未找到");
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
 *print_bstree(tree, key, direction)的作用是打印整颗二叉树(tree)。其中，tree是二叉树节点，key是二叉树的键值，而direction表示该节点的类型：
 *direction为 0，表示该节点是根节点;
 *direction为-1，表示该节点是它的父结点的左孩子;
 *direction为 1，表示该节点是它的父结点的右孩子.
 */
void print_bstree(PtrToBST tree, Type key, int direction)
{
	if (tree != NULL)
	{
		if (direction == 0)    // tree是根节点
			printf("%2d is root\n", tree->key);
		else                // tree是分支节点
			printf("%2d is %2d's %6s child\n", tree->key, key, direction == 1 ? "right" : "left");

		print_bstree(tree->left, tree->key, -1);
		print_bstree(tree->right, tree->key, 1);
	}
}

//销毁二叉树
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