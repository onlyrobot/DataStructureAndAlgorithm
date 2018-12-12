#include <iostream>
using namespace std;
struct node
{
	int no;
	node * next;
	node(int no, node * next) : no(no), next(next) {};
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
	node * head = new node(1, NULL), *cur = head, *start = k == 2 ? head : NULL;
	for (int i = 1; i < n; ++i)
	{
		cur->next = new node(i + 1, NULL), cur = cur->next;
		if (i + 2 == k) start = cur;
	}
	cur->next = head, start = start == NULL ? cur : start;
	//simulation
	int count = 0, num = 1;
	while (true)
	{
		++count;
		if (count == m)
		{
			cur = start->next;
			if (cur != cur->next)
			{
				if (num % 10 == 0) cout << cur->no << endl;
				else cout << cur->no << ' ';
				++num;
			}
			else
			{
				cout << cur->no << endl;
				delete cur;
				break;
			}
			count = 0;
			start->next = cur->next;
			delete cur;
		}
		else start = start->next;
	}
	return 0;
}