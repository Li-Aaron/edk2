#ifndef SORT_H
#define SORT_H

#include <uefi.h>

#include <Library/BaseMemoryLib.h>
#include <Library/MemoryAllocationLib.h>
#include <Library/DebugLib.h>

extern inline BOOLEAN compare(INTN a, INTN b);
extern inline void swap(INTN a[], INT32 x, INT32 y);

void SortBubble(INTN a[], INT32 n);
void SortInsert(INTN a[], INT32 n);
void SortSelect(INTN a[], INT32 n);
void SortShell(INTN a[], INT32 n);
void SortQuick(INTN a[], INT32 n);
void SortQuick2(INTN a[], INT32 n);
void SortMerge(INTN a[], INT32 n);
void SortHeap(INTN a[], INT32 n);

#endif