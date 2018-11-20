#include "sort.h"

// select sort
void SortSelect(INTN a[], INT32 n)
{
  INT32 i, j, minIdx;

  for (i = 0; i < n-1; i++)
  {
    minIdx = i;
    for (j = i+1; j < n; j++)
    {
      if (compare(a[j], a[minIdx]))
      {
        minIdx = j;
      }
    }
    if (minIdx != i){
      swap(a, minIdx, i);
    }
  }
}