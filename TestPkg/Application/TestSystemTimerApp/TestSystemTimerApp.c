/** @file
  An Application to test Timer Usage.
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
  EFI_EVENT             TimerEvent;
  UINTN                 Index;
  UINT64                TriggerTime;
  UINTN                 Times;

  //
  // Initialize
  //
  Index = 0;
  TriggerTime = 1 * 1000 * 1000 * 10; // 1s = 1 * 1000 * 1000 * 10 * 100ns
  Status = gBS->CreateEvent(EVT_TIMER, TPL_NOTIFY, (EFI_EVENT_NOTIFY)NULL, (VOID*)NULL, &TimerEvent);
  DEBUG((EFI_D_INFO, "gBS->CreateEvent() returns: 0x%08X\r\n", Status));
  Status = gBS->SetTimer(TimerEvent, TimerPeriodic, TriggerTime);
  DEBUG((EFI_D_INFO, "gBS->SetTimer() returns: 0x%08X\r\n", Status));

  for (Times = 0; Times < 10; Times ++) {
    Status = gBS->WaitForEvent(1, &TimerEvent, &Index);
    DEBUG((EFI_D_INFO, "gBS->WaitForEvent() returns: 0x%08X\r\n", Status));
    Print(L"Times:%02d, Time Out Triggered\r\n", Times);
    DEBUG((EFI_D_INFO, "Times:%02d, Time Out Triggered\r\n", Times));
  }

  Status = gBS->CloseEvent(TimerEvent);
  DEBUG((EFI_D_INFO, "gBS->CloseEvent() returns: 0x%08X\r\n", Status));

  return Status;
}
