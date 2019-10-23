#include <iostream>
#include <vector>
#include <queue>
#include <algorithm>
using namespace std;
const int infinity = 100000;
struct Edge
{
	int x;
	int y;
	int cost;
	Edge(int _x=0,int _y=0,int _cost=0):x(_x),y(_y),cost(_cost){}
};
struct GreaterFunctor //重写仿函数
{
	bool operator ()(const Edge &e1, const Edge &e2)
	{
		/*返回true时，e1的优先级低于e2的优先级（e1排在e2的后面）*/
		return e1.cost > e2.cost;
	}
};
int PrimAlgorithm(const vector<vector<int>> &graph,vector<int> &dist,vector<int> &path,int Root)
{
	/*
	priority_queue<Type, Container, Functional>，
	其中Type 为数据类型，Container为保存数据的容器，Functional 为元素比较方式
	*/
	priority_queue<Edge, vector<Edge>, GreaterFunctor> pq;
	vector<bool> visited;
	int n;
	n = graph.size();
	dist.resize(n, infinity);
	path.resize(n, -1);
	visited.resize(n, false);
	int visit_count = n - 1;
	int min_cost = 0;
	dist[Root] = 0;
	visited[Root] = true;
	for (int i = 0; i < n; ++i)
	{
		if (graph[Root][i] == infinity)
		{
			continue;
		}
		pq.push(Edge(Root, i, graph[Root][i]));
	}
	Edge e;
	while (!pq.empty())
	{
		e = pq.top();
		pq.pop();
		if (visited[e.y])
		{
			continue;
		}
		dist[e.y] = e.cost;
		path[e.y] = e.x;
		min_cost += e.cost;
		visited[e.y] = true;
		--visit_count;
		if (visit_count == 0)
		{
			break;
		}
		for (int i = 0; i < n; ++i)
		{
			if (i == e.y || graph[e.y][i] == infinity || visited[i])
			{
				continue;
			}
			pq.push(Edge(e.y, i, graph[e.y][i]));
		}
	}
	while (!pq.empty())
	{
		pq.pop();
	}
	return min_cost;
}
void printResult_prim(vector<int> &dist, vector<int> &path,int n)
{
	for (int i = 0; i < n; ++i)
	{
		cout << i << ": ";
		cout << " dist " << dist[i] << " path " << path[i] << endl;
	}
}
void main2()
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
	int min_cost;
	int Root = 0;
	min_cost = PrimAlgorithm(graph, dist, path, Root);
	printResult_prim(dist, path, n);
	cout << "The weighted sum of minimum spanning tree is  " << min_cost << " ." << endl;

	for (int i = 0; i < n; ++i)
	{
		graph[i].clear();
	}
	graph.clear();
	cin.get();
	cin.get();
}