#include <iostream>
using namespace std;
struct node
{
	int no;
	node * last, *next;
	node(int no, node * last) : no(no), last(last), next(NULL) {};
};
int main()
{
	int n, k, m;
	char temp;
	cin >> n >> temp >> k >> temp >> m;
	if (n < 1 || k < 1 || m < 1)
	{
		cout << "n,m,k must bigger than 0." << endl;
		return 0;
	}
	if (k > n)
	{
		cout << "k should not bigger than n." << endl;
		return 0;
	}
	node * head = new node(1, NULL), *cur = head, *start = head;
	for (int i = 1; i < n; ++i)
	{
		cur->next = new node(i + 1, cur), cur = cur->next;
		if (i + 1 == k) start = cur;
	}
	cur->next = head, head->last = cur;
	//simulation
	int count = 0;
	node * clockwise = start->last, *anticlockwise = start->next;
	while (true)
	{
		++count;
		if (count == m)
		{
			if (clockwise != clockwise->next)
			{
				if (clockwise->next == anticlockwise->last)
				{
					cout << clockwise->next->no << ',';
					delete clockwise->next;
					clockwise->next = anticlockwise, anticlockwise->last = clockwise;
				}
				else
				{
					cout << clockwise->next->no << '-' << anticlockwise->last->no << ',';
					if (clockwise->next == anticlockwise)
					{
						clockwise = clockwise->last, anticlockwise = anticlockwise->next;
						if (clockwise->next == anticlockwise)
						{
							delete clockwise, delete anticlockwise;
							cout << endl;
							break;
						}
						delete clockwise->next, delete anticlockwise->last;
						clockwise->next = anticlockwise, anticlockwise->last = clockwise;
					}
					else
					{
						cur = clockwise->next, clockwise->next = cur->next, cur->next->last = clockwise, delete cur;
						cur = anticlockwise->last, anticlockwise->last = cur->last, cur->last->next = anticlockwise, delete cur;
					}
				}
			}
			else
			{
				cout << clockwise->no << ',' << endl;
				delete clockwise;
				break;
			}
			count = 0;
		}
		else clockwise = clockwise->next, anticlockwise = anticlockwise->last;
	}
	return 0;
}