#include<iostream>
using namespace std;


typedef struct BiTNode {
	int data;
	struct BiTNode *lchild, *rchild;
}BiTNode,*BiTree;

//创建一个节点
BiTree newBiTNode(int data)
{
	BiTree T = new BiTNode;
	T->data = data;
	T->lchild = NULL;
	T->rchild = NULL;

	return T;
}

//后序遍历输出
void printPostorder(BiTree T)
{
	if (T == NULL)
		return;
	printPostorder(T->lchild);
	printPostorder(T->rchild);

	cout << T->data << " ";
}

//中序遍历输出
void printInorder(BiTree T)
{
	if (T == NULL)
		return;
	printInorder(T->lchild);
	cout << T->data << " ";
	printInorder(T->rchild);

}

//先序遍历输出
void printPreorder(BiTree T)
{
	if (T == NULL)
		return;
	cout << T->data << " ";
	printPreorder(T->lchild);
	printPreorder(T->rchild);
}


int main()
{
	BiTree root = newBiTNode(1);
	root->lchild = newBiTNode(2);
	root->rchild = newBiTNode(3);
	root->lchild->lchild = newBiTNode(4);
	root->lchild->rchild = newBiTNode(5);

	printf("\nPreorder traversal of binary tree is \n");
	printPreorder(root);

	printf("\nInorder traversal of binary tree is \n");
	printInorder(root);

	printf("\nPostorder traversal of binary tree is \n");
	printPostorder(root);

	getchar();
	return 0;
}
