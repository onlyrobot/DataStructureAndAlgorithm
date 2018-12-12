#include <stdio.h>
#include <stdlib.h>
typedef struct link
{
	int index;
	struct link * next;
} link;
typedef struct node
{
	char data[10];
	link * list;
} node;
typedef struct queue
{
	link * front;
	link * rear;
} queue;
int main()
{
	node nodes[1000];
	char c;
	int count = 0;
	while ((c = getchar()) != '*')
	{
		int count2 = 0;
		nodes[count].data[count2++] = c;
		while ((c = getchar()) != '\n')
		{
			nodes[count].data[count2++] = c;
		}
		nodes[count].data[count2] = '\0', nodes[count++].list = NULL;
	}
	int x, y;
	while (1)
	{
		scanf("%d,%d", &x, &y);
		if (x == -1 && y == -1) break;
		link * new_link = (link *)malloc(sizeof(link));
		new_link->index = y, new_link->next = nodes[x].list;
		nodes[x].list = new_link;
		new_link = (link *)malloc(sizeof(link));
		new_link->index = x, new_link->next = nodes[y].list;
		nodes[y].list = new_link;
	}
	printf("the ALGraph is\n");
	for (int i = 0; i < count; ++i)
	{
		printf("%s", nodes[i].data);
		link * cur = nodes[i].list;
		while (cur != NULL)
		{
			printf(" %d", cur->index);
			cur = cur->next;
		}
		printf("\n");
	}
	printf("the Breadth-First-Seacrh list:");
	queue que = { NULL, NULL };
	for (int i = 0; i < count; ++i)
	{
		if (nodes[i].data[0] != '\0')
		{
			que.front = que.rear = (link *)malloc(sizeof(link));
			que.front->index = i, que.front->next = NULL;
			printf("%s", nodes[i].data);
			nodes[i].data[0] = '\0';
			while (que.front != NULL)
			{
				int index = que.front->index;
				link * cur = nodes[index].list;
				while (cur != NULL)
				{
					if (nodes[cur->index].data[0] != '\0')
					{
						printf("%s", nodes[cur->index].data);
						nodes[cur->index].data[0] = '\0';
						que.rear = que.rear->next = (link *)malloc(sizeof(link));
						que.rear->index = cur->index, que.rear->next = NULL;
					}
					cur = cur->next;
				}
				link * temp = que.front;
				que.front = temp->next;
				free(temp);
			}
		}
	}
	printf("\n");
	return 0;
}