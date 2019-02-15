/** @file
  An Application to test GetMemoryMap Usage.
  Self Study usage.
**/

#include "TestSystemServiceApp.h"


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