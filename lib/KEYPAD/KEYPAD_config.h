#ifndef __KEYPAD_CONFIG__
#define __KEYPAD_CONFIG__

#include "DIO_interface.h"


#define HIGH            DIO_PIN_HIGH
#define LOW             DIO_PIN_LOW

#define MAX_ROW_SIZE    4
#define MAX_COL_SIZE    4

//TODO support MORE OR LESS PINS 
//depends on pins are pulled high or low 
#define ACTIVATOR       LOW
#define NOT_ACTIVATOR   HIGH

/* Rows*/
#define ROW1_PORT   DIO_PORTA
#define ROW2_PORT   DIO_PORTA
#define ROW3_PORT   DIO_PORTA
#define ROW4_PORT   DIO_PORTA

#define ROW1_PIN    DIO_PIN0
#define ROW2_PIN    DIO_PIN1
#define ROW3_PIN    DIO_PIN2
#define ROW4_PIN    DIO_PIN3
/* Columns*/
#define COL1_PORT   DIO_PORTA
#define COL2_PORT   DIO_PORTA
#define COL3_PORT   DIO_PORTA
#define COL4_PORT   DIO_PORTA

#define COL1_PIN    DIO_PIN4
#define COL2_PIN    DIO_PIN5
#define COL3_PIN    DIO_PIN6
#define COL4_PIN    DIO_PIN7

#endif

// If size of rows or cols changes array must be //!UPDATED  


