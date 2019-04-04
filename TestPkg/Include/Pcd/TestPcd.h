/** @file
  Provides Pcd Type Structures.

  Self study usage.
**/

#ifndef __TEST_PCD_H__
#define __TEST_PCD_H__

// #include <Uefi.h>

#pragma pack(1)
typedef struct {
  BOOLEAN  Bool;  
  UINT8    A:4; 
  UINT8    B:4;
  UINT16   C;
  UINT16   D;
  union {
    UINT8   Foo[8];
    UINT64  Bar;
  } E;
  UINT8    Guid[16];
  //UINT8    FlexibleArray[];
} TESTPCD;
#pragma pack()

#endif
