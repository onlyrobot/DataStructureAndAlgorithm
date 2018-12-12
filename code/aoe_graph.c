#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#define MAX(a, b) ( a > b ? a : b )
#define MIN(a, b) ( a < b ? a : b )
typedef struct graph
{
	int size;
	int set_size;
	int ** list;
	int * in_degree;
	char ** map;
} graph;
graph init()
{
	int num;
	graph g;
	scanf("%d,%d\n", &g.size, &num);
	g.map = (char **)malloc(g.size * sizeof(char *));
	g.list = (int **)malloc(g.size * sizeof(int *));
	g.in_degree = (int *)malloc(g.size * sizeof(int));
	memset(g.in_degree, 0, g.size * sizeof(int));
	for (int i = 0; i < g.size; ++i)
	{
		g.list[i] = (int *)malloc(g.size * sizeof(int));
		memset(g.list[i], 0, g.size * sizeof(int));
		char * s = (char *)malloc(10 * sizeof(char));
		int count = 0;
		while ((s[count] = getchar()) != '\n')
		{
			if (s[count] == ',') break;
			else ++count;
		}
		s[count] = '\0';
		g.map[i] = s;
	}
	for (int i = 0; i < num; ++i)
	{
		int from, to, weight;
		scanf("<%d,%d,%d>", &from, &to, &weight);
		g.list[from][to] = weight;
		++g.in_degree[to];
		getchar();
	}
	return g;
}
void init_e_time(graph * g, int * e_time, int node)
{
	for (int i = 0; i < g->size; ++i)
	{
		if (g->list[node][i] != 0)
		{
			e_time[i] = MAX(e_time[i], e_time[node] + g->list[node][i]);
			init_e_time(g, e_time, i);
		}
	}
}
int init_l_time(graph * g, int * l_time, int node)
{
	if (node == g->size - 1) return l_time[node];
	for (int i = 0; i < g->size; ++i)
	{
		if (g->list[node][i] != 0)
		{
			l_time[node] = MIN(l_time[node], init_l_time(g, l_time, i) - g->list[node][i]);
		}
	}
	return l_time[node];
}
void print_path(graph * g, int * path, int node)
{
	if (path[node] == -1) printf("%s", g->map[node]);
	else
	{
		print_path(g, path, path[node]);
		printf("-%s", g->map[node]);
	}
}
void pass_path(graph * g, int node, int * e_time, int * l_time, int * path)
{
	if (node == g->size - 1)
	{
		print_path(g, path, g->size - 1);
		printf("\n");
	}
	else
	{
		for (int i = 0; i < g->size; ++i)
		{
			if (g->list[node][i] != 0 && e_time[node] + g->list[node][i] == l_time[i])
			{
				path[i] = node;
				pass_path(g, i, e_time, l_time, path);
			}
		}
	}
}
int main()
{
	graph g = init();
	int * orded = (int *)malloc(g.size * sizeof(int));
	//sort
	for (int i = 0; i < g.size; ++i)
	{
		int j;
		for (j = 0; j < g.size; ++j)
		{
			if (g.in_degree[j] == 0)
			{
				orded[i] = j;
				--g.in_degree[j]; //mark as sorted
				break;
			}
		}
		if (j == g.size)
		{
			printf("NOTOPOLOGICALPATH\n");
			return -1;
		}
		for (int k = 0; k < g.size; ++k) if (g.list[j][k] != 0) --g.in_degree[k];
	}
	//print orded
	printf("%s", g.map[orded[0]]);
	for (int i = 1; i < g.size; ++i) printf("-%s", g.map[orded[i]]);
	printf("\n");
	//find all path
	int * e_time = (int *)malloc(g.size * sizeof(int));
	int * l_time = (int *)malloc(g.size * sizeof(int));
	memset(e_time, -1, g.size * sizeof(int));
	memset(l_time, 0x3f, g.size * sizeof(int));
	e_time[0] = 0;
	init_e_time(&g, e_time, 0);
	l_time[g.size - 1] = e_time[g.size - 1];
	init_l_time(&g, l_time, 0);
	/*for (int i = 0; i < g.size; ++i) printf("%d\t", e_time[i]);
	printf("\n");
	for (int i = 0; i < g.size; ++i) printf("%d\t", l_time[i]);
	printf("\n");*/
	int * path = (int *)malloc(g.size * sizeof(int));
	path[0] = -1;
	pass_path(&g, 0, e_time, l_time, path);
	return 0;
}