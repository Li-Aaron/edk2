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

  Status = gBS->AllocatePool(EfiBootServicesData, BufferSize, (VOID **)&Buffer);
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


/**
  Test GetVariable / SetVariable (difference length).

  @retval EFI_SUCCESS            Command completed successfully.

**/
EFI_STATUS
EFIAPI
TestSetVariable( VOID )
{
  EFI_STATUS             Status;
  UINTN                  BufferSize;
  UINT8                  *Buffer;
  UINT32                 Attribute;

  CHAR16                 *String1 = L"Hello World";
  CHAR16                 *String2 = L"My Name is Aaron";



  //
  // Set variable process
  //
  Status = gRT->SetVariable(
                  L"TestString",
                  (EFI_GUID*)&gSelfVariableGuid,
                  EFI_VARIABLE_BOOTSERVICE_ACCESS,
                  StrSize(String1),
                  String1
                  );
  DEBUG((EFI_D_INFO, "SetVariable Status : 0x%x\n", Status));

  //
  // Get variable process
  //
  Status = gRT->GetVariable(
                  L"TestString",
                  (EFI_GUID*)&gSelfVariableGuid,
                  NULL,
                  &BufferSize,
                  NULL
                  );
  Buffer = (UINT8 *)AllocateZeroPool(BufferSize);
  if (Buffer == NULL) {
    DEBUG((EFI_D_ERROR, "Buffer Not Allocated.\n"));
    return EFI_OUT_OF_RESOURCES;
  }
  Status = gRT->GetVariable(
                  L"TestString",
                  (EFI_GUID*)&gSelfVariableGuid,
                  &Attribute,
                  &BufferSize,
                  Buffer
                  );

  DEBUG((EFI_D_INFO, "GetVariable Status : 0x%x\n", Status));
  DEBUG((EFI_D_INFO, "TestString Length : %d\r\n", BufferSize));
  DEBUG((EFI_D_INFO, "TestString Attribute : 0x%X\r\n", Attribute));
  InternalDumpHexDebug((UINT8 *)Buffer, BufferSize);
  Print(L"[TestString] %s.\n", Buffer);

  //
  // Set variable again
  //
  Status = gRT->SetVariable(
                  L"TestString",
                  (EFI_GUID*)&gSelfVariableGuid,
                  EFI_VARIABLE_BOOTSERVICE_ACCESS,
                  StrSize(String2),
                  String2
                  );
  DEBUG((EFI_D_INFO, "SetVariable Status : 0x%x\n", Status));
  FreePool(Buffer);

  //
  // Get variable again
  //
  Status = gRT->GetVariable(
                  L"TestString",
                  (EFI_GUID*)&gSelfVariableGuid,
                  NULL,
                  &BufferSize,
                  NULL
                  );
  Buffer = (UINT8 *)AllocateZeroPool(BufferSize);
  if (Buffer == NULL) {
    DEBUG((EFI_D_ERROR, "Buffer Not Allocated.\n"));
    return EFI_OUT_OF_RESOURCES;
  }
  Status = gRT->GetVariable(
                  L"TestString",
                  (EFI_GUID*)&gSelfVariableGuid,
                  &Attribute,
                  &BufferSize,
                  Buffer
                  );

  DEBUG((EFI_D_INFO, "GetVariable Status : 0x%x\n", Status));
  DEBUG((EFI_D_INFO, "TestString Length : %d\r\n", BufferSize));
  DEBUG((EFI_D_INFO, "TestString Attribute : 0x%X\r\n", Attribute));
  InternalDumpHexDebug((UINT8 *)Buffer, BufferSize);
  Print(L"[TestString] %s.\n", Buffer);
  FreePool(Buffer);

  return Status;
}