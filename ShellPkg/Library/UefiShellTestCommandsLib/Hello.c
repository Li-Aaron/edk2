/** @file
  The implementation for Shell command IfConfig6.

  Copyright (c) 2016, Intel Corporation. All rights reserved.<BR>
  (C) Copyright 2017 Hewlett Packard Enterprise Development LP<BR>

  This program and the accompanying materials
  are licensed and made available under the terms and conditions of the BSD License
  which accompanies this distribution.  The full text of the license may be found at
  http://opensource.org/licenses/bsd-license.php.

  THE PROGRAM IS DISTRIBUTED UNDER THE BSD LICENSE ON AN "AS IS" BASIS,
  WITHOUT WARRANTIES OR REPRESENTATIONS OF ANY KIND, EITHER EXPRESS OR IMPLIED.

**/
#include "UefiShellTestCommandsLib.h"


/**
  Function for 'hello' command.

  @param[in]  ImageHandle           Handle to the Image (NULL if Internal).
  @param[in]  SystemTable           Pointer to the System Table (NULL if Internal).

  @retval  SHELL_SUCCESS            The command completed successfully.
  @retval  Others                   The command failed.

**/
SHELL_STATUS
EFIAPI
ShellCommandRunHello (
  IN  EFI_HANDLE                    ImageHandle,
  IN  EFI_SYSTEM_TABLE              *SystemTable
  )
{
  ShellPrintEx (-1, -1, L"%VHello World%N\r\n");
  ShellPrintEx (-1, -1, L"%BThis is %EAaron Li%N\r\n");

  return SHELL_SUCCESS;
}