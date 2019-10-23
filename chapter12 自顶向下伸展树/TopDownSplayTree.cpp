#include <iostream>
using namespace std;
/****************************************************************************
自顶向下伸展树，旋转删除操作相对于一般的自底向上伸展树更加的方便，开销更小
****************************************************************************/
template<class T>
struct TreeNode
{
	T Val;
	TreeNode<T> *left;
	TreeNode<T> *right;
	TreeNode(T _Val):Val(_Val),left(nullptr),right(nullptr){}
};
template<class T>
class TopDownSplayTree
{
public:
	TopDownSplayTree():root(nullptr){}
	~TopDownSplayTree()
	{
		clear();
	}
	void insertNode(T Val)
	{
		root=insert(Val, root);
	}
	void deleteNode(T Val)
	{
		root=Delete(Val, root);
	}
	TreeNode<T> *findNode(T Val)
	{
		return FindNode(Val, root);
	}
	void updateNode(T Old_Val, T New_Val)
	{
		deleteNode(Old_Val);
		insertNode(New_Val);
	}
	void print()
	{
		printTree(root, 1);
		cout << "\n\n";
	}
	void clear()
	{
		/**************************************************************************
		当clearTree( )传递的不是根节点的引用时，就要接收clearTree( )的最终返回值
		**************************************************************************/
		root=clearTree(root);
	}
private:
	TreeNode<T> *root;
	TreeNode<T> *insert(T Val, TreeNode<T> *root);
	TreeNode<T> *Delete(T Val, TreeNode<T> *root);
	TreeNode<T> *FindNode(T Val, TreeNode<T> *root);
	TreeNode<T> *Splaying(T Val, TreeNode<T> *root);
	TreeNode<T> *SingleRotateWithLeft(TreeNode<T> *root);
	TreeNode<T> *SingleRotateWithRight(TreeNode<T> *root);
	void printTree(TreeNode<T> *root, int n);
	TreeNode<T> * clearTree(TreeNode<T> *root);
};
template<class T>
TreeNode<T> *TopDownSplayTree<T>::Splaying(T Val, TreeNode<T> *root)
{
	TreeNode<T> *head, *leftTreeMax, *rightTreeMin;
	head = new TreeNode<T>(Val);
	leftTreeMax = rightTreeMin = head;
	while (Val != root->Val)
	{
		if (Val < root->Val)
		{
			if (root->left == nullptr)
			{
				break;
			}
			if (Val < root->left->Val)
			{
				root = SingleRotateWithLeft(root);
				if (root->left == nullptr)
				{
					break;
				}
			}
			rightTreeMin->left = root;
			rightTreeMin = root;
			root = root->left;
		}
		else
		{
			if (root->right == nullptr)
			{
				break;
			}
			if (Val > root->right->Val)
			{
				root = SingleRotateWithRight(root);
				if (root->right == nullptr)
				{
					break;
				}
			}
			leftTreeMax->right = root;
			leftTreeMax = root;
			root = root->right;
		}
	}
	leftTreeMax->right = root->left;
	rightTreeMin->left = root->right;
	root->left = head->right;
	root->right = head->left;
	return root;
}
template<class T>
TreeNode<T> *TopDownSplayTree<T>::SingleRotateWithLeft(TreeNode<T> *root)
{
	TreeNode<T> *K1 = root->left;
	root->left = K1->right;
	K1->right = root;
	return K1;
}
template<class T>
TreeNode<T> *TopDownSplayTree<T>::SingleRotateWithRight(TreeNode<T> *root)
{
	TreeNode<T>* K2 = root->right;
	root->right = K2->left;
	K2->left = root;
	return K2;
}
template<class T>
TreeNode<T> *TopDownSplayTree<T>::insert(T Val, TreeNode<T> *root)
{
	TreeNode<T> *pnew = new TreeNode<T>(Val);
	if (root == nullptr)
	{
		pnew->left = pnew->right = nullptr;
		root = pnew;
	}
	else
	{
		root = Splaying(Val, root);
		if (Val < root->Val)
		{
			pnew->right = root;
			pnew->left = root->left;
			root->left = nullptr;
			root = pnew;
		}
		else if (Val>root->Val)
		{
			pnew->left = root;
			pnew->right = root->right;
			root->right = nullptr;
			root = pnew;
		}
		else
		{
			return root;
		}
	}
	return root;
}
template<class T>
TreeNode<T> *TopDownSplayTree<T>::Delete(T Val, TreeNode<T> *root)
{
	TreeNode<T> *ptemp = nullptr;
	while (root != nullptr)
	{
		root = Splaying(Val, root);
		if (Val == root->Val)
		{
			if (root->left == nullptr)
			{
				ptemp = root->right;
			}
			else
			{
				ptemp = root->left;
				ptemp = Splaying(Val, ptemp);
				ptemp->right = root->right;
			}
			delete root;
			root = ptemp;
		}
		else
		{
			break;
		}
	}
	return root;
}
template<class T>
TreeNode<T> *TopDownSplayTree<T>::FindNode(T Val, TreeNode<T> *root)
{
	if (root == nullptr)
	{
		return nullptr;
	}
	else
	{
		if (root->Val == Val)
		{
			return root;
		}
		else if (Val < root->Val)
		{
			return FindNode(Val, root->left);
		}
		else
		{
			return FindNode(Val, root->right);
		}
	}
	return root;
}
template<class T>
void TopDownSplayTree<T>::printTree(TreeNode<T> *root, int n)
{
	if (root == nullptr)
	{
		return;
	}
	else
	{
		printTree(root->left, n + 1);
		for (int i = 0; i < n; ++i)
		{
			cout << "   ";
		}
		cout << root->Val << endl;
		printTree(root->right, n + 1);
	}
	/*************************
	所有执行完毕也应该 return 
	*************************/
	return;
}
template<class T>
TreeNode<T> * TopDownSplayTree<T>::clearTree(TreeNode<T> *root)
{
	if (root==nullptr)
	{
		return nullptr;
	}
	else
	{
		/*********************************************************
		不能接收 clearTree( )的返回值，因为当返回值为nullptr时
		再执行clearTree( )就会出错
		*********************************************************/
		clearTree(root->left);
		clearTree(root->right);
		delete root;
		root = nullptr;
	}
	/*****************************
	所有执行完毕再return 是没问题的
	*****************************/
	return root;
}
void main()
{
	TopDownSplayTree<int> tree;
	tree.insertNode(30);
	tree.insertNode(20);
	tree.insertNode(40);
	tree.insertNode(10);
	tree.insertNode(100);
	tree.insertNode(80);
	tree.insertNode(200);
	tree.print();
	tree.deleteNode(20);
	tree.print();
	tree.deleteNode(100);
	tree.print();
	tree.deleteNode(30);
	tree.print();
	cout << tree.findNode(80)->Val << endl;
	tree.updateNode(80, 300);
	tree.print();
	tree.clear();
	tree.print();
	cin.get();
}