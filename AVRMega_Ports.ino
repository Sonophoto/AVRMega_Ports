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

#define REGISTER_X     0x02
#define REGISTER_Y     0x04
#define REGISTER_Z     0x08
#define REGISTER_CTRL  0x20
#define REGISTER_FLAG  0x40

#define REGISTER_LIST_SIZE 5
unsigned int register_list[REGISTER_LIST_SIZE] = {
  REGISTER_X, REGISTER_Y, REGISTER_Z, REGISTER_CTRL, REGISTER_FLAG
};

/* ******************************************************************************
 * UTILITY MASKS 
 * ******************************************************************************
 */
#define MASK_NULL       0x00
#define MASK_FULL       0xFF

#define MASK_YES        0x01
#define MASK_NO         0x00

#define MASK_FAILURE    0x00
#define MASK_SUCCESS    0x01

#define MASK_BYTE       0xFF
#define MASK_Lo_NIBBLE  0x0F
#define MASK_Hi_NIBBLE  0xF0

#define MASK_LoLo_NIB   0x03
#define MASK_LoHi_NIB   0x0C
#define MASK_HiLo_NIB   0x30     
#define MASK_HiHi_NIB   0xC0

/* ******************************************************************************
 * We use these for our test and demo functions
 * ******************************************************************************
 */
#define NIBBLE_COUNTER_SIZE 16 
unsigned int nibble_counter[NIBBLE_COUNTER_SIZE] = {
   0x00, 0x01, 0x02, 0x03, 0x04, 0x05, 0x06, 0x07,
   0x08, 0x09, 0x0A, 0x0B, 0x0C, 0x0D, 0x0E, 0x0F
};

#define BYTE_COUNTER_SIZE 256
unsigned int byte_counter[BYTE_COUNTER_SIZE] = {
     0x00, 0x01, 0x02, 0x03, 0x04, 0x05, 0x06, 0x07,
     0x08, 0x09, 0x0a, 0x0b, 0x0c, 0x0d, 0x0e, 0x0f,
     0x10, 0x11, 0x12, 0x13, 0x14, 0x15, 0x16, 0x17,
     0x18, 0x19, 0x1a, 0x1b, 0x1c, 0x1d, 0x1e, 0x1f,
     0x20, 0x21, 0x22, 0x23, 0x24, 0x25, 0x26, 0x27,
     0x28, 0x29, 0x2a, 0x2b, 0x2c, 0x2d, 0x2e, 0x2f,
     0x30, 0x31, 0x32, 0x33, 0x34, 0x35, 0x36, 0x37,
     0x38, 0x39, 0x3a, 0x3b, 0x3c, 0x3d, 0x3e, 0x3f,
     0x40, 0x41, 0x42, 0x43, 0x44, 0x45, 0x46, 0x47,
     0x48, 0x49, 0x4a, 0x4b, 0x4c, 0x4d, 0x4e, 0x4f,
     0x50, 0x51, 0x52, 0x53, 0x54, 0x55, 0x56, 0x57,
     0x58, 0x59, 0x5a, 0x5b, 0x5c, 0x5d, 0x5e, 0x5f,
     0x60, 0x61, 0x62, 0x63, 0x64, 0x65, 0x66, 0x67,
     0x68, 0x69, 0x6a, 0x6b, 0x6c, 0x6d, 0x6e, 0x6f,
     0x70, 0x71, 0x72, 0x73, 0x74, 0x75, 0x76, 0x77,
     0x78, 0x79, 0x7a, 0x7b, 0x7c, 0x7d, 0x7e, 0x7f,
     0x80, 0x81, 0x82, 0x83, 0x84, 0x85, 0x86, 0x87,
     0x88, 0x89, 0x8a, 0x8b, 0x8c, 0x8d, 0x8e, 0x8f,
     0x90, 0x91, 0x92, 0x93, 0x94, 0x95, 0x96, 0x97,
     0x98, 0x99, 0x9a, 0x9b, 0x9c, 0x9d, 0x9e, 0x9f,
     0xa0, 0xa1, 0xa2, 0xa3, 0xa4, 0xa5, 0xa6, 0xa7,
     0xa8, 0xa9, 0xaa, 0xab, 0xac, 0xad, 0xae, 0xaf,
     0xb0, 0xb1, 0xb2, 0xb3, 0xb4, 0xb5, 0xb6, 0xb7,
     0xb8, 0xb9, 0xba, 0xbb, 0xbc, 0xbd, 0xbe, 0xbf,
     0xc0, 0xc1, 0xc2, 0xc3, 0xc4, 0xc5, 0xc6, 0xc7,
     0xc8, 0xc9, 0xca, 0xcb, 0xcc, 0xcd, 0xce, 0xcf,
     0xd0, 0xd1, 0xd2, 0xd3, 0xd4, 0xd5, 0xd6, 0xd7,
     0xd8, 0xd9, 0xda, 0xdb, 0xdc, 0xdd, 0xde, 0xdf,
     0xe0, 0xe1, 0xe2, 0xe3, 0xe4, 0xe5, 0xe6, 0xe7,
     0xe8, 0xe9, 0xea, 0xeb, 0xec, 0xed, 0xee, 0xef,
     0xf0, 0xf1, 0xf2, 0xf3, 0xf4, 0xf5, 0xf6, 0xf7,
     0xf8, 0xf9, 0xfa, 0xfb, 0xfc, 0xfd, 0xfe, 0xff
};

/* ******************************************************************************
 * BASIC API FUNCTIONS
 * ******************************************************************************
 */
unsigned int readMega(unsigned int reg_name, unsigned int mask_name);
unsigned int writeMega(unsigned int reg_name, unsigned int mask_name, unsigned int data_byte);
void debugPorts();

void setup() {
   Serial.begin(115200);
   while( !Serial);
}

void loop() {

     unsigned int test_status = 1;
     unsigned long write_count = 0;

  for (unsigned int rindex = 0; rindex < REGISTER_LIST_SIZE; rindex++) {
     Serial.print("Testing Register number: "); Serial.println(register_list[rindex]);
     unsigned int write_var, read_var = 0;

     switch (register_list[rindex]) {
        case REGISTER_X:
        case REGISTER_Y:
        case REGISTER_Z: {
           for (unsigned int cindex = 0; cindex < BYTE_COUNTER_SIZE; cindex++) {
              write_var = byte_counter[cindex];
              {
              (void)writeMega(register_list[rindex], 0x00, byte_counter[cindex]);
              write_count++;
              }
              read_var = readMega(register_list[rindex], 0x00);
              Serial.print("write_var is: "); Serial.println(write_var, BIN);
              Serial.print(" read_var is: "); Serial.println(read_var, BIN);
              if ( !(write_var == read_var) ) {
                 test_status = 0;
                 Serial.println("FAILED TEST AT __FUNC__, __LINE__");
                 Serial.print("write_var is: "); Serial.println(write_var, BIN);
                 Serial.print(" read_var is: "); Serial.println(read_var, BIN);
                 debugRegister(register_list[rindex]);
              }
           }
           break;
        }// End 8 bit cases
        case REGISTER_CTRL:
        case REGISTER_FLAG: {
           for (unsigned int cindex = 0; cindex < NIBBLE_COUNTER_SIZE; cindex++) {
              write_var = byte_counter[cindex];
              {
              (void)writeMega(register_list[rindex], 0x00, nibble_counter[cindex]);
              write_count++;
              }
              read_var = readMega(register_list[rindex], 0x00);
              Serial.print("write_var is: "); Serial.println(write_var, BIN);
              Serial.print(" read_var is: "); Serial.println(read_var, BIN);
              if ( !(write_var == read_var) ) {
                 test_status = 0;
                 Serial.println("FAILED TEST AT __FUNC__, __LINE__");
                 Serial.print("write_var is: "); Serial.println(write_var, BIN);
                 Serial.print(" read_var is: "); Serial.println(read_var, BIN);
                 debugRegister(register_list[rindex]);
              }
           }
           break;
        } // end 4 bit cases
     } // End switch (register_list[rindex])
  } // End for(rindex)
   if (test_status) {
      Serial.println("ALL TESTS PASSED");
      Serial.print("Number of writes: "); Serial.println(write_count);
   }
   delay(100000);
} // End loop()


/* ******************************************************************************
 * FUNCTION IMPLEMENTATIONS
 * ******************************************************************************
 */

// FUNCTION:
// Returns: data_byte read.
unsigned int readMega(unsigned int reg_name, unsigned int mask_name) {
   unsigned int data_read = 0;

   switch (reg_name) { 
      case REGISTER_X: {
         DDR_X &= ~(MASK_REG_X);    // Set AVRMega pins to receive input (1 clock)
         data_read = (PIN_X);       // Capture data bits                 (1 clock)
         data_read &= (MASK_REG_X); // Only save OUR bits                (1 clock)
         break;                     //                                   (1 clock)
      }
      case REGISTER_Y: {
         DDR_Y &= ~(MASK_REG_Y);
         data_read = (PIN_Y);
         data_read &= (MASK_REG_Y);
         break;
      }
      case REGISTER_Z: {
         DDR_Z &= ~(MASK_REG_Z);
         data_read = (PIN_Z);
         data_read &= (MASK_REG_Z);
         break;
      }
      case REGISTER_CTRL: {            // ONLY USE THE LOWER 4 BITS OF REGISTER_CTRL
         DDR_CTRL &= ~(MASK_REG_CTRL); // CRITICAL: Set ONLY our AVRMega Pins to receive input
         data_read = (PIN_CTRL);       // Capture data bits from entire register
         data_read &= (MASK_REG_CTRL); // Clear data bits in the high nibble.
         break;
      }
      case REGISTER_FLAG: {            // ONLY USE THE LOWER 4 BITS OF REGISTER_FLAG
         DDR_FLAG &= ~(MASK_REG_FLAG); // CRITICAL: Set ONLY our AVRMega Pins to receive input
         data_read = (PIN_FLAG);
         data_read &= (MASK_REG_FLAG);
         break;
      }
      default : {
         Serial.println("ERROR: BAD reg_name VALUE TO __FUNC__, __LINE__");
         Serial.print("reg_name value: "); Serial.println(reg_name);
         debugPorts();
         return MASK_FAILURE;
      }
   } // End switch (reg_name)
   return data_read;
} // End readMega()


// FUNCTION:
// Returns: MASK_NULL on SUCCESS; MASK_FULL on FAILURE
unsigned int writeMega(unsigned int reg_name, unsigned int mask_name, unsigned int data_byte) {
   unsigned int data_write = 0;

   switch (reg_name) {
      case REGISTER_X: {
         data_write = ( (data_byte) & (MASK_REG_X) ); // Trim data with register's mask
         DDR_X |= (MASK_REG_X);                       // Set our data register to source output
         REG_X ^= REG_X;                              // Clear existing data
         REG_X |= data_write;                         // write register with our bits
         return MASK_SUCCESS;
      }
      case REGISTER_Y: {
         data_write = ( (data_byte) & (MASK_REG_Y) );
         DDR_Y |= (MASK_REG_Y);
         REG_Y ^= REG_Y;
         REG_Y |= data_write;
         return MASK_SUCCESS;
      }
      case REGISTER_Z: {
         data_write = ( (data_byte) & (MASK_REG_Z) );
         DDR_Z |= (MASK_REG_Z);
         REG_Z ^= REG_Z;
         REG_Z |= data_write;
         return MASK_SUCCESS;
      }
      case REGISTER_CTRL: {
         data_write = ( (data_byte) & (MASK_REG_CTRL) );
         DDR_CTRL |= (MASK_REG_CTRL);
         REG_CTRL &= ~(MASK_REG_CTRL);                   // Clear ONLY our bits, not entire register ;-)
         REG_CTRL |= data_write;
         return MASK_SUCCESS;
      }
      case REGISTER_FLAG: {
         data_write = ( (data_byte) & (MASK_REG_FLAG) );
         DDR_FLAG |= (MASK_REG_FLAG);
         REG_FLAG &= ~(MASK_REG_FLAG);                   // Clear ONLY our bits, not entire register
         REG_FLAG |= data_write;
         return MASK_SUCCESS;
      }
      default : {
         Serial.println("ERROR: BAD reg_name VALUE TO __FUNC__, __LINE__");
         debugPorts();
         return MASK_FAILURE;
      }
   } // End switch (reg_name)
} // End writeMega()


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
} // End debugPorts()


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

