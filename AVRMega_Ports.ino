/* ******************************************************************************
 *                       AVR Mega Ports: A How-To
 *
 * A fairly complete example of how to use the double row of digital I/O pins
 * on "Arduino Mega" boards (Arduino pins 22-53) by direct access to the AVR
 * Mega 2560 Ports: PORTA PORTC PORTL and the lower nibbles of PORTB and PORTG.
 * 
 * This example teaches how to directly use IO pins by manipulating the control
 * registers of each pin. To simplify the process we use the Arduino prototyping
 * environment and the PORTx variables which map to the AVR Mega's registers.
 * ******************************************************************************
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

/* ******************************************************************************
 * BIT MASKS FOR NAMING 8-bit PORTS
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

#define REG_FLAG       PORTB
#define DDR_FLAG       DDRB
#define PIN_FLAG       PINB 
#define MASK_REG_FLAG  0x0F

#define REG_CTRL       PORTG
#define DDR_CTRL       DDRG
#define PIN_CTRL       PING 
#define MASK_REG_CTRL  0x0F

/* ******************************************************************************
 * UTILITY MASKS 
 * ******************************************************************************
 */
#define MASK_YES       0x01
#define MASK_NO        0x00

#define MASK_NULL      0x00
#define MASK_LOW       0x0F
#define MASK_HIGH      0xF0
#define MASK_FULL      0xFF

/* ******************************************************************************
 * 
 * ******************************************************************************
 */
#define NIBBLE_COUNTER_SIZE 64 
unsigned int nibble_counter[NIBBLE_COUNTER_SIZE] = {
   0x00, 0x01, 0x02, 0x03, 0x04, 0x05, 0x06, 0x07,
   0x08, 0x09, 0x0A, 0x0B, 0x0C, 0x0D, 0x0E, 0x0F
};

/* ******************************************************************************
 * BASIC API FUNCTIONS
 * ******************************************************************************
 */
unsigned int readMega(unsigned int port_name, unsigned int mask_name);
unsigned int writeMega(unsigned int port_name, unsigned int mask_name, unsigned int data_byte);
void debugPorts();

/* ******************************************************************************
 * FUNCTION IMPLEMENTATIONS
 * ******************************************************************************
 */

// FUNCTION:
// Returns: data_byte read.
unsigned int readMega(unsigned int port_name, unsigned int mask_name) {
   unsigned int data_read = 0;
   return data_read;
}


// FUNCTION:
// Returns: MASK_NULL on SUCCESS; MASK_FULL on FAILURE
unsigned int writeMega(unsigned int port_name, unsigned int mask_name, unsigned int data_byte) {
   if ( 1 ) {
      return MASK_NULL;
   } else { 
      return MASK_FULL;
   }
}


// FUNCTION:
// Returns: void
void debugPorts() {
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

}

void setup() {
   Serial.begin(115200);
   while( !Serial);
}

void loop() {
delay(1);
}

