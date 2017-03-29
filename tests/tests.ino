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

#include <mega2560_ports.h>

/* ******************************************************************************
 * DEBUGGING BITS
 * ******************************************************************************
 */
// #define DEBUG_MEGA2560_READWRITE 
// #define DEBUG_MEGA2560_WRITEMASKED
// #define DEBUG_MEGA2560_READMASKED
// #define DEBUG_MEGA2560_TIMERS

/* ******************************************************************************
 * We use these for our test and demo functions

 * ******************************************************************************
 */


#define MASK_MODE_TESTING 170
#define MASK_MODE_LIST_SIZE 6
unsigned char mask_mode_list[MASK_MODE_LIST_SIZE] = {
   MASK_MODE_AND, MASK_MODE_OR, MASK_MODE_XOR, MASK_MODE_NOT, MASK_MODE_NAND, MASK_MODE_NOR
};

#define REGISTER_LIST_SIZE 5
unsigned char register_list[REGISTER_LIST_SIZE] = {
REGISTER_X, REGISTER_Y, REGISTER_Z, REGISTER_CTRL, REGISTER_FLAG
};

#define NIBBLE_COUNTER_SIZE 16 
unsigned char nibble_counter[NIBBLE_COUNTER_SIZE] = {
   0x00, 0x01, 0x02, 0x03, 0x04, 0x05, 0x06, 0x07,
   0x08, 0x09, 0x0A, 0x0B, 0x0C, 0x0D, 0x0E, 0x0F
};

#define BYTE_COUNTER_SIZE 256
unsigned char byte_counter[BYTE_COUNTER_SIZE] = {
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


// FUNCTION: Acccepts a mask_mode and a data_value, performs mask_mode on data_value
// RETURNS:  Masked data_value
unsigned char switchMaskMode(unsigned char mask_mode, unsigned char data_value);

/* ******************************************************************************
 * Arduino Setup()
 * ******************************************************************************
 */
void setup() {
   Serial.begin(115200);
   while( !Serial);
   }


/* ******************************************************************************
 * Arduino Loop()
 * ******************************************************************************
 */
void loop() {
   unsigned long write_count = 0; // keep track of how many "write" we do

/* ******************************************************************************
 * BEGIN readMega() and writeMega() TEST SECTION
 */
   unsigned char test_status = 1; // We only need/want to init this once

   Serial.println("");
   Serial.println("Beginning Tests of readMega() and writeMega()");

   for (unsigned char rindex = 0; rindex < REGISTER_LIST_SIZE; rindex++) {
      Serial.print("Testing Register number: "); Serial.println(register_list[rindex]);
      unsigned char write_var, read_var = 0;

      switch (register_list[rindex]) {
         case REGISTER_X:
         case REGISTER_Y:
         case REGISTER_Z: {
            for (unsigned char cindex = 0; cindex < BYTE_COUNTER_SIZE; cindex++) {
               write_var = byte_counter[cindex];
               {
               (void)writeMega(register_list[rindex], byte_counter[cindex]);
               write_count++;
               }
               read_var = readMega(register_list[rindex]);
#ifdef DEBUG_MEGA2560_READWRITE
               Serial.print("write_var is: "); Serial.println(write_var, BIN);
               Serial.print(" read_var is: "); Serial.println(read_var, BIN);
               debugRegister(register_list[rindex]);
#endif
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
            for (unsigned char cindex = 0; cindex < NIBBLE_COUNTER_SIZE; cindex++) {
               write_var = byte_counter[cindex];
               {
               (void)writeMega(register_list[rindex], nibble_counter[cindex]);
               write_count++;
               }
               read_var = readMega(register_list[rindex]);
#ifdef DEBUG_MEGA2560_READWRITE
               Serial.print("write_var is: "); Serial.println(write_var, BIN);
               Serial.print(" read_var is: "); Serial.println(read_var, BIN);
               debugRegister(register_list[rindex]);
#endif 
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


/* ******************************************************************************
 * BEGIN writeMegaMasked() TEST SECTION
 */
   Serial.println("");
   Serial.println("Beginning Tests of writeMegaMasked()");

   for (unsigned char rindex = 0; rindex < REGISTER_LIST_SIZE; rindex++) {
      Serial.print("Testing Register number: "); Serial.println(register_list[rindex]);
      unsigned char write_var, read_var, masked_write_var = 0;

      switch (register_list[rindex]) {
         case REGISTER_X:
         case REGISTER_Y:
         case REGISTER_Z: {                     // TODO BYTE_COUNTER_SIZE
            for (unsigned char cindex = 0; cindex < 1; cindex++) {
               for (unsigned char mindex = 3; mindex < MASK_MODE_LIST_SIZE; mindex++) {
                  masked_write_var = switchMaskMode(mask_mode_list[mindex], MASK_MODE_TESTING, byte_counter[cindex]);
                  Serial.print("masked_write_var: "); Serial.println(masked_write_var, BIN);
                  {
                     (void)writeMegaMasked(register_list[rindex], mask_mode_list[mindex], MASK_MODE_TESTING, byte_counter[cindex]);
                     write_count++;
                  }
                  read_var = readMega(register_list[rindex]);
               Serial.print("     read_var is: "); Serial.println(read_var, BIN);
#ifdef DEBUG_MEGA2560_WRITEMASKED
               Serial.print("masked_write_var is: "); Serial.println(masked_write_var, BIN);
               Serial.print("        read_var is: "); Serial.println(read_var, BIN);
               debugRegister(register_list[rindex]);
#endif 
                  if ( !(masked_write_var == read_var) ) {
                     test_status = 0;
                     Serial.println("FAILED TEST AT __FUNC__, __LINE__");
                     Serial.print("masked_write_var is: "); Serial.println(masked_write_var, BIN);
                     Serial.print("        read_var is: "); Serial.println(read_var, BIN);
                     //debugRegister(register_list[rindex]);
                  }
               } // End for (mindex)
            } // End for (cindex)
            break;

         }// End 8 bit cases
 
         case REGISTER_CTRL:
         case REGISTER_FLAG: {
            for (unsigned char cindex = 0; cindex < NIBBLE_COUNTER_SIZE; cindex++) {
               for (unsigned char mindex = 0; mindex < MASK_MODE_LIST_SIZE; mindex++) {

                  masked_write_var = switchMaskMode(mask_mode_list[mindex], MASK_MODE_TESTING, nibble_counter[cindex]);
                  Serial.print("masked_write_var: "); Serial.println(masked_write_var, BIN);
                  {
                     (void)writeMegaMasked(register_list[rindex], mask_mode_list[mindex], MASK_MODE_TESTING, nibble_counter[cindex]);
                     write_count++;
                  }
                  read_var = readMega(register_list[rindex]);
               Serial.print(" read_var is:     "); Serial.println(read_var, BIN);
#ifdef DEBUG_MEGA2560_WRITEMASKED
               Serial.print("masked_write_var is: "); Serial.println(masked_write_var, BIN);
               Serial.print(" read_var is: "); Serial.println(read_var, BIN);
               debugRegister(register_list[rindex]);
#endif 
                  if ( !(masked_write_var == read_var) ) {
                     test_status = 0;
                     Serial.println("FAILED TEST AT __FUNC__, __LINE__");
                     Serial.print("masked_write_var is: "); Serial.println(masked_write_var, BIN);
                     Serial.print("        read_var is: "); Serial.println(read_var, BIN);
                     //debugRegister(register_list[rindex]);
                  }
               } // End for (mindex)
            } // End for (cindex)
            break;
         } // End 4 bit cases
      } // End switch (register_list[rindex])
   } // End for(rindex)


/* ***********************************************************************************
 * End of Tests, evaluate results
 */

   if (test_status) {
      Serial.println("");
      Serial.println("****** TESTING SUMMARY ******");
      Serial.println("ALL TESTS PASSED");
      Serial.print("Number of writes: "); Serial.println(write_count);
   }
   delay(30000);
} // End loop()





/* ***********************************************************************************
 * 
 */

// FUNCTION: Acccepts a mask_mode and a data_value, performs mask_mode on data_value
// RETURNS:  Masked data_value
unsigned char switchMaskMode(unsigned char mask_mode, unsigned char mask_value, unsigned char data_value) {

      unsigned char data_masked = 0;
      Serial.println();
      Serial.println("Entering switchMaskMode()");
      Serial.print("  mask_mode: "); Serial.println(mask_mode, BIN);
      Serial.print(" mask_value: "); Serial.println(mask_value, BIN);
      Serial.print(" data_value: "); Serial.println(data_value, BIN);
  
   switch(mask_mode) {
      case MASK_MODE_AND: {
         data_masked = (data_value & mask_value);
      Serial.print("data_masked: "); Serial.println(data_masked, BIN);
         return data_masked;
         break;
      }
      case MASK_MODE_OR: {
         data_masked = (data_value | mask_value);
      Serial.print("data_masked: "); Serial.println(data_masked, BIN);
         return data_masked;
         break;
      }
      case MASK_MODE_XOR: {
         data_masked = (data_value ^ mask_value);
      Serial.print("data_masked: "); Serial.println(data_masked, BIN);
         return data_masked;
         break;
      }
      case MASK_MODE_NOT: {
         data_masked = (~(data_value));
      Serial.print("data_masked: "); Serial.println(data_masked, BIN);
         return data_masked;
         break;
      }
      case MASK_MODE_NAND: {
         data_masked = ( ~((data_value) & (mask_value)) );
      Serial.print("data_masked: "); Serial.println(data_masked, BIN);
         return data_masked;
         break;
      }
      case MASK_MODE_NOR: {
         data_masked = ( ~((data_value) | (mask_value)) );
      Serial.print("data_masked: "); Serial.println(data_masked, BIN);
         return data_masked;
         break;
      }
      default : {
         return MASK_FAILURE;
      }
   } // End switch (mask_mode)
}


