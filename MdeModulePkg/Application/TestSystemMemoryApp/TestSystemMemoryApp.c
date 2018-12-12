/** @file
  An Application to test Memory Service Usage.
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

#define BUF_STRING L"THIS IS BUFFER\r\n"
#define NUM_OF_BUF 10

//DEBUG: This is for debug usage
#define DUMP_SIZE 64
VOID
InternalDumpDataDebug (
  IN UINT8  *Data,
  IN UINTN  Size
  )
{
  UINTN  Index;

  for (Index = 0; Index < Size; Index++) {
    DEBUG ((DEBUG_INFO, "%02x ", (UINTN)Data[Index]));
  }
}

VOID
InternalDumpHexDebug (
  IN UINT8  *Data,
  IN UINTN  Size
  )
{
  UINTN   Index;
  UINTN   Count;
  UINTN   Left;

#define COLUME_SIZE  (16)
  Count = Size / COLUME_SIZE;
  Left  = Size % COLUME_SIZE;
  for (Index = 0; Index < Count; Index++) {
   InternalDumpDataDebug (Data + Index * COLUME_SIZE, COLUME_SIZE);
    DEBUG ((DEBUG_INFO, "\n"));
  }
  if (Left != 0) {
    InternalDumpDataDebug(Data + Index * COLUME_SIZE, Left);
    DEBUG ((DEBUG_INFO, "\n"));
  }
  DEBUG ((DEBUG_INFO, "\n"));
}
//DEBUG: end of debug



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
  Status = gBS->AllocatePool(EfiBootServicesData, BufferSize, &Buffer);
  if (EFI_ERROR(Status)){
    DEBUG((EFI_D_ERROR, "Status = 0x%x\n", Status));
    return Status;
  }
  gBS->CopyMem(Buffer, BUF_STRING, sizeof(BUF_STRING));
  InternalDumpHexDebug((UINT8*)Buffer, DUMP_SIZE); // debug
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
  InternalDumpHexDebug((UINT8*)Buffer, DUMP_SIZE); // debug
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
  InternalDumpHexDebug((UINT8*)Buffer, DUMP_SIZE); // debug
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
  InternalDumpHexDebug((UINT8*)Buffer, DUMP_SIZE); // debug
  Status = gST->ConOut->OutputString(gST->ConOut, Buffer);
  FreePages(Buffer, EFI_SIZE_TO_PAGES (BufferSize));

  return Status;
}



/**
  Test GetMemoryMap.

  @retval EFI_SUCCESS            Command completed successfully.

**/
EFI_STATUS
EFIAPI
TestGetMemoryMap ( VOID )
{
  EFI_STATUS             Status;
  UINTN                  MemoryMapSize;  // A pointer to the size of buffer
  EFI_MEMORY_DESCRIPTOR *MemoryMap;      // A pointer to the buffer in which firmware places the current memory map.
  EFI_MEMORY_DESCRIPTOR *MMap;
  UINTN                  MapKey;
  UINTN                  DescriptorSize;
  UINTN                  DescriptorVersion;
  UINTN                  i;
  BOOLEAN                Allocated;

  MemoryMapSize     = 0;
  MemoryMap         = NULL;
  MMap              = NULL;
  MapKey            = 0;
  DescriptorSize    = 0;
  DescriptorVersion = 0;
  Allocated         = FALSE;

  // Call GetMemoryMap : no MemoryMap buffer allocated must return EFI_BUFFER_TOO_SMALL
  Status = gBS->GetMemoryMap(
                  &MemoryMapSize,
                  MemoryMap,
                  &MapKey,
                  &DescriptorSize,
                  &DescriptorVersion
                  );
  DEBUG((EFI_D_INFO, "MemoryMapSize = 0x%x\n",     MemoryMapSize));
  DEBUG((EFI_D_INFO, "MapKey = 0x%x\n",            MapKey));
  DEBUG((EFI_D_INFO, "DescriptorSize = 0x%x\n",    DescriptorSize));
  DEBUG((EFI_D_INFO, "DescriptorVersion = 0x%x\n", DescriptorVersion));
  DEBUG((EFI_D_INFO, "MemoryMap = 0x%p\n\n",       MemoryMap));

  // MemoryMapSize -- The size of the buffer needed to contain the map if the buffer was too small.
  if (Status == EFI_BUFFER_TOO_SMALL){
    DEBUG((EFI_D_ERROR, "EFI_BUFFER_TOO_SMALL\n"));
    // AllocatePool
    Status = gBS->AllocatePool(EfiBootServicesData, MemoryMapSize, &MemoryMap);
    // Call GetMemoryMap
    Status = gBS->GetMemoryMap(
                    &MemoryMapSize,
                    MemoryMap,
                    &MapKey,
                    &DescriptorSize,
                    &DescriptorVersion
                    );
    DEBUG((EFI_D_INFO, "MemoryMapSize = 0x%x\n",     MemoryMapSize));
    DEBUG((EFI_D_INFO, "MapKey = 0x%x\n",            MapKey));
    DEBUG((EFI_D_INFO, "DescriptorSize = 0x%x\n",    DescriptorSize));
    DEBUG((EFI_D_INFO, "DescriptorVersion = 0x%x\n", DescriptorVersion));
    DEBUG((EFI_D_INFO, "MemoryMap = 0x%p\n\n",       MemoryMap));
  }

  Print(L"MemoryMap Type NumberOfPages PhysicalStart VirtualStart\n");
  DEBUG((EFI_D_INFO, "MemoryMap Type NumberOfPages PhysicalStart VirtualStart\n"));

  for (i = 0; i < MemoryMapSize/DescriptorSize; i++){
    MMap = (EFI_MEMORY_DESCRIPTOR *)((UINTN)MemoryMap + i*DescriptorSize);
    Print(L"MemoryMap %4d %10d :", MMap[0].Type, MMap[0].NumberOfPages);
    Print(L"%10lx<->%10lx\n",      MMap[0].PhysicalStart, MMap[0].VirtualStart);
    DEBUG((EFI_D_INFO, "MemoryMap %4d %10d :",  MMap[0].Type, MMap[0].NumberOfPages));
    DEBUG((EFI_D_INFO, "%10lx<->%10lx\n",       MMap[0].PhysicalStart, MMap[0].VirtualStart));
  }

  // Free MemoryMap Buffer
  if (Allocated){
    Status = gBS->FreePool(MemoryMap);
  }

  return Status;
}



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

  Status = TestAllocate();
  DEBUG((EFI_D_INFO, "Status = 0x%x\n", Status));

  Status = TestGetMemoryMap();
  DEBUG((EFI_D_INFO, "Status = 0x%x\n", Status));

  return Status;
}
