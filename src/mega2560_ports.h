
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
