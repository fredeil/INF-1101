#include "sort.h"

static int partition(int *data, int min, int max)
{
	int piv = data[(min + (max - min) / 2)];

	while(min <= max)
	{
		while(data[min] < piv) min++;
		while(data[max] > piv) max--;

		if(min <= max)
		{
			int tmp = data[min];
			data[min] = data[max];
			data[max] = tmp;

			min++;
			max--;
		}
	}

	return min;
}

static void _quicksort(int *data, int min, int max)
{
	int idx = partition(data, min, max);

	if(min < idx - 1)
		_quicksort(data, min, idx - 1); // go left
	
	if(idx < max)
		_quicksort(data, idx, max); // go right
}

void quicksort(int *data, int size)
{
	_quicksort(data, 0, size - 1);
}
