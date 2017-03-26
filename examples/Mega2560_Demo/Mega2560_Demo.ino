/* ******************************************************************************
 *                       Mega2560_Demo: A Ports How-To
 *
 * A fairly complete example of how to use the double row of digital I/O pins
 * on "Arduino Mega" boards (Arduino pins 22-53) by direct access to the AVR
 * Mega 2560 Ports: PORTA PORTC PORTL and the lower nibbles of PORTB and PORTG.
 * 
 * This example teaches how to directly use IO pins by manipulating the control
 * registers of each pin. To simplify the process we use the Arduino prototyping
 * environment and the PORTx variables which map to the ATmega2560's registers.
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
   Serial.println("This software, Mega2560_Demo, intentionally left non-blank");
   delay(100000);
} // End loop()



