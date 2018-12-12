#include <iostream>
#include <vector>
#include <algorithm>
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
		return left.weight < right.weight;
	}
};
struct graph
{
	int size;
	int ** adj;
};
int find(int * dis_set, int no)
{
	while (dis_set[no] != no)
	{
		dis_set[no] = dis_set[dis_set[no]];
		no = dis_set[no];
	}
	return no;
}
void union_set(int * dis_set, int no, int to)
{
	no = find(dis_set, no);
	to = find(dis_set, to);
	dis_set[no] = to;
}
int main()
{
	graph g, tree;
	cin >> g.size;
	tree.size = g.size;
	g.adj = new int*[g.size];
	tree.adj = new int*[tree.size];
	vector<edge> edges;
	for (int i = 0; i < g.size; ++i)
	{
		g.adj[i] = new int[g.size];
		tree.adj[i] = new int[tree.size];
		for (int j = 0; j < g.size; ++j)
		{
			cin >> g.adj[i][j];
			if (i >= j && g.adj[i][j] != 0) edges.emplace_back(i, j, g.adj[i][j]);
			tree.adj[i][j] = 0;
		}
	}

	sort(edges.begin(), edges.end(), cmp());
	int * dis_set = new int[g.size];
	for (int i = 0; i < g.size; ++i) dis_set[i] = i;
	for (auto it = edges.begin(); it != edges.end(); ++it)
	{
		if (find(dis_set, it->from) != find(dis_set, it->to))
		{
			tree.adj[it->from][it->to] = it->weight;
			union_set(dis_set, it->from, it->to);
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