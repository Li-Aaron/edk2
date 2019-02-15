  /** @file
  Library used for sorting method compare.
  Self Study usage.

**/
#include "BaseSortCmpLib.h"

SORT_FUNC_WARP mSortFunction[SORT_FUNC_MAX_NUM] = {
  { L"SortBubble" ,    SortBubble },
  { L"SortSelect" ,    SortSelect },
  { L"SortInsert" ,    SortInsert },
  { L"SortShell"  ,    SortShell  },
  { L"SortQuick"  ,    SortQuick  },
  { L"SortQuick2" ,    SortQuick2 },
  { L"SortMerge"  ,    SortMerge  },
  { L"SortHeap"   ,    SortHeap   }
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