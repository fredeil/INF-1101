#include "sort.h"

void bubblesort(int *data, int size)
{
  for (int i = 0; i < size; i++)
  {
    for (int j = 0; j < size; j++)
    {
      if (data[i] < data[j])
      {
        int tmp = data[i];
        data[i] = data[j];
        data[j] = tmp;
      }
    }
  }
}
