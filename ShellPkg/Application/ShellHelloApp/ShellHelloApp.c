/** @file
  This is a test application that demonstrates how to use the C-style entry point
  for a shell application.
  Self Study usage.
**/

#include <Uefi.h>
#include <Library/UefiLib.h>
#include <Library/UefiBootServicesTableLib.h>
#include <Library/ShellCEntryLib.h>

/**
  UEFI application entry point which has an interface similar to a
  standard C main function.

  The ShellCEntryLib library instance wrappers the actual UEFI application
  entry point and calls this ShellAppMain function.

  @param[in] Argc     The number of items in Argv.
  @param[in] Argv     Array of pointers to strings.

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
  UINTN i;
  gST -> ConOut -> OutputString(gST -> ConOut, L"HelloWorld: ");
  for(i = 1; i < Argc; i++){
    gST -> ConOut -> OutputString(gST -> ConOut, Argv[i]);
    gST -> ConOut -> OutputString(gST -> ConOut, L" ");
  }
  gST -> ConOut -> OutputString(gST -> ConOut, L"\n");
  return 0;
}
