/** @file
  The implementation for Shell command hello.
  Simple Hello World command.
  Self Study usage.
**/
#include "UefiShellTestCommandsLib.h"


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
  )
{
  ShellPrintEx (-1, -1, L"%VHello World%N\r\n");
  ShellPrintEx (-1, -1, L"%BThis is %EAaron Li%N\r\n");

  return SHELL_SUCCESS;
}