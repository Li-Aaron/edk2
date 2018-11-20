/** @file
  This is a test application that demonstrates how to use the sorting functions.

  Copyright (c) 2009 - 2010, Intel Corporation. All rights reserved.<BR>
  This program and the accompanying materials
  are licensed and made available under the terms and conditions of the BSD License
  which accompanies this distribution.  The full text of the license may be found at
  http://opensource.org/licenses/bsd-license.php

  THE PROGRAM IS DISTRIBUTED UNDER THE BSD LICENSE ON AN "AS IS" BASIS,
  WITHOUT WARRANTIES OR REPRESENTATIONS OF ANY KIND, EITHER EXPRESS OR IMPLIED.

**/

#include <Uefi.h>
#include <Library/UefiLib.h>
#include <Library/BaseMemoryLib.h>
#include <Library/MemoryAllocationLib.h>
#include <Library/ShellCEntryLib.h>
#include <Library/SortCmpLib.h>



/**
  Comparison function for an array.

  Transferred function caller.

  @param[in]   Buffer              Buffer to Sort.
  @param[in]   Count               Length of Buffer.
  @param[in]   SortFunction        Called sort function.
**/
VOID
EFIAPI
RandomNumberGen (
  IN OUT   INTN                         *Buffer,
  IN CONST UINTN                        Count
  )
{
  UINTN i;

  for(i = 0; i < Count; i++){
    AsmRdRand32((UINT32*)&Buffer[i]);
    Buffer[i] %= 1000;
  }
}

/**
  UEFI application entry point which has an interface similar to a
  standard C main function.

  The ShellCEntryLib library instance wrappers the actual UEFI application
  entry point and calls this ShellAppMain function.

  @param  Argc             Argument count
  @param  Argv             The parsed arguments

  @retval  0               The application exited normally.
  @retval  Other           An error occurred.

**/
INTN
EFIAPI
ShellAppMain (
  IN UINTN Argc,
  IN CHAR16 **Argv
  )
{
  UINTN           Count = 10;
  UINTN           i, idx;
  INTN            *Buffer;          // For Generating Random Array
  INTN            *BufferCpy;       // For Sorting
  SORT_FUNC_WARP  *SortFunctionWarp;    // Sort Function Array

  if (Argc > 1){
    Count = StrDecimalToUintn(Argv[1]);
  }
  Print(L"Random Number Array Length Is: %d\n", Count);

  //
  // Init Sort Functions
  //
  SortFunctionWarp = AllocatePool(sizeof(SORT_FUNC_WARP) * SORT_FUNC_MAX_NUM);
  SortFunctionInit(SortFunctionWarp);

  //
  // Generate Random Array Buffer
  //
  Buffer = AllocatePool(sizeof(INTN) * Count);
  BufferCpy = AllocatePool(sizeof(INTN) * Count);
  RandomNumberGen(Buffer, Count);

  //
  // Test each Sort Function
  //
  for(i = 0; i < SORT_FUNC_MAX_NUM; i++){
    CopyMem(BufferCpy, Buffer, sizeof(INTN) * Count);
    SortFunctionCaller(BufferCpy, Count, SortFunctionWarp[i].SortFunc);

    //
    // Print result
    //
    Print(L"[%12s]: ", SortFunctionWarp[i].SortFuncName);
    for(idx = 0; idx < 5; idx++){
      Print(L"%d ", BufferCpy[idx]);
    }
    Print(L"... ");
    for(idx = Count - 5; idx < Count; idx++){
      Print(L"%d ", BufferCpy[idx]);
    }
    Print(L"\n");
  }

  return 0;
}
