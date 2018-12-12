#pragma once
#include <iostream>
#include <climits>
using namespace std;
struct heap;
void make_heap(heap & hp);
int pop_key(heap & hp);
void push_key(heap & hp, int key);
void decrease_key(heap & hp, int key, int value);
void increase_key(heap & hp, int key, int value);
void delete_key(heap & hp, int key);
void percolate_down(heap & hp, int i);
void percolate_up(heap & hp, int i);

struct heap
{
	int capacity;
	int size;
	int * keys;
};
heap create_heap(int capacity)
{
	//assumimg size greater than 0
	heap hp;
	hp.capacity = capacity;
	hp.size = 0;
	hp.keys = (int *)malloc((capacity + 1) * sizeof(int));
	hp.keys[0] = INT_MIN;
	return hp;
}
void percolate_down(heap & hp, int i)
{
	int temp = hp.keys[i], child;
	while ((child = 2 * i) <= hp.size)
	{
		if (hp.keys[child] < temp)
		{
			if (child < hp.size && hp.keys[child + 1] < hp.keys[child]) ++child;
			hp.keys[i] = hp.keys[child];
		}
		else if (child < hp.size && hp.keys[++child] < temp)
		{
			hp.keys[i] = hp.keys[child];
		}
		else break;
		i = child;
	}
	hp.keys[i] = temp;
}
void percolate_up(heap & hp, int i)
{
	int parent = i / 2, temp = hp.keys[i];
	while (hp.keys[parent] > temp)
	{
		hp.keys[i] = hp.keys[parent];
		i = parent, parent = i / 2;
	}
	hp.keys[i] = temp;
}
void make_heap(heap & hp)
{
	for (int i = hp.size / 2; i > 0; --i) percolate_down(hp, i);
}
int pop_key(heap & hp)
{
	//assuming heap is not empty
	int key = hp.keys[1];
	hp.keys[1] = hp.keys[hp.size--];
	percolate_down(hp, 1);
	return key;
}
void push_key(heap & hp, int key)
{
	hp.keys[++hp.size] = key;
	percolate_up(hp, hp.size);
}
void decrease_key(heap & hp, int key, int value)
{
	for (int i = 0; i < hp.size; ++i)
	{
		if (hp.keys[i + 1] == key)
		{
			hp.keys[i + 1] -= value;
			percolate_up(hp, i + 1);
			return;
		}
	}
}
void increase_key(heap & hp, int key, int value)
{
	for (int i = 0; i < hp.size; ++i)
	{
		if (hp.keys[i + 1] == key)
		{
			hp.keys[i + 1] += value;
			percolate_down(hp, i + 1);
			return;
		}
	}
}
void delete_key(heap & hp, int key)
{
	decrease_key(hp, key, key - hp.keys[0] - 1);
	pop_key(hp);
}
void print_heap(heap & hp)
{
	for (int i = 0; i < hp.size; ++i)
	{
		cout << hp.keys[i + 1] << "\t";
	}
	cout << endl;
}