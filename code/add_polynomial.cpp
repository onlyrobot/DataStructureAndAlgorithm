#include <iostream>
using namespace std;
struct node
{
	int coef, exp;
	node * next;
	node(int coef, int exp) : coef(coef), exp(exp), next(NULL) {};
};
void create_polynomial(node * head, int n)
{
	node * p_head = head;
	for (int i = 0; i < n; ++i)
	{
		int coef, exp;
		cin >> coef >> exp;
		node * cur = new node(coef, exp);
		head->next = cur, head = cur;
	}
	if (p_head->next == NULL) p_head->next = new node(0, 0);
}
void add_polynomial(node * a, node * b)
{
	node * pa = a, *pb = b, *cur_a = pa->next, *cur_b = pb->next;
	while (cur_b != NULL)
	{
		if (cur_a == NULL)
		{
			while (cur_b != NULL)
			{
				pa->next = new node(*cur_b);
				cur_b = cur_b->next;
				pa = pa->next;
			}
			break;
		}
		if (cur_a->exp < cur_b->exp)
		{
			pa = cur_a, cur_a = cur_a->next;
		}
		else if (cur_a->exp > cur_b->exp)
		{
			pa->next = new node(*cur_b);
			pa = pa->next, pa->next = cur_a;
			pb = cur_b, cur_b = cur_b->next;
		}
		else
		{
			cur_a->coef += cur_b->coef;
			pa = cur_a, cur_a = cur_a->next;
			pb = cur_b, cur_b = cur_b->next;
		}
	}
	//adjust finally
	pa = a, cur_a = pa->next;
	while (cur_a != NULL)
	{
		if (cur_a->coef == 0)
		{
			pa->next = cur_a->next;
			delete cur_a;
			cur_a = pa->next;
		}
		else pa = cur_a, cur_a = cur_a->next;
	}
	if (a->next == NULL) a->next = new node(0, 0);
}
void print_polynomial(node * head)
{
	head = head->next;
	cout << '<' << head->coef << ',' << head->exp << '>';
	head = head->next;
	while (head != NULL)
	{
		cout << ",<" << head->coef << ',' << head->exp << '>';
		head = head->next;
	}
	cout << endl;
}
int main()
{
	int command;
	cin >> command;
	if (command == 0)
	{
		return 0;
	}
	int n;
	node * pa_head = new node(-1, -1);
	cin >> n;
	create_polynomial(pa_head, n);
	node * pb_head = new node(-1, -1);
	cin >> n;
	create_polynomial(pb_head, n);
	node * pc_head = new node(-1, -1);
	cin >> n;
	create_polynomial(pc_head, n);

	print_polynomial(pa_head), print_polynomial(pb_head), print_polynomial(pc_head);
	add_polynomial(pa_head, pb_head);
	print_polynomial(pa_head);
	add_polynomial(pa_head, pc_head);
	print_polynomial(pa_head);

	//free
	node * cur;
	while (pa_head != NULL) cur = pa_head, pa_head = pa_head->next, delete cur;
	while (pb_head != NULL) cur = pb_head, pb_head = pb_head->next, delete cur;
	while (pc_head != NULL) cur = pc_head, pc_head = pc_head->next, delete cur;
}