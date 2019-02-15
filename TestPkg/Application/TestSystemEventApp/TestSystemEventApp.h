/** @file
  An Application to test System Event Usage.
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

#include <Guid/SelfTestDefined.h>

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
  Test WaitForEvent.

  @retval EFI_SUCCESS            Command completed successfully.

**/
EFI_STATUS
EFIAPI
TestWaitForEvent( VOID );

/**
  Test WaitForEvent.

  @retval EFI_SUCCESS            Command completed successfully.

**/
EFI_STATUS
EFIAPI
TestNotifyEvent( VOID );

/**
  Test NotifyEvent with CreateEventEx.

  Call MyEventNotifyWait after each timer time out.

  @retval EFI_SUCCESS            Command completed successfully.

**/
EFI_STATUS
EFIAPI
TestNotifyEventEx( VOID );

/**
  Test WaitForEvent.

  @retval EFI_SUCCESS            Command completed successfully.

**/
EFI_STATUS
EFIAPI
TestNotifyTimerSignal( VOID );
