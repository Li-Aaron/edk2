/** @file
  An Application to Test File IO
  Self Study usage.
**/

#include "TestFileIoApp.h"

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
  EFI_STATUS                         Status;

  Status = TestReadAndWrite();
  CheckStatus("TestReadAndWrite()");

  Status = TestListDirectory();
  CheckStatus("TestListDirectory()");

  return Status;
}
