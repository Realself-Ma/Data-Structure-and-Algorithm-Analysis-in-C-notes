#include <iostream>
using namespace std;
struct TreeNode
{
	int Val;
	TreeNode *left;
	TreeNode *right;
	TreeNode(int _Val) :Val(_Val), left(nullptr), right(nullptr) {}
};
TreeNode *gettest(TreeNode * root)
{
	return root->left;
}
class Test
{
public:
	TreeNode *gettest()
	{
		return this->root->left;
	}
private:
	TreeNode *root;
};
void main2()
{
	/*Test t1;
	t1.gettest() = nullptr;*/
	TreeNode *root = nullptr;
	//gettest(root) = nullptr;

	cin.get();
}