#include <iostream>
#include <vector>
using namespace std;
const int INF = 100000;
void AllpairsShortestPath(vector<vector<int>> &graph)
{
	int n = graph.size();
	for (int k = 0; k < n; ++k)
	{
		for (int i = 0; i < n; ++i)
		{
			for (int j = 0; j < n; ++j)
			{
				/*
				将k作为中间节点，遍历所有中间节点
				*/
				if (graph[i][k] + graph[k][j] < graph[i][j])
				{
					graph[i][j] = graph[i][k] + graph[k][j];
				}
			}
		}
	}
}
void printdist(const vector<vector<int>> &graph)
{
	int n = graph.size();
	for (int i = 0; i < n; ++i)
	{
		cout << i << ":  ";
		for (int j = 0; j < n; ++j)
		{
			cout << "  to  " << j;
			cout <<"  "<<graph[i][j] << " " ;
		}
		cout << "\n";
	}
}
void main()
{
	vector<vector<int>> graph;
	vector<vector<int>> Path;
	int n, num, temp, dist;
	cin >> n;
	graph.resize(n);
	for (int i = 0; i < n; ++i)
	{
		graph[i].resize(n, INF);
	}
	for (int i = 0; i < n; ++i)
	{
		cin >> num;
		for (int j = 0; j < num; ++j)
		{
			cin >> temp >> dist;
			graph[i][temp] = dist;
		}
	}

	AllpairsShortestPath(graph);
	printdist(graph);
	cin.get();
	cin.get();
}