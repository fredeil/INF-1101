#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <sys/time.h>

#include "sort.h"

#define RED "\x1B[31m"
#define GREEN "\x1B[32m"
#define NORM "\x1B[0m"

typedef enum
{
	false,
	true
} bool;

typedef struct test_data
{
	int *unsorted; // Data for testing
	int *sorted;   // Data for correctness test
	int size;	  // Data size
} test_data_t;

bool print = false;

unsigned long long now(void)
{
	struct timeval time;
	gettimeofday(&time, NULL);
	return time.tv_sec * 1000000 + time.tv_usec;
}

// Sort int array
bool range_sort(int *data, int size, int range)
{
	int i, pos;
	int *buff = calloc(sizeof(int), range);
	if (buff == NULL)
		return false;

	for (i = 0; i < size; i++)
	{
		if (data[i] > range)
		{
			free(buff);
			return false; // Error data not within range
		}
		buff[data[i]]++;
	}

	pos = 0;
	for (i = 0; i < range; i++)
	{
		while (buff[i] > 0)
		{
			data[pos++] = i;
			buff[i]--;
		}
	}

	free(buff);

	return true; // Success
}

// Validate sorted data set
bool validate_sort(int *sorted, test_data_t *test_data)
{
	int i;
	for (i = 0; i < test_data->size; i++)
	{
		if (sorted[i] != test_data->sorted[i])
			return false;
	}
	return true;
}

// Print array of ints
void print_data(int *data, int size)
{
	int i;
	printf("\nDATA:\n");
	for (i = 0; i < size; i++)
	{
		printf("[%d] -> %d\n", i, data[i]);
	}
}

// Generate new random data set
int *new_data(int size)
{
	int i;
	int *data = malloc(sizeof(int) * size);
	if (data == NULL)
		return NULL;

	for (i = 0; i < size; i++)
	{
		data[i] = rand() % size;
	}

	return data;
}

/* Destroy test data */
void teardown(test_data_t *test_data)
{
	free(test_data->unsorted);
	free(test_data->sorted);
	free(test_data);
}

// Initialize test data
test_data_t *init(int size)
{
	bool success;
	unsigned long long time;
	test_data_t *new = malloc(sizeof(test_data_t));
	if (new == NULL)
		return NULL;

	new->size = size;

	// Generate test data
	new->unsorted = new_data(size);
	if (new->unsorted == NULL)
	{
		free(new);
		return NULL;
	}

	// Setup correctness test
	new->sorted = malloc(sizeof(int) * size);
	if (new->sorted == NULL)
	{
		free(new->unsorted);
		free(new);
		return NULL;
	}

	memcpy(new->sorted, new->unsorted, sizeof(int) * size);

	time = now();
	success = range_sort(new->sorted, size, size);
	time = now() - time;

	if (success)
	{
		printf("Correctness data sorted in %.2f sec.\n", (float)time / 1000000);
	}
	else
	{
		teardown(new);
		return NULL; // Error
	}

	return new; // Success
}

// Test given sorting algorithm with given test data
void test_algorithm(sortfunc_t sort_func, test_data_t *test_data, char *name)
{
	int *data;
	unsigned long long time;

	// Allocate space for this test run
	data = malloc(sizeof(int) * test_data->size);
	if (data == NULL)
	{
		printf("Memory allocation error.\n");
		return;
	}

	// Copy test data
	memcpy(data, test_data->unsorted, sizeof(int) * test_data->size);

	printf("Running %s...", name);
	fflush(stdout);

	// Run test
	time = now();					  // Start timer
	sort_func(data, test_data->size); // Run sort
	time = now() - time;			  // Stop timer

	if (print)
		print_data(data, test_data->size);

	// Print result
	printf("\r%14s completed in %.2f sec. Result: ", name, (float)time / 1000000);
	if (validate_sort(data, test_data))
		printf(GREEN "Success\n" NORM);
	else
		printf(RED "Failure\n" NORM);

	free(data);
}

int main(int argc, char **argv)
{
	int size = 1000; // Default size

	while (--argc > 0)
	{
		if (strcmp(argv[argc], "-p") == 0)
			print = true; // Set print
		else
			size = (atoi(argv[argc]) > 0) ? atoi(argv[argc]) : 1000;
	}

	printf("Initializing test data...\n");
	test_data_t *test_data = init(size);
	if (test_data == NULL)
	{
		printf("Could not allocate memory for test data.\n");
		return 1;
	}

	// Run tests
	printf("Running tests with %d elements:\n", size);
	test_algorithm(bubblesort, test_data, "Bubblesort");
	test_algorithm(insertion_sort, test_data, "Insertion sort");
	test_algorithm(selection_sort, test_data, "Selection sort");
	test_algorithm(merge_sort, test_data, "Mergesort");
	test_algorithm(heap_sort, test_data, "Heapsort");
	test_algorithm(quicksort, test_data, "Quicksort");

	// Cleanup
	teardown(test_data);

	return 0;
}
