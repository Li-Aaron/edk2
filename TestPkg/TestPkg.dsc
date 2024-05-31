## @file
# self test pkg
#
##

[Defines]
  PLATFORM_NAME                  = Test
  PLATFORM_GUID                  = fbd9331b-2ea7-414b-8f3f-80c8a5d8d998
  PLATFORM_VERSION               = 0.01
  DSC_SPECIFICATION              = 0x00010005
  OUTPUT_DIRECTORY               = Build/Test
  SUPPORTED_ARCHITECTURES        = IA32|X64|EBC|ARM|AARCH64
  BUILD_TARGETS                  = DEBUG|RELEASE|NOOPT
  SKUID_IDENTIFIER               = DEFAULT

[LibraryClasses]
  #
  # Entry point
  #
  SerialOutLib|TestPkg/Library/SerialOutLib/SerialOutLib.inf

[Components]
  # TODO: self added
  ShellPkg/Application/ShellHelloApp/ShellHelloApp.inf {
    <LibraryClasses>
      ShellCEntryLib|ShellPkg/Library/UefiShellCEntryLib/UefiShellCEntryLib.inf
  }
  ShellPkg/Application/ShellSortCmpTestApp/ShellSortCmpTestApp.inf {
    <LibraryClasses>
      ShellCEntryLib|ShellPkg/Library/UefiShellCEntryLib/UefiShellCEntryLib.inf
      SortCmpLib|TestPkg/Library/BaseSortCmpLib/BaseSortCmpLib.inf
  }
  TestPkg/Application/HelloApp/HelloApp.inf
  TestPkg/Application/TestSystemConsoleApp/TestSystemConsoleApp.inf
  TestPkg/Application/TestSystemServiceApp/TestSystemServiceApp.inf
  TestPkg/Application/TestSystemRtServiceApp/TestSystemRtServiceApp.inf
  TestPkg/Application/TestSystemEventApp/TestSystemEventApp.inf
  TestPkg/Application/TestSystemTimerApp/TestSystemTimerApp.inf
  TestPkg/Application/TestMouseKeyboardApp/TestMouseKeyboardApp.inf
  TestPkg/Application/TestDevicePathApp/TestDevicePathApp.inf
  TestPkg/Application/TestFileIoApp/TestFileIoApp.inf
  TestPkg/Application/TestPcdApp/TestPcdApp.inf
  TestPkg/Application/TestAslc/TestAslc.inf