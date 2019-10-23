#include <iostream>
#include <vector>
#include <queue>
#include <string>
#include <map>
#include <unordered_map>
using namespace std;
/********************************************************************************************
map�е�����Ԫ�ض������Ԫ�صļ�ֵkey�Զ�����Ҳ�ɸ����Զ���ķº��������Զ�������
���е�ÿ��Ԫ�ض���<key, value>�ļ�ֵ�ԣ�map�в������м�ֵ��ͬ��Ԫ��
*********************************************************************************************//*

multimap��map��Ψһ�����map��key������Ψһ�ģ���multimap�е�key�ǿ����ظ���
********************************************************************************************* /

/********************************************************************************************
��C++11�����³�4������ʽ������unordered_map/unordered_set/unordered_multimap/unordered_multiset��
��4������ʽ������map/multimap/set/multiset���ܻ������ƣ�����Ҫ���ǵײ�ṹ��ͬ��ʹ�ó������ݡ�
�����Ҫ�õ�һ���������У�ʹ�ú����ϵ�еĹ���ʽ�����������Ҫ���ߵĲ�ѯЧ�ʣ�ʹ���Թ�ϣ��Ϊ�ײ�Ĺ���ʽ������

unordered_map�е�Ԫ��û�а������ǵļ�ֵ��ӳ��ֵ���κ�˳������(
���Ǹ������ǵ�ɢ��ֵ��֯��Ͱ������ͨ�����ǵļ�ֱֵ�ӿ��ٷ��ʵ���Ԫ�أ����г���ƽ��ʱ�临�Ӷȣ�
*********************************************************************************************/
struct compare
{
	bool operator ()(const char &char1, const char & char2)
	{
		return char1 < char2;
	}
};
typedef unordered_map<char, int> statType;
typedef map<char, string,compare> encodeType;
struct TreeNode
{
	char ch;
	int weight;
	TreeNode *left;
	TreeNode *right;
	TreeNode(char _ch,int _weight):ch(_ch),weight(_weight),left(nullptr),right(nullptr){}
};
struct GreaterFunctor
{
	bool operator ()(const TreeNode * t1, const TreeNode * t2)
	{
		return t1->weight > t2->weight;
	}
};
void deleteTree(TreeNode *&root)
{
	if (root == nullptr)
	{
		return;
	}
	deleteTree(root->left);
	deleteTree(root->right);
	delete root; 
	root = nullptr;
}
void calculateCode(const statType &statistic, encodeType &encoded, TreeNode * root, string &path)
{
	if (root == nullptr)
	{
		return;
	}
	if (root->ch != '\0')
	{
		encoded[root->ch] = path;
	}
	path.push_back('0');
	calculateCode(statistic, encoded, root->left, path);
	path.pop_back();
	path.push_back('1');
	calculateCode(statistic, encoded, root->right, path);
	path.pop_back();
}
void HuffmanEncode(const statType &statistic, encodeType &encoded)
{
	priority_queue<TreeNode *, vector<TreeNode *>, GreaterFunctor> pq;
	int n = 0;
	for (statType::const_iterator st_it = statistic.begin(); st_it != statistic.end(); ++st_it)
	{
		pq.push(new TreeNode(st_it->first, st_it->second));
		++n;
	}
	for (int i = 0; i < n-1; ++i)
	{
		TreeNode *p1, *p2, *p3;
		p1 = pq.top();
		pq.pop();
		p2 = pq.top();
		pq.pop();
		p3 = new TreeNode('\0', p1->weight + p2->weight);
		p3->left = p1;
		p3->right = p2;
		pq.push(p3);
	}
	TreeNode *root = pq.top();
	pq.pop();
	string code = "";
	calculateCode(statistic, encoded, root, code);
	deleteTree(root);
}
void main()
{
	statType statistic;
	encodeType encoded;
	string s;
	int n, weight;
	cin >> n;
	for (int i = 0; i < n; ++i)
	{
		cin >> s >> weight;
		statistic[s[0]] = weight;
	}

	HuffmanEncode(statistic, encoded);

	for (encodeType::const_iterator ec_it = encoded.begin(); ec_it != encoded.end(); ++ec_it)
	{
		cout << ec_it->first << ":" << ec_it->second << endl;
	}

	cin.get();
	cin.get();
}