#pragma once
//#include "c:\Users\onlyrobot\iCloudDrive\code\structure_and_algorithm\memory.hpp"
#include <iostream>
#include <cmath>
using namespace std;
struct radix;
struct bucket;
void insert_sort(int * a, int size);
void shell_sort(int * a, int size);
void select_sort(int * a, int size);
void heap_sort(int * a, int size);
void quick_sort(int * a, int size);
void radix_sort(int * a, int size);

struct radix
{
	int remain;
	int number;
	radix * next;
	radix() {};
	radix(int remain, int number, radix * next) : \
		remain(remain), number(number), next(next) {};
};

void insert_sort(int * a, int size)
{
	for (int i = 1; i < size; ++i)
	{
		int j, temp = a[i];
		for (j = i; j > 0 && a[j - 1] > temp; --j)
		{
			a[j] = a[j - 1];
		}
		a[j] = temp;
	}
}
void shell_sort(int * a, int size)
{
	int k = log(size + 1) / log(2);
	for (int h = pow(2, k) - 1; h > 0; --k, h = pow(2, k) - 1)
	{
		for (int i = h; i < size; ++i)
		{
			int j, temp = a[i];
			for (j = i; j >= h && a[j - h] > temp; j -= h)
			{
				a[j] = a[j - h];
			}
			a[j] = temp;
		}
	}
}
void select_sort(int * a, int size)
{
	for (int i = 0; i < size - 1; ++i)
	{
		int min = i;
		for (int j = i + 1; j < size; ++j)
		{
			if (a[j] < a[min]) min = j;
		}
		swap(a[i], a[min]);
	}
}
void heap_sort(int * a, int size)
{
	//build heap (top-greatest)
	for (int i = (size - 2) / 2; i >= 0; --i)
	{
		int temp = a[i], child, j = i;
		while ((child = 2 * j + 1) <= size - 1)
		{
			if (a[child] > temp)
			{
				if (child < size - 1 && a[child + 1] > a[child]) ++child;
				a[j] = a[child];
			}
			else if (child < size - 1 && a[++child] > temp)
			{
				a[j] = a[child];
			}
			else break;
			j = child;
		}
		a[j] = temp;
	}
	//heap sort
	for (int i = size; i > 1; --i)
	{
		int temp = a[--size];
		a[size] = a[0];
		//percolate down
		int child, j = 0;
		while ((child = 2 * j + 1) <= size - 1)
		{
			if (a[child] > temp)
			{
				if (child < size - 1 && a[child + 1] > a[child]) ++child;
				a[j] = a[child];
			}
			else if (child < size - 1 && a[++child] > temp)
			{
				a[j] = a[child];
			}
			else break;
			j = child;
		}
		a[j] = temp;
	}
}
void quick_sort(int * a, int size)
{
	if (size > 10)
	{
		int front = 0, center = size / 2, rear = size - 1;
		//find the median of front, center and rear
		if (a[0] > a[center]) swap(a[0], a[center]);
		if (a[0] > a[rear]) swap(a[0], a[center]);
		if (a[center] > a[rear]) swap(a[center], a[rear]);
		//partition the elements in range 1 to size - 1
		int median = --rear;
		swap(a[center], a[median]);
		while (true)
		{
			while (a[++front] < a[median]);
			while (a[--rear] > a[median]);
			if (front < rear) swap(a[front], a[rear]);
			else break;
		}
		swap(a[front], a[median]);
		quick_sort(a, front);
		quick_sort(a + front + 1, size - front - 1);
	}
	else //insert sort
		insert_sort(a, size);
}
void radix_sort(int * a, int size)
{
	radix * radixs1[19][2] = { { NULL, NULL } }, *radixs2[19][2] = { { NULL, NULL } };
	radix * (*r1)[2] = radixs1, *(*r2)[2] = radixs2;
	for (int i = 0; i < 19; ++i)
	{
		r1[i][0] = r1[i][1] = new radix(-1, -1, NULL);
		r2[i][0] = r2[i][1] = new radix(-1, -1, NULL);
 	}
	for (int i = 0; i < size; ++i) //initial radixs
	{
		int index = a[i] % 10 + 9;
		r1[index][1] = r1[index][1]->next = new radix(a[i] / 10, a[i], NULL);
	}
	bool terminate = false;
	while (!terminate)
	{
		terminate = true;
		for (int i = 0; i < 19; ++i)
		{
			radix * cur = r1[i][0];
			while (cur != r1[i][1]) 
			{
				cur = cur->next;
				int index = cur->remain % 10 + 9;
				cur->remain /= 10;
				if (cur->remain != 0) terminate = false;
				r2[index][1] = r2[index][1]->next = cur;
			}
			r1[i][1] = r1[i][0];
		}
		swap(r1, r2);
	}
	int count = 0;
	for (int i = 0; i < 19; ++i)
	{
		radix * cur = r1[i][0];
		while (cur != r1[i][1])
		{
			radix * temp = cur;
			cur = cur->next;
			delete temp;
			a[count++] = cur->number;
		}
		cur = r2[i][0];
		while (cur != r2[i][1])
		{
			radix * temp = cur;
			cur = cur->next;
			delete temp;
			a[count++] = cur->number;
		}
	}
}
//void radix_sort_with_memory_control(int * a, int size)
//{
//	Memory<radix> mem(size + 38);
//	radix * radixs1[19][2] = { { NULL, NULL } }, *radixs2[19][2] = { { NULL, NULL } };
//	radix * (*r1)[2] = radixs1, *(*r2)[2] = radixs2;
//	for (int i = 0; i < 19; ++i)
//	{
//		r1[i][0] = r1[i][1] = mem.get();
//		r2[i][0] = r2[i][1] = mem.get();
//	}
//	for (int i = 0; i < size; ++i) //initial radixs
//	{
//		int index = a[i] % 10 + 9;
//		radix * new_r = mem.get();
//		new_r->number = a[i], new_r->remain = a[i] / 10;
//		r1[index][1] = r1[index][1]->next = new_r;
//	}
//	bool terminate = false;
//	while (!terminate)
//	{
//		terminate = true;
//		for (int i = 0; i < 19; ++i)
//		{
//			radix * cur = r1[i][0];
//			while (cur != r1[i][1])
//			{
//				cur = cur->next;
//				int index = cur->remain % 10 + 9;
//				cur->remain /= 10;
//				if (cur->remain != 0) terminate = false;
//				r2[index][1] = r2[index][1]->next = cur;
//			}
//			r1[i][1] = r1[i][0];
//		}
//		swap(r1, r2);
//	}
//	int count = 0;
//	for (int i = 0; i < 19; ++i)
//	{
//		radix * cur = r1[i][0];
//		while (cur != r1[i][1])
//		{
//			cur = cur->next;
//			a[count++] = cur->number;
//		}
//		cur = r2[i][0];
//		while (cur != r2[i][1])
//		{
//			cur = cur->next;
//			a[count++] = cur->number;
//		}
//	}
//	mem.free_all();
//}