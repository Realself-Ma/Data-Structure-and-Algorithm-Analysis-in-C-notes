#include <iostream>
#include <vector>
#include <algorithm>
using namespace std;
const int infinity = 1000000;
/*�ݹ�ʵ��Ѱ�Ҹ��ڵ㣬��ѹ��·��*/
int findRoot(vector<int> &dj, int x)
{
	if (dj[x] == x)
	{
		return x;
	}
	return dj[x]= findRoot(dj, dj[x]);
}
/*�ǵݹ�ʵ��Ѱ�Ҹ��ڵ㣬��ѹ��·��*/
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
struct Edge
{
	int x;
	int y;
	int cost;
	Edge(int _x = 0, int _y = 0, int _cost = 0):x(_x),y(_y),cost(_cost){}
};
bool comparator(const Edge &e1, const Edge &e2)
{
	return e1.cost < e2.cost;
}
int KruskalAlgorithm(const vector<vector<int>> &graph,vector<int> &dist, vector<int> &path)
{
	int n = graph.size();
	dist.resize(n-1, -1);
	path.resize(n-1, 0);
	vector<Edge> Edges;
	for (int i = 0; i < n; ++i)
	{
		for (int j = 0; j < n; ++j)
		{
			if (graph[i][j] == infinity)
			{
				continue;
			}
			Edges.push_back(Edge(i, j, graph[i][j]));
		}
	}
	/*�����еı߽�������Ȩֵ�͵���ǰ�棨����comparator���ģ�*/
	sort(Edges.begin(), Edges.end(), comparator);
	vector<int> dj;
	dj.resize(n);
	/*�Ը��������ʼ��*/
	for (int i = 0; i < n; ++i)
	{
		dj[i] = i;
	}
	int Edges_Num = Edges.size();
	/*n����������һ������ֻ��Ҫn-1����*/
	int Edge_count = n-1;
	int min_cost = 0;
	for (int i = 0; i < Edges_Num; ++i)
	{
		int rx = findRoot(dj, Edges[i].x);
		int ry = findRoot(dj, Edges[i].y);
		/*��������ĸ��ڵ���ͬ���������ͨ�����ߣ�����ͨ�����Ȧ��*/
		if (rx == ry)
		{
			continue;
		}
		dj[rx] = ry;
		findRoot(dj, Edges[i].x);
		/*������ͨ��ʽҲ���ԣ������� findRootҲ���� */
		/*dj[ry] = rx;
		findRoot(dj, Edges[i].y);*/
		dist[rx] = Edges[i].cost;
		path[rx] = ry;
		min_cost += Edges[i].cost;
		--Edge_count;
		if (Edge_count == 0)
		{
			break;
		}
	}
	Edges.clear();
	return min_cost;
}
void printResult_Kruskal(vector<int> &dist, vector<int> &path, int n)
{
	for (int i = 0; i < n-1; ++i)
	{
		cout << i << ": ";
		cout << " dist " << dist[i] << " path " << path[i] << endl;
	}
}
void main()
{
	vector<vector<int>> graph;
	vector<int> dist;
	vector<int> path;
	int n, num, temp, temp_dist;
	cin >> n;
	graph.resize(n);
	for (int i = 0; i < n; ++i)
	{
		graph[i].resize(n, infinity);
	}
	for (int i = 0; i < n; ++i)
	{
		cin >> num;
		for (int j = 0; j < num; ++j)
		{
			cin >> temp >> temp_dist;
			graph[i][temp] = graph[temp][i] = temp_dist;
		}
	}
	int min_cost = KruskalAlgorithm(graph, dist, path);
	printResult_Kruskal(dist, path, n);
	cout << "The weighted sum of minimum spanning tree is  " << min_cost << " ." << endl;

	for (int i = 0; i < n; ++i)
	{
		graph[i].clear();
	}
	graph.clear();


	cin.get();
	cin.get();
}