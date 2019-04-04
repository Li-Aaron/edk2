/** @file
  An Application to test Timer+Signal Usage.
  Self Study usage.
**/

#include "TestSystemEventApp.h"

/**
  Invoke a notification event From Timer

  @param[in]  Event                 Event whose notification function is being invoked.
  @param[in]  Context               The pointer to the notification function's context,
                                    which is implementation-dependent.

**/
static VOID
EFIAPI
MyEventNotify(
  IN  EFI_EVENT                Event,
  IN  VOID                     *Context
  )
{
  static UINTN times = 0;
  Print(L"%s - myEventNotify Wait %d\r\n", Context, times);
  DEBUG((EFI_D_INFO, "%S - myEventNotify Wait %d\r\n", Context, times));
  times ++;
}


/**
  Test NotifyEvent.

  Call MyEventNotify each timer period until keyboard input.

  @retval EFI_SUCCESS            Command completed successfully.

**/
EFI_STATUS
EFIAPI
TestNotifyTimerSignal( VOID )
{
  EFI_STATUS             Status;
  EFI_EVENT              MyEvent;
  UINTN                  Index;
  UINT64                 TriggerTime;

  TriggerTime = 1 * 1000 * 1000 * 10; // 1s = 1 * 1000 * 1000 * 10 * 100ns

  Status = gBS->CreateEvent(EVT_TIMER|EVT_NOTIFY_SIGNAL, TPL_NOTIFY, (EFI_EVENT_NOTIFY)MyEventNotify, (VOID*)L"TIME OUT!", &MyEvent);
  Status = gBS->SetTimer(MyEvent, TimerPeriodic, TriggerTime); // set preiodic Timer

  Status = gBS->CheckEvent(MyEvent); // will return EFI_INVALID_PARAMETER
  DEBUG((EFI_D_INFO, "Event Status is 0x%X\r\n", Status));

  Status = gBS->WaitForEvent(1, &gST->ConIn->WaitForKey, &Index);
  Status = gBS->CheckEvent(MyEvent); // will return EFI_INVALID_PARAMETER
  DEBUG((EFI_D_INFO, "Event Status is 0x%X\r\n", Status));

  Status = gBS->CloseEvent(MyEvent);
  Print(L"WaitForKey Has Been Triggered\r\n");
  DEBUG((EFI_D_INFO, "WaitForKey Has Been Triggered\r\n"));

  return EFI_SUCCESS;
}