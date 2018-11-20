/** @file
  Library used for sorting method compare.
  Self Study usage.

**/
#ifndef __SORT_CMP_LIB_H__
#define __SORT_CMP_LIB_H__


#define SORT_FUNC_MAX_NUM  8

/**
  Prototype for comparison function for an array.

  Transferred function.

  @param[in,out] Array                    Array to Sort.
  @param[in]     ArrayLength              Length of array.
**/

typedef
VOID
(EFIAPI *SORT_FUNC)(
  IN OUT INTN                 Array[],
  IN     INT32                ArrayLength
  );


typedef struct
{
  CHAR16        *SortFuncName;
  SORT_FUNC     SortFunc;
} SORT_FUNC_WARP;

/**
  Comparison function for an array.

  Transferred function caller.

  @param[in]     BufferToSort        Buffer to Sort.
  @param[in]     Count               Length of Buffer.
  @param[in]     SortFunction        Called sort function.

  @param[out]    BufferToSort        Buffer Sorted.
**/
VOID
EFIAPI
SortFunctionCaller (
  IN OUT   INTN                         *BufferToSort,
  IN CONST UINTN                        Count,
  IN       SORT_FUNC                    SortFunction
  );

/**
  Comparison function Initialize.

  @param[out]    SortFunction        SortFunction Array.
**/
VOID
EFIAPI
SortFunctionInit (
  OUT SORT_FUNC_WARP *SortFunction
  );

#endif //__SORT_CMP_LIB_H__
