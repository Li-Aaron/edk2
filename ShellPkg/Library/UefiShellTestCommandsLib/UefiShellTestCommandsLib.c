/** @file
  Main file for NULL named library for "Hello World" shell command functions.
  Self Study usage.
**/
#include "UefiShellTestCommandsLib.h"

CONST CHAR16 gShellTestFileName[] = L"ShellCommands";
EFI_HANDLE gShellTestHiiHandle = NULL;

/**
  return the file name of the help text file if not using HII.

  @return The string pointer to the file name.
**/
CONST CHAR16*
EFIAPI
ShellCommandGetManFileNameTest (
  VOID
  )
{
  return (gShellTestFileName);
}

/**
  Constructor for the Shell Test Commands library.

  Install the handlers for Test UEFI Shell 2.0 profile commands.

  @param ImageHandle            The image handle of the process.
  @param SystemTable            The EFI System Table pointer.

  @retval EFI_SUCCESS           The shell command handlers were installed sucessfully.
  @retval EFI_UNSUPPORTED       The shell level required was not found.
**/
EFI_STATUS
EFIAPI
ShellTestCommandsLibConstructor (
  IN EFI_HANDLE        ImageHandle,
  IN EFI_SYSTEM_TABLE  *SystemTable
  )
{
  gShellTestHiiHandle = NULL;

  //
  // check our bit of the profiles mask
  //
  if ((PcdGet8(PcdShellProfileMask) & BIT5) == 0) {
    return (EFI_SUCCESS);
  }
  gShellTestHiiHandle = HiiAddPackages (&gShellTestHiiGuid, 
                                            gImageHandle, 
                                            UefiShellTestCommandsLibStrings, 
                                            NULL);

  if (gShellTestHiiHandle == NULL) {
    return (EFI_DEVICE_ERROR);
  }
  //
  // install our shell command handlers
  //
    ShellCommandRegisterCommandName (
     L"hello", ShellCommandRunHello, ShellCommandGetManFileNameTest, 0,
     L"hello", TRUE , gShellTestHiiHandle, STRING_TOKEN (STR_GET_HELP_TEST)
     );

  return EFI_SUCCESS;

}

/**
  Destructor for the library.  free any resources.

  @param ImageHandle            The image handle of the process.
  @param SystemTable            The EFI System Table pointer.
**/
EFI_STATUS
EFIAPI
ShellTestCommandsLibDestructor (
  IN EFI_HANDLE        ImageHandle,
  IN EFI_SYSTEM_TABLE  *SystemTable
  )
{
  if (gShellTestHiiHandle != NULL) {
    HiiRemovePackages(gShellTestHiiHandle);
  }
  return EFI_SUCCESS;
}

