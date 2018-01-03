
#include<iostream>
#include<iomanip>
using namespace std;

static int arr[]= {1,5,4,3,2,6};
#define TBL_SIZE(a) ( (sizeof(a)) / (sizeof(a[0])) )

template<class T>
class BSTNode
{
public:
	T key;                          //键值
	BSTNode *left;                  //左孩子
	BSTNode *right;                 //右孩子
	BSTNode *parent;                //根节点
	BSTNode(T value,BSTNode *p, BSTNode *l,BSTNode *r):key(value),left(l),right(r),parent(p){}
};

template<class T>
class BSTree
{
private:
	BSTNode<T> *mRoot;
public:
	BSTree();
	~BSTree();

	//前序遍历二叉树
	void preOrder();
	//中序遍历
	void inOrder();
	//后序遍历
	void postOrder();
	//递归实现查找关键字为key的节点
	BSTNode<T>* search(T key);
	//非递归实现查找关键字为key的节点
	BSTNode<T>*  iterativeSearch(T key);
	//查找最小节点，返回最小节点的键值
	T minimum();
	//查找最大节点，返回最大节点的键值
	T maxmum();
	// 找结点(x)的后继结点。即，查找"二叉树中数据值大于该结点"的"最小结点"。
	BSTNode<T>* successor(BSTNode<T> *x);
	// 找结点(x)的前驱结点。即，查找"二叉树中数据值小于该结点"的"最大结点"。
	BSTNode<T>* predecessor(BSTNode<T> *x);

	// 将结点(key为节点键值)插入到二叉树中
	void insert(T key);

	// 删除结点(key为节点键值)
	void remove(T key);

	// 销毁二叉树
	void destroy();

	// 打印二叉树
	void print();
private:
	// 前序遍历"二叉树"
	void preOrder(BSTNode<T>* tree) const;
	// 中序遍历"二叉树"
	void inOrder(BSTNode<T>* tree) const;
	// 后序遍历"二叉树"
	void postOrder(BSTNode<T>* tree) const;

	// (递归实现)查找"二叉树x"中键值为key的节点
	BSTNode<T>* search(BSTNode<T>* x, T key) const;
	// (非递归实现)查找"二叉树x"中键值为key的节点
	BSTNode<T>* iterativeSearch(BSTNode<T>* x, T key) const;

	// 查找最小结点：返回tree为根结点的二叉树的最小结点。
	BSTNode<T>* minimum(BSTNode<T>* tree);
	// 查找最大结点：返回tree为根结点的二叉树的最大结点。
	BSTNode<T>* maximum(BSTNode<T>* tree);

	// 将结点(z)插入到二叉树(tree)中
	void insert(BSTNode<T>* &tree, BSTNode<T>* z);

	// 删除二叉树(tree)中的结点(z)，并返回被删除的结点
	BSTNode<T>* remove(BSTNode<T>* &tree, BSTNode<T> *z);

	// 销毁二叉树
	void destroy(BSTNode<T>* &tree);

	// 打印二叉树
	void print(BSTNode<T>* tree, T key, int direction);

};

template<class T>
inline BSTree<T>::BSTree():mRoot(NULL)
{
}

template<class T>
inline BSTree<T>::~BSTree()
{
	destroy();
}

//前序遍历二叉树
template<class T>
inline void BSTree<T>::preOrder(BSTNode<T>* tree) const
{
	if (tree != NULL)
	{
		cout << tree->key << " ";
		preOrder(tree->left);
		preOrder(tree->right);
	}
}

template<class T>
inline void BSTree<T>::inOrder(BSTNode<T>* tree) const
{
	if (tree != NULL)
	{
		inOrder(tree->left);
		cout << tree->key << " ";
		inOrder(tree->right);
	}
}

template<class T>
inline void BSTree<T>::postOrder(BSTNode<T>* tree) const
{
	if (tree != NULL) {
		postOrder(tree->left);
		postOrder(tree->right);
		cout << tree->key << " ";
	}
}

template<class T>
inline BSTNode<T>* BSTree<T>::search(BSTNode<T>* x, T key) const
{
	if (x == NULL || key == x->key)
		return x;

	if (key < x->key)
		return search(x->left, key);
	else
		return search(x->right, key);
}

template<class T>
inline BSTNode<T>* BSTree<T>::iterativeSearch(BSTNode<T>* x, T key) const
{
	while ((key != x->key) && x != NULL)
	{
		if (key < x->key)
			x = x->left;
		else
			x = x->right;
	}
	return x;
}

template<class T>
inline BSTNode<T>* BSTree<T>::minimum(BSTNode<T>* tree)
{
	if (tree == NULL)
		return NULL;
	while (tree->left != NULL)
		tree = tree->left;

	return tree;
}

template<class T>
inline BSTNode<T>* BSTree<T>::maximum(BSTNode<T>* tree)
{
	if (tree == NULL)
		return NULL;

	while (tree->right != NULL)
		tree = tree->right;

	return tree;
}

template<class T>
inline void BSTree<T>::insert(BSTNode<T>*& tree, BSTNode<T>* z)
{
	BSTNode<T>* y = NULL;
	BSTNode<T>*x = tree;

	//查找z的插入位置
	while (x != NULL)
	{
		y = x;
		if (z->key < x->key)
			x = x->left;
		else
			x = x->right;
	}
	z->parent = y;
	if (y == NULL)
		tree = z;
	else if (z->key < y->key)
		y->left = z;
	else
		y->right = z;
}

template<class T>
inline BSTNode<T>* BSTree<T>::remove(BSTNode<T>*& tree, BSTNode<T>* z)
{
	BSTNode<T>* x = NULL;
	BSTNode<T>* y = NULL;

	if (z->left == NULL || z->right == NULL)
		y = z;
	else
		y = successor(z);
	if (y->left != NULL)
		x = y->left;
	else
		x = y->right;

	if (x != NULL)
		x->parent = y->parent;
	if (y->parent == NULL)
		tree = x;
	else if (y == y->parent->left)
		y->parent->left = x;
	else
		y->parent->right = x;

	if (y != z)
		z->key = y->key;

	return y;
}

//销毁二叉树
template<class T>
inline void BSTree<T>::destroy(BSTNode<T>*& tree)
{
	if (tree == NULL)
		return;
	if (tree->left != NULL)
		destroy(tree->left);
	if (tree->right != NULL)
		destroy(tree->right);

	delete tree;
	tree = NULL;

}


/*
* 打印"二叉查找树"
*
* key        -- 节点的键值
* direction  --  0，表示该节点是根节点;
*               -1，表示该节点是它的父结点的左孩子;
*                1，表示该节点是它的父结点的右孩子。
*/
template<class T>
inline void BSTree<T>::print(BSTNode<T>* tree, T key, int direction)
{
	if (tree != NULL)
	{
		if (direction == 0)
			cout << setw(2) << tree->key << "is root" << endl;
		else
			cout << setw(2) << tree->key << " is " << key << "'s" << setw(12) << (direction == 1 ? "right child" : "left child") << endl;

		print(tree->left, tree->key, -1);
		print(tree->right, tree->key, 1);
	}
}

template<class T>
inline void BSTree<T>::preOrder()
{
	preOrder(mRoot);
}

template<class T>
inline void BSTree<T>::inOrder()
{
	inOrder(mRoot);
}

template<class T>
inline void BSTree<T>::postOrder()
{
	postOrder(mRoot);
}

template<class T>
inline BSTNode<T>* BSTree<T>::search(T key)
{
	return search(mRoot, key);
}

template<class T>
inline BSTNode<T>* BSTree<T>::iterativeSearch(T key)
{
	return iterativeSearch(mRoot, key);
}

template<class T>
inline T BSTree<T>::minimum()
{
	BSTNode<T>* p = minimum(mRoot);
	if (p != NULL)
		return p->key;

	return (T)NULL;
}

template<class T>
inline T BSTree<T>::maxmum()
{
	BSTNode<T> *p = maximum(mRoot);
	if (p != NULL)
		return p->key;

	return (T)NULL;
}

template<class T>
inline BSTNode<T>* BSTree<T>::successor(BSTNode<T>* x)
{
	if (x->right != NULL)
		return minimum(x->right);

	BSTNode<T>* y = x->parent;
	while ((y != NULL) && (x == y->right))
	{
		x = y;
		y = y->parent;
	}
	return y;
}

template<class T>
inline BSTNode<T>* BSTree<T>::predecessor(BSTNode<T>* x)
{
	if (x->left != NULL)
		return maximum(x->left);

	BSTNode<T>* y = x->parent;
	while (y != NULL&&x == y->left)
	{
		x = y;
		y = y->parent;
	}

	return y;
}

template<class T>
inline void BSTree<T>::insert(T key)
{
	BSTNode<T> *z = NULL;
	if ((z = new BSTNode<T>(key, NULL, NULL, NULL)) == NULL)
		return;

	insert(mRoot, z);
}

template<class T>
inline void BSTree<T>::remove(T key)
{
	BSTNode<T>*z, *node;

	if ((z = search(mRoot, key) )!= NULL)
		if ((node = remove(mRoot, z)) != NULL)
			delete node;
}

template<class T>
inline void BSTree<T>::destroy()
{
	destroy(mRoot);
}

template<class T>
inline void BSTree<T>::print()
{
	if (mRoot != NULL)
		print(mRoot, mRoot->key, 0);
}


int main()
{
    int i, ilen;
    BSTree<int>* tree=new BSTree<int>();

    cout << "== 依次添加: ";
    ilen = TBL_SIZE(arr);
    for(i=0; i<ilen; i++) 
    {
        cout << arr[i] <<" ";
        tree->insert(arr[i]);
    }

    cout << "\n== 前序遍历: ";
    tree->preOrder();

    cout << "\n== 中序遍历: ";
    tree->inOrder();

    cout << "\n== 后序遍历: ";
    tree->postOrder();
    cout << endl;

    cout << "== 最小值: " << tree->minimum() << endl;
    cout << "== 最大值: " << tree->maxmum() << endl;
    cout << "== 树的详细信息: " << endl;
    tree->print();

    cout << "\n== 删除根节点: " << arr[3];
    tree->remove(arr[3]);

    cout << "\n== 中序遍历: ";
    tree->inOrder();
    cout << endl;

    // 销毁二叉树
    tree->destroy();

    return 0;
}
