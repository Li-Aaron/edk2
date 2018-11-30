#ifndef SORT_H
#define SORT_H

#include <uefi.h>

#include <Library/BaseMemoryLib.h>
#include <Library/MemoryAllocationLib.h>
#include <Library/DebugLib.h>

extern inline BOOLEAN compare(INTN a, INTN b);
extern inline void swap(INTN a[], INTN x, INTN y);

void SortBubble(INTN a[], INTN n);
void SortInsert(INTN a[], INTN n);
void SortSelect(INTN a[], INTN n);
void SortShell(INTN a[], INTN n);
void SortQuick(INTN a[], INTN n);
void SortQuick2(INTN a[], INTN n);
void SortMerge(INTN a[], INTN n);
void SortHeap(INTN a[], INTN n);

#endif