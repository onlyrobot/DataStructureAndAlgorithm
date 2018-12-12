#include <iostream>
#include <string>
#include <stack>
#include <climits>
#include <cmath>
using namespace std;
struct op
{
	int priority;
	int(*fun)(int, int);
	op(int priority, int(*fun)(int, int)) : priority(priority), fun(fun) {};
};
int add(int a, int b)
{
	return a + b;
}
int multiply(int a, int b)
{
	return a * b;
}
int subtraction(int a, int b)
{
	return a - b;
}
int divide(int a, int b)
{
	if (b == 0)
	{
		cout << "Divide 0." << endl;
		return INT_MIN;
	}
	return a / b;
}
int mode(int a, int b)
{
	if (b == 0)
	{
		cout << "Divide 0." << endl;
		return INT_MIN;
	}
	return a % b;
}
int my_pow(int a, int b)
{
	if (b < 0)
	{
		cout << "error." << endl;
		return INT_MIN;
	}
	return pow(a * 1.0, b * 1.0);
}
int parse_int(string & s, string::iterator & pos)
{
	int symbol = 1;
	if (*pos == '-')
	{
		symbol = -1;
		++pos;
	}
	int num = 0;
	while (pos != s.end() && *pos >= '0' && *pos <= '9')
	{
		num = num * 10 + *pos++ - '0';
	}
	return num * symbol;
}
op parse_op(stack<op> & o, string::iterator & pos)
{
	switch (*pos++)
	{
	case '+': return op(0, add);
	case '-': return op(0, subtraction);
	case '*': return op(1, multiply);
	case '/': return op(1, divide);
	case '%': return op(1, mode);
	case '^': return op(o.empty() ? 2 : o.top().priority + 3, my_pow); //specil
	default:
		cout << "error." << endl;
		return op(-1, NULL);
	}
}
int main()
{
	int n;
	cin >> n;
	getchar();
	while (n-- > 0)
	{
		string input;
		getline(cin, input);
		string::iterator pos = input.begin();
		stack<op> o;
		stack<int> n;
		while (true)
		{
			int num;
			if (*pos == '-' || *pos >= '0' && *pos <= '9')
			{
				n.push(parse_int(input, pos));
			}
			else if (*pos == '(')
			{
				o.push(op(-1, NULL));
				++pos;
				continue;
			}

			if (pos == input.end()) break;

			while (*pos == ')')
			{
				if (o.empty())
				{
					cout << "error." << endl;
					goto next;
				}
				while (o.top().priority != -1)
				{
					int num1, num2;
					if (n.empty())
					{
						cout << "error." << endl;
						goto next;
					}
					num2 = n.top(), n.pop();
					if (n.empty())
					{
						cout << "error." << endl;
						goto next;
					}
					num1 = n.top(), n.pop();

					int res = o.top().fun(num1, num2);
					if (res == INT_MIN) return -1; //error occurred
					else n.push(res);
					o.pop();
					if (o.empty())
					{
						cout << "error." << endl;
						goto next;
					}
				}
				o.pop();
				++pos;
				if (pos == input.end()) goto outer;
			}
			op optor = parse_op(o, pos);
			if (optor.fun == NULL) goto next;

			if (o.empty() || optor.priority > o.top().priority)
			{
				o.push(optor);
			}
			else
			{
				while (!o.empty() && optor.priority <= o.top().priority)
				{
					int num1, num2;
					if (n.empty())
					{
						cout << "error." << endl;
						goto next;
					}
					num2 = n.top(), n.pop();
					if (n.empty())
					{
						cout << "error." << endl;
						goto next;
					}
					num1 = n.top(), n.pop();

					int res = o.top().fun(num1, num2);
					if (res == INT_MIN) goto next; //error occurred
					else n.push(res);
					o.pop();
				}
				o.push(optor);
			}
		}
	outer:;
		while (!o.empty())
		{
			int num1, num2;
			if (n.empty())
			{
				cout << "error." << endl;
				goto next;
			}
			num2 = n.top(), n.pop();
			if (n.empty())
			{
				cout << "error." << endl;
				goto next;
			}
			num1 = n.top(), n.pop();

			int res = o.top().fun(num1, num2);
			if (res == INT_MIN) goto next; //error occurred
			else n.push(res);
			o.pop();
		}
		if (n.size() != 1)
		{
			cout << "error." << endl;
			goto next;
		}
		cout << n.top() << endl;
	next:;
	}
	return 0;
}