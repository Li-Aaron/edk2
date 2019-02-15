#include "sort.h"

// compare condition (important)
inline BOOLEAN compare(INTN a, INTN b)
{
  return a <= b;
}

inline void swap(INTN a[], INTN x, INTN y)
{
  INTN tmp = a[x];
  a[x] = a[y];
  a[y] = tmp;
}