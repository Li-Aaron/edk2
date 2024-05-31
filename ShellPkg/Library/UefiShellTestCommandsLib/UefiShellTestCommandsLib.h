/** @file
  Main file for NULL named library for "Hello World" shell command functions.
  Self Study usage.
**/

#ifndef _UEFI_SHELL_NETWORK2_COMMANDS_LIB_H_
#define _UEFI_SHELL_NETWORK2_COMMANDS_LIB_H_

#include <Uefi.h>

#include <Guid/ShellLibHiiGuid.h>

#include <Library/ShellLib.h>
#include <Library/ShellCommandLib.h>
#include <Library/BaseMemoryLib.h>
#include <Library/BaseLib.h>
#include <Library/PcdLib.h>
#include <Library/MemoryAllocationLib.h>
#include <Library/DebugLib.h>
#include <Library/UefiBootServicesTableLib.h>
#include <Library/HiiLib.h>


extern EFI_HANDLE gShellTestHiiHandle;

/**
  Function for 'hello' command.

  @param[in]  ImageHandle           Handle to the Image (NULL if Internal).
  @param[in]  SystemTable           Pointer to the System Table (NULL if Internal).

  @retval  SHELL_SUCCESS            The command completed successfully.
  @retval  Others                   The command failed.

**/
SHELL_STATUS
EFIAPI
ShellCommandRunHello (
  IN  EFI_HANDLE                    ImageHandle,
  IN  EFI_SYSTEM_TABLE              *SystemTable
  );

#endif

