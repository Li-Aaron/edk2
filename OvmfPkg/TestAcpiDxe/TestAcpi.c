/** @file

SPDX-License-Identifier: BSD-2-Clause-Patent

**/
#include <Uefi.h>
#include <Library/UefiBootServicesTableLib.h>
#include <Library/UefiLib.h>
#include <Library/DebugLib.h>
#include <Library/BaseMemoryLib.h>
#include <Library/MemoryAllocationLib.h>
#include <IndustryStandard/Acpi.h>
#include <Protocol/AcpiTable.h>
#include <Library/DxeServicesLib.h>

// https://li-aaron.github.io/2023/04/asl-code-intro4/
// DefOpRegion := OpRegionOp NameString RegionSpace RegionOffset RegionLen
// OpRegionOp := ExtOpPrefix 0x80
// ExtOpPrefix := 0x5B
// RegionSpace := ByteData  (0x00 SystemMemory)
// RegionOffset := TermArg => Integer (0x0A)
// RegionLen := TermArg => Integer
// TermArg := ExpressionOpcode | [DataObject] | ArgObj | LocalObj
// DataObject := [ComputationalData] | DefPackage | DefVarPackage
// ComputationalData := ByteConst | WordConst | [DWordConst] | QWordConst | String | ConstObj | RevisionOp | DefBuffer
// DWordConst := DWordPrefix DWordData
// DWordPrefix := 0x0C
#pragma pack(push, 1)
typedef struct {
  UINT8     ExtOpPrefix;
  UINT8     ExtOpCode;
  UINT32    NameString;
  UINT8     RegionSpace;
  UINT8     DwordPrefix1;
  UINT32    RegionOffset;
  UINT8     DwordPrefix2;
  UINT32    RegionLen;
} TEST_OP_REGION;

typedef struct {
  UINT32                Iteration;
  UINT16                Buffer[0x20];
} ACPI_TEST_BUFFER;
#pragma pack(pop)

ACPI_TEST_BUFFER   *mAcpiTestBuffer;

EFI_STATUS
EFIAPI
PatchSsdtTable (
  IN OUT EFI_ACPI_DESCRIPTION_HEADER  *Table
  )
{
  EFI_STATUS Status;
  TEST_OP_REGION *OpRegion;
  UINT8 *Start;
  UINT8 *End;
  UINT8 *BytePtr;

  Start = (UINT8 *)(Table + 1);
  End = Start + Table->Length;
  Status = EFI_NOT_FOUND;

  // Find the OpRegion in the SSDT table
  for (BytePtr = Start; BytePtr < End; BytePtr++) {
    OpRegion = (TEST_OP_REGION *)BytePtr;

    // 5B 80 54 45 53 54 00 0C A5 A5 A5 A5 0C A5 A5 A5 A5
    if (OpRegion->ExtOpPrefix == 0x5B
        && OpRegion->ExtOpCode == 0x80
        && OpRegion->NameString == SIGNATURE_32('T', 'E', 'S', 'T')
        && OpRegion->RegionSpace == 0x00
        && OpRegion->DwordPrefix1 == 0x0C
        && OpRegion->DwordPrefix2 == 0x0C
        ) {
      // Patch the OpRegion
      OpRegion->RegionOffset = (UINT32) (UINTN) mAcpiTestBuffer;
      OpRegion->RegionLen = (UINT32) (UINTN) sizeof(ACPI_TEST_BUFFER);
      Status = EFI_SUCCESS;
      break;
    }
  }

  return Status;
}


EFI_STATUS
EFIAPI
InstallSsdtTable (
  IN EFI_HANDLE        ImageHandle,
  IN EFI_SYSTEM_TABLE  *SystemTable
  )
{
  EFI_STATUS                   Status;
  EFI_ACPI_TABLE_PROTOCOL      *AcpiTableProtocol;
  EFI_ACPI_DESCRIPTION_HEADER  *SsdtTable;
  UINTN                        SsdtTableSize;
  UINTN                        TableKey;

  // Locate the ACPI Table Protocol
  Status = gBS->LocateProtocol(&gEfiAcpiTableProtocolGuid, NULL, (VOID **)&AcpiTableProtocol);
  if (EFI_ERROR(Status)) {
    DEBUG((EFI_D_ERROR, "%a, Failed to locate ACPI Table Protocol: %r\n", __func__, Status));
    return Status;
  }

  // Locate the SSDT table from the firmware volume using GetSectionFromFv
  Status = GetSectionFromFv(&gEfiCallerIdGuid, EFI_SECTION_RAW, 0, (VOID **)&SsdtTable, &SsdtTableSize);
  if (EFI_ERROR(Status)) {
    DEBUG((EFI_D_ERROR, "%a, Failed to get SSDT table from firmware volume: %r\n", __func__, Status));
    return Status;
  }

  // Allocate memory for the ACPI test buffer
  Status = gBS->AllocatePool (
                  EfiRuntimeServicesData,
                  sizeof (ACPI_TEST_BUFFER),
                  (VOID **) &mAcpiTestBuffer
                  );
  if (EFI_ERROR (Status)) {
    DEBUG((EFI_D_ERROR, "%a, Failed to allocate memory for ACPI test buffer: %r\n", __func__, Status));
    FreePool(SsdtTable);
    return Status;
  }
  ZeroMem (mAcpiTestBuffer, sizeof (ACPI_TEST_BUFFER));
  mAcpiTestBuffer->Iteration = 0x18;

  // Patch SSDT table's OpRegion
  Status = PatchSsdtTable(SsdtTable);
  if (EFI_ERROR(Status)) {
    DEBUG((EFI_D_ERROR, "%a, Failed to patch SSDT table: %r\n", __func__, Status));
    FreePool(SsdtTable);
    return Status;
  }

  // Install the SSDT table
  Status = AcpiTableProtocol->InstallAcpiTable(AcpiTableProtocol, SsdtTable, SsdtTable->Length, &TableKey);
  if (EFI_ERROR(Status)) {
    DEBUG((EFI_D_ERROR, "%a, Failed to install SSDT table: %r\n", __func__, Status));
    FreePool(SsdtTable);
    return Status;
  }

  DEBUG((EFI_D_ERROR, "%a, SSDT table installed successfully\n", __func__));
  FreePool(SsdtTable);
  return EFI_SUCCESS;
}

EFI_STATUS
EFIAPI
TestAcpiEntryPoint (
  IN EFI_HANDLE        ImageHandle,
  IN EFI_SYSTEM_TABLE  *SystemTable
  )
{
  DEBUG((EFI_D_ERROR, "%a, entered\n", __func__));
  return InstallSsdtTable(ImageHandle, SystemTable);
}