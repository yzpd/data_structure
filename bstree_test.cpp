/**
* C 语言: 二叉查找树
*/

#include <stdio.h>
#include "bstree.h"

static int arr[] = { 1,5,4,3,2,6 };
#define TBL_SIZE(a) ( (sizeof(a)) / (sizeof(a[0])) )

void main_bstree_test()
{
	int i, ilen;
	PtrToBST root = NULL;

	printf("== 依次添加: ");
	ilen = TBL_SIZE(arr);
	for (i = 0; i<ilen; i++)
	{
		printf("%d ", arr[i]);
		root = bstree_insert(arr[i], root);
	}

	printf("\n== 前序遍历: ");
	preorder_bstree(root);

	printf("\n== 中序遍历: ");
	inorder_bstree(root);

	printf("\n== 后序遍历: ");
	postorder_bstree(root);
	printf("\n");

	printf("== 最小值: %d\n", bstree_min(root)->key);
	printf("== 最大值: %d\n", bstree_max(root)->key);
	printf("== 树的详细信息: \n");
	print_bstree(root, root->key, 0);

	printf("\n== 删除根节点: %d", arr[3]);
	root = bstree_delete(arr[3], root);

	printf("\n== 中序遍历: ");
	inorder_bstree(root);
	printf("\n");

	// 销毁二叉树
	destroy_bstree(root);

	getchar();
}