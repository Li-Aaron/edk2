/** @file
  An Application to Mouse and Keyboard Usage.
  Not available on NT32 Platform.
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
#include <Protocol/SimplePointer.h>


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
  EFI_STATUS                     Status;
  EFI_SIMPLE_POINTER_PROTOCOL   *Mouse;
  EFI_SIMPLE_POINTER_STATE       State;
  EFI_EVENT                      Events[2];
  EFI_INPUT_KEY                  Key;
  UINTN                          NumOfEvent;
  UINTN                          Index;

  NumOfEvent = 2;
  gST->ConOut->EnableCursor(gST->ConOut, TRUE);
  //
  // Find mouse device and install protocol to Mouse
  //
  Status = gBS->LocateProtocol(&gEfiSimplePointerProtocolGuid, NULL, (VOID**) &Mouse);
  Status = Mouse->Reset(Mouse, TRUE);

  Events[0] = Mouse->WaitForInput;
  Events[1] = gST->ConIn->WaitForKey;

  while(1) {
    Status = gBS->WaitForEvent(NumOfEvent, Events, &Index);
    if (Index == 0){
      //
      // Get Mouse Status
      //
      Status = Mouse->GetState(Mouse, &State);
      Print(L"X:%d Y:%d Z:%d L:%d R:%d\r\n",
        State.RelativeMovementX,
        State.RelativeMovementY,
        State.RelativeMovementZ,
        State.LeftButton,
        State.RightButton
        );
    } else if (Index == 1) {
      Status = gST->ConIn->ReadKeyStroke (gST->ConIn, &Key);
      if (Key.UnicodeChar == 'q'){
        break;
      }
    }
  }

  return Status;
}
