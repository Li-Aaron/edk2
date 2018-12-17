/** @file
  An Application to test GetVariable/SetVariable Usage.
  Self Study usage.
**/

#include "TestSystemRtServiceApp.h"


/**
  Test GetVariable / SetVariable.

  @retval EFI_SUCCESS            Command completed successfully.

**/
EFI_STATUS
EFIAPI
TestGetVariable( VOID )
{
  EFI_STATUS             Status;
  UINTN                  Length;
  UINT16                 *BootOrder;

  UINTN                  BufferSize;
  UINT8                  *Buffer;
  UINT32                 Attribute;
  UINTN                  i;

  BufferSize       = 10240;

  Status = gBS->AllocatePool(EfiBootServicesData, BufferSize, &Buffer);
  if (EFI_ERROR(Status)){
    DEBUG((EFI_D_ERROR, "Status = 0x%x\n", Status));
    return Status;
  }

  //
  // Get variable process
  //
  Length = BufferSize;
  Status = gRT->GetVariable(
                  L"BootOrder",
                  (EFI_GUID*)&gEfiGlobalVariableGuid,
                  &Attribute,
                  &Length,
                  Buffer
                  );
  DEBUG((EFI_D_INFO, "GetVariable Status : 0x%x\n", Status));
  DEBUG((EFI_D_INFO, "BootOrder Length : %d\r\n", Length));
  DEBUG((EFI_D_INFO, "BootOrder Attribute : 0x%X\r\n", Attribute));
  InternalDumpHexDebug(Buffer, Length);

  BootOrder = (UINT16 *)Buffer;
  for (i = 0; i < Length/sizeof(UINT16); i++){
    Print(L"BootOrder[%02d]: [%02d]\r\n", i, BootOrder[i]);
    DEBUG((EFI_D_INFO, "BootOrder[%02d]: [%02d]\r\n", i, BootOrder[i]));
  }

  //
  // Set variable process
  //
  for (i = 0; i < Length/sizeof(UINT16); i++){
    BootOrder[i] = (UINT16)i;
  }

  Status = gRT->SetVariable(
                  L"BootOrder",
                  (EFI_GUID*)&gEfiGlobalVariableGuid,
                  Attribute,
                  Length,
                  Buffer
                  );
  DEBUG((EFI_D_INFO, "SetVariable Status : 0x%x\n", Status));

  //
  // Get variable again
  //
  Status = gRT->GetVariable(
                  L"BootOrder",
                  (EFI_GUID*)&gEfiGlobalVariableGuid,
                  &Attribute,
                  &Length,
                  Buffer
                  );

  DEBUG((EFI_D_INFO, "GetVariable Status : 0x%x\n", Status));
  DEBUG((EFI_D_INFO, "BootOrder Length : %d\r\n", Length));
  DEBUG((EFI_D_INFO, "BootOrder Attribute : 0x%X\r\n", Attribute));
  InternalDumpHexDebug(Buffer, Length);

  BootOrder = (UINT16 *)Buffer;
  for (i = 0; i < Length/sizeof(UINT16); i++){
    Print(L"BootOrder[%02d]: [%02d]\r\n", i, BootOrder[i]);
    DEBUG((EFI_D_INFO, "BootOrder[%02d]: [%02d]\r\n", i, BootOrder[i]));
  }

  Status = gBS->FreePool(Buffer);
  return Status;
}