/** @file
  An Application to Test Write and Read File.
  Self Study usage.
**/

#include "TestFileIoApp.h"

/**
  Test Write and Read File.

  @retval EFI_SUCCESS            Command completed successfully.

**/
EFI_STATUS
EFIAPI
TestReadAndWrite ( VOID )
{
  EFI_STATUS                         Status;
  UINTN                              BufSize;
  EFI_SIMPLE_FILE_SYSTEM_PROTOCOL   *FileSystem;
  EFI_FILE_PROTOCOL                 *Root;
  EFI_FILE_PROTOCOL                 *FileHandle;

  CHAR16                            *FileName;
  CHAR16                            *TextBuf;
  CHAR16                            *TextReadBuf;


  Root = NULL;
  FileHandle = NULL;
  FileName = L"TestFileIoApp.txt";
  TextBuf = L"This is a file for testing File IO\n";
  TextReadBuf = NULL;

  // Open Protocol & Root
  Status = gBS->LocateProtocol(&gEfiSimpleFileSystemProtocolGuid, NULL, (VOID **)&FileSystem);
  CheckStatus("gBS->LocateProtocol()");

  Status = FileSystem->OpenVolume(FileSystem, &Root);
  CheckStatus("FileSystem->OpenVolume()");


  // Open File
  Status = Root->Open(
                  Root,
                  &FileHandle,
                  FileName,
                  EFI_FILE_MODE_CREATE | EFI_FILE_MODE_READ | EFI_FILE_MODE_WRITE,
                  0
                  );
  CheckStatus("Root->Open()");


  // Write File
  if (FileHandle && !EFI_ERROR(Status)) {
    BufSize = StrSize(TextBuf);
    Status = FileHandle->Write(FileHandle, &BufSize, TextBuf);
    CheckStatus("FileHandle->Write()");

    // Close File
    Status = FileHandle->Close(FileHandle);
    CheckStatus("FileHandle->Close()");
  }


  // Open File
  Status = Root->Open(
                Root,
                &FileHandle,
                FileName,
                EFI_FILE_MODE_READ,
                0
                );
  CheckStatus("Root->Open()");

  // Read File
  if (FileHandle && !EFI_ERROR(Status)) {
    BufSize = 64 * sizeof(*TextReadBuf);
    TextReadBuf = AllocateZeroPool(BufSize);
    Status = FileHandle->Read(FileHandle, &BufSize, TextReadBuf);
    CheckStatus("FileHandle->Read()");

    // Close File
    Status = FileHandle->Close(FileHandle);
    CheckStatus("FileHandle->Close()");
  }

  // Print
  Print(L"%s\n", TextReadBuf);
  DEBUG((EFI_D_INFO, "%s\n", TextReadBuf));

  return Status;
}
