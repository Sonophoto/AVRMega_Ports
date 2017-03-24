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
 #include "../avrmega_ports.h"
 #include "../avrmega_testdebug.h"
/* ******************************************************************************
 * DEBUGGING BITS
 * ******************************************************************************
 */
// #define DEBUG_AVRMEGA_REGISTERS
// #define DEBUG_AVRMEGA_TIMERS

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

   unsigned int test_status = 1;
   unsigned long write_count = 0;

   Serial.println("Beginning Counter Test Suite on AVR Mega 2560 Ports");
   Serial.println("");

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
               (void)writeMega(register_list[rindex], byte_counter[cindex]);
               write_count++;
               }
               read_var = readMega(register_list[rindex]);
#ifdef DEBUG_AVRMEGA_REGISTERS
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
            for (unsigned int cindex = 0; cindex < NIBBLE_COUNTER_SIZE; cindex++) {
               write_var = byte_counter[cindex];
               {
               (void)writeMega(register_list[rindex], nibble_counter[cindex]);
               write_count++;
               }
               read_var = readMega(register_list[rindex]);
#ifdef DEBUG_AVRMEGA_REGISTERS
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

   if (test_status) {
      Serial.println("ALL TESTS PASSED");
      Serial.print("Number of writes: "); Serial.println(write_count);
   }
   delay(15000);
} // End loop()



