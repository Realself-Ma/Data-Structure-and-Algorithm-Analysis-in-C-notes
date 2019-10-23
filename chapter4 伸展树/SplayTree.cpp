#include <iostream>
using namespace std;
template<class T>
struct TreeNode
{
	T Val;
	TreeNode<T> *left;
	TreeNode<T> *right;
	TreeNode(T _Val):Val(_Val),left(nullptr),right(nullptr){}
};
template<class T>
class SplayTree
{
public:
	SplayTree():root(nullptr),numRotations(0){}
	~SplayTree()
	{
		clear();
	}
	void insertNode(T Val)
	{
		insert(Val, this->root);
	}
	void deleteNode(T Val)
	{
		Delete(Val, this->root);
	}
	TreeNode<T> *findNode(T Val)
	{
		return FindNode(Val, this->root);
	}
	void updateNode(T Old_Val, T New_Val)
	{
		deleteNode(Old_Val);
		insertNode(New_Val);
	}
	void clear()
	{
		clearTree(this->root);
	}
	void print()
	{
		printTree(this->root, 1);
		cout << "\n\n";
	}
private:
	TreeNode<T> *root;
	int numRotations;
	void insert(T Val, TreeNode<T> *&root);
	void Delete(T Val, TreeNode<T> *&root);
	TreeNode<T> *FindNode(T Val, TreeNode<T> *&root);
	TreeNode<T> *FindMax(TreeNode<T> *root);
	TreeNode<T> *FindMin(TreeNode<T> *root);
	TreeNode<T> *Splaying(T Val, TreeNode<T> *&root);
	int InTree(T Val, TreeNode<T> *root);
	void clearTree(TreeNode<T> *&root);
	void printTree(TreeNode<T> * root, int n);
	TreeNode<T> *SingleRotateWithLeft(TreeNode<T> *root);
	TreeNode<T> *SingleRotateWithRight(TreeNode<T> *root);
	TreeNode<T> *DoubleRotateWithLeftRight(TreeNode<T> *root);
	TreeNode<T> *DoubleRotateWithRightLeft(TreeNode<T> *root);
	TreeNode<T> *DoubleRotateWithLeftLeft(TreeNode<T> *root);
	TreeNode<T> *DoubleRotateWithRightRight(TreeNode<T> *root);
};
template<class T>
TreeNode<T> *SplayTree<T>::SingleRotateWithLeft(TreeNode<T> *root)
{
	TreeNode<T> *K1 = root->left;
	root->left = K1->right;
	K1->right = root;
	numRotations++;
	return K1;
}
template<class T>
TreeNode<T> *SplayTree<T>::SingleRotateWithRight(TreeNode<T> *root)
{
	TreeNode<T>* K2 = root->right;
	root->right = K2->left;
	K2->left = root;
	numRotations++;
	return K2;
}
template<class T>
TreeNode<T> *SplayTree<T>::DoubleRotateWithLeftRight(TreeNode<T> *root)
{
	root->left = SingleRotateWithRight(root->left);
	return SingleRotateWithLeft(root);
}
template<class T>
TreeNode<T> *SplayTree<T>::DoubleRotateWithRightLeft(TreeNode<T> *root)
{
	root->right = SingleRotateWithLeft(root->right);
	return SingleRotateWithRight(root);
}
template<class T>
TreeNode<T> *SplayTree<T>::DoubleRotateWithLeftLeft(TreeNode<T> *root)
{
	root = SingleRotateWithLeft(root);
	return SingleRotateWithLeft(root);
}
template<class T>
TreeNode<T> *SplayTree<T>::DoubleRotateWithRightRight(TreeNode<T> *root)
{
	root = SingleRotateWithRight(root);
	return SingleRotateWithRight(root);
}
/************************************************************
Splaying�����ò�����Ϊ��ƽ�⣬����Ϊ����Ŀ��ڵ���ת�����ڵ㴦
*************************************************************/
template<class T>
TreeNode<T> *SplayTree<T>::Splaying(T Val, TreeNode<T> *&root)
{
	if (root == nullptr || root->Val == Val)
	{
		return root;
	}
	else if (Val < root->Val)
	{
		if (root->left == nullptr)
		{
			return root;
		}
		else if (Val < root->left->Val)
		{
			/********************************************************
			�ݹ�����Ѱ�����ƵĽṹ,���Դ��ݵ��Ǹýṹ�����һ���ڵ�
			********************************************************/
			Splaying(Val, root->left->left);
			/********************************************************
			DoubleRotateWithLeftLeft( ) ���ݵĲ�����������
			��Ҫ���ܺ����ķ���ֵ�����𵽶�ԭ���������޸�
			********************************************************/
			root=DoubleRotateWithLeftLeft(root);
		}
		else if (Val > root->left->Val)
		{
			Splaying(Val, root->left->right);
			root=DoubleRotateWithLeftRight(root);
		}
		else
		{
			/*************************************************
			Val=root->left->Val   SingleRotateWithLeft�Ϳ�����
			root->left��ת�����㴦
			*************************************************/
			Splaying(Val, root->left);
			root = SingleRotateWithLeft(root);
		}
		return root;
	}
	else  /* ��ʹ��else if  ��û�ж���else �ķ���ֵ ����������ʾ����������·�����з���ֵ */
	{
		if (root->right == nullptr)
		{
			return root;
		}
		else if (Val > root->right->Val)
		{
			Splaying(Val,root->right->right);
			root = DoubleRotateWithRightRight(root);
		}
		else if (Val < root->right->Val)
		{
			Splaying(Val, root->right->left);
			root = DoubleRotateWithRightLeft(root);
		}
		else
		{
			Splaying(Val, root->right);
			root = SingleRotateWithRight(root);
		}
		return root;
	}
}
template<class T>
int SplayTree<T>::InTree(T Val, TreeNode<T> *root)
{
	if (Val < root->Val)
	{
		/**************************
		�ݹ��ҵ����һ���ڵ�ķ���
		**************************/
		if (root->left == nullptr)
		{
			return root->Val;
		}
		InTree(Val, root->left);
	}
	else if (Val>root->Val)
	{
		if (root->right == nullptr)
		{
			return root->Val;
		}
		InTree(Val, root->right);
	}
	else
	{
		return root->Val;
	}
}
template<class T>
void SplayTree<T>::clearTree(TreeNode<T> *&root)
{
	if (root == nullptr)
	{
		return;
	}
	else
	{
		clearTree(root->left);
		clearTree(root->right);
		delete root;
		root = nullptr;
	}
}
template<class T>
void SplayTree<T>::printTree(TreeNode<T> * root, int n)
{
	if (root == nullptr)
	{
		return;
	}
	printTree(root->left, n + 1);
	for (int i = 0; i < n; ++i)
	{
		cout << "   ";
	}
	cout << root->Val << endl;
	printTree(root->right, n + 1);
}
template<class T>
void SplayTree<T>::insert(T Val, TreeNode<T> *&root)
{
	if (root == nullptr)
	{
		TreeNode<T> *pnew = new TreeNode<T>(Val);
		pnew->left = pnew->right = nullptr;
		root = pnew;
		return;
	}
	if (Val < root->Val)
	{
		insert(Val, root->left);
	}
	else if (Val>root->Val)
	{
		insert(Val, root->right);
	}
	Splaying(Val, root);
}
template<class T>
void SplayTree<T>::Delete(T Val, TreeNode<T> *&root)
{
	root=Splaying(Val, root);
	TreeNode<T> *leftSubTree = root->left;
	TreeNode<T> *rightSubTree = root->right;
	delete root;
	/**************************************************************
	�Ƚ�Ҫɾ���Ľڵ���չ�����������������е����ֵ��������ֵ
	�������Ѱ���������е���Сֵ�����ף���Ϊ��չ�����������ڵ���ࣩ
	**************************************************************/
	root = FindMax(leftSubTree);
	root->right = rightSubTree;
}
template<class T>
TreeNode<T> * SplayTree<T>::FindNode(T Val, TreeNode<T> *&root)
{
	Val = InTree(Val, root);
	return Splaying(Val, root);
}
template<class T>
TreeNode<T> *SplayTree<T>::FindMax(TreeNode<T> *root)
{
	TreeNode<T> *ptemp = root;
	if (root != nullptr)
	{
		while (root->right != nullptr)
		{
			root = root->right;
		}
		/**********************************************************
		��ΪҪ������һ�δ��ݵ�rootֵ�����Բ����õݹ���Ѱ�����ֵ
		**********************************************************/
		Splaying(root->Val, ptemp);
	}
	return root;
}
template<class T>
TreeNode<T> *SplayTree<T>::FindMin(TreeNode<T> *root)
{
	if (root == nullptr)
	{
		return nullptr;
	}
	else
	{
		if (root->left == nullptr)
		{
			Splaying(root->Val, root);
			return root;
		}
		else
		{
			return FindMin(root->left);
		}
	}
}
void main()
{
	SplayTree<int> tree;
	tree.insertNode(50);
	tree.insertNode(20);
	tree.insertNode(80);
	tree.insertNode(40);
	tree.insertNode(100);
	tree.insertNode(10);
	tree.print();
	tree.findNode(50);
	tree.print();
	tree.deleteNode(40);
	tree.print();
	tree.updateNode(80, 200);
	tree.print();
	tree.findNode(80);
	tree.print();
	tree.clear();
	tree.print();
	cin.get();
}