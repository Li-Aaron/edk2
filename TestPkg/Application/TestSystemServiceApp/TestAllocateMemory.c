/** @file
  An Application to test AllocateMemory Usage.
  Self Study usage.
**/

#include "TestSystemServiceApp.h"


/**
  Test AllocateMemory / Page.

  @retval EFI_SUCCESS            Command completed successfully.

**/
EFI_STATUS
EFIAPI
TestAllocate ( VOID )
{
  EFI_STATUS             Status;
  UINTN                  BufferSize;
  CHAR16                *Buffer;
  EFI_PHYSICAL_ADDRESS   Pages;

  BufferSize        = 10240;

  //
  // use UefiBootServicesTableLib
  //
  Status = gBS->AllocatePool(EfiBootServicesData, BufferSize, (VOID **)&Buffer);
  if (EFI_ERROR(Status)){
    DEBUG((EFI_D_ERROR, "Status = 0x%x\n", Status));
    return Status;
  }
  gBS->CopyMem(Buffer, BUF_STRING, sizeof(BUF_STRING));
  InternalDumpHexDebug((UINT8*)Buffer, DUMP_SIZE);
  Status = gST->ConOut->OutputString(gST->ConOut, Buffer);
  Status = gBS->FreePool(Buffer);
  if (EFI_ERROR(Status)){
    DEBUG((EFI_D_ERROR, "Status = 0x%x\n", Status));
    return Status;
  }

  //
  // use BaseMemoryLib + MemoryAllocationLib
  //
  Buffer = (CHAR16 *)AllocatePool(BufferSize);
  if (Buffer == NULL){
    DEBUG((EFI_D_ERROR, "EFI_OUT_OF_RESOURCES\n"));
    return EFI_OUT_OF_RESOURCES;
  }
  CopyMem(Buffer, BUF_STRING, sizeof(BUF_STRING));
  InternalDumpHexDebug((UINT8*)Buffer, DUMP_SIZE);
  Status = gST->ConOut->OutputString(gST->ConOut, Buffer);
  FreePool(Buffer);

  //
  // Use Pages
  //
  DEBUG((EFI_D_INFO, "EFI_SIZE_TO_PAGES (0x%x):0x%x\n", BufferSize, EFI_SIZE_TO_PAGES (BufferSize)));
  Status = gBS->AllocatePages(
                  AllocateAnyPages,
                  EfiBootServicesData,
                  EFI_SIZE_TO_PAGES (BufferSize),
                  &Pages
                  );
  if (EFI_ERROR(Status)){
    DEBUG((EFI_D_ERROR, "Status = 0x%x\n", Status));
    return Status;
  }
  Buffer = (CHAR16 *)(UINTN)Pages;
  gBS->CopyMem(Buffer, BUF_STRING, sizeof(BUF_STRING));
  InternalDumpHexDebug((UINT8*)Buffer, DUMP_SIZE);
  Status = gST->ConOut->OutputString(gST->ConOut, Buffer);
  Status = gBS->FreePages(Pages, EFI_SIZE_TO_PAGES (BufferSize));
  if (EFI_ERROR(Status)){
    DEBUG((EFI_D_ERROR, "Status = 0x%x\n", Status));
    return Status;
  }

  //
  // Use AllocatePages
  //
  Buffer = (CHAR16 *)AllocatePages(EFI_SIZE_TO_PAGES (BufferSize));
  if (Buffer == NULL){
    DEBUG((EFI_D_ERROR, "EFI_OUT_OF_RESOURCES\n"));
    return EFI_OUT_OF_RESOURCES;
  }
  CopyMem(Buffer, BUF_STRING, sizeof(BUF_STRING));
  InternalDumpHexDebug((UINT8*)Buffer, DUMP_SIZE);
  Status = gST->ConOut->OutputString(gST->ConOut, Buffer);
  FreePages(Buffer, EFI_SIZE_TO_PAGES (BufferSize));

  return Status;
}