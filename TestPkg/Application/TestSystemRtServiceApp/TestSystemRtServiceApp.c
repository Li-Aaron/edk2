/** @file
  An Application to test System Service Usage.
  Self Study usage.
**/

#include "TestSystemRtServiceApp.h"

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
  EFI_STATUS             Status;
  
  Status = TestGetVariable();
  DEBUG((EFI_D_INFO, "TestGetVariable() Status : 0x%X\r\n", Status));

  Status = TestGetNextVariableName();
  DEBUG((EFI_D_INFO, "TestGetNextVariableName() Status : 0x%X\r\n", Status));

  return Status;
}
