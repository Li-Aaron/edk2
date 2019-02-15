#include "sort.h"

// bubble sort
void SortBubble(INTN a[], INTN n)
{
  INTN i, j;
  for (i = 0; i < n; i++)
  {
    for (j = 0; j < n-1; j++)
    {
      if (!compare(a[j], a[j + 1]))
      {
        swap(a, j, j+1);
      }
    }
  }
}