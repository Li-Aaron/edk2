/** @file
  Test Aslc Header
  Self Study usage.

**/
#ifndef _TEST_ASLC_H_
#define _TEST_ASLC_H_

#include <Uefi.h>


// {d62e3311-ac14-4210-ae84-564dbe8296f3}
#define TEST_ASLC_GUID \
 { \
   0xd62e3311, 0xac14, 0x4210, {0xae, 0x84, 0x56, 0x4d, 0xbe, 0x82, 0x96, 0xf3} \
 }
#define TEST_ASLC_HEADER_SIGNATURE  SIGNATURE_32 ('T', 'E', 'S', 'T')
#define TEST_ASLC_OEM_ID             'T','E','S','T',' ',' '   // OEMID 6 bytes long
#define TEST_ASLC_OEM_TABLE_ID       SIGNATURE_64('T','E','S','T','A','S','L','C') // OEM table id 8 bytes long
#define TEST_ASLC_OEM_REVISION       0x20190325
#define TEST_ASLC_CREATOR_ID         SIGNATURE_32 ('T', 'E', 'S', 'T')
#define TEST_ASLC_CREATOR_REVISION   0x00000099

typedef struct {
  UINT8                       e[8];
  UINT32                      f;
  EFI_GUID                    g;
} TEST_ASLC_CONTENT;

typedef struct _TEST_ASLC_TYPE {
  EFI_ACPI_DESCRIPTION_HEADER Header;
  TEST_ASLC_CONTENT           Content[0];
} TEST_ASLC_TYPE;

#endif