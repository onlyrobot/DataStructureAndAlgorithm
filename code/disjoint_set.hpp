#include <iostream>	
using namespace std;
struct disjoint_set;
int find(disjoint_set & ds, int element);
int merge(disjoint_set & ds, int element1, int element2);
struct disjoint_set
{
	int size;
	int * a;
	disjoint_set(int size)
	{
		this->size = size;
		a = new int[size];
		for (int i = 0; i < size; ++i) a[i] = i;
	}
};
int find(disjoint_set & ds, int element)
{
	int parent;
	while ((parent = ds.a[element]) != element)
	{
		ds.a[element] = ds.a[parent];
		element = parent;
	}
	return parent;
}
int merge(disjoint_set & ds, int element1, int element2)
{
	int parent1 = find(ds, element1), parent2 = find(ds, element2);
	ds.a[parent1] = parent2;
	return parent2;
}