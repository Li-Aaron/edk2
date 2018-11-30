#include "sort.h"

void SortInsert(INTN a[], INTN n)
{
  INTN target;
  INTN j;
  for (INTN i = 1; i < n; i++){
    target = a[i];
    j = i;
    // using compare instead of a <= b
    while (j>0 && compare(target, a[j - 1])){
      a[j] = a[j - 1];
      j--;
    }
    a[j] = target;
  }
}