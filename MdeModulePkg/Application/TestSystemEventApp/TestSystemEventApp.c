/** @file
  An Application to test System Event Usage.
  Self Study usage.
**/

#include "TestSystemEventApp.h"

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

  Status = TestNotifyEvent();
  DEBUG((EFI_D_INFO, "TestNotifyEvent() Status : 0x%x\n", Status));

  Status = TestNotifyEventEx();
  DEBUG((EFI_D_INFO, "TestNotifyEvent() Status : 0x%x\n", Status));

  Status = TestNotifyTimerSignal();
  DEBUG((EFI_D_INFO, "TestNotifyTimerSignal() Status : 0x%x\n", Status));

  Status = TestWaitForEvent();
  DEBUG((EFI_D_INFO, "TestWaitForEvent() Status : 0x%x\n", Status));

  return Status;
}
