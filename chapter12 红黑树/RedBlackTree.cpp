#include <iostream>
using namespace std;
typedef enum { Red, Black } colorType;
template<class T>
struct TreeNode
{
	T Val;
	TreeNode<T> *left;
	TreeNode<T> *right;
	TreeNode<T> *parent;
	colorType color;
	TreeNode(T _Val):Val(_Val),left(nullptr),right(nullptr),parent(nullptr),color(Black){}
};
template<class T>
class RedBlackTree
{
public:
	RedBlackTree(){}
	~RedBlackTree()
	{
		clear();
	}
	void insertNode(T Val)
	{
		insert(Val, root);
	}
	void deleteNode(T Val)
	{
		TreeNode<T> *node;
		if ((node = findNode(Val)) != nullptr)
		{
			Delete(root, node);
		}
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
		printRedBlackTree(root, 1);
		cout << "\n\n";
	}
	void clear()
	{
		clearTree(root);
	}
private:
	TreeNode<T> *root;
	void insert(T Val, TreeNode<T> *&root);
	void insertFixUp(TreeNode<T> *&root, TreeNode<T> *node);
	void Delete(TreeNode<T> *&root,TreeNode<T> *node);
	void DeleteFixUp(TreeNode<T> *&root,TreeNode<T> *node,TreeNode<T> *parent);
	TreeNode<T> *FindNode(T Val, TreeNode<T> *root);
	void LeftRotate(TreeNode<T> *&root,TreeNode<T> *x);
	void RightRotate(TreeNode<T> *&root, TreeNode<T> *y);
	void printRedBlackTree(TreeNode<T> *root, int n);
	void clearTree(TreeNode<T> *&root);
};
/*
* �Ժ�����Ľڵ�(x)��������ת
*
* ����ʾ��ͼ(�Խڵ�x��������)��
*      px                              px
*     /                               /
*    x                               y
*   /  \      --(����)-->           / \                #
*  lx   y                          x  ry
*     /   \                       /  \
*    ly   ry                     lx  ly
*
*
*/
template<class T>
void RedBlackTree<T>::LeftRotate(TreeNode<T> * &root, TreeNode<T> *x)
{
	TreeNode<T> *y = x->right;
	x->right = y->left;
	if (y->left)
	{
		y->left->parent = x;
	}
	y->parent = x->parent;
	if (x->parent == nullptr)
	{
		root = y;
	}
	else
	{
		if (x->parent->left == x)
		{
			x->parent->left = y;
		}
		else
		{
			x->parent->right = y;
		}
	}
	y->left = x;
	x->parent = y;
}
/*
* �Ժ�����Ľڵ�(y)��������ת
*
* ����ʾ��ͼ(�Խڵ�y��������)��
*            py                               py
*           /                                /
*          y                                x
*         /  \      --(����)-->            /  \                     #
*        x   ry                           lx   y
*       / \                                   / \                   #
*      lx  rx                                rx  ry
*
*/
template<class T>
void RedBlackTree<T>::RightRotate(TreeNode<T> *&root, TreeNode<T> *y)
{
	TreeNode<T> *x = y->left;
	y->left = x->right;
	if (x->right)
	{
		x->right->parent = y;
	}
	x->parent = y->parent;
	if (y->parent == nullptr)
	{
		root = x;
	}
	else
	{
		if (y->parent->left == y)
		{
			y->parent->left = x;
		}
		else
		{
			y->parent->right = x;
		}
	}
	x->right = y;
	y->parent = x;
}
template<class T>
void RedBlackTree<T>::insert(T Val, TreeNode<T> *&root)
{
	TreeNode<T> *ptemp1 = nullptr;
	TreeNode<T> *ptemp2 = root;
	while (ptemp2 != nullptr)
	{
		ptemp1 = ptemp2;
		if (Val < ptemp2->Val)
		{
			ptemp2 = ptemp2->left;
		}
		else if(Val>ptemp2->Val)
		{
			ptemp2 = ptemp2->right;
		}
		else
		{
			break;
		}
	}
	TreeNode<T> *pnew = new TreeNode<T>(Val);
	if (pnew == nullptr)
	{
		return;
	}
	pnew->parent = ptemp1;
	if (ptemp1 == nullptr)
	{
		root = pnew;
	}
	else
	{
		if (Val < ptemp1->Val)
		{
			ptemp1->left = pnew;
		}
		else
		{
			ptemp1->right = pnew;
		}
	}
	pnew->color = Red;
	insertFixUp(root, pnew);
}
template<class T>
void RedBlackTree<T>::insertFixUp(TreeNode<T> *&root, TreeNode<T> *node)
{
	TreeNode<T> *parent, *grandparent;
	/*  ���ڵ���ڲ���Ϊ��   */
	while ((parent = node->parent) && (parent->color == Red))
	{
		grandparent = parent->parent;
		/*  ���ڵ�Ϊ�游�ڵ������   */
		if (grandparent->left == parent)
		{
			{
				/*  case1: ����ڵ�Ϊ�� ����������������ֲ���ڵ��Ǹ��ڵ����/�Һ��ӣ� */
				TreeNode<T> *uncle = grandparent->right;
				if (uncle&&uncle->color == Red)
				{
					parent->color = Black;
					uncle->color = Black;
					grandparent->color = Red;
					node = grandparent;
					continue;
				}
			}
			/*  case2: ����ڵ�Ϊ�ڣ�����ڵ�Ϊ���׽ڵ���Һ���  */
			if (parent->right == node)
			{
				LeftRotate(root, parent);
				/*****************************************************************
				LeftRotate�ı�������Ľṹ����û�иı丸�ڵ�Ͳ���ڵ��ָ��ָ��
				���ԣ�����Ҫ�������ڵ�Ͳ���ڵ��ָ��
				*****************************************************************/
				TreeNode<T> *ptemp;
				ptemp = parent;
				parent = node;
				node = ptemp;
			}
			/*  case3:����ڵ�Ϊ�ڣ�����ڵ��Ǹ��ڵ������   */
			parent->color = Black;
			grandparent->color = Red;
			RightRotate(root, grandparent);
		}
		/*  ���ڵ�Ϊ�游�ڵ���Һ���   */
		else
		{
			{
				/*  case1: ����ڵ�Ϊ�� ����������������ֲ���ڵ��Ǹ��ڵ����/�Һ��ӣ� */
				TreeNode<T> *uncle = grandparent->left;
				if (uncle&&uncle->color == Red)
				{
					parent->color = Black;
					uncle->color = Black;
					grandparent->color = Red;
					node = grandparent;
					continue;
				}
			}
			/*  case2: ����ڵ�Ϊ�ڣ�����ڵ�Ϊ���׽ڵ������  */
			if (parent->left == node)
			{
				RightRotate(root, parent);
				TreeNode<T> *ptemp;
				ptemp = parent;
				parent = node;
				node = ptemp;
			}
			/*  case3:����ڵ�Ϊ�ڣ�����ڵ��Ǹ��ڵ���Һ���   */
			parent->color = Black;
			grandparent->color = Red;
			LeftRotate(root, grandparent);
		}
	}
	root->color = Black;
}
/*
* ɾ�����(node)�������ر�ɾ���Ľ��
*
* ����˵����
*     root ������ĸ����
*     node ɾ���Ľ��
*/
template<class T>
void RedBlackTree<T>::Delete(TreeNode<T> *&root, TreeNode<T> *node)
{
	TreeNode<T> *child, *parent;
	colorType color;

	// ��ɾ���ڵ��"���Һ��Ӷ���Ϊ��"�������
	if ((node->left != NULL) && (node->right != NULL))
	{
		// ��ɾ�ڵ�ĺ�̽ڵ㡣(��Ϊ"ȡ���ڵ�")
		// ������ȡ��"��ɾ�ڵ�"��λ�ã�Ȼ���ٽ�"��ɾ�ڵ�"ȥ����
		TreeNode<T> *replace = node;

		// ��ȡ��̽ڵ�
		replace = replace->right;
		while (replace->left != NULL)
			replace = replace->left;

		// "node�ڵ�"���Ǹ��ڵ�(ֻ�и��ڵ㲻���ڸ��ڵ�)
		if (node->parent)
		{
			if (node->parent->left == node)
				node->parent->left = replace;
			else
				node->parent->right = replace;
		}
		else
			// "node�ڵ�"�Ǹ��ڵ㣬���¸��ڵ㡣
			root = replace;

		// child��"ȡ���ڵ�"���Һ��ӣ�Ҳ����Ҫ"�����Ľڵ�"��
		// "ȡ���ڵ�"�϶����������ӣ���Ϊ����һ����̽ڵ㡣
		child = replace->right;
		parent = replace->parent;
		// ����"ȡ���ڵ�"����ɫ
		color = replace->color;

		// "��ɾ���ڵ�"��"���ĺ�̽ڵ�ĸ��ڵ�"
		if (parent == node)
		{
			parent = replace;
		}
		else
		{
			// child��Ϊ��
			if (child)
				child->parent = parent;
			parent->left = child;

			replace->right = node->right;
			node->right->parent = replace;
		}

		replace->parent = node->parent;
		replace->color = node->color;
		replace->left = node->left;
		node->left->parent = replace;

		if (color == Black)
			DeleteFixUp(root, child, parent);

		delete node;
		return;
	}

	if (node->left != nullptr)
		child = node->left;
	else
		child = node->right;

	parent = node->parent;
	// ����"ȡ���ڵ�"����ɫ
	color = node->color;

	if (child)
		child->parent = parent;

	// "node�ڵ�"���Ǹ��ڵ�
	if (parent)
	{
		if (parent->left == node)
			parent->left = child;
		else
			parent->right = child;
	}
	else
		root = child;

	if (color == Black)
		DeleteFixUp(root, child, parent);
	delete node;
}
/*
* �����ɾ����������
*
* �ڴӺ������ɾ������ڵ�֮��(�����ʧȥƽ��)���ٵ��øú�����
* Ŀ���ǽ������������һ�ź������
*
* ����˵����
*     root ������ĸ�
*     node �������Ľڵ�
*/
template<class T>
void RedBlackTree<T>::DeleteFixUp(TreeNode<T> *&root, TreeNode<T> *node, TreeNode<T> *parent)
{
	TreeNode<T> *other;

	while ((!node || node->color==Black) && node != root)
	{
		if (parent->left == node)
		{
			other = parent->right;
			if (other->color==Red)
			{
				// Case 1: x���ֵ�w�Ǻ�ɫ��  
				other->color = Black;
				parent->color = Red;
				LeftRotate(root, parent);
				other = parent->right;
			}
			if ((!other->left || other->left->color==Black) &&
				(!other->right || other->right->color==Black))
			{
				// Case 2: x���ֵ�w�Ǻ�ɫ����w����������Ҳ���Ǻ�ɫ��  
				other->color=Red;
				node = parent;
				parent = node->parent;
			}
			else
			{
				if (!other->right || other->right->color==Black)
				{
					// Case 3: x���ֵ�w�Ǻ�ɫ�ģ�����w�������Ǻ�ɫ���Һ���Ϊ��ɫ��  
					other->left->color=Black;
					other->color=Red;
					RightRotate(root, other);
					other = parent->right;
				}
				// Case 4: x���ֵ�w�Ǻ�ɫ�ģ�����w���Һ����Ǻ�ɫ�ģ�����������ɫ��
				other->color = parent->color;
				parent->color = Black;
				other->right->color = Black;
				LeftRotate(root, parent);
				node = root;
				break;
			}
		}
		else
		{
			other = parent->left;
			if (other->color==Red)
			{
				// Case 1: x���ֵ�w�Ǻ�ɫ��  
				other->color = Black;
				parent->color=Red;
				RightRotate(root, parent);
				other = parent->left;
			}
			if ((!other->left || other->left->color==Black) &&
				(!other->right || other->right->color==Black))
			{
				// Case 2: x���ֵ�w�Ǻ�ɫ����w����������Ҳ���Ǻ�ɫ��  
				other->color = Red;
				node = parent;
				parent = node->parent;
			}
			else
			{
				if (!other->left || other->left->color == Black)
				{
					// Case 3: x���ֵ�w�Ǻ�ɫ�ģ�����w�������Ǻ�ɫ���Һ���Ϊ��ɫ��  
					other->right->color=Black;
					other->color = Red;
					LeftRotate(root, other);
					other = parent->left;
				}
				// Case 4: x���ֵ�w�Ǻ�ɫ�ģ�����w���Һ����Ǻ�ɫ�ģ�����������ɫ��
				other->color = parent->color;
				parent->color = Black;
				other->left->color = Black;
				RightRotate(root, parent);
				node = root;
				break;
			}
		}
	}
	if (node)
		node->color = Black;
}
/***********************************************************************************************************/
template<class T>
TreeNode<T> *RedBlackTree<T>::FindNode(T Val, TreeNode<T> *root)
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
void RedBlackTree<T>::printRedBlackTree(TreeNode<T> *root, int n)
{
	if (root == nullptr)
	{
		return;
	}
	else
	{
		printRedBlackTree(root->left, n + 1);
		for (int i = 0; i < n; ++i)
		{
			cout << "        ";
		}
		cout << root->Val << "(" << root->color << ")" << endl;
		printRedBlackTree(root->right, n + 1);
	}
	return;
}
template<class T>
void RedBlackTree<T>::clearTree(TreeNode<T> *&root)
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
	return;
}
void main2()
{
	RedBlackTree<int> tree;
	tree.insertNode(10);
	tree.insertNode(25);
	tree.insertNode(35);
	tree.insertNode(70);
	tree.print();
	cin.get();
}
void main()
{
	RedBlackTree<int> tree;
	tree.insertNode(10);
	tree.insertNode(85);
	tree.insertNode(15);
	tree.insertNode(70);
	tree.insertNode(20);
	tree.insertNode(60);
	tree.insertNode(30);
	tree.insertNode(50);
	tree.insertNode(65);
	tree.insertNode(80);
	tree.insertNode(90);
	tree.insertNode(40);
	tree.insertNode(5);
	tree.insertNode(55);
	tree.print();
	tree.deleteNode(70);
	tree.print();
	tree.deleteNode(30);
	tree.print();
	cout << tree.findNode(90)->Val << endl;
	tree.updateNode(90, 800);
	tree.print();
	tree.clear();
	tree.print();
	cin.get();
}
