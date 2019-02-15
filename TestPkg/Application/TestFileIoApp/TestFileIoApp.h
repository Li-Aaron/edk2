/** @file
  An Application to Test File IO
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
#include <Guid/FileInfo.h>

#define CheckStatus(String) \
  if (EFI_ERROR(Status)) { \
    DEBUG((EFI_D_ERROR, String" return Status: 0x%x\n", Status)); \
    return Status; \
  }


typedef VOID (*ACCESS_FILE_INFO) (EFI_FILE_INFO* FileInfo);

/**
  Test Write and Read File.

  @retval EFI_SUCCESS            Command completed successfully.

**/
EFI_STATUS
EFIAPI
TestReadAndWrite ( VOID );

/**
  Test List Directory.

  @retval EFI_SUCCESS            Command completed successfully.

**/
EFI_STATUS
EFIAPI
TestListDirectory ( VOID );