#include <iostream>
#include <vector>
#include <queue>
#include <string>
#include <map>
#include <unordered_map>
using namespace std;
/********************************************************************************************
map中的所有元素都会根据元素的键值key自动排序（也可根据自定义的仿函数进行自定义排序）
其中的每个元素都是<key, value>的键值对，map中不允许有键值相同的元素
*********************************************************************************************//*

multimap和map的唯一差别是map中key必须是唯一的，而multimap中的key是可以重复的
********************************************************************************************* /

/********************************************************************************************
在C++11中有新出4个关联式容器：unordered_map/unordered_set/unordered_multimap/unordered_multiset。
这4个关联式容器与map/multimap/set/multiset功能基本类似，最主要就是底层结构不同，使用场景不容。
如果需要得到一个有序序列，使用红黑树系列的关联式容器，如果需要更高的查询效率，使用以哈希表为底层的关联式容器。

unordered_map中的元素没有按照它们的键值或映射值的任何顺序排序，(
而是根据它们的散列值组织成桶以允许通过它们的键值直接快速访问单个元素（具有常数平均时间复杂度）
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