/** @file
  An Application to test System Table Usage.
  Self Study usage.
**/

#include <Uefi.h>
#include <Library/UefiLib.h>
#include <Library/UefiApplicationEntryPoint.h>
#include <Library/DebugLib.h>


/**
  Application Entry.

  @param[in]  ImageHandle     The image handle.
  @param[in]  SystemTable     The system table.

  @retval EFI_SUCCESS            Command completed successfully.

**/
EFI_STATUS
EFIAPI
UefiMain (
  IN EFI_HANDLE        ImageHandle,
  IN EFI_SYSTEM_TABLE  *SystemTable
  )
{
  EFI_STATUS            Status;
  UINTN                 Index;
  EFI_INPUT_KEY         Key;
  CHAR16                StrBuffer[2] = {0};

  //
  // If not pressed enter
  //
  while (StrBuffer[0] != (CHAR16)'\r') {
    //
    // Wait for key event and read key
    //
    SystemTable->BootServices->WaitForEvent(1, &SystemTable->ConIn->WaitForKey, &Index);
    Status = SystemTable->ConIn->ReadKeyStroke(SystemTable->ConIn, &Key);
    //
    // Display Key
    //
    StrBuffer[0] = Key.UnicodeChar;
    Status = SystemTable->ConOut->OutputString(SystemTable->ConOut, StrBuffer);
  }
   Status = SystemTable->ConOut->OutputString(SystemTable->ConOut, L"\nComplete\n");
  DEBUG((EFI_D_INFO, "Status = 0x%x\n", Status));
  return Status;
}
