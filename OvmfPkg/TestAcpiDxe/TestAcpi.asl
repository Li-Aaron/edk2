/** @file

SPDX-License-Identifier: BSD-2-Clause-Patent

**/
DefinitionBlock (
  "TestAcpi.aml", // Output File Name
  "SSDT",         // Signature
  2,              // Version
  "OEMID",        // OEM ID
  "OEMTABLE",     // OEM Table ID
  0x00000001      // OEM Revision
  )
{
  Scope (\_SB)
  {
    Device (TEST)
    {
      Name (_HID, "ACPI0012")
      Name (_STR, Unicode ("Test ACPI Device"))
      Method (_STA, 0)
      {
        Return (0x0f)
      }

      // https://li-aaron.github.io/2023/04/asl-code-intro4/
      OperationRegion (TEST, SystemMemory, 0xA5A5A5A5, 0xA5A5A5A5)
      Field (TEST, ByteAcc, NoLock, Preserve) {
        ITER, 32,  // Iteration
        //
        // 16 bit x 32 = 512 bits.
        //
        IBUF, 512, // Buffer
      }
      Method(EXEC, 0, Serialized) {
        Name (BUFF, Buffer(64){0}) //64 bytes = 512 bits.
        // BUFF[0] = 1
        // BUFF[1] = 1
        Store (0x1, Index(BUFF, 0))
        Store (0x1, Index(BUFF, 2)) //Buffer index is byte, IBUF index is word.
        Store (2, Local0)
        // BUFF[i] = BUFF[i-2] + BUFF[i-1]
        // i in [2, ITER) -- Local0
        While (LLess(Local0, ITER)) {
          Multiply (Local0, 2, Local1) // 1 Word = 2 Byte
          Store (DerefOf(Index(BUFF, Subtract(Local1, 3))),Local2)        // BUFF[i-2] higher byte
          ShiftLeft (Local2, 8, Local2)
          Add (Local2, DerefOf(Index(BUFF, Subtract(Local1, 4))), Local2) // BUFF[i-2] lower byte

          Store (DerefOf(Index(BUFF, Subtract(Local1, 1))),Local3)        // BUFF[i-1] higher byte
          ShiftLeft (Local3, 8, Local3)
          Add (Local3, DerefOf(Index(BUFF, Subtract(Local1, 2))), Local3) // BUFF[i-1] lower byte

          Add (Local2, Local3, Local4)

          Store (And(Local4, 0xFF), Index(BUFF, Local1))                  // BUFF[i] lower byte
          ShiftRight(Local4, 8, Local4)
          Store (And(Local4, 0xFF), Index(BUFF, Add(Local1, 1)))          // BUFF[i] higher byte
          Increment (Local0)
        }
        Store (BUFF, IBUF)
      }
    }
  }
}