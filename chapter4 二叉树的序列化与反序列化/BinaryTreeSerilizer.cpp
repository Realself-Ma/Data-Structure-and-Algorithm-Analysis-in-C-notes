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
		ɾ�����һ������ġ����������ַ���
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
	����ֵΪ TreeNode<T> * ʱ��tree.getroot()=tree.deserialize(str);�ᱨ��tree.getroot()���ǿ��޸ĵ���ֵ
   	����ֵ��Ϊ TreeNode<T> * &ʱ����OK�� 
	ԭ���ǣ�
	********************************************************************************************************
	����ֵΪ�Զ��������ͣ�TreeNode<T> *,�����ǲ���ģ���ࣩ����������Ϊ��ֵ�������Ե��ó�Ա����������ֵʱ����ÿ������캯��
	����ֵΪ�Զ��������͵����ã�TreeNode<T> * &����������Ϊ��ֵ��Ҳ�ɵ��ó�Ա���������ҷ���ֵ������ÿ������캯��
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