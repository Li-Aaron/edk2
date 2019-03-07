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

#define INIT_NAME_BUFFER_SIZE 128
#define INIT_DATA_BUFFER_SIZE 1024

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
  Test GetVariable / SetVariable.

  @retval EFI_SUCCESS            Command completed successfully.

**/
EFI_STATUS
EFIAPI
TestGetVariable( VOID );

/**
  Test GetVariable / SetVariable (difference length).

  @retval EFI_SUCCESS            Command completed successfully.

**/
EFI_STATUS
EFIAPI
TestSetVariable( VOID );

/**
  Test GetNextVariableName.

  @retval EFI_SUCCESS            Command completed successfully.

**/
EFI_STATUS
EFIAPI
TestGetNextVariableName( VOID );