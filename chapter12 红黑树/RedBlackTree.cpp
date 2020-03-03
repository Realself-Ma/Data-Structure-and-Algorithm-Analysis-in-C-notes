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
* 对红黑树的节点(x)进行左旋转
*
* 左旋示意图(对节点x进行左旋)：
*      px                              px
*     /                               /
*    x                               y
*   /  \      --(左旋)-->           / \                #
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
* 对红黑树的节点(y)进行右旋转
*
* 右旋示意图(对节点y进行左旋)：
*            py                               py
*           /                                /
*          y                                x
*         /  \      --(右旋)-->            /  \                     #
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
	/*  父节点存在并且为红   */
	while ((parent = node->parent) && (parent->color == Red))
	{
		grandparent = parent->parent;
		/*  父节点为祖父节点的左孩子   */
		if (grandparent->left == parent)
		{
			{
				/*  case1: 叔叔节点为红 （此种情况不用区分插入节点是父节点的左/右孩子） */
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
			/*  case2: 叔叔节点为黑，插入节点为父亲节点的右孩子  */
			if (parent->right == node)
			{
				LeftRotate(root, parent);
				/*****************************************************************
				LeftRotate改变的是树的结构，并没有改变父节点和插入节点的指针指向
				所以，还需要调换父节点和插入节点的指向
				*****************************************************************/
				TreeNode<T> *ptemp;
				ptemp = parent;
				parent = node;
				node = ptemp;
			}
			/*  case3:叔叔节点为黑，插入节点是父节点的左孩子   */
			parent->color = Black;
			grandparent->color = Red;
			RightRotate(root, grandparent);
		}
		/*  父节点为祖父节点的右孩子   */
		else
		{
			{
				/*  case1: 叔叔节点为红 （此种情况不用区分插入节点是父节点的左/右孩子） */
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
			/*  case2: 叔叔节点为黑，插入节点为父亲节点的左孩子  */
			if (parent->left == node)
			{
				RightRotate(root, parent);
				TreeNode<T> *ptemp;
				ptemp = parent;
				parent = node;
				node = ptemp;
			}
			/*  case3:叔叔节点为黑，插入节点是父节点的右孩子   */
			parent->color = Black;
			grandparent->color = Red;
			LeftRotate(root, grandparent);
		}
	}
	root->color = Black;
}
/*
* 删除结点(node)，并返回被删除的结点
*
* 参数说明：
*     root 红黑树的根结点
*     node 删除的结点
*/
template<class T>
void RedBlackTree<T>::Delete(TreeNode<T> *&root, TreeNode<T> *node)
{
	TreeNode<T> *child, *parent;
	colorType color;

	// 被删除节点的"左右孩子都不为空"的情况。
	if ((node->left != NULL) && (node->right != NULL))
	{
		// 被删节点的后继节点。(称为"取代节点")
		// 用它来取代"被删节点"的位置，然后再将"被删节点"去掉。
		TreeNode<T> *replace = node;

		// 获取后继节点
		replace = replace->right;
		while (replace->left != NULL)
			replace = replace->left;

		// "node节点"不是根节点(只有根节点不存在父节点)
		if (node->parent)
		{
			if (node->parent->left == node)
				node->parent->left = replace;
			else
				node->parent->right = replace;
		}
		else
			// "node节点"是根节点，更新根节点。
			root = replace;

		// child是"取代节点"的右孩子，也是需要"调整的节点"。
		// "取代节点"肯定不存在左孩子！因为它是一个后继节点。
		child = replace->right;
		parent = replace->parent;
		// 保存"取代节点"的颜色
		color = replace->color;

		// "被删除节点"是"它的后继节点的父节点"
		if (parent == node)
		{
			parent = replace;
		}
		else
		{
			// child不为空
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
	// 保存"取代节点"的颜色
	color = node->color;

	if (child)
		child->parent = parent;

	// "node节点"不是根节点
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
* 红黑树删除修正函数
*
* 在从红黑树中删除插入节点之后(红黑树失去平衡)，再调用该函数；
* 目的是将它重新塑造成一颗红黑树。
*
* 参数说明：
*     root 红黑树的根
*     node 待修正的节点
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
				// Case 1: x的兄弟w是红色的  
				other->color = Black;
				parent->color = Red;
				LeftRotate(root, parent);
				other = parent->right;
			}
			if ((!other->left || other->left->color==Black) &&
				(!other->right || other->right->color==Black))
			{
				// Case 2: x的兄弟w是黑色，且w的俩个孩子也都是黑色的  
				other->color=Red;
				node = parent;
				parent = node->parent;
			}
			else
			{
				if (!other->right || other->right->color==Black)
				{
					// Case 3: x的兄弟w是黑色的，并且w的左孩子是红色，右孩子为黑色。  
					other->left->color=Black;
					other->color=Red;
					RightRotate(root, other);
					other = parent->right;
				}
				// Case 4: x的兄弟w是黑色的；并且w的右孩子是红色的，左孩子任意颜色。
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
				// Case 1: x的兄弟w是红色的  
				other->color = Black;
				parent->color=Red;
				RightRotate(root, parent);
				other = parent->left;
			}
			if ((!other->left || other->left->color==Black) &&
				(!other->right || other->right->color==Black))
			{
				// Case 2: x的兄弟w是黑色，且w的俩个孩子也都是黑色的  
				other->color = Red;
				node = parent;
				parent = node->parent;
			}
			else
			{
				if (!other->left || other->left->color == Black)
				{
					// Case 3: x的兄弟w是黑色的，并且w的左孩子是红色，右孩子为黑色。  
					other->right->color=Black;
					other->color = Red;
					LeftRotate(root, other);
					other = parent->left;
				}
				// Case 4: x的兄弟w是黑色的；并且w的右孩子是红色的，左孩子任意颜色。
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
