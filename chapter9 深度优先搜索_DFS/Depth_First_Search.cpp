#include <iostream>
#include <vector>
using namespace std;
const int infinity = 100000;
void DFS(const vector<vector<int>> &graph,vector<bool> &visited,vector<int> &path,int source)
{
	int n = graph.size();
	visited.resize(n, false);
	visited[source] = true;
	path.push_back(source);
	for (int j = 0; j < n; ++j)
	{
		if (graph[source][j] == infinity)
		{
			continue;
		}
		if (!visited[j])
		{
			DFS(graph, visited, path, j);
		}
	}
	
}
void printResult(vector<int> &path)
{
	int n = path.size();
	for (int i = 0; i < n; ++i)
	{
		if (i == n - 1)
		{
			cout << path[i];
		}
		else
		{
			cout << path[i] << "->";
		}
	}
}
void main()
{
	vector<vector<int>> graph;
	vector<bool> visited;
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
	int source = 0;
	DFS(graph, visited, path, source);
	printResult(path);
	cin.get();
	cin.get();
}
