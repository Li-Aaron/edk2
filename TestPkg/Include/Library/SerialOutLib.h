  /** @file
  Library used for directly serial out
  Self Study usage.

**/

// output a single byte
VOID
SerialOut (
  IN UINT8     OutData
  );

// output a CHAR string
VOID
EFIAPI
SerialOutput (
  IN UINT8     *Buffer
  );

// Output a UINT8 data's Hex value
VOID
SerialOutU8Data (
  IN UINT8  Data
  );

// Output a UINT16 data's Hex value
VOID
SerialOutU16Data(
  IN UINT16  Data
  );

// Output a UINT32 data's Hex value
VOID
SerialOutU32Data(
  IN UINT32  Data
  );

// Output a UINT64 data's Hex value
VOID
SerialOutU64Data(
  IN UINT64  Data
  );

// Dump Buffer's Hex value
VOID
SerialDumpHex (
  IN UINT8  *Data,
  IN UINTN  Size
  );