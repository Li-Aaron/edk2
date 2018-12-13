/** @file
  An Application to test System Service Usage.
  Self Study usage.
**/

#include <Uefi.h>
#include <Library/UefiLib.h>
#include <Library/UefiApplicationEntryPoint.h>
#include <Library/DebugLib.h>
#include <Library/UefiBootServicesTableLib.h>
#include <Library/UefiRuntimeServicesTableLib.h>
#include <Library/BaseMemoryLib.h>
#include <Library/MemoryAllocationLib.h>

#define BUF_STRING L"THIS IS BUFFER\r\n"
#define NUM_OF_BUF 10
#define DUMP_SIZE 64

/**
  Dump Hex.

  @param[in]  Data   Pointer to Data Block
  @param[in]  Size   Data Block Size

**/
VOID
InternalDumpHexDebug (
  IN UINT8  *Data,
  IN UINTN  Size
  );

/**
  Test AllocateMemory / Page.

  @retval EFI_SUCCESS            Command completed successfully.

**/
EFI_STATUS
EFIAPI
TestAllocate ( VOID );


/**
  Test GetMemoryMap.

  @retval EFI_SUCCESS            Command completed successfully.

**/
EFI_STATUS
EFIAPI
TestGetMemoryMap ( VOID );
