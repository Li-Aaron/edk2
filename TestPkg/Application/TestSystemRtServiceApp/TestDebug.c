/** @file
  An Debug File for Dump Hex.
  Self Study usage.
**/

#include "TestSystemRtServiceApp.h"


VOID
InternalDumpDataDebug (
  IN UINT8  *Data,
  IN UINTN  Size
  )
{
  UINTN  Index;

  for (Index = 0; Index < Size; Index++) {
    DEBUG ((DEBUG_INFO, "%02x ", (UINTN)Data[Index]));
  }
}


/**
  Dump Hex.

  @param[in]  Data   Pointer to Data Block
  @param[in]  Size   Data Block Size

**/
VOID
InternalDumpHexDebug (
  IN UINT8  *Data,
  IN UINTN  Size
  )
{
  UINTN   Index;
  UINTN   Count;
  UINTN   Left;

#define COLUME_SIZE  (16)
  Count = Size / COLUME_SIZE;
  Left  = Size % COLUME_SIZE;
  for (Index = 0; Index < Count; Index++) {
   InternalDumpDataDebug (Data + Index * COLUME_SIZE, COLUME_SIZE);
    DEBUG ((DEBUG_INFO, "\n"));
  }
  if (Left != 0) {
    InternalDumpDataDebug(Data + Index * COLUME_SIZE, Left);
    DEBUG ((DEBUG_INFO, "\n"));
  }
  DEBUG ((DEBUG_INFO, "\n"));
}