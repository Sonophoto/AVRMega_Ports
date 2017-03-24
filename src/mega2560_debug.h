
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

#include <Arduino.h>
#include "mega2560_ports.h"

#ifndef _MEGA2560_DEBUG_H
   #define _MEGA2560_DEBUG_H

/* ******************************************************************************
 * DEBUG REGISTER FUNCTIONS
 * ******************************************************************************
 */

// FUNCTION: debugRegisters() Prints the values of Registers _X, _Y, _Z, _CTRL and _FLAG on Serial0
// Returns: void
// TODO: Re-Write to return a formatted string.
void debugRegisters() {
Serial.print("\n==============================================\n");
Serial.println("Begin register diagnostics");
Serial.println("Output Register, Direction Register, Input Register");
Serial.println("Register X");
Serial.println(REG_X, BIN);
Serial.println(DDR_X, BIN);
Serial.println(PIN_X, BIN);
Serial.println("Register Y");
Serial.println(REG_Y, BIN);
Serial.println(DDR_Y, BIN);
Serial.println(PIN_Y, BIN);
Serial.println("Register Z");
Serial.println(REG_Z, BIN);
Serial.println(DDR_Z, BIN);
Serial.println(PIN_Z, BIN);
Serial.println("Flags Register");
Serial.println(REG_FLAG & MASK_REG_FLAG, BIN);
Serial.println(DDR_FLAG & MASK_REG_FLAG, BIN);
Serial.println(PIN_FLAG & MASK_REG_FLAG,  BIN);
Serial.println("Control Register");
Serial.println(REG_CTRL & MASK_REG_CTRL, BIN);
Serial.println(DDR_CTRL & MASK_REG_CTRL, BIN);
Serial.println(PIN_CTRL & MASK_REG_CTRL, BIN);
Serial.println("End register diagnostics");
Serial.print(  "==============================================\n\n");
} // End debugRegisters()


// FUNCTION: debugRegister() Prints the value of register reg_name on Serial0
// Returns: void
// TODO: Re-Write to return a formatted string.
void debugRegister(unsigned int reg_name) {
   Serial.print("\n==============================================\n");
   Serial.println("Begin register diagnostics");
   Serial.println("Output Register, Direction Register, Input Register");
   switch(reg_name) {
   case REGISTER_X:
      Serial.println("Register X");
      Serial.println(REG_X, BIN);
      Serial.println(DDR_X, BIN);
      Serial.println(PIN_X, BIN);
      break;
   case REGISTER_Y:
      Serial.println("Register Y");
      Serial.println(REG_Y, BIN);
      Serial.println(DDR_Y, BIN);
      Serial.println(PIN_Y, BIN);
      break;
   case REGISTER_Z:
      Serial.println("Register Z");
      Serial.println(REG_Z, BIN);
      Serial.println(DDR_Z, BIN);
      Serial.println(PIN_Z, BIN);
      break;
   case REGISTER_CTRL:
      Serial.println("Control Register");
      Serial.println(REG_CTRL & MASK_REG_CTRL, BIN);
      Serial.println(DDR_CTRL & MASK_REG_CTRL, BIN);
      Serial.println(PIN_CTRL & MASK_REG_CTRL, BIN);
      break;
   case REGISTER_FLAG:
      Serial.println("Flags Register");
      Serial.println(REG_FLAG & MASK_REG_FLAG, BIN);
      Serial.println(DDR_FLAG & MASK_REG_FLAG, BIN);
      Serial.println(PIN_FLAG & MASK_REG_FLAG,  BIN);
      break;
   default:
      debugPorts();
      break;
   }
   Serial.println("End register diagnostics");
   Serial.print(  "==============================================\n\n");
} // End debugRegister()

#endif // DEFINED _MEGA2560_DEBUG_H
