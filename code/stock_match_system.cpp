#include <iostream>
#include <cstdio>
#include <list>
#include <algorithm>
using namespace std;
struct order
{
	int id;
	float price;
	int quantity;
	order * next;
	order(int id, int price, int quantity) : id(id), price(price), quantity(quantity), next(NULL) {};
};
struct stock
{
	int id;
	order * buy;
	order * sell;
};
bool cmp(const stock & l, int code)
{
	return l.id < code;
}
void apply_order(list<stock> & s, int & id)
{
	printf("orderid: %04d\n", id);
	int code, price, quantity;
	char buy_or_sell;
	cin >> code >> price >> quantity >> buy_or_sell;
	list<stock>::iterator it_stock = lower_bound(s.begin(), s.end(), code, cmp);
	if (it_stock == s.end() || it_stock->id != code)
	{
		stock new_stock = { code, new order(-1, -1, -1), new order(-1, -1, -1) };
		it_stock = s.insert(it_stock, new_stock);
	}

	order * new_order = new order(id++, price, quantity);
	//insert to the accroding position
	if (buy_or_sell == 'b')
	{
		order * sell = it_stock->sell, *sell_order = sell->next;
		while (sell_order != NULL && sell_order->price <= new_order->price)
		{
			if (sell_order->quantity < new_order->quantity)
			{
				printf("deal--price:%6.1f  quantity:%4d  buyorder:%04d  sellorder:%04d\n", (sell_order->price + new_order->price) / 2, sell_order->quantity, new_order->id, sell_order->id);
				new_order->quantity -= sell_order->quantity;
				sell->next = sell_order->next, delete sell_order, sell_order = sell->next;
			}
			else if (sell_order->quantity == new_order->quantity)
			{
				printf("deal--price:%6.1f  quantity:%4d  buyorder:%04d  sellorder:%04d\n", (sell_order->price + new_order->price) / 2, sell_order->quantity, new_order->id, sell_order->id);
				new_order->quantity = 0;
				sell->next = sell_order->next, delete sell_order, sell_order = sell->next;
				break;
			}
			else
			{
				printf("deal--price:%6.1f  quantity:%4d  buyorder:%04d  sellorder:%04d\n", (sell_order->price + new_order->price) / 2, new_order->quantity, new_order->id, sell_order->id);
				sell_order->quantity -= new_order->quantity, new_order->quantity = 0;
				break;
			}
		}
		if (new_order->quantity > 0)
		{
			order * insert_after = it_stock->buy;
			while (insert_after->next != NULL)
			{
				order * cur_order = insert_after->next;
				if (new_order->price <= cur_order->price) insert_after = cur_order;
				else break;
			}
			new_order->next = insert_after->next, insert_after->next = new_order;
		}
	}
	else
	{
		order * buy = it_stock->buy, *buy_order = buy->next;
		while (buy_order != NULL && buy_order->price >= new_order->price)
		{
			if (buy_order->quantity < new_order->quantity)
			{
				printf("deal--price:%6.1f  quantity:%4d  sellorder:%04d  buyorder:%04d\n", (buy_order->price + new_order->price) / 2, buy_order->quantity, new_order->id, buy_order->id);
				new_order->quantity -= buy_order->quantity;
				buy->next = buy_order->next, delete buy_order, buy_order = buy->next;
			}
			else if (buy_order->quantity == new_order->quantity)
			{
				printf("deal--price:%6.1f  quantity:%4d  sellorder:%04d  buyorder:%04d\n", (buy_order->price + new_order->price) / 2, buy_order->quantity, new_order->id, buy_order->id);
				new_order->quantity = 0;
				buy->next = buy_order->next, delete buy_order, buy_order = buy->next;
				break;
			}
			else
			{
				printf("deal--price:%6.1f  quantity:%4d  sellorder:%04d  buyorder:%04d\n", (buy_order->price + new_order->price) / 2, new_order->quantity, new_order->id, buy_order->id);
				buy_order->quantity -= new_order->quantity, new_order->quantity = 0;
				break;
			}
		}
		if (new_order->quantity != 0)
		{
			order * insert_after = it_stock->sell;
			while (insert_after->next != NULL)
			{
				order * cur_order = insert_after->next;
				if (new_order->price >= cur_order->price) insert_after = cur_order;
				else break;
			}
			new_order->next = insert_after->next, insert_after->next = new_order;
		}
	}
}
void query_order(list<stock> & s)
{
	int code;
	cin >> code;
	list<stock>::iterator it_stock = lower_bound(s.begin(), s.end(), code, cmp);
	if (it_stock == s.end() || it_stock->id != code)
	{
		cout << "buy orders:" << endl << "sell orders:" << endl;
		return;
	}
	cout << "buy orders:" << endl;
	order * buy = it_stock->buy->next;
	while (buy != NULL)
	{
		printf("orderid: %04d, stockid:%04d, price: %6.1f, quantity: %4d, b/s: b\n", buy->id, it_stock->id, buy->price, buy->quantity);
		buy = buy->next;
	}
	cout << "sell orders:" << endl;
	order * sell = it_stock->sell->next;
	while (sell != NULL)
	{
		printf("orderid: %04d, stockid:%04d, price: %6.1f, quantity: %4d, b/s: s\n", sell->id, it_stock->id, sell->price, sell->quantity);
		sell = sell->next;
	}
}
void withdraw_order(list<stock> & s)
{
	int id;
	cin >> id;
	for (list<stock>::iterator it = s.begin(); it != s.end(); ++it)
	{
		stock stck = *it;
		for (int i = 0; i < 2; ++i)
		{
			order *remove_after = i == 0 ? stck.buy : stck.sell;
			while (remove_after->next != NULL)
			{
				order * cur = remove_after->next;
				if (cur->id == id)
				{
					printf("deleted order:orderid: %04d, stockid:%04d, price: %6.1f, quantity: %4d, b/s: %c\n", cur->id, stck.id, cur->price, cur->quantity, i == 0 ? 'b' : 's');
					remove_after->next = cur->next, delete cur;
					return;
				}
				remove_after = cur;
			}
		}
	}
	cout << "not found" << endl;
}
int main()
{
	int id = 1, command;
	list<stock> s;
	while (true)
	{
		cin >> command;
		if (command == 1) apply_order(s, id);
		else if (command == 2) query_order(s);
		else if (command == 3) withdraw_order(s);
		else return 0;
	}
	return 0;
}