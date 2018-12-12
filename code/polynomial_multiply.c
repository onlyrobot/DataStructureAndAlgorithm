
/* PRESET CODE BEGIN - NEVER TOUCH CODE BELOW */

#include <stdio.h>
#include <stdlib.h>

typedef struct node
{
	int    coef, exp;
	struct node  *next;
} NODE;

void multiplication(NODE *, NODE *, NODE *);
void input(NODE *);
void output(NODE *);

void input(NODE * head)
{
	int flag, sign, sum, x;
	char c;

	NODE * p = head;

	while ((c = getchar()) != '\n')
	{
		if (c == '<')
		{
			sum = 0;
			sign = 1;
			flag = 1;
		}
		else if (c == '-')
			sign = -1;
		else if (c >= '0'&& c <= '9')
		{
			sum = sum * 10 + c - '0';
		}
		else if (c == ',')
		{
			if (flag == 1)
			{
				x = sign * sum;
				sum = 0;
				flag = 2;
				sign = 1;
			}
		}
		else if (c == '>')
		{
			p->next = (NODE *)malloc(sizeof(NODE));
			p->next->coef = x;
			p->next->exp = sign * sum;
			p = p->next;
			p->next = NULL;
			flag = 0;
		}
	}
}

void output(NODE * head)
{
	while (head->next != NULL)
	{
		head = head->next;
		printf("<%d,%d>,", head->coef, head->exp);
	}
	printf("\n");
}

int main()
{
	NODE * head1, *head2, *head3;

	head1 = (NODE *)malloc(sizeof(NODE));
	input(head1);

	head2 = (NODE *)malloc(sizeof(NODE));
	input(head2);

	head3 = (NODE *)malloc(sizeof(NODE));
	head3->next = NULL;
	multiplication(head1, head2, head3);

	output(head3);

	return 0;
}

/* PRESET CODE END - NEVER TOUCH CODE ABOVE */
void multiplication(NODE * poly1, NODE * poly2, NODE * res)
{
	poly1 = poly1->next, poly2 = poly2->next;
	NODE * cur_res, *cur_poly2;
	while (poly1 != NULL && poly1->coef != 0)
	{
		cur_poly2 = poly2, cur_res = res;
		while (cur_poly2 != NULL && cur_poly2->coef != 0)
		{
			NODE new_node = { poly1->coef * cur_poly2->coef, poly1->exp + cur_poly2->exp, NULL };

			while (cur_res->next != NULL && cur_res->next->exp < new_node.exp) cur_res = cur_res->next;

			if (cur_res->next == NULL || cur_res->next->exp > new_node.exp)
			{
				NODE * temp = (NODE *)malloc(sizeof(NODE));
				temp->next = cur_res->next, temp->coef = 0, temp->exp = new_node.exp, cur_res->next = temp;
			}
			cur_res = cur_res->next, cur_res->coef += new_node.coef;

			cur_poly2 = cur_poly2->next;
		}
		poly1 = poly1->next;
	}
	cur_res = res;
	while (cur_res->next != NULL)
	{
		NODE * temp = cur_res->next;
		if (temp->coef == 0) cur_res->next = temp->next, free(temp);
		else cur_res = temp;
	}
	if (res->next == NULL)
	{
		res->next = (NODE *)malloc(sizeof(NODE));
		res->next->next = NULL, res->next->coef = 0, res->next->exp = 0;
	}
}