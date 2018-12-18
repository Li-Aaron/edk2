/** @file
  An Application to test WaitForEvent Usage.
  Self Study usage.
**/

#include "TestSystemEventApp.h"


/**
  Test WaitForEvent.

  Wait For Key Input, if time out print time out
  If detect "enter", then complete.

  @retval EFI_SUCCESS            Command completed successfully.

**/
EFI_STATUS
EFIAPI
TestWaitForEvent( VOID )
{
  EFI_STATUS             Status;
  EFI_EVENT              MyEvent[2];
  UINTN                  NumOfEvent;
  UINTN                  Index;
  EFI_INPUT_KEY          Key;
  CHAR16                 StrBuffer[2] = {0};
  UINT64                 TriggerTime;

  NumOfEvent = 2;
  TriggerTime = 2 * 1000 * 1000 * 10; // 2s = 2 * 1000 * 1000 * 10 * 100ns
  //
  // Create a timer event and register to MyEvent[0]
  //
  Status = gBS->CreateEvent(EVT_TIMER, TPL_CALLBACK, (EFI_EVENT_NOTIFY)NULL, (VOID*)NULL, &MyEvent[0]);
  Status = gBS->SetTimer(MyEvent[0], TimerRelative, TriggerTime); // 2s = 2 * 1000 * 1000 * 10 * 100ns
  MyEvent[1] = gST->ConIn->WaitForKey;

  while(StrBuffer[0] != (CHAR16)'\r') {
    //
    // Wait for event in event array happens
    //
    Status = gBS->WaitForEvent(NumOfEvent, MyEvent, &Index);
    Status = gBS->SetTimer(MyEvent[0], TimerCancel, TriggerTime); // Stop Timer
    if (Index == 0) {
      //
      // Timer Out
      //
      Print(L"\r\nTIME OUT\r\n");
    } else if (Index == 1) {
      //
      // Key Inputed and Display Key
      //
      Status = gST->ConIn->ReadKeyStroke(gST->ConIn, &Key);
      StrBuffer[0] = Key.UnicodeChar;
      Status = gST->ConOut->OutputString(gST->ConOut, StrBuffer);
    }
    Status = gBS->SetTimer(MyEvent[0], TimerRelative, TriggerTime); // Restart Timer
  }
  Status = gST->ConOut->OutputString(gST->ConOut, L"\nComplete\n");

  Status = gBS->CloseEvent(MyEvent[0]);

  return Status;
}