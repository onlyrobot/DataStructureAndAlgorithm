#include <iostream>
#include <string>
using namespace std;
#pragma once
template <class T>
class Node;
template <class T>
class Memory;

void error(string error_message);

template <class T>
class Node
{
public:
	T body;
	Node * next;
};
template <class T>
class Memory
{
private:
	int size;
	Node<T> * array;
public:
	Memory(int size);
	T * get();
	void free(T * t);
	void free_all();
};

void error(string error_message)
{
	cout << error_message << endl;
	system("pause");
	exit(-1);
}
template <class T>
Memory<T>::Memory(int size) : size(size)
{
	if (size == 0)
	{
		error("Memory size cannot be 0");
	}
	array = new Node<T>[size + 1];
	for (int i = 0; i < size; ++i)
	{
		array[i].next = array + i + 1;
	}
	array[size].next = NULL;
}
template <class T>
T * Memory<T>::get()
{
	if (array->next == NULL) error("all the memory is used up");
	Node<T> * temp = array->next;
	array->next = temp->next;
	temp->next = NULL;
	return &temp->body;
}
template <class T>
void Memory<T>::free(T * t)
{
	for (int i = 1; i < size + 1; ++i)
	{
		if (t == &array[i].body)
		{
			if (array[i].next != NULL) error("this element cannot be free");
			array[i].next = array->next;
			array->next = array + i;
		}
	}
}
template <class T>
void Memory<T>::free_all()
{
	for (int i = 0; i < size; ++i)
	{
		array[i].next = array + i + 1;
	}
	array[size].next = NULL;
}