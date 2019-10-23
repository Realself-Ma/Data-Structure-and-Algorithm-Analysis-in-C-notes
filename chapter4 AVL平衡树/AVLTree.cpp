#include <iostream>
using namespace std;
template<class T>
struct AVLNode
{
	T Val;
	AVLNode<T> *left;
	AVLNode<T> *right;
	int height;
	AVLNode(T _Val):Val(_Val),left(nullptr),right(nullptr),height(0){}
};
template<class T>
class AVLTree
{
public:
	AVLTree():root(nullptr){}
	~AVLTree()
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
	AVLNode<T> *findNode(T Val)
	{
		return FindNode(Val, this->root);
	}
	void updateNode(T Old_Val,T New_Val)
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
	AVLNode<T> *root;
	void insert(T Val, AVLNode<T>* &root);
	AVLNode<T>* Delete(T Val, AVLNode<T>* &root);
	AVLNode<T>* FindNode(T Val, AVLNode<T>* root);
	void clearTree(AVLNode<T>* &root);
	void Rotate_InDelete(AVLNode<T> *&root);
	int Height(AVLNode<T> * root);
	void printTree(AVLNode<T> *root, int n);
	AVLNode<T> *findMax(AVLNode<T> *root);
	AVLNode<T> *findMin(AVLNode<T> *root);
	AVLNode<T> *SingleRotateWithLeft(AVLNode<T> *root);
	AVLNode<T> *SingleRotateWithRight(AVLNode<T> *root);
	AVLNode<T> *DoubleRotateWithLeftRight(AVLNode<T> *root);
	AVLNode<T> *DoubleRotateWithRightLeft(AVLNode<T> *root);
};
template<class T>
void AVLTree<T>::insert(T Val, AVLNode<T>* &root)
{
	AVLNode<T> *pnew = new AVLNode<T>(Val);
	if (root == nullptr)
	{
		root = pnew;
		pnew->left = pnew->right = nullptr;
	}
	else if (Val < root->Val)
	{
		insert(Val, root->left);
		if (Height(root->left) - Height(root->right) == 2)
		{
			if (Val < root->left->Val)
			{
				root=SingleRotateWithLeft(root);
			}
			else
			{
				root = DoubleRotateWithLeftRight(root);
			}
		}
	}
	else if (Val>root->Val)
	{
		insert(Val, root->right);
		if (Height(root->right) - Height(root->left) == 2)
		{
			if (Val > root->right->Val)
			{
				root = SingleRotateWithRight(root);
			}
			else
			{
				root = DoubleRotateWithRightLeft(root);
			}
		}
	}
	root->height = Max(Height(root->left), Height(root->right)) + 1;
}
template<class T>
AVLNode<T>* AVLTree<T>::Delete(T Val, AVLNode<T>* &root)
{
	AVLNode<T> *ptemp = nullptr;
	if (root == nullptr)
	{
		return nullptr;
	}
	else if (Val < root->Val)
	{
		root->left = Delete(Val, root->left);
		Rotate_InDelete(root);
	}
	else if (Val>root->Val)
	{
		root->right = Delete(Val, root->right);
		Rotate_InDelete(root);
	}
	else
	{
		if (root->left&&root->right)
		{
			ptemp = findMin(root->right);
			root->Val = ptemp->Val;
			root->right = Delete(root->Val, root->right);
			Rotate_InDelete(root);
		}
		else
		{
			ptemp = root;
			if (!root->left)
			{
				root = root->right;
			}
			else if (!root->right)
			{
				root = root->left;
			}
			delete(ptemp);
			ptemp = nullptr;
		}
	}
	return root;
}
template<class T>
AVLNode<T>* AVLTree<T>::FindNode(T Val, AVLNode<T>* root)
{
	if (root == nullptr)
	{
		return nullptr;
	}
	else
	{
		if (Val < root->Val)
		{
			return FindNode(Val, root->left);
		}
		else if (Val>root->Val)
		{
			return FindNode(Val, root->right);
		}
		else
		{
			return root;
		}
	}
}
template<class T>
void AVLTree<T>::clearTree(AVLNode<T>* &root)
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
int AVLTree<T>::Height(AVLNode<T> * root)
{
	if (root == nullptr)
	{
		return -1;
	}
	else
	{
		return root->height;
	}
}
template<class T>
void AVLTree<T>::Rotate_InDelete(AVLNode<T> *&root)
{
	if (Height(root->right) - Height(root->left) == 2)
	{
		if (Height(root->right->right) - Height(root->right->left) == 1)
		{
			
			root = SingleRotateWithRight(root);/* 右-单旋转 修复情形4 */
		}
		else if (Height(root->right->left) - Height(root->right->right) == 1)
		{
			root = DoubleRotateWithRightLeft(root);/* 右-左双旋转 修复情形3 */
		}
		else
		{
			root = SingleRotateWithRight(root);/* 左子树为空 也是右-单旋转 修复 */
		}
	}
	else if (Height(root->left) - Height(root->right) == 2)
	{
		if (Height(root->left->left) - Height(root->left->right) == 1)
		{
			root = SingleRotateWithLeft(root);/* 左-单旋转 修复情形1 */
		}
		else if (Height(root->left->right) - Height(root->left->left) == 1)
		{
			root = DoubleRotateWithLeftRight(root);/* 左-右 双旋转 修复情形2 */
		}
		else
		{
			root = SingleRotateWithLeft(root);/* 右子树为空 也是左-单旋转 修复 */
		}
	}
}
template<class T>
void AVLTree<T>::printTree(AVLNode<T> *root, int n)
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
			cout << "    ";
		}
		cout << root->Val << endl;
		printTree(root->right, n + 1);
	}
}
template<class T>
AVLNode<T> *AVLTree<T>::findMax(AVLNode<T> *root)
{
	if (root == nullptr)
	{
		return nullptr;
	}
	else
	{
		if (root->right == nullptr)
		{
			return root;
		}
		else
		{
			return findMax(root->right);
		}
	}
}
template<class T>
AVLNode<T> *AVLTree<T>::findMin(AVLNode<T> *root)
{
	if (root == nullptr)
	{
		return nullptr;
	}
	else
	{
		if (root->left == nullptr)
		{
			return root;
		}
		else
		{
			return findMin(root->left);
		}
	}
}
int Max(int a, int b)
{
	int max = a;
	if (b > a)
	{
		max = b;
	}
	return max;
}
template<class T>
AVLNode<T> *AVLTree<T>::SingleRotateWithLeft(AVLNode<T> *root)
{
	AVLNode<T> *K1 = root->left;
	root->left = K1->right;
	K1->right = root;
	root->height = Max(Height(root->left), Height(root->right)) + 1;
	K1->height = Max(Height(K1->left), root->height) + 1;
	return K1;
}
template<class T>
AVLNode<T> *AVLTree<T>::SingleRotateWithRight(AVLNode<T> *root)
{
	AVLNode<T>* K2 = root->right;
 	root->right = K2->left;
	K2->left = root;
	root->height = Max(Height(root->left), Height(root->right)) + 1;
	K2->height = Max(Height(K2->right), root->height) + 1;
	return K2;
}
template<class T>
AVLNode<T> *AVLTree<T>::DoubleRotateWithLeftRight(AVLNode<T> *root)
{
	root->left = SingleRotateWithRight(root->left);
	return SingleRotateWithLeft(root);
}
template<class T>
AVLNode<T> *AVLTree<T>::DoubleRotateWithRightLeft(AVLNode<T> *root)
{
	root->right = SingleRotateWithLeft(root->right);
	return SingleRotateWithRight(root);
}
void main()
{
	AVLTree<int> tree;
	tree.insertNode(3);
	tree.insertNode(2);
	tree.insertNode(1);
	tree.insertNode(4);
	tree.insertNode(5);
	tree.insertNode(6);
	tree.insertNode(7);
	tree.insertNode(16);
	tree.insertNode(15);
	tree.insertNode(14);
	tree.insertNode(13);
	tree.insertNode(12);
	tree.insertNode(11);
	tree.insertNode(10);
	tree.insertNode(8);
	tree.insertNode(9);
	tree.print();
	cout << tree.findNode(10)->Val << endl;
	tree.updateNode(10, 100);
	tree.print();
	tree.clear();
	tree.print();
	cin.get();
}
void main1()
{
	AVLTree<int> tree;
	tree.insertNode(3);
	tree.insertNode(2);
	tree.insertNode(1);
	tree.insertNode(4);
	tree.insertNode(5);
	tree.insertNode(6);
	tree.insertNode(7);
	tree.insertNode(16);
	tree.insertNode(15);
	tree.insertNode(14);
	tree.insertNode(13);
	tree.insertNode(12);
	tree.insertNode(11);
	tree.insertNode(10);
	tree.insertNode(8);
	tree.insertNode(9);
	tree.print();
	tree.deleteNode(11);
	cout << "After 11 delete" << endl;
	tree.print();
	tree.deleteNode(13);
	cout << "After 13 delete" << endl;
	tree.print();
	tree.deleteNode(14);
	cout << "After 14 delete" << endl;
	tree.print();
	tree.deleteNode(12);
	cout << "After 12 delete" << endl;
	tree.print();
	tree.deleteNode(15);
	cout << "After 15 delete" << endl;
	tree.print();
	tree.deleteNode(9);
	cout << "After 9 delete" << endl;
	tree.print();
	tree.deleteNode(10);
	cout << "After 10 delete" << endl;
	tree.print();
	tree.deleteNode(16);
	cout << "After 16 delete" << endl;
	tree.print();

	cin.get();
}