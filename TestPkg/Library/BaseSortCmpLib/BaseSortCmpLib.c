  /** @file
  Library used for sorting method compare.
  Self Study usage.

**/
#include "BaseSortCmpLib.h"

SORT_FUNC_WARP mSortFunction[SORT_FUNC_MAX_NUM] = {
  { L"SortBubble" ,    (SORT_FUNC) SortBubble },
  { L"SortSelect" ,    (SORT_FUNC) SortSelect },
  { L"SortInsert" ,    (SORT_FUNC) SortInsert },
  { L"SortShell"  ,    (SORT_FUNC) SortShell  },
  { L"SortQuick"  ,    (SORT_FUNC) SortQuick  },
  { L"SortQuick2" ,    (SORT_FUNC) SortQuick2 },
  { L"SortMerge"  ,    (SORT_FUNC) SortMerge  },
  { L"SortHeap"   ,    (SORT_FUNC) SortHeap   }
};

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
  IN CONST INTN                         Count,
  IN       SORT_FUNC                    SortFunction
  )
{
  SortFunction(&BufferToSort[0], Count);
}


/**
  Comparison function Initialize.

  @param[out]    SortFunction        SortFunction Warp Array.
**/
VOID
EFIAPI
SortFunctionInit (
  OUT SORT_FUNC_WARP *SortFunction
  )
{
  INTN i;

  for (i = 0; i < SORT_FUNC_MAX_NUM; i++){
    SortFunction[i].SortFunc = mSortFunction[i].SortFunc;
    SortFunction[i].SortFuncName = mSortFunction[i].SortFuncName;
  }
}