#include <iostream>
#include <queue>
using namespace std;
struct edge
{
	int from;
	int to;
	int weight;
	edge(int from, int to, int weight) : from(from), to(to), weight(weight) {};
};
struct cmp
{
	bool operator()(const edge & left, const edge & right) const
	{
		return left.weight > right.weight;
	}
};
struct graph
{
	int size;
	int ** adj;
};
int main()
{
	graph g, tree;
	cin >> g.size;
	tree.size = g.size;
	g.adj = new int*[g.size];
	tree.adj = new int*[tree.size];
	for (int i = 0; i < g.size; ++i)
	{
		g.adj[i] = new int[g.size];
		tree.adj[i] = new int[tree.size];
		for (int j = 0; j < g.size; ++j)
		{
			cin >> g.adj[i][j];
			tree.adj[i][j] = 0;
		}
	}
	int node_count = 1;
	bool * used_nodes = new bool[g.size];
	memset(used_nodes, false, g.size * sizeof(int));
	used_nodes[0] = 1;
	priority_queue<edge, vector<edge>, cmp> pq;
	for (int i = 0; i < g.size; ++i)
	{
		if (g.adj[0][i] != 0) pq.emplace(0, i, g.adj[0][i]);
	}
	while (node_count != g.size)
	{
		if (pq.empty())
		{
			cout << "no spanning tree" << endl;
			return 0;
		}
		edge e = pq.top();
		pq.pop();
		if (!used_nodes[e.to])
		{
			used_nodes[e.to] = true;
			tree.adj[e.from][e.to] = e.weight;
			for (int i = 0; i < g.size; ++i)
			{
				if (!used_nodes[i] && g.adj[e.to][i] != 0) pq.emplace(e.to, i, g.adj[e.to][i]);
			}
			++node_count;
		}
	}
	//print the minimum spanning tree
	for (int i = 0; i < tree.size; ++i)
	{
		for (int j = 0; j < tree.size; ++j)
		{
			cout << tree.adj[i][j] << "\t";
		}
		cout << endl;
	}
	return 0;
}
/*7
0 2 4 1 0 0 0
2 0 0 3 10 0 0
4 0 0 2 0 5 0
1 3 2 0 7 8 4
0 10 0 7 0 0 6
0 0 5 8 0 0 1
0 0 0 4 6 1 0*/