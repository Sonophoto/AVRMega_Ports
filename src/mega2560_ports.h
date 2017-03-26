
 /* ******************************************************************************
  * BSD 2-Clause License
  *
  * Copyright (c) 2017, Brig Young, All rights reserved.
  *
  * Redistribution and use in source and binary forms, with or without
  * modification, are permitted provided that the following conditions are met:
  *
  * Redistributions of source code must retain the above copyright notice, this
  * list of conditions and the following disclaimer.
  *
  * Redistributions in binary form must reproduce the above copyright notice,
  * this list of conditions and the following disclaimer in the documentation
  * and/or other materials provided with the distribution.
  *
  * THIS SOFTWARE IS PROVIDED BY BRIG YOUNG AND CONTRIBUTORS "AS IS" AND ANY
  * EXPRESS OR IMPLIED WARRANTIES, INCLUDING, BUT NOT LIMITED TO, THE IMPLIED
  * WARRANTIES OF MERCHANTABILITY AND FITNESS FOR A PARTICULAR PURPOSE ARE
  * DISCLAIMED. IN NO EVENT SHALL BRIG YOUNG OR CONTRIBUTORS BE LIABLE FOR ANY
  * DIRECT, INDIRECT, INCIDENTAL, SPECIAL, EXEMPLARY, OR CONSEQUENTIAL DAMAGES
  * (INCLUDING, BUT NOT LIMITED TO, PROCUREMENT OF SUBSTITUTE GOODS OR 
  * SERVICES; LOSS OF USE, DATA, OR PROFITS; OR BUSINESS INTERRUPTION) HOWEVER
  * CAUSED AND ON ANY THEORY OF LIABILITY, WHETHER IN CONTRACT, STRICT LIABILITY,
  * OR TORT (INCLUDING NEGLIGENCE OR OTHERWISE) ARISING IN ANY WAY OUT OF THE
  * USE OF THIS SOFTWARE, EVEN IF ADVISED OF THE POSSIBILITY OF SUCH DAMAGE.
  * ******************************************************************************
  */


#ifndef _MEGA2560_PORTS_H
#define _MEGA2560_PORTS_H

#include <Arduino.h> // Source of our PORTx variables we are renaming


/* ******************************************************************************
 * BIT MASKS FOR SEMANTIC NAMING OF 8-bit REGISTERS 
 * ******************************************************************************
 */
#define REG_X          PORTA
#define DDR_X          DDRA
#define PIN_X          PINA 
#define MASK_REG_X     0xFF

#define REG_Y          PORTC
#define DDR_Y          DDRC
#define PIN_Y          PINC 
#define MASK_REG_Y     0xFF

#define REG_Z          PORTL
#define DDR_Z          DDRL
#define PIN_Z          PINL 
#define MASK_REG_Z     0xFF


/* ******************************************************************************
 * BIT MASKS FOR SEMANTIC NAMING OF 4-bit REGISTERS 
 * ******************************************************************************
 */
#define REG_FLAG       PORTB
#define DDR_FLAG       DDRB
#define PIN_FLAG       PINB 
#define MASK_REG_FLAG  0x0F

#define REG_CTRL       PORTG
#define DDR_CTRL       DDRG
#define PIN_CTRL       PING 
#define MASK_REG_CTRL  0x0F


/* ******************************************************************************
 * BIT MASKS FOR NAMING OUR REGISTERS IN FUNCTION CALLS
 * ******************************************************************************
 */
#define REGISTER_X     0x02
#define REGISTER_Y     0x04
#define REGISTER_Z     0x08
#define REGISTER_CTRL  0x20
#define REGISTER_FLAG  0x40


/* ******************************************************************************
 * UTILITY MASKS FOR SEMANTIC CLARITY IN CODING 
 * ******************************************************************************
 */
#define MASK_NULL        0x00
#define MASK_FULL        0xFF

#define MASK_YES         0x01
#define MASK_NO          0x00

#define MASK_FAILURE     0x00
#define MASK_SUCCESS     0x01

#define MASK_MODE_OUTPUT 0x00
#define MASK_MODE_INPUT  0x01

#define MASK_MODE_LO     0x00
#define MASK_MODE_HI     0x01

#define MASK_MODE_AND    0x02
#define MASK_MODE_OR     0x03
#define MASK_MODE_XOR    0x04
#define MASK_MODE_NOT    0x05
#define MASK_MODE_NAND   0x06
#define MASK_MODE_NOR    0x07

#define MASK_BYTE        0xFF
#define MASK_Lo_NIBBLE   0x0F
#define MASK_Hi_NIBBLE   0xF0

#define MASK_LoLo_NIB    0x03
#define MASK_LoHi_NIB    0x0C
#define MASK_HiLo_NIB    0x30     
#define MASK_HiHi_NIB    0xC0


/* ******************************************************************************
 * BASIC API FUNCTIONS
 * ******************************************************************************
 */

// DOCSTRING:
// RETURNS:
// STATUS: TESTED PASSED
unsigned int readMega(unsigned int register_name);

// DOCSTRING:
// RETURNS:
// STATUS: TESTED PASSED
unsigned int writeMega(unsigned int register_name, unsigned int data_byte);

// DOCSTRING:
// RETURNS:
// STATUS: UNIMPLEMENTED UNTESTED
unsigned int pinModeFast(unsigned int pin_number, unsigned int mask_mode);

// DOCSTRING:
// RETURNS:
// STATUS: UNIMPLEMENTED UNTESTED
unsigned int readMegaFast(unsigned int pin_number);

// DOCSTRING:
// RETURNS:
// STATUS: UNIMPLEMENTED UNTESTED
unsigned int writeMegaFast(unsigned int pin_number, unsigned int mask_pin);


/* ******************************************************************************
 * DEBUGGING API FUNCTIONS
 * ******************************************************************************
 */

// DOCSTRING: Prints the value of all registers on Serial0 (USB serial)
// RETURNS: VOID
// STATUS: TESTED PASSED
void debugRegisters();

// DOCSTRING: Prints the value of register reg_name on Serial0 (USB serial)
// RETURNS: VOID
// STATUS: TESTED PASSED
void debugRegister(unsigned int register_name);


// TODO:
/* ******************************************************************************
 * ADVANCED API FUNCTIONS
 * ******************************************************************************
 */

// DOCSTRING:
// RETURNS:
// STATUS: UNIMPLEMENTED UNTESTED
unsigned int writeMegaMasked(unsigned int register_name,
                             unsigned int mask_mode,
                             unsigned int mask_value,
                             unsigned int data_value);

// DOCSTRING:
// RETURNS:
// STATUS: UNIMPLEMENTED UNTESTED
unsigned int readMegaMasked(unsigned int register_name,
                            unsigned int mask_mode,
                            unsigned int mask_value);

#endif // DEFINED _MEGA2560_PORTS_H
