#include <iostream>
#include <vector>
using namespace std;
/*
查找的根是每棵树的根，而不是每个节点的父节点
*/
int findRoot(vector<int> &dj, int x)
{
	if (dj[x] == x)
	{
		return x;
	}
	return dj[x] = findRoot(dj, dj[x]);
}
//int findRoot(vector<int> &dj, int x)
//{
//	int r, k;
//
//	r = x;
//	while (r != dj[r]) {
//		r = dj[r];
//	}
//
//	// Path compression speeds up the disjoint set.
//	k = x;
//	while (x != r) {
//		x = dj[x];
//		dj[k] = r;
//		k = x;
//	}
//
//	return r;
//}
void setunion(vector<int> &dj, int x, int y)
{
	dj[y] = x;
}
void main()
{
	vector<int> dj;
	dj.resize(8);
	for (int i = 0; i <= 7; ++i)
	{
		dj[i] = i;
	}
	setunion(dj, 1, 3);
	setunion(dj, 3, 5);
	setunion(dj, 3, 6);
	setunion(dj, 2, 4);
	setunion(dj, 2, 7);

	cout << findRoot(dj, 5) << endl;
	/*cout << findRoot(dj, 6) << endl;
	cout << findRoot(dj, 6) << endl;*/
	cin.get();
}