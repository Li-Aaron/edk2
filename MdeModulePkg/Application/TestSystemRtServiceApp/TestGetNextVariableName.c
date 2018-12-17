/** @file
  An Application to test GetNextVariableName Usage.
  Self Study usage.
**/

#include "TestSystemRtServiceApp.h"


/**
  Test GetNextVariableName.

  @retval EFI_SUCCESS            Command completed successfully.

**/
EFI_STATUS
EFIAPI
TestGetNextVariableName( VOID )
{
  EFI_STATUS             Status;

  UINT8                 *DataBuffer;
  UINT16                *NameBuffer;
  UINTN                  DataBufferSize;
  UINTN                  DataSize;
  UINTN                  NameBufferSize;
  UINTN                  NameSize;
  EFI_GUID               VariableGuid; 

  Status         = EFI_SUCCESS;
  DataBufferSize = INIT_DATA_BUFFER_SIZE;
  NameBufferSize = INIT_NAME_BUFFER_SIZE;

  DataBuffer = AllocateZeroPool(DataBufferSize);
  if (DataBuffer == NULL){
    DEBUG((EFI_D_ERROR, "DataBuffer EFI_OUT_OF_RESOURCES\r\n"));
    return EFI_OUT_OF_RESOURCES;
  }
  NameBuffer = AllocateZeroPool(NameBufferSize);
  if (NameBuffer == NULL){
    DEBUG((EFI_D_ERROR, "NameBuffer EFI_OUT_OF_RESOURCES\r\n"));
    FreePool(DataBuffer);
    return EFI_OUT_OF_RESOURCES;
  }

  while(!EFI_ERROR(Status)) {
    NameSize = NameBufferSize;
    Status = gRT->GetNextVariableName(&NameSize, NameBuffer, &VariableGuid);
    //
    // Buffer size not enough
    //
    if(Status == EFI_BUFFER_TOO_SMALL){
      NameBufferSize = NameSize > NameBufferSize * 2 ? NameSize : NameBufferSize * 2;
      DEBUG((EFI_D_ERROR, "NameBufferSize adjust to %d\r\n", NameBufferSize));
      FreePool(NameBuffer);
      NameBuffer = AllocateZeroPool(NameBufferSize);
      if (NameBuffer == NULL){
        DEBUG((EFI_D_ERROR, "NameBuffer EFI_OUT_OF_RESOURCES\r\n"));
        FreePool(DataBuffer);
        return EFI_OUT_OF_RESOURCES;
      }
      Status = gRT->GetNextVariableName(&NameSize, NameBuffer, &VariableGuid);
    }

    //
    // End of Variable table
    //
    if (Status == EFI_NOT_FOUND)
    {
      Print(L"END of Variable Table\r\n");
      DEBUG((EFI_D_INFO, "END of Variable Table\r\n"));
      Status = EFI_SUCCESS;
      break;
    }

    //
    // Get variable Value
    //
    DataSize = DataBufferSize;
    Status = gRT->GetVariable(NameBuffer, &VariableGuid, NULL, &DataSize, DataBuffer);

    //
    // Buffer size not enough
    //
    if (Status == EFI_BUFFER_TOO_SMALL)
    {
      DataBufferSize = DataSize;
      DEBUG((EFI_D_ERROR, "DataBufferSize adjust to %d\r\n", DataBufferSize));
      FreePool(DataBuffer);
      DataBuffer = AllocateZeroPool(DataBufferSize);
      Status = gRT->GetVariable(NameBuffer, &VariableGuid, NULL, &DataSize, DataBuffer);
    }

    //
    // Print Variables
    //
    Print(L"VariableName: %s\r\n", NameBuffer);
    Print(L"VariableGuid: %g\r\n", &VariableGuid);
    DEBUG((EFI_D_INFO, "VariableName: %s\r\n", NameBuffer));
    DEBUG((EFI_D_INFO, "VariableGuid: %g\r\n", &VariableGuid));
    InternalDumpHexDebug(DataBuffer, DataSize);
    
  }

  FreePool(DataBuffer);
  FreePool(NameBuffer);

  return Status;
}