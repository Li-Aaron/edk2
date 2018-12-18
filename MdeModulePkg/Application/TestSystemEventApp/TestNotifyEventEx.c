/** @file
  An Application to test CreateEventEx Usage.
  Self Study usage.
**/

#include "TestSystemEventApp.h"


/**
  Invoke a notification event Signal

  @param[in]  Event                 Event whose notification function is being invoked.
  @param[in]  Context               The pointer to the notification function's context,
                                    which is implementation-dependent.

**/
static VOID
EFIAPI
MyEventSignal(
  IN  EFI_EVENT                Event,
  IN  VOID                     *Context
  )
{
  static UINTN times = 0;
  Print(L"%s - myEventSignal Count %d\r\n", Context, times);
  DEBUG((EFI_D_INFO, "%S - myEventSignal Count %d\r\n", Context, times));
  times ++;
}

/**
  Test NotifyEvent with CreateEventEx.

  Call MyEventNotifyWait after each timer time out.

  @retval EFI_SUCCESS            Command completed successfully.

**/
EFI_STATUS
EFIAPI
TestNotifyEventEx( VOID )
{
  EFI_STATUS             Status;
  EFI_EVENT              MyEvent[4];

  Status = gBS->CreateEventEx(EVT_NOTIFY_SIGNAL, TPL_CALLBACK, (EFI_EVENT_NOTIFY)MyEventSignal, (VOID*)L"Signal (TPL_CALLBACK) 0", &gSelfEventExGuid, &MyEvent[0]);
  Status = gBS->CreateEventEx(EVT_NOTIFY_SIGNAL, TPL_NOTIFY,   (EFI_EVENT_NOTIFY)MyEventSignal, (VOID*)L"Signal (TPL_NOTIFY)   1", &gSelfEventExGuid, &MyEvent[1]);
  Status = gBS->CreateEventEx(EVT_NOTIFY_SIGNAL, TPL_NOTIFY,   (EFI_EVENT_NOTIFY)MyEventSignal, (VOID*)L"Signal (TPL_NOTIFY)   2", &gSelfEventExGuid, &MyEvent[2]);
  Status = gBS->CreateEventEx(EVT_NOTIFY_SIGNAL, TPL_CALLBACK, (EFI_EVENT_NOTIFY)MyEventSignal, (VOID*)L"Signal (TPL_CALLBACK) 3", &gSelfEventExGuid, &MyEvent[3]);

  Status = gBS->SignalEvent(MyEvent[0]);

  Status = gBS->CloseEvent(MyEvent[0]);
  Status = gBS->CloseEvent(MyEvent[1]);
  Status = gBS->CloseEvent(MyEvent[2]);
  Status = gBS->CloseEvent(MyEvent[3]);

  return EFI_SUCCESS;
}