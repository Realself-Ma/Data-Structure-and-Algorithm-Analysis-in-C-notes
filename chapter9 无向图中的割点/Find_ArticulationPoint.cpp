#include <iostream>
#include <vector>
using namespace std;
int Min(int a, int b)
{
	int min = a;
	if (a > b)
	{
		min = b;
	}
	return min;
}
int counter = 1;
void findArticulationPoints(const vector<vector<bool>> &graph,vector<bool> &visited,vector<int> &low,vector<int> &Num,vector<int> &parent,int source)
{
	int n = graph.size();
	visited[source] = true;
	low[source] = Num[source] = counter++;
	for (int j = 0; j < n; ++j)
	{
		if (!graph[source][j])
		{
			continue;
		}
		if (!visited[j])
		{
			parent[j] = source;
			findArticulationPoints(graph, visited, low, Num, parent, j);
			if (low[j] >= Num[source])
			{
				if (j > source)
				{
					cout << "Vertex " << source << " is a articulation point" << endl;
				}
			}
			low[source] = Min(low[source], low[j]);
		}
		else
		{
			if (parent[source] != j)
			{
				low[source] = Min(low[source], Num[j]);
			}
		}
	}
}
void main()
{
	vector<vector<bool>> graph;
	int n, num, temp;
	cin >> n;
	graph.resize(n);
	for (int i = 0; i < n; ++i)
	{
		graph[i].resize(n, false);
	}
	for (int i = 0; i < n; ++i)
	{
		cin >> num;
		for (int j = 0; j < num; ++j)
		{
			cin >> temp;
			graph[i][temp] = graph[temp][i] = true;
		}
	}
	vector<bool> visited;
	visited.resize(n, false);
	vector<int> low;
	vector<int> Num;
	vector<int> parent;
	low.resize(n, -1);
	Num.resize(n, -1);
	parent.resize(n, -1);
	int source = 2;

	findArticulationPoints(graph, visited, low, Num, parent, source);


	cin.get();
	cin.get();
}