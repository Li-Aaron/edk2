#include "sort.h"

void _Merge(INTN a[], INTN left, INTN middle, INTN right, BOOLEAN cmp(INTN, INTN))
{
  INTN idx = 0;
  INTN idxL = left;
  INTN idxR = middle;
  INTN len = right - left;

  // generate a memory space for merge
  INTN *a_temp;
  if (NULL == (a_temp = (INTN*)AllocatePool(len * sizeof(INTN))))
  {
    DEBUG((EFI_D_ERROR, "Not Enough Memory"));
    ASSERT(FALSE);
  }
  SetMem(a_temp, len * sizeof(INTN), 0);

  // main process of merge
  while (idxL < middle && idxR < right){
    // left < right then append left
    // right < left then append right
    if (cmp(a[idxL], a[idxR])){
      a_temp[idx] = a[idxL];
      idxL++;
    } else {
      a_temp[idx] = a[idxR];
      idxR++;
    }
    idx++;
  }

  // padding the rest part
  if (idxL < middle){
    CopyMem(&a_temp[idx], &a[idxL], (middle - idxL)*sizeof(INTN));
  } else if (idxR < right){
    CopyMem(&a_temp[idx], &a[idxR], (right - idxR)*sizeof(INTN));
  }

  // re copy to input array and free memory space
  CopyMem(&a[left], &a_temp[0], len*sizeof(INTN));
  FreePool(a_temp);
}

void _SortMerge(INTN a[], INTN left, INTN right, BOOLEAN cmp(INTN, INTN))
{
  if (right - left <= 1){
    // Terminate Condition
    // if right - left <= 0, when right - left = 1, the
    // middle will always be left
    return;
  }

  INTN middle = (left + right) / 2;
  _SortMerge(a, left, middle, cmp);
  _SortMerge(a, middle, right, cmp);
  _Merge(a, left, middle, right, cmp);
}


void SortMerge(INTN a[], INTN n)
{
  _SortMerge(a, 0, n, compare);
}