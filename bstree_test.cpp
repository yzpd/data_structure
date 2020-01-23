/**
* C ����: ���������
*/

#include <stdio.h>
#include "bstree.h"

static int arr[] = { 1,5,4,3,2,6 };
#define TBL_SIZE(a) ( (sizeof(a)) / (sizeof(a[0])) )

void main_bstree_test()
{
	int i, ilen;
	PtrToBST root = NULL;

	printf("== �������: ");
	ilen = TBL_SIZE(arr);
	for (i = 0; i<ilen; i++)
	{
		printf("%d ", arr[i]);
		root = bstree_insert(arr[i], root);
	}

	printf("\n== ǰ�����: ");
	preorder_bstree(root);

	printf("\n== �������: ");
	inorder_bstree(root);

	printf("\n== �������: ");
	postorder_bstree(root);
	printf("\n");

	printf("== ��Сֵ: %d\n", bstree_min(root)->key);
	printf("== ���ֵ: %d\n", bstree_max(root)->key);
	printf("== ������ϸ��Ϣ: \n");
	print_bstree(root, root->key, 0);

	printf("\n== ɾ�����ڵ�: %d", arr[3]);
	root = bstree_delete(arr[3], root);

	printf("\n== �������: ");
	inorder_bstree(root);
	printf("\n");

	// ���ٶ�����
	destroy_bstree(root);

	getchar();
}