/** @file
  An Application to test Event+WaitSignal Usage.
  Self Study usage.
**/

#include "TestSystemEventApp.h"

/**
  Invoke a notification event Waiting

  @param[in]  Event                 Event whose notification function is being invoked.
  @param[in]  Context               The pointer to the notification function's context,
                                    which is implementation-dependent.

**/
static VOID
EFIAPI
MyEventNotifyWait(
  IN  EFI_EVENT                Event,
  IN  VOID                     *Context
  )
{
  static UINTN times = 0;
  Print(L"%s - myEventNotify Wait %d\r\n", Context, times);
  DEBUG((EFI_D_INFO, "%S - myEventNotify Wait %d\r\n", Context, times));
  times ++;
  if (times > 5){
    gBS->SignalEvent(Event);
  }
}


/**
  Test NotifyEvent.

  Call MyEventNotifyWait after each timer time out.

  @retval EFI_SUCCESS            Command completed successfully.

**/
EFI_STATUS
EFIAPI
TestNotifyEvent( VOID )
{
  EFI_STATUS             Status;
  EFI_EVENT              MyEvent;
  UINTN                  NumOfEvent;
  UINTN                  Index;

  NumOfEvent = 1;

  Status = gBS->CreateEvent(EVT_NOTIFY_WAIT, TPL_NOTIFY, (EFI_EVENT_NOTIFY)MyEventNotifyWait, (VOID*)L"WAIT!", &MyEvent);
  Status = gBS->CheckEvent(MyEvent); // will return EFI_NOT_READY
  DEBUG((EFI_D_INFO, "Event Status is 0x%X\r\n", Status));

  Status = gBS->WaitForEvent(NumOfEvent, &MyEvent, &Index);
  Print(L"Event %d Has Been Triggered\r\n", Index);
  DEBUG((EFI_D_INFO, "Event %d Has Been Triggered\r\n", Index));

  Status = gBS->CheckEvent(MyEvent); // will return EFI_SUCCESS
  DEBUG((EFI_D_INFO, "Event Status is 0x%X\r\n", Status));

  Status = gBS->CloseEvent(MyEvent);

  return EFI_SUCCESS;
}