  /** @file
  Library used for directly serial out
  Self Study usage.

**/

#include <Library/BaseLib.h>
#include <Library/IoLib.h>

#define SERIAL_PORT_IO     0x3f8
#define LSR_TXRDY          0x20
#define LSR_OFFSET         0x05

// output a single byte
VOID
SerialOut (
  IN UINT8     OutData
  )
{
  UINT8 Data;
  //
  // Wait for the serail port to be ready.
  //
  do {
    Data = IoRead8 ((UINT16) SERIAL_PORT_IO + LSR_OFFSET);
  } while ((Data & LSR_TXRDY) == 0);
  IoWrite8 ((UINT16) SERIAL_PORT_IO, OutData);
}

// output a CHAR string
VOID
EFIAPI
SerialOutput (
  IN UINT8     *Buffer
  )
{
  UINT8 Data;
  UINTN NumberOfBytes = AsciiStrLen (Buffer);
  while (NumberOfBytes--) {
    //
    // Wait for the serail port to be ready.
    //
    do {
      Data = IoRead8 ((UINT16) SERIAL_PORT_IO + LSR_OFFSET);
    } while ((Data & LSR_TXRDY) == 0);
    IoWrite8 ((UINT16) SERIAL_PORT_IO, *Buffer++);
  }
}

// Output a UINT8 data's Hex value
VOID
SerialOutU8Data (
  IN UINT8  Data
  )
{
  UINT8 High;
  UINT8 Low;
  High = (Data & 0xF0) >> 4;
  High = High > 0x9 ? High + 0x37 : High + 0x30;
  Low = Data & 0x0F;
  Low = Low > 0x9 ? Low + 0x37 : Low + 0x30;
  SerialOut (High);
  SerialOut (Low);
}

// Output a UINT16 data's Hex value
VOID
SerialOutU16Data(
  IN UINT16  Data
  )
{
  SerialOutU8Data((Data & 0xFF00) >> 8);
  SerialOutU8Data((Data & 0x00FF));
}

// Output a UINT32 data's Hex value
VOID
SerialOutU32Data(
  IN UINT32  Data
  )
{
  SerialOutU16Data((Data & 0xFFFF0000) >> 16);
  SerialOutU16Data((Data & 0x0000FFFF));
}

// Output a UINT64 data's Hex value
VOID
SerialOutU64Data(
  IN UINT64  Data
  )
{
  SerialOutU32Data((Data & 0xFFFFFFFF00000000) >> 32);
  SerialOutU32Data((Data & 0x00000000FFFFFFFF));
}

// Dump Buffer's Hex value
VOID
SerialDumpHex (
  IN UINT8  *Data,
  IN UINTN  Size
  )
{
  UINTN   RestSize;
  UINTN   Left;
  UINTN   Index;
  UINTN   IndexCol;
#define COLUME_SIZE  (16)
  SerialOutput ("Dump data from: ");
  SerialOutU32Data ((UINT32) (UINTN) Data);
  SerialOut('\n');
  for (Index = 0; Index < Size; Index += COLUME_SIZE) {
    RestSize = Size - Index;
    Left = RestSize > COLUME_SIZE ? COLUME_SIZE : RestSize;
    //
    // Print Data
    //
    for (IndexCol = 0; IndexCol < Left; IndexCol++) {
      SerialOutU8Data(Data[Index + IndexCol]);
      SerialOut(' ');
    }
    //
    // Next line
    //
    SerialOut('\r');
    SerialOut('\n');
  }
}