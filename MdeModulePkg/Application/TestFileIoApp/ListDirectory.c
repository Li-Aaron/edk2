/** @file
  An Application to Test List Directory.
  Self Study usage.
**/

#include "TestFileIoApp.h"


/**
  Callback Function Type AccessFileInfo.
  Used in ListDirectory
  Print FileInfo

  @param[in] FileInfo      EFI_FILE_INFO, File Info Pointer.

**/
VOID
ListFileInfo (
  EFI_FILE_INFO  *FileInfo
)
{
  Print(L"Size : %d\nFileSize : %d\nPhysicalSize : %d\n%s\n",
    FileInfo->Size,
    FileInfo->FileSize,
    FileInfo->PhysicalSize,
    FileInfo->FileName
  );
  DEBUG((EFI_D_INFO, "Size : %d\nFileSize : %d\nPhysicalSize : %d\n%s\n",
    FileInfo->Size,
    FileInfo->FileSize,
    FileInfo->PhysicalSize,
    FileInfo->FileName
  ));
}

/**
  List Directory.

  @param[in] Directory      EFI_FILE_PROTOCOL, Directory Pointer.
  @param[in] CallBack       ACCESS_FILE_INFO, File Info Callback Function.

  @retval EFI_SUCCESS            Command completed successfully.

**/
EFI_STATUS
ListDirectory (
  EFI_FILE_PROTOCOL  *Directory,
  ACCESS_FILE_INFO    CallBack
)
{
  EFI_STATUS           Status;
  UINTN                BufSize;
  UINTN                ReadSize;
  EFI_FILE_INFO       *FileInfo;

  FileInfo = NULL;

  BufSize = sizeof(EFI_FILE_INFO) + sizeof(CHAR16) * 512;
  Status = gBS->AllocatePool(EfiBootServicesCode, BufSize, (VOID**)&FileInfo);
  CheckStatus("gBS->AllocatePool()");

  //
  // List All Directories.
  //
  while(TRUE){
    ReadSize = BufSize;
    Status = Directory->Read(Directory, &ReadSize, FileInfo);
    if (Status == EFI_BUFFER_TOO_SMALL) {
      BufSize = ReadSize;
      Status = gBS->FreePool(FileInfo);
      CheckStatus("gBS->FreePool()");

      Status = gBS->AllocatePool(EfiBootServicesCode, BufSize, (VOID**)&FileInfo);
      CheckStatus("gBS->AllocatePool()");

      Status = Directory->Read(Directory, &ReadSize, FileInfo);
      CheckStatus("Directory->Read()");
    }
    if (ReadSize == 0){
      break;
    }
    CallBack(FileInfo);
  }

  Status = gBS->FreePool(FileInfo);
  CheckStatus("gBS->FreePool()");
  return Status;
}

/**
  Test List Directory.

  @param[in] Directory      EFI_FILE_PROTOCOL, Directory Pointer.
  @param[in] CallBack       ACCESS_FILE_INFO, File Info Callback Function.

  @retval EFI_SUCCESS            Command completed successfully.

**/
EFI_STATUS
EFIAPI
TestListDirectory ( VOID )
{
  EFI_STATUS                         Status;
  EFI_SIMPLE_FILE_SYSTEM_PROTOCOL   *FileSystem;
  EFI_FILE_PROTOCOL                 *Root;

  Root = NULL;

  // Open Protocol & Root
  Status = gBS->LocateProtocol(&gEfiSimpleFileSystemProtocolGuid, NULL, (VOID **)&FileSystem);
  CheckStatus("gBS->LocateProtocol()");

  Status = FileSystem->OpenVolume(FileSystem, &Root);
  CheckStatus("FileSystem->OpenVolume()");

  Status = ListDirectory(Root, ListFileInfo);
  CheckStatus("ListDirectory()");

  return Status;
}