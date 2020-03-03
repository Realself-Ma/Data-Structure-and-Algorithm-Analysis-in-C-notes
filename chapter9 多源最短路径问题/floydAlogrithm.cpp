#include <iostream>
#include <vector>
using namespace std;
const int infinity = 100000;
void FloydAlogrithm(const vector<vector<int>> &graph, vector<vector<int>> &dist)
{
	int n;
	n = graph.size();
	dist.resize(n);
	for (int i = 0; i < n; ++i)
	{
		dist[i].resize(n, infinity);
	}
	for (int i = 0; i < n; ++i)
	{
		for (int j = 0; j < n; ++j)
		{
			dist[i][j] = graph[i][j];
		}
	}
	for (int k = 0; k < n; ++k)
	{
		for (int i = 0; i < n; ++i)
		{
			for (int j = 0; j < n; ++j)
			{
				if (dist[i][k] + dist[k][j] >= dist[i][j])
				{
					continue;
				}
				dist[i][j] = dist[i][k] + dist[k][j];
			}
		}
	}
}
void main()
{
	vector<vector<int>> graph;
	vector<vector<int>> dist;
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
			graph[i][temp] = temp_dist;
		}
	}

	FloydAlogrithm(graph, dist);

	for (int i = 0; i < n; ++i)
	{
		for (int j = 0; j < n; ++j)
		{
			cout << "[" << i << "][" << j << "]" << ":";
			if (dist[i][j] < infinity)
			{
				cout << dist[i][j] << endl;
			}
			else
			{
				cout << "Unreachable!" << endl;
			}
		}
	}
	cin.get();
	cin.get();
}