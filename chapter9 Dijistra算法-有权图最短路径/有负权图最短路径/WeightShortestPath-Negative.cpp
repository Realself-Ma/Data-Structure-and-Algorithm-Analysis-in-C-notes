#include <iostream>
#include <vector>
#include <queue>
const int infinity = 100000;
using namespace std;
struct GraphVertex
{
	int dist;
	bool reachable;
	int path;
	int Vertex;
	GraphVertex() :dist(infinity), reachable(false), path(-1), Vertex(-1) {}
};
void WeightShortestPath(vector<vector<int>> &graph, vector<GraphVertex> &Node, int source)
{
	int n;
	n = graph.size();
	if (n < 1)
	{
		return;
	}
	Node.resize(n);
	for (int i = 0; i < n; ++i)
	{
		Node[i].Vertex = i;
	}
	queue<GraphVertex> q;
	Node[source].dist = 0;
	Node[source].reachable = true;
	q.push(Node[source]);
	GraphVertex temp;
	while (!q.empty())
	{
		temp = q.front();
		q.pop();
		for (int j = 0; j < n; ++j)
		{
			/*有负权边，就需要保留最大的路径值*/
			if (graph[temp.Vertex][j] == infinity || Node[j].reachable&&temp.dist + graph[temp.Vertex][j] <= Node[j].dist)
			{
				continue;
			}
			Node[j].dist = temp.dist + graph[temp.Vertex][j];
			Node[j].path = temp.Vertex;
			if (!Node[j].reachable)
			{
				q.push(Node[j]);
			}
			Node[j].reachable = true;
		}
	}
}
void printdist(const vector<GraphVertex> &Node, int n)
{
	for (int i = 0; i < n; ++i)
	{
		cout << i << ": ";
		if (Node[i].reachable)
		{
			cout << Node[i].dist << endl;
		}
		else
		{
			cout << "Unreachable!" << endl;
		}
	}
}
void printpath(const vector<GraphVertex> &Node, int Vertex, int destination)
{
	if (Node[Vertex].path != -1)
	{
		printpath(Node, Node[Vertex].path, destination);
		cout << " -> ";
	}
	cout << Vertex;
	if (Vertex == destination)
	{
		cout << "  The Total Distance: " << Node[Vertex].dist << endl;
	}
}
void main()
{
	vector<vector<int>> graph;
	vector<GraphVertex> Node;
	int source = 1;
	int destination = 2;
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

	WeightShortestPath(graph, Node, source);
	printdist(Node, n);
	printpath(Node, destination, destination);


	cin.get();
	cin.get();
}