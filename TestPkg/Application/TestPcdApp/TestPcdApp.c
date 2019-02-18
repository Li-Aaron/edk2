/** @file
  An Application to test Timer Usage.
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
#include <Library/PcdLib.h>

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
  EFI_STATUS            Status;
  UINT32                RunTimes;

  DEBUG((EFI_D_INFO, "[PcdTest] PcdTestApp Start.\n"));

  //
  // Fixed at build
  //
  DEBUG((EFI_D_INFO, "[PcdTest] PcdTestFixedAtBuild1:0x%x.\n", PcdGet8 (PcdTestFixedAtBuild1)));
  DEBUG((EFI_D_INFO, "[PcdTest] PcdTestFixedAtBuild2:0x%x.\n", PcdGet16 (PcdTestFixedAtBuild2)));
  // warning C4013: '_PCD_SET_MODE_16_S_PcdTestFixedAtBuild2' undefined; assuming extern returning int
  // Fixed at build can not use set
  // Status = PcdSet16S(PcdTestFixedAtBuild2, 0xA5A5);
  DEBUG((EFI_D_INFO, "[PcdTest] PcdTestFixedAtBuild3:0x%x.\n", PcdGet32 (PcdTestFixedAtBuild3)));
  DEBUG((EFI_D_INFO, "[PcdTest] PcdTestFixedAtBuild4:0x%x.\n", PcdGet64 (PcdTestFixedAtBuild4))); //const
  DEBUG((EFI_D_INFO, "[PcdTest] PcdTestFixedAtBuild4:0x%x.\n", FixedPcdGet64 (PcdTestFixedAtBuild4))); //marco

  //
  // FeatureFlag
  //
  DEBUG((EFI_D_INFO, "[PcdTest] PcdTestFeatureFlag1:0x%x.\n", PcdGetBool (PcdTestFeatureFlag1)));
  DEBUG((EFI_D_INFO, "[PcdTest] PcdTestFeatureFlag1:0x%x.\n", FeaturePcdGet (PcdTestFeatureFlag1)));
  DEBUG((EFI_D_INFO, "[PcdTest] PcdTestFeatureFlag2:0x%x.\n", PcdGetBool (PcdTestFeatureFlag2)));
  DEBUG((EFI_D_INFO, "[PcdTest] PcdTestFeatureFlag2:0x%x.\n", FeaturePcdGet (PcdTestFeatureFlag2)));

  //
  // Fixed/Patch in module (is present as fixed pcd)
  //
  DEBUG((EFI_D_INFO, "[PcdTest] PcdTestFixedPatchableInModule1:0x%x.\n", PcdGet16 (PcdTestFixedPatchableInModule1)));
  DEBUG((EFI_D_INFO, "[PcdTest] PcdTestFixedPatchableInModule2:0x%x.\n", PcdGet16 (PcdTestFixedPatchableInModule2)));
  // warning C4013: '_PCD_SET_MODE_16_S_PcdTestFixedPatchableInModule2' undefined; assuming extern returning int
  // Fixed at build can not use set
  // Status = PcdSet16S(PcdTestFixedPatchableInModule2, 0xDDDD);

  //
  // Patch in module, can use set
  //
  DEBUG((EFI_D_INFO, "[PcdTest] PcdTestPatchableInModule1:0x%x.\n", PcdGet16 (PcdTestPatchableInModule1)));
  DEBUG((EFI_D_INFO, "[PcdTest] PcdTestPatchableInModule2:0x%x.\n", PcdGet16 (PcdTestPatchableInModule2)));
  Status = PcdSet16S(PcdTestPatchableInModule2, 0xDDDD);
  DEBUG((EFI_D_INFO, "[PcdTest] PcdSet16S(PcdTestPatchableInModule2) returns:0x%x.\n", Status));
  DEBUG((EFI_D_INFO, "[PcdTest] PcdTestPatchableInModule2:0x%x.\n", PcdGet16 (PcdTestPatchableInModule2)));

  //
  // Dynamic
  //
  // UEFI driver and application can use Dynamic/DynamicEx PCDs when they are built together with platform.
  DEBUG((EFI_D_INFO, "[PcdTest] PcdTestDynamic1:0x%x.\n", PcdGet32 (PcdTestDynamic1)));
  DEBUG((EFI_D_INFO, "[PcdTest] PcdTestDynamic2:0x%x.\n", PcdGet32 (PcdTestDynamic2)));
  Status = PcdSet32S(PcdTestDynamic2, 0xDDDDDDDD);
  DEBUG((EFI_D_INFO, "[PcdTest] PcdSet32S(PcdTestDynamic2) returns:0x%x.\n", Status));
  DEBUG((EFI_D_INFO, "[PcdTest] PcdTestDynamic2:0x%x.\n", PcdGet32 (PcdTestDynamic2)));

  //
  // Dynamic vs Patch in module
  //
  RunTimes = PcdGet32 (PcdRunedPatchableInModule);
  DEBUG((EFI_D_INFO, "[PcdTest.Runtime] PcdRunedPatchableInModule:0x%x.\n", RunTimes));
  Print(L"[PcdTest.Runtime] PcdRunedPatchableInModule:0x%x.\n", RunTimes);
  Status = PcdSet32S(PcdRunedPatchableInModule, RunTimes + 1);
  DEBUG((EFI_D_INFO, "[PcdTest.Runtime] PcdSet32S(PcdRunedPatchableInModule) returns:0x%x.\n", Status));
  // Clear when application ends
  DEBUG((EFI_D_INFO, "[PcdTest.Runtime] (Updated)PcdRunedPatchableInModule:0x%x.\n", PcdGet32 (PcdRunedPatchableInModule)));

  RunTimes = PcdGet32 (PcdRunedDynamic);
  DEBUG((EFI_D_INFO, "[PcdTest.Runtime] PcdRunedDynamic:0x%x.\n", RunTimes));
  Print(L"[PcdTest.Runtime] PcdRunedDynamic:0x%x.\n", RunTimes);
  Status = PcdSet32S(PcdRunedDynamic, RunTimes + 1);
  DEBUG((EFI_D_INFO, "[PcdTest.Runtime] PcdSet32S(PcdRunedDynamic) returns:0x%x.\n", Status));
  // Not be cleared
  DEBUG((EFI_D_INFO, "[PcdTest.Runtime] (Updated)PcdRunedDynamic:0x%x.\n", PcdGet32 (PcdRunedDynamic)));

  DEBUG((EFI_D_INFO, "[PcdTest] PcdTestApp End.\n"));

  Status = EFI_SUCCESS;

  return Status;
}
