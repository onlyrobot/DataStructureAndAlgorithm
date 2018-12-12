#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#define swap(a, b) {int c = *a; *a = *b; *b = c;}
void quick_sort(int * front, int * rear, int ** medians)
{
	if (rear - front >= 5) //quick sort
	{
		int * center = front + (rear - front) / 2;
		if (*front > *center) swap(front, center);
		if (*front > *rear) swap(front, rear);
		if (*center > *rear) swap(center, rear);
		int * median = --rear;
		swap(center, median);
		*(*medians)++ = *median;
		center = front;
		while (1)
		{
			while (*(++center) < *median);
			while (*(--rear) > *median);
			if (center < rear) swap(center, rear)
			else break;
		}
		swap(center, median);
		quick_sort(front, center - 1, medians);
		quick_sort(center + 1, median + 1, medians);
	}
	else //insert sort 
	{
		for (int * i = front + 1; i <= rear; ++i)
		{
			int temp = *i, * j;
			for (j = i; j > front && *(j - 1) > temp; --j)
				*j = *(j - 1);
			*j = temp;
		}
	}
}
int main()
{
	int a[1000], count = 0, medians[1000];
	memset(medians, 0x3f, 1000 * sizeof(int));
	char c;
	while ((c = getchar()) != '#')
	{
		int flag = 1, number = 0;
		if (c == '-') flag = -1;
		else number = c - '0';
		while ((c = getchar()) != '\n')
		{
			number = number * 10 + c - '0';
		}
		a[count++] = flag * number;
	}
	int * pos = medians;
	quick_sort(a, a + count - 1, &pos);
	printf("After Sorting:\n");
	for (int i = 0; i < count; ++i)
	{
		printf("%d ", a[i]);
	}
	printf("\nMedian3 Value:\n");
	if (medians[0] == 0x3f3f3f3f) printf("none\n");
	else
	{
		for (int i = 0; medians[i] != 0x3f3f3f3f; ++i)
		{
			printf("%d ", medians[i]);
		}
		printf("\n");
	}
	return 0;
}