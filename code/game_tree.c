#include <stdio.h>
#include <stdlib.h>
#include <limits.h>
typedef struct node
{
	char data;
	struct node * child;
	struct node * sibling;
	struct node * even_min;
	struct node * even_max;
	struct node * odd_min;
	struct node * odd_max;
	int even_min_height;
	int even_max_height;
	int odd_min_height;
	int odd_max_height;
} node;
node * create_tree(char ** p)
{
	if (**p == '\n') return NULL;
	++*p;
	node * root = NULL;
	if (**p != ')')
	{
		root = (node *)malloc(sizeof(node));
		root->data = *(*p)++, root->child = NULL, root->sibling = NULL;
		if (**p != ')')
		{
			++*p;
			node * next = root->child = create_tree(p);
			while (**p != ')')
			{
				++*p;
				next = next->sibling = create_tree(p);
			}
		}
	}
	++*p;
	return root;
}
void pre_process(node * root)
{
	node * sub = root->child;
	if (sub == NULL)
	{
		root->even_max = root->even_min = root;
		root->even_max_height = root->even_min_height = 0;
		root->odd_max/* = root->odd_min*/ = NULL;
		//root->odd_max_height = root->odd_min_height = -1;
	}
	else
	{
		sub = root->child;
		pre_process(sub);
		if (sub->even_max != NULL)
		{
			root->odd_max = sub, root->odd_max_height = sub->even_max_height + 1;
			root->odd_min = sub, root->odd_min_height = sub->even_min_height + 1;
		}
		else root->odd_max/* = root->odd_min*/ = NULL;
		if (sub->odd_max != NULL)
		{
			root->even_max = sub, root->even_max_height = sub->odd_max_height + 1;
			root->even_min = sub, root->even_min_height = sub->odd_min_height + 1;
		}
		else root->even_max/* = root->even_min*/ = NULL;
		sub = sub->sibling;
		while (sub != NULL)
		{
			pre_process(sub);
			if (sub->even_max != NULL)
			{
				if (sub->even_max_height > root->odd_max_height) root->odd_max = sub, root->odd_max_height = sub->even_max_height + 1;
				if (sub->even_min_height < root->odd_min_height) root->odd_min = sub, root->odd_min_height = sub->even_min_height + 1;
			}
			if (sub->odd_max != NULL)
			{
				if (sub->odd_max_height > root->even_max_height) root->even_max = sub, root->even_max_height = sub->odd_max_height + 1;
				if (sub->odd_min_height < root->even_min_height) root->even_min = sub, root->even_min_height = sub->odd_min_height + 1;
			}
			sub = sub->sibling;
		}
	}
}
void print_tree(node * root, int depth)
{
	if (root == NULL) return;
	for (int i = 0; i < depth; ++i) printf("    ");
	printf("%c\n", root->data);
	node * sub = root->child;
	while (sub != NULL)
	{
		print_tree(sub, depth + 1);
		sub = sub->sibling;
	}
}
node * check_valid(node * root, char data)
{
	node * sub = root->child;
	while (sub != NULL)
	{
		if (sub->data == data) return sub;
		sub = sub->sibling;
	}
	return NULL;
}
int height(node * root)
{
	if (root->even_max == NULL) return root->odd_max_height;
	else if (root->odd_max == NULL) return root->even_max_height;
	else return root->even_max_height > root->odd_max_height ? root->even_max_height : root->odd_max_height;
}
node * computer_play(node * root)
{
	int winable = 0;
	node * next = root->child, *sub = next->sibling;
	if (next->even_max != NULL) winable = 1;
	while (sub != NULL)
	{
		if (sub->even_max != NULL)
		{
			if (!winable || next->odd_max != NULL && sub->odd_max == NULL \
				|| next->odd_max != NULL && height(sub) > height(next) || \
				sub->odd_max == NULL && height(sub) < height(next))
			{
				next = sub;
			}
		}
		else if (!winable && height(sub) > height(next))
		{
			next = sub;
		}
		sub = sub->sibling;
	}
	printf("computer: %c\n", next->data);
	return next;
}
node * player_play(node * cur)
{
	node * next;
	char input;
	while (1)
	{
		printf("player:\n");
		getchar();
		scanf("%c", &input);
		if ((next = check_valid(cur, input)) != NULL) return next;
		else printf("illegal move.\n");
	}
}
int win(node * root)
{
	return root->child == NULL;
}
int main()
{
	char s[1000];
	scanf("%s", s);
	char * p = s;
	node * root = create_tree(&p);
	print_tree(root, 0);
	pre_process(root); //generate the priority information
	while (1)
	{
		printf("Who play first(0: computer; 1: player )?\n");
		int who_first;
		scanf("%d", &who_first);
		node * cur = root; //current node
		if (who_first == 1) //player first
		{
			while (1)
			{
				cur = player_play(cur);
				if (win(cur))
				{
					printf("Congratulate, you win.\n");
					break;
				}
				cur = computer_play(cur);
				if (win(cur))
				{
					printf("Sorry, you lost.\n");
					break;
				}
			}
		}
		else //computer first
		{
			while (1)
			{
				cur = computer_play(cur);
				if (win(cur))
				{
					printf("Sorry, you lost.\n");
					break;
				}
				cur = player_play(cur);
				if (win(cur))
				{
					printf("Congratulate, you win.\n");
					break;
				}
			}
		}
		printf("Continue(y/n)?\n");
		char again;
		getchar();
		scanf("%c", &again);
		if (again == 'n') break;
	}
	return 0;
}