/** @file
 * Self Defined Test Guid
 * Self Study usage.
**/

#ifndef __SELF_TEST_DEFINED_H__
#define __SELF_TEST_DEFINED_H__

#define SELF_EVENT_EX_GUID \
  { \
    0xaed4d53f, 0x3b48, 0x4dba, {0xbc, 0x5e, 0xa0, 0x22, 0xe1, 0xb2, 0xe6, 0x95} \
  }

#define SELF_VARIABLE_GUID \
  { \
    0x2c87c751, 0x8543, 0x464b, {0xbe, 0xa6, 0xac, 0x32, 0x01, 0x09, 0xe1, 0xb9} \
  }

extern EFI_GUID gSelfEventExGuid;
extern EFI_GUID gSelfVariableGuid;
#endif
