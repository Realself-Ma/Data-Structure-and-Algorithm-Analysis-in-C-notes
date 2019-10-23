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
class BinarySearchTree
{
public:
	BinarySearchTree():root(nullptr){}
	~BinarySearchTree()
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
	TreeNode<T> *find(T Val)
	{
		return findNode(Val, this->root);
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
	void printTree()
	{
		inorderprint(this->root,1);
		cout << "\n\n";
	}
	void preorderTravel()
	{
		cout << "PreOrderTravel:";
		preordertravel(this->root);
		cout << "\n";
	}
	void inorderTravel()
	{
		cout << "InOrderTravel:";
		inordertravel(this->root);
		cout << "\n";
	}
	void postorderTravel()
	{
		cout << "PostOrderTravel:";
		postordertravel(this->root);
		cout << "\n";
	}
private:
	TreeNode<T> *root;
	void insert(T Val, TreeNode<T> *&root);
	void Delete(T Val, TreeNode<T> *&root);
	TreeNode<T> *findNode(T Val, TreeNode<T> *root);
	TreeNode<T> *findMin(TreeNode<T> *root);
	TreeNode<T> *findMax(TreeNode<T> *root);
	void clearTree(TreeNode<T> * &root);
	void inorderprint(TreeNode<T> *root, int n);
	void preordertravel(TreeNode<T> *root);
	void inordertravel(TreeNode<T> *root);
	void postordertravel(TreeNode<T> *root);
};
template<class T>
void BinarySearchTree<T>::insert(T Val,TreeNode<T> *&root)
{
	if (root == nullptr)
	{
		root = new TreeNode<T>(Val);
		root->left = root->right = nullptr;
		return;
	}
	else
	{
		if (Val < root->Val)
		{
			insert(Val, root->left);
		}
		else
		{
			insert(Val, root->right);
		}
	}
}
template<class T>
void BinarySearchTree<T>::Delete(T Val, TreeNode<T> * &root)
{
	if (root == nullptr)
	{
		return;
	}
	else
	{
		if (Val < root->Val)
		{
			Delete(Val, root->left);
		}
		else if (Val>root->Val)
		{
			Delete(Val, root->right);
		}
		else
		{
			if (root->left&&root->right)
			{
				TreeNode<T> *ptemp = findMin(root->right);
				root->Val = ptemp->Val;
				Delete(ptemp->Val, root->right);
			}
			else
			{
				TreeNode<T> *ptemp = root;
				if (!root->left)
				{
					root = root->right;
				}
				else
				{
					root = root->left;
				}
				delete(ptemp);
				ptemp = nullptr;
			}
		}
	}
}
template<class T>
TreeNode<T> *BinarySearchTree<T>::findNode(T Val, TreeNode<T> *root)
{
	if (root == nullptr)
	{
		return nullptr;
	}
	else
	{
		if (Val < root->Val)
		{
			findNode(Val, root->left);
		}
		else if(Val>root->Val)
		{
			findNode(Val, root->right);
		}
		else
		{
			return root;
		}
	}

}
template<class T>
TreeNode<T> *BinarySearchTree<T>::findMin(TreeNode<T> *root)
{
	if (root == nullptr)
	{
		return nullptr;
	}
	else if (root->left == nullptr)
	{
		return root;
	}
	else
	{
		return findMin(root->left);
	}
}
template<class T>
TreeNode<T> *BinarySearchTree<T>::findMax(TreeNode<T> *root)
{
	if (root == nullptr)
	{
		return nullptr;
	}
	else if (root->right == nullptr)
	{
		return root;
	}
	else
	{
		return findMax(root->right);
	}
}
template<class T>
void BinarySearchTree<T>::clearTree(TreeNode<T> * &root)
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
		/*
		释放节点后记得赋值为空
		*/
		root = nullptr;
	}
}
template<class T>
void BinarySearchTree<T>::inorderprint(TreeNode<T> *root, int n)
{
	if (root == nullptr)
	{
		return;
	}
	else
	{
		inorderprint(root->left, n + 1);
		for (int i = 0; i < n; ++i)
		{
			cout << "     ";
		}
		cout << root->Val << endl;
		inorderprint(root->right, n + 1);
	}
}
template<class T>
void BinarySearchTree<T>::preordertravel(TreeNode<T> *root)
{
	if (root == nullptr)
	{
		return;
	}
	else
	{
		cout << root->Val << " ";
		preordertravel(root->left);
		preordertravel(root->right);
	}
}
template<class T>
void BinarySearchTree<T>::inordertravel(TreeNode<T> *root)
{
	if (root == nullptr)
	{
		return;
	}
	else
	{
		inordertravel(root->left);
		cout << root->Val << " ";
		inordertravel(root->right);
	}
}
template<class T>
void BinarySearchTree<T>::postordertravel(TreeNode<T> *root)
{
	if (root == nullptr)
	{
		return;
	}
	else
	{
		postordertravel(root->left);
		postordertravel(root->right);
		cout << root->Val << " ";
	}
}
void main()
{
	BinarySearchTree<int> tree;
	tree.insertNode(6);
	tree.insertNode(8);
	tree.insertNode(2);
	tree.insertNode(5);
	tree.insertNode(1);
	tree.insertNode(3);
	tree.insertNode(4);
	tree.printTree();
	tree.preorderTravel();
	tree.inorderTravel();
	tree.postorderTravel();
	tree.deleteNode(2);
	tree.printTree();
	cout << tree.find(4)->Val << endl;
	tree.updateNode(4, 10);
	tree.printTree();
	tree.clear();
	tree.printTree();
	cin.get();
}