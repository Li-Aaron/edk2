#include "sort.h"

void _ShiftDown(INTN a[], INTN parent, INTN boundary, BOOLEAN cmp(INTN, INTN))
{
  // index start with 0
  INTN child = parent * 2 + 1;

  if (child <= boundary){
    if (child + 1 <= boundary){
      // both 2 values in boundary, compare two child first
      if (cmp(a[child], a[child+1])){
        child += 1;
      }
    }
    // compare parent and (larger) child
    if (cmp(a[parent], a[child])){
      // swap then compare with grandchilds
      swap(a, parent, child);
      _ShiftDown(a, child, boundary, cmp);
    }
  }
}

// build big root heap
void _BuildHeap(INTN a[], INTN start, INTN stop, BOOLEAN cmp(INTN, INTN))
{
  INTN parent;
  // incase of unsigned overflow
  for (parent = stop/2; parent > start - 1; parent--){
    _ShiftDown(a, parent, stop, cmp);
  }
}

// heap sort
void SortHeap(INTN a[], INTN n)
{
  INTN stop = n-1;
  // Building Big Root Heap
  _BuildHeap(a, 0, stop, compare);

  while (stop > 0){
    // Make First Node Down
    swap(a, 0, stop);
    // Shift New First Node Down (without consider of last number)
    _ShiftDown(a, 0, stop-1, compare);
    stop--;
  }
}