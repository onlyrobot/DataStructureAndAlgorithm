#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#define MIN(a, b) (a < b ? a : b)
typedef struct adj
{
	int to;
	int weight;
	struct adj * next;
} adj;
typedef struct graph
{
	int node_num;
	adj ** nodes;
} graph;
int maximum_flow(graph * g, int * sum, int * marked, int min, int from, int to)
{
	marked[from] = 1;
	adj * cur = g->nodes[from];
	int sub_mins_sum = 0;
	while (cur != NULL)
	{
		if (!marked[cur->to] && min - sub_mins_sum > 0 && cur->weight > 0)
		{
			int sub_min = 0;
			if (cur->to != to) sub_min = maximum_flow(g, sum, marked, MIN(min - sub_mins_sum, cur->weight), cur->to, to);
			else
			{
				sub_min = MIN(cur->weight, min - sub_mins_sum);
				*sum += sub_min;
			}
			sub_mins_sum += sub_min;
			cur->weight -= sub_min; //delete?

			//add a verse flow
			adj * adj_to = g->nodes[cur->to];
			while (adj_to != NULL)
			{
				if (adj_to->to == from) break;
				adj_to = adj_to->next;
			}
			if (adj_to != NULL) adj_to->weight += sub_min;
			else
			{
				adj * new_adj = (adj *)malloc(sizeof(adj));
				new_adj->to = from, new_adj->next = g->nodes[cur->to], new_adj->weight = sub_min;
				g->nodes[cur->to] = new_adj;
			}
		}
		/*for (int i = 0; i < g->node_num; ++i)
		{
			adj * temp = g->nodes[i];
			while (temp != NULL)
			{
				printf("%d to %d weights %d\t", i, temp->to, temp->weight);
				temp = temp->next;
			}
			printf("\n");
		}
		printf("\n");*/
		cur = cur->next;
	}
	marked[from] = 0;
	return sub_mins_sum;
}
int main()
{
	graph g;
	scanf("%d", &g.node_num);
	g.nodes = (adj **)malloc(g.node_num * sizeof(adj *));
	for (int i = 0; i < g.node_num; ++i) g.nodes[i] = NULL;
	int edge_num;
	scanf("%d", &edge_num);
	for (int i = 0; i < edge_num; ++i)
	{
		int from, to, weight;
		scanf("%d %d %d", &from, &to, &weight);
		adj * a = (adj *)malloc(sizeof(adj));
		a->next = g.nodes[from], a->weight = weight, a->to = to;
		g.nodes[from] = a;
	}
	/*for (int i = 0; i < g.node_num; ++i)
	{
		adj * cur = g.nodes[i];
		while (cur != NULL)
		{
			printf("%d to %d weights %d\t", i, cur->to, cur->weight);
			cur = cur->next;
		}
		printf("\n");
	}*/
	int maximum = 0;
	int * marked = (int *)malloc(g.node_num * sizeof(int));
	memset(marked, 0, g.node_num * sizeof(int));
	maximum_flow(&g, &maximum, marked, INT_MAX, 0, g.node_num - 1);
	printf("%d\n", maximum);
	return 0;
}
/*6
8
0 1 3
0 2 2
1 2 1
1 3 3
1 4 4
2 4 2
3 5 2
4 5 3*/
/*11
21
0 1 1
0 4 4
0 7 6
1 2 2
1 5 2
2 3 2
3 10 4
4 5 3
4 1 3
5 3 2
5 6 3
5 9 3
6 3 1
6 10 3
7 4 2
7 5 1
7 8 6
8 5 2
8 9 6
9 6 1
9 10 4*/