/** @file
  A Hello World Application.
  Self Study usage.
**/

#include <Uefi.h>
#include <Library/UefiLib.h>
#include <Library/UefiApplicationEntryPoint.h>
#include <Library/DebugLib.h>


/**
  Execute Hello World.

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
  EFI_STATUS                    Status;
  Status = SystemTable->ConOut->OutputString(SystemTable->ConOut, L"AaronLi Hello World\n");
  DEBUG((EFI_D_INFO, "Status = 0x%x\n", Status));
  return Status;
}
