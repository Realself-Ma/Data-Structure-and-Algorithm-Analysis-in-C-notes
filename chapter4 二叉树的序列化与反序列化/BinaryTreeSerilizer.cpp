#define _CRT_SECURE_NO_WARNINGS
#include <iostream>
#include <vector>
#include <string>
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
class BinaryTreeSerializer
{
public:
	BinaryTreeSerializer():root(nullptr){}
	string serialize(TreeNode<T> *root)
	{
		string res = "";
		res += "{";
		serializetravel(root, res);
		/**********************************
		删除最后一个多余的‘，’的两种方法
		**********************************/
		//res=res.substr(0, res.length() - 1);
		res[res.length() - 1] = '}';

		return res;
	}
	TreeNode<T> * deserialize(string & str)
	{
		vector<string> data;
		int lenth = str.length();
		int i = 1;
		while (true)
		{
			int j = i + 1;
			if (str[j] != ','&&str[j] != '}')
			{
				++j;
			}
			data.push_back(str.substr(i,j-i));
			i = j + 1;
			if (i >= lenth)
			{
				break;
			}
		}
		int iter = 0;
		//preordertravel
		deserializetravel(data, root, iter);
		return root;
	}
	/********************************************************************************************************
	返回值为 TreeNode<T> * 时，tree.getroot()=tree.deserialize(str);会报错：tree.getroot()不是可修改的左值
   	返回值改为 TreeNode<T> * &时，就OK了 
	原因是：
	********************************************************************************************************
	返回值为自定义类类型（TreeNode<T> *,不管是不是模板类），不可以作为左值，但可以调用成员函数，返回值时会调用拷贝构造函数
	返回值为自定义类类型的引用（TreeNode<T> * &），可以作为左值，也可调用成员函数，并且返回值不会调用拷贝构造函数
	********************************************************************************************************/
	TreeNode<T> * &getroot()
	{
		return this->root;
	}
	//inorder to printTree
	void printTree(TreeNode<T> *root,int n)
	{
		if (root == nullptr)
		{
			return;
		}
		printTree(root->left, n + 1);
		for (int i = 0; i < n; ++i)
		{
			cout << "     ";
		}
		cout << root->Val << endl;
		printTree(root->right, n + 1);
	}
private:
	TreeNode<T> *root;
	char ss[10];
	void serializetravel(TreeNode<T> *root, string &res)
	{
		if (root == nullptr)
		{
			res += "#,";
			return;
		}
		else
		{
			sprintf(ss, "%d", root->Val);
			res += ss;
			res += ",";
			serializetravel(root->left, res);
			serializetravel(root->right, res);
		}
	}
	void deserializetravel(const vector<string> &data, TreeNode<T> *&root, int &iter)
	{
		iter++;
		if (data[iter - 1] == "#")
		{
			root = nullptr;
		}
		else
		{
			int Val;
			sscanf(data[iter - 1].c_str(), "%d", &Val);
			root = new TreeNode<T>(Val);
			deserializetravel(data, root->left, iter);
			deserializetravel(data, root->right, iter);
		}
	}
};
void main()
{
	BinaryTreeSerializer<int> tree;
	string str = "{3,1,#,#,10,6,#,#,11,#,14,#,#}";
	//tree.getroot()=tree.deserialize(str);
	tree.deserialize(str);
	//tree.printTree(tree.getroot(),1);
	string treestr = tree.serialize(tree.getroot());
	BinaryTreeSerializer<int> tree2;
	tree2.deserialize(treestr);
	tree2.printTree(tree2.getroot(),1);
	cin.get();
}