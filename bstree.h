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


//前序遍历
void preorder_bstree(PtrToBST tree);
//中序遍历
void inorder_bstree(PtrToBST tree);
//后序遍历
void postorder_bstree(PtrToBST tree);


//查找,递归版本
PtrToBST bstree_search(Type x, PtrToBST tree);
//查找,迭代版本
PtrToBST iterative_bstree_search(Type x, PtrToBST tree);


//查找最大值
PtrToBST bstree_max(PtrToBST tree);
//查找最小值
PtrToBST bstree_min(PtrToBST tree);


//插入结点
PtrToBST bstree_insert(Type x, PtrToBST tree);
//删除结点,采用右子树最小元素的删除代替策略
PtrToBST bstree_delete(Type x, PtrToBST tree);

/**
*print_bstree(tree, key, direction)的作用是打印整颗二叉树(tree)。其中，tree是二叉树节点，key是二叉树的键值，而direction表示该节点的类型：
*direction为 0，表示该节点是根节点;
*direction为-1，表示该节点是它的父结点的左孩子;
*direction为 1，表示该节点是它的父结点的右孩子.
*/
void print_bstree(PtrToBST tree, Type key, int direction);

//销毁二叉树
void destroy_bstree(PtrToBST tree);

#endif
