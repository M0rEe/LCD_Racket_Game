#ifndef __LCD_CONFIG__
#define __LCD_CONFIG__

#include "Std_Types.h"
#include "DIO_interface.h"

#define ENABLED             1
#define DISABLED            0

#define LCD_8BIT            DISABLED
#define LCD_4BIT            ENABLED


#if LCD_4BIT == ENABLED

#define LCD_4_BIT_NUM_OF_LINES        4

#define LCD_4_BIT_D4_PORT       DIO_PORTB
#define LCD_4_BIT_D4_PIN        DIO_PIN0

#define LCD_4_BIT_D5_PORT       DIO_PORTB
#define LCD_4_BIT_D5_PIN        DIO_PIN1

#define LCD_4_BIT_D6_PORT       DIO_PORTB
#define LCD_4_BIT_D6_PIN        DIO_PIN2

#define LCD_4_BIT_D7_PORT       DIO_PORTB
#define LCD_4_BIT_D7_PIN        DIO_PIN3

#define LCD_4_BIT_RS_PORT       DIO_PORTB
#define LCD_4_BIT_RS_PIN        DIO_PIN4

#define LCD_4_BIT_RW_PORT       DIO_PORTB
#define LCD_4_BIT_RW_PIN        DIO_PIN5

#define LCD_4_BIT_EN_PORT       DIO_PORTB
#define LCD_4_BIT_EN_PIN        DIO_PIN6


#endif

#if LCD_8BIT == ENABLED
#define LCD_8_BIT_NUM_OF_LINES        2

#define LCD_8_BIT_D0_PORT       DIO_PORTC
#define LCD_8_BIT_D0_PIN        DIO_PIN0

#define LCD_8_BIT_D1_PORT       DIO_PORTC
#define LCD_8_BIT_D1_PIN        DIO_PIN1

#define LCD_8_BIT_D2_PORT       DIO_PORTC
#define LCD_8_BIT_D2_PIN        DIO_PIN2

#define LCD_8_BIT_D3_PORT       DIO_PORTC
#define LCD_8_BIT_D3_PIN        DIO_PIN3

#define LCD_8_BIT_D4_PORT       DIO_PORTC
#define LCD_8_BIT_D4_PIN        DIO_PIN4

#define LCD_8_BIT_D5_PORT       DIO_PORTC
#define LCD_8_BIT_D5_PIN        DIO_PIN5

#define LCD_8_BIT_D6_PORT       DIO_PORTC
#define LCD_8_BIT_D6_PIN        DIO_PIN6

#define LCD_8_BIT_D7_PORT       DIO_PORTC
#define LCD_8_BIT_D7_PIN        DIO_PIN7

#define LCD_8_BIT_RS_PORT       DIO_PORTD
#define LCD_8_BIT_RS_PIN        DIO_PIN4

#define LCD_8_BIT_RW_PORT       DIO_PORTD
#define LCD_8_BIT_RW_PIN        DIO_PIN5

#define LCD_8_BIT_EN_PORT       DIO_PORTD
#define LCD_8_BIT_EN_PIN        DIO_PIN6



#endif


#endif //__LCD_CONFIG__ 