#include <iostream>
#include <cstdio>
#include <stack>
using namespace std;
int main()
{
	stack<char> b;
	char c;
	c = getchar();
	while (c != '\n')
	{
		char match = '\0';
		switch (c)
		{
		case '(': case '[': b.push(c); break;
		case ')': match = '('; break;
		case ']': match = '['; break;
		default:
			break;
		}
		c = getchar();
		if (match == '\0') continue;
		if (b.empty() || b.top() != match)
		{
			cout << "Match false!" << endl;
			return 0;
		}
		else
		{
			b.pop();
		}
	}
	if (b.empty())
	{
		cout << "Match succeed!" << endl;
	}else cout << "Match false!" << endl;
	return 0;
}