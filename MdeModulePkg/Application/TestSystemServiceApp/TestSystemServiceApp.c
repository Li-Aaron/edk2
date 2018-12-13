/** @file
  An Application to test System Service Usage.
  Self Study usage.
**/

#include "TestSystemServiceApp.h"

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
  CHAR16                *Vendor;

  UINTN                  MemoryMapSize;  // A pointer to the size of buffer
  EFI_MEMORY_DESCRIPTOR *MemoryMap;      // A pointer to the buffer in which firmware places the current memory map.
  UINTN                  MapKey;
  UINTN                  DescriptorSize;
  UINTN                  DescriptorVersion;

  MemoryMapSize     = 0;
  MemoryMap         = NULL;
  MapKey            = 0;
  DescriptorSize    = 0;
  DescriptorVersion = 0;

  Status = TestAllocate();
  DEBUG((EFI_D_INFO, "Status = 0x%x\n", Status));

  Status = TestGetMemoryMap();
  DEBUG((EFI_D_INFO, "Status = 0x%x\n", Status));

  //
  // Print Firmware Vendor
  //
  Vendor = gST->FirmwareVendor;
  gST->ConOut->OutputString(gST->ConOut, Vendor);
  gST->ConOut->OutputString(gST->ConOut, L"\r\nEXIT BOOT SERVICE\r\n");

  //
  // Get Latest MapKey
  //
  Status = gBS->GetMemoryMap(
                  &MemoryMapSize,
                  MemoryMap,
                  &MapKey,
                  &DescriptorSize,
                  &DescriptorVersion
                  );

  //
  // Exit Boot Service
  //
  _asm int 3
  Status = gBS->ExitBootServices(ImageHandle, MapKey);
  _asm int 3

  ASSERT(gST->BootServices == NULL);

  return Status;
}
