#include <stdio.h>
#include <stdlib.h>
struct heap
{
	int size;
	int * array;
};
void percolate_down(struct heap hp, int index)
{
	int l_c_index = index * 2 + 1, r_c_index = index * 2 + 2;
	if (l_c_index >= hp.size) return;
	int target_index = r_c_index;
	if (r_c_index >= hp.size) target_index = l_c_index;
	target_index = hp.array[l_c_index] > hp.array[target_index] ? l_c_index : target_index;
	if (hp.array[index] < hp.array[target_index])
	{
		int swap = hp.array[index];
		hp.array[index] = hp.array[target_index];
		hp.array[target_index] = swap;
		percolate_down(hp, target_index);
	}
}
void make_heap(struct heap hp)
{
	for (int i = (hp.size - 2) / 2; i >= 0; --i) percolate_down(hp, i);
}
int pop(struct heap * hp)
{
	int data = hp->array[0];
	--hp->size;
	hp->array[0] = hp->array[hp->size];
	percolate_down(*hp, 0);
	return data;
}
int main()
{
	struct heap hp;
	scanf("%d", &hp.size);
	hp.array = (int *)malloc(hp.size * sizeof(int));
	for (int i = 0; i < hp.size; ++i) scanf("%d", &hp.array[i]);
	make_heap(hp);
	for (int i = 0; i < hp.size; ++i) printf("%d ", hp.array[i]);
	printf("\n");
	pop(&hp);
	for (int i = 0; i < hp.size; ++i) printf("%d ", hp.array[i]);
	printf("\n");
	pop(&hp);
	for (int i = 0; i < hp.size; ++i) printf("%d ", hp.array[i]);
	printf("\n");
	return 0;
}