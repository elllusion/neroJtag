/* 
 * Copyright (C) 2011 Chris McClelland
 *
 * This program is free software: you can redistribute it and/or modify
 * it under the terms of the GNU General Public License as published by
 * the Free Software Foundation, either version 3 of the License, or
 * (at your option) any later version.
 *
 * This program is distributed in the hope that it will be useful,
 * but WITHOUT ANY WARRANTY; without even the implied warranty of
 * MERCHANTABILITY or FITNESS FOR A PARTICULAR PURPOSE.  See the
 * GNU General Public License for more details.
 *  
 * You should have received a copy of the GNU General Public License
 * along with this program.  If not, see <http://www.gnu.org/licenses/>.
 */
#ifndef JTAG_H
#define JTAG_H

#include <types.h>

// Macros for NeroJTAG implementation
#define bmNEEDRESPONSE (1<<0)
#define bmISLAST       (1<<1)
#define bmSENDZEROS    (0<<2)
#define bmSENDONES     (1<<2)
#define bmSENDDATA     (2<<2)
#define bmSENDMASK     (3<<2)

// Bit masks on Port B for the four JTAG lines
enum {
	TCK = 0x80,
	TMS = 0x40,
	TDO = 0x20,
	TDI = 0x10
};

// Kick off a shift operation. Next time jtagExecuteShift() runs, it will execute the shift.
void jtagShiftBegin(uint32 numBits, uint8 flagByte);

// Return true if there's a shift operation pending
bool jtagIsShiftPending(void);

// Actually execute the shift operation initiated by jtagBeginShift(). This is done in a
// separate method because vendor commands cannot read & write to bulk endpoints.
void jtagShiftExecute(void);

// Transition the JTAG state machine to another state: clock "transitionCount" bits from
// "bitPattern" into TMS, LSB-first.
void jtagClockFSM(uint32 bitPattern, uint8 transitionCount);

// Keep TMS and TDI as they are, and clock the JTAG state machine "numClocks" times.
void jtagClocks(uint32 numClocks);

#endif