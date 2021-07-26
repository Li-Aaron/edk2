#include "sort.h"

// shell sort
void SortShell(INTN a[], INTN n)
{
  INTN target;
  INTN i, idx1, idx2;
  INTN step = n; // Initial Spacing Value
  while(step >= 1){
    step /= 2;
    for(i = 0; i < step; i++){
      // Grouping
      // Insert Sort (Start From Second - This Part is more clear in python code)
      for(idx1 = i+step; idx1 < n; idx1 += step){
        target = a[idx1];
        idx2 = idx1;
        while (idx2 > i && compare(target, a[idx2 - step])){
          a[idx2] = a[idx2 - step];
          idx2 -= step;
        }
        a[idx2] = target;
      }
    }
  }
}