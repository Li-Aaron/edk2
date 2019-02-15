/** @file
  An Application to Print Device Path
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
#include <Library/DevicePathLib.h>
#include <Protocol/DevicePathToText.h>


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
  EFI_STATUS                        Status;
  UINTN                             HandleIndex;
  UINTN                             NumOfHandles;
  EFI_HANDLE                        *ControllerHandle;
  EFI_DEVICE_PATH_TO_TEXT_PROTOCOL  *DeviceToText;
  EFI_DEVICE_PATH_PROTOCOL          *DevicePath;
  EFI_DEVICE_PATH_PROTOCOL          *DevicePathTmp;
  CHAR16                            *TextDevicePath;

  ControllerHandle = NULL;
  DeviceToText     = NULL;
  TextDevicePath   = NULL;

  //
  // Get Protocol
  //
  Status = gBS->LocateProtocol(&gEfiDevicePathToTextProtocolGuid, NULL, (VOID **)&DeviceToText);
  if (EFI_ERROR(Status)) {
    DEBUG((EFI_D_INFO, "gBS->LocateProtocol() return Status : 0x%x\n", Status));
    return Status;
  }

  //
  // Get All Device Handles with DiskIoProtocol
  //
  Status = gBS->LocateHandleBuffer(
                  ByProtocol,
                  &gEfiDiskIoProtocolGuid,
                  NULL,
                  &NumOfHandles,
                  &ControllerHandle
                  );
  if (EFI_ERROR(Status)) {
    DEBUG((EFI_D_INFO, "gBS->LocateHandleBuffer() return Status : 0x%x\n", Status));
    return Status;
  }

  //
  // For each DiskIo Device, Open Device Path Protocol
  //
  for (HandleIndex = 0; HandleIndex < NumOfHandles; HandleIndex++) {
    Status = gBS->OpenProtocol(
                    ControllerHandle[HandleIndex],
                    &gEfiDevicePathProtocolGuid,
                    (VOID**)&DevicePath,
                    gImageHandle,
                    NULL,
                    EFI_OPEN_PROTOCOL_GET_PROTOCOL
                    );
    if (EFI_ERROR(Status)) {
      DEBUG((EFI_D_INFO, "HandleIndex: %d gBS->OpenProtocol() return Status : 0x%x\n", HandleIndex, Status));
      continue;
    }

    //
    // Convert DevicePath to String
    //
    TextDevicePath = DeviceToText->ConvertDevicePathToText(DevicePath, TRUE, TRUE);
    Print(L"HandleIndex: %d: %s\n", HandleIndex, TextDevicePath);
    DEBUG((EFI_D_INFO, "HandleIndex: %d: %s\n", HandleIndex, TextDevicePath));

    //
    // Walk Through Path and Print Nodes
    //
    DevicePathTmp = DevicePath;
    while(!IsDevicePathEnd(DevicePathTmp)) {
      Print(L"(%d %d)/", DevicePathTmp->Type, DevicePathTmp->SubType);
      DEBUG((EFI_D_INFO, "(%d %d)/", DevicePathTmp->Type, DevicePathTmp->SubType));
      DevicePathTmp = NextDevicePathNode(DevicePathTmp);
    }
    Print(L"\n\n");
    DEBUG((EFI_D_INFO, "\n\n"));
  }

  return Status;
}
