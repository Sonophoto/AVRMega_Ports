
#include <Arduino.h>

#ifndef AVRMEGA_PORTS_H
#define AVRMEGA_PORTS_H
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
 * BASIC API FUNCTIONS
 * ******************************************************************************
 */
unsigned int readMega(unsigned int register_name);
unsigned int writeMega(unsigned int register_name, unsigned int data_byte);

void debugPorts();
void debugPorts(unsigned int register_name);


/* ******************************************************************************
 * API FUNCTIONS 
 * ******************************************************************************
 */

// FUNCTION: readMega() Reads register reg_name.
// Returns: data_byte read.
unsigned int readMega(unsigned int reg_name) {
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


// FUNCTION: writeMega() Writes the given data_byte to the given reg_name.
// Returns: MASK_SUCCESS on SUCCESS; MASK_FAILURE on FAILURE
unsigned int writeMega(unsigned int reg_name, unsigned int data_byte) {
   unsigned int data_write = 0;

   switch (reg_name) {
      case REGISTER_X: {
         data_write = ( (data_byte) & (MASK_REG_X) ); // Trim data with register's mask
         DDR_X |= (MASK_REG_X);                       // Set our data register to source output
         REG_X ^= REG_X;                              // Clear register
         REG_X |= data_write;                         // write ONLY our bits to register
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
         data_write = ( (data_byte) & (MASK_REG_CTRL) ); // Trim data with register's mask
         DDR_CTRL |= (MASK_REG_CTRL);                    // Set our data register to source output
         REG_CTRL &= ~(MASK_REG_CTRL);                   // Clear ONLY our bits, not entire register ;-)
         REG_CTRL |= data_write;                         // write ONLY our bits to register
         return MASK_SUCCESS;
      }
      case REGISTER_FLAG: {
         data_write = ( (data_byte) & (MASK_REG_FLAG) );
         DDR_FLAG |= (MASK_REG_FLAG);
         REG_FLAG &= ~(MASK_REG_FLAG);                   // Clear ONLY our bits, not entire register
         REG_FLAG |= data_write;                         // write ONLY our bits to register
         return MASK_SUCCESS;
      }
      default : {
         Serial.println("ERROR: BAD reg_name VALUE TO __FUNC__, __LINE__");
         debugPorts();
         return MASK_FAILURE;
      }
   } // End switch (reg_name)
} // End writeMega()

#endif // DEFINED AVRMEGA_PORTS_H
