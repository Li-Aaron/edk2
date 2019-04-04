#ifndef SORT_H
#define SORT_H

#include <Uefi.h>

#include <Library/BaseMemoryLib.h>
#include <Library/MemoryAllocationLib.h>
#include <Library/DebugLib.h>

extern BOOLEAN compare(INTN a, INTN b);
extern VOID swap(INTN a[], INTN x, INTN y);

VOID SortBubble(INTN a[], INTN n);
VOID SortInsert(INTN a[], INTN n);
VOID SortSelect(INTN a[], INTN n);
VOID SortShell(INTN a[], INTN n);
VOID SortQuick(INTN a[], INTN n);
VOID SortQuick2(INTN a[], INTN n);
VOID SortMerge(INTN a[], INTN n);
VOID SortHeap(INTN a[], INTN n);

#endif