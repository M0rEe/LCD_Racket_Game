#include "Std_Types.h"
#include "DIO_interface.h"
#include "BitMath.h"
#include <avr/io.h>
#include "DIO_config.h"

/* Pin Apis */
#define ENABLED 1
#define DISABLED 0

#define ERR_DETECTION DISABLED

/**
 * @return void
 * @brief : Initialize all MCU Pins As defined in config file
 */
void DIO_voidInitPins(void)
{
    DDRA = PORTA_DIR;
    DDRB = PORTB_DIR;
    DDRC = PORTC_DIR;
    DDRD = PORTD_DIR;

    PORTA = PORTA_PULLUP;
    PORTB = PORTB_PULLUP;
    PORTC = PORTC_PULLUP;
    PORTD = PORTD_PULLUP;

    PORTA = PORTA_VALUE;
    PORTB = PORTB_VALUE;
    PORTC = PORTC_VALUE;
    PORTD = PORTD_VALUE;
}

/**
 * @return void
 * @param : copy_u8PortId       Port ID
 * @param : copy_u8PinId        Pin ID
 * @param : copy_u8PinDirection Pin Direction
 * @brief : Set given pin At port to Direction E.g, Input /Output
 */
void DIO_voidSetPinDirection(u8 copy_u8PortId, u8 copy_u8PinId, u8 copy_u8PinDirection)
{
/*Validate Input*/
#if ERR_DETECTION == ENABLED
    switch (copy_u8PortId)
    {
    case DIO_PORTA:
        if ((DIO_PIN0 <= copy_u8PinId) && (DIO_PIN7 >= copy_u8PinId))
        {
            if (DIO_PIN_OUTPUT == copy_u8PinDirection)
            {
                Set_Bit(PORTA, copy_u8PinId);
            }
            else if (DIO_PIN_INPUT == copy_u8PinDirection)
            {
                Clr_Bit(PORTA, copy_u8PinId);
            }
        }
        break;
    case DIO_PORTB:
        if ((DIO_PIN0 <= copy_u8PinId) && (DIO_PIN7 >= copy_u8PinId))
        {
            if (DIO_PIN_OUTPUT == copy_u8PinDirection)
            {
                Set_Bit(PORTB, copy_u8PinId);
            }
            else if (DIO_PIN_INPUT == copy_u8PinDirection)
            {
                Clr_Bit(PORTB, copy_u8PinId);
            }
        }
        break;
    case DIO_PORTC:
        if ((DIO_PIN0 <= copy_u8PinId) && (DIO_PIN7 >= copy_u8PinId))
        {
            if (DIO_PIN_OUTPUT == copy_u8PinDirection)
            {
                Set_Bit(PORTC, copy_u8PinId);
            }
            else if (DIO_PIN_INPUT == copy_u8PinDirection)
            {
                Clr_Bit(PORTC, copy_u8PinId);
            }
        }
        break;
    case DIO_PORTD:
        if ((DIO_PIN0 <= copy_u8PinId) && (DIO_PIN7 >= copy_u8PinId))
        {
            if (DIO_PIN_OUTPUT == copy_u8PinDirection)
            {
                Set_Bit(PORTD copy_u8PinId);
            }
            else if (DIO_PIN_INPUT == copy_u8PinDirection)
            {
                Clr_Bit(PORTD, copy_u8PinId);
            }
        }
        break;

    default:
        break;
    }
#else

    /*Perform Function */
    if (DIO_PIN_OUTPUT == copy_u8PinDirection)
    {
        switch (copy_u8PortId)
        {
        case DIO_PORTA:
            Set_Bit(DDRA, copy_u8PinId);
            break;
        case DIO_PORTB:
            Set_Bit(DDRB, copy_u8PinId);
            break;
        case DIO_PORTC:

            Set_Bit(DDRC, copy_u8PinId);
            break;
        case DIO_PORTD:

            Set_Bit(DDRD, copy_u8PinId);
            break;
        }
    }
    else if (DIO_PIN_INPUT == copy_u8PinDirection)
    {

        switch (copy_u8PortId)
        {
        case DIO_PORTA:
            Clr_Bit(DDRA, copy_u8PinId);
            break;
        case DIO_PORTB:
            Clr_Bit(DDRB, copy_u8PinId);
            break;
        case DIO_PORTC:
            Clr_Bit(DDRC, copy_u8PinId);
            break;
        case DIO_PORTD:
            Clr_Bit(DDRD, copy_u8PinId);
            break;
        }
    }
#endif
}

/**
 * @return void
 * @param : copy_u8PortId       Port ID
 * @param : copy_u8PinId        Pin ID
 * @param : copy_u8PinValue     Pin Value
 * @brief : Set given pin At port to Value E.g, High / Low
 */
void DIO_voidSetPinValue(u8 copy_u8PortId, u8 copy_u8PinId, u8 copy_u8PinValue)
{
/*Validate Input*/
#if ERR_DETECTION == ENABLED
    switch (copy_u8PortId)
    {
    case DIO_PORTA:
        if ((DIO_PIN0 <= copy_u8PinId) && (DIO_PIN7 >= copy_u8PinId))
        {
            if (DIO_PIN_HIGH == copy_u8PinValue)
            {
                Set_Bit(PINA, copy_u8PinId);
            }
            else if (DIO_PIN_LOW == copy_u8PinValue)
            {
                Clr_Bit(PINA, copy_u8PinId);
            }
        }
        break;
    case DIO_PORTB:
        if ((DIO_PIN0 <= copy_u8PinId) && (DIO_PIN7 >= copy_u8PinId))
        {
            if (DIO_PIN_HIGH == copy_u8PinValue)
            {
                Set_Bit(PINB, copy_u8PinId);
            }
            else if (DIO_PIN_LOW == copy_u8PinValue)
            {
                Clr_Bit(PINB, copy_u8PinId);
            }
        }
        break;
    case DIO_PORTC:
        if ((DIO_PIN0 <= copy_u8PinId) && (DIO_PIN7 >= copy_u8PinId))
        {
            if (DIO_PIN_HIGH == copy_u8PinValue)
            {
                Set_Bit(PINC, copy_u8PinId);
            }
            else if (DIO_PIN_LOW == copy_u8PinValue)
            {
                Clr_Bit(PINC, copy_u8PinId);
            }
        }
        break;
    case DIO_PORTD:
        if ((DIO_PIN0 <= copy_u8PinId) && (DIO_PIN7 >= copy_u8PinId))
        {
            if (DIO_PIN_HIGH == copy_u8PinValue)
            {
                Set_Bit(PIND, copy_u8PinId);
            }
            else if (DIO_PIN_LOW == copy_u8PinValue)
            {
                Clr_Bit(PIND, copy_u8PinId);
            }
        }
        break;
    default:
        break;
    }
#else

    /*Perform Function */
    switch (copy_u8PortId)
    {
    case DIO_PORTA:
        if (DIO_PIN_HIGH == copy_u8PinValue)
            Set_Bit(PORTA, copy_u8PinId);
        else if (DIO_PIN_LOW == copy_u8PinValue)
            Clr_Bit(PORTA, copy_u8PinId);
        break;

    case DIO_PORTB:
        if (DIO_PIN_HIGH == copy_u8PinValue)
            Set_Bit(PORTB, copy_u8PinId);
        else if (DIO_PIN_LOW == copy_u8PinValue)
            Clr_Bit(PORTB, copy_u8PinId);
        break;

    case DIO_PORTC:
        if (DIO_PIN_HIGH == copy_u8PinValue)
            Set_Bit(PORTC, copy_u8PinId);
        else if (DIO_PIN_LOW == copy_u8PinValue)
            Clr_Bit(PORTC, copy_u8PinId);
        break;

    case DIO_PORTD:
        if (DIO_PIN_HIGH == copy_u8PinValue)
            Set_Bit(PORTD, copy_u8PinId);
        else if (DIO_PIN_LOW == copy_u8PinValue)
            Clr_Bit(PORTD, copy_u8PinId);
        break;
    }
#endif
}

/**
 * @return void
 * @param : copy_u8PortId       Port ID
 * @param : copy_u8PinId        Pin ID
 * @param : *copy_pu8PinValue   pointer to Pin Value
 * @brief : Get pin Value at port E.g, High / Low
 */
void DIO_voidGetPinValue(u8 copy_u8PortId, u8 copy_u8PinId, u8 *copy_pu8PinValue)
{
/*Validate Input*/
#if ERR_DETECTION == ENABLED
    switch (copy_u8PortId)
    {
    case DIO_PORTA:
        if ((DIO_PIN0 <= copy_u8PinId) && (DIO_PIN7 >= copy_u8PinId))
        {
            *copy_pu8PinValue = Get_Bit(PINA, copy_u8PinId);
        }
        break;
    case DIO_PORTB:
        if ((DIO_PIN0 <= copy_u8PinId) && (DIO_PIN7 >= copy_u8PinId))
        {
            *copy_pu8PinValue = Get_Bit(PINB, copy_u8PinId);
        }
        break;
    case DIO_PORTC:
        if ((DIO_PIN0 <= copy_u8PinId) && (DIO_PIN7 >= copy_u8PinId))
        {
            *copy_pu8PinValue = Get_Bit(PINC, copy_u8PinId);
        }
        break;
    case DIO_PORTD:
        if ((DIO_PIN0 <= copy_u8PinId) && (DIO_PIN7 >= copy_u8PinId))
        {
            *copy_pu8PinValue = Get_Bit(PIND, copy_u8PinId);
        }
        break;
    default:
        break;
    }
#else
    /*Perform Function */
    switch (copy_u8PortId)
    {
    case DIO_PORTA:
        *copy_pu8PinValue = Get_Bit(PINA, copy_u8PinId);
        break;
    case DIO_PORTB:
        *copy_pu8PinValue = Get_Bit(PINB, copy_u8PinId);
        break;
    case DIO_PORTC:
        *copy_pu8PinValue = Get_Bit(PINC, copy_u8PinId);
        break;
    case DIO_PORTD:
        *copy_pu8PinValue = Get_Bit(PIND, copy_u8PinId);
        break;
    }
#endif
}

/**
 * @return void
 * @param : copy_u8PortId       Port ID
 * @param : copy_u8PinId        Pin ID
 * @brief : Toggles pin value
 */
void DIO_voidTogglePinValue(u8 copy_u8PortId, u8 copy_u8PinId)
{
/*Validate Input*/
#if ERR_DETECTION == ENABLED
    switch (copy_u8PortId)
    {
    case DIO_PORTA:
        if ((DIO_PIN0 <= copy_u8PinId) && (DIO_PIN7 >= copy_u8PinId))
        {
            Set_Bit(PORTA, copy_u8PinId);
        }
        break;
    case DIO_PORTB:
        if ((DIO_PIN0 <= copy_u8PinId) && (DIO_PIN7 >= copy_u8PinId))
        {
            Set_Bit(PORTB, copy_u8PinId);
        }
        break;
    case DIO_PORTC:
        if ((DIO_PIN0 <= copy_u8PinId) && (DIO_PIN7 >= copy_u8PinId))
        {
            Set_Bit(PORTC, copy_u8PinId);
        }
        break;
    case DIO_PORTD:
        if ((DIO_PIN0 <= copy_u8PinId) && (DIO_PIN7 >= copy_u8PinId))
        {
            Set_Bit(PORTD, copy_u8PinId);
        }
        break;
    default:
        break;
    }
#else
    /*Perform Function */

    switch (copy_u8PortId)
    {
    case DIO_PORTA:
        Tog_Bit(PORTA, copy_u8PinId);
        break;
    case DIO_PORTB:
        Tog_Bit(PORTB, copy_u8PinId);
        break;
    case DIO_PORTC:
        Tog_Bit(PORTC, copy_u8PinId);
        break;
    case DIO_PORTD:
        Tog_Bit(PORTD, copy_u8PinId);
        break;
    }
#endif
}

/**
 * @return void
 * @param : copy_u8PortId       Port ID
 * @param : copy_u8PinId        Pin ID
 * @brief : Activate Internal Pull-Up resistor
 */
void DIO_voidActivePinInPullUpResistance(u8 copy_u8PortId, u8 copy_u8PinId)
{
/*Validate Input*/
#if ERR_DETECTION == ENABLED
    switch (copy_u8PortId)
    {
    case DIO_PORTA:
        if ((DIO_PIN0 <= copy_u8PinId) && (DIO_PIN7 >= copy_u8PinId))
        {
            Set_Bit(PORTA, copy_u8PinId);
        }
        break;
    case DIO_PORTB:
        if ((DIO_PIN0 <= copy_u8PinId) && (DIO_PIN7 >= copy_u8PinId))
        {
            Set_Bit(PORTB, copy_u8PinId);
        }
        break;
    case DIO_PORTC:
        if ((DIO_PIN0 <= copy_u8PinId) && (DIO_PIN7 >= copy_u8PinId))
        {
            Set_Bit(PORTC, copy_u8PinId);
        }
        break;
    case DIO_PORTD:
        if ((DIO_PIN0 <= copy_u8PinId) && (DIO_PIN7 >= copy_u8PinId))
        {
            Set_Bit(PORTD, copy_u8PinId);
        }
        break;
    default:
        break;
    }
#else
    /*Perform Function */
    switch (copy_u8PortId)
    {
    case DIO_PORTA:
        Set_Bit(PORTA, copy_u8PinId);
        break;
    case DIO_PORTB:
        Set_Bit(PORTB, copy_u8PinId);
        break;
    case DIO_PORTC:
        Set_Bit(PORTC, copy_u8PinId);
        break;
    case DIO_PORTD:
        Set_Bit(PORTD, copy_u8PinId);
        break;
    }
#endif
}

/* Port Apis */

/**
 * @return void
 * @param : copy_u8PortId               Port ID
 * @param : copy_u8PortDirection        Port Direction
 * @brief : Set Whole Port into Input /Output
 */
void DIO_voidSetPortDirection(u8 copy_u8PortId, u8 copy_u8PortDirection)
{
/*Validate Input*/
#if ERR_DETECTION == ENABLED
    switch (copy_u8PortId)
    {
    case DIO_PORTA:
        if (DIO_PORT_INPUT == copy_u8PortDirection)
        {
            DDRA = DIO_PORT_INPUT;
        }
        else if (DIO_PORT_OUTPUT == copy_u8PortDirection)
        {
            DDRA = DIO_PORT_OUTPUT;
        }
        else
        {
            DDRA = copy_u8PortDirection;
        }
        break;
    case DIO_PORTB:
        if (DIO_PORT_INPUT == copy_u8PortDirection)
        {
            DDRB = DIO_PORT_INPUT;
        }
        else if (DIO_PORT_OUTPUT == copy_u8PortDirection)
        {
            DDRB = DIO_PORT_OUTPUT;
        }
        else
        {
            DDRB = copy_u8PortDirection;
        }
        break;
    case DIO_PORTC:
        if (DIO_PORT_INPUT == copy_u8PortDirection)
        {
            DDRC = DIO_PORT_INPUT;
        }
        else if (DIO_PORT_OUTPUT == copy_u8PortDirection)
        {
            DDRC = DIO_PORT_OUTPUT;
        }
        else
        {
            DDRC = copy_u8PortDirection;
        }
        break;
    case DIO_PORTD:
        if (DIO_PORT_INPUT == copy_u8PortDirection)
        {
            DDRD = DIO_PORT_INPUT;
        }
        else if (DIO_PORT_OUTPUT == copy_u8PortDirection)
        {
            DDRD = DIO_PORT_OUTPUT;
        }
        else
        {
            DDRD = copy_u8PortDirection;
        }
        break;
    default:
        break;
    }
#else
    /*Perform Function */
    switch (copy_u8PortId)
    {
    case DIO_PORTA:
        if (DIO_PORT_INPUT == copy_u8PortDirection)
        {
            DDRA = DIO_PORT_INPUT;
        }
        else if (DIO_PORT_OUTPUT == copy_u8PortDirection)
        {
            DDRA = DIO_PORT_OUTPUT;
        }
        else
        {
            DDRA = copy_u8PortDirection;
        }
        break;
    case DIO_PORTB:
        if (DIO_PORT_INPUT == copy_u8PortDirection)
        {
            DDRB = DIO_PORT_INPUT;
        }
        else if (DIO_PORT_OUTPUT == copy_u8PortDirection)
        {
            DDRB = DIO_PORT_OUTPUT;
        }
        else
        {
            DDRB = copy_u8PortDirection;
        }
        break;
    case DIO_PORTC:
        if (DIO_PORT_INPUT == copy_u8PortDirection)
        {
            DDRC = DIO_PORT_INPUT;
        }
        else if (DIO_PORT_OUTPUT == copy_u8PortDirection)
        {
            DDRC = DIO_PORT_OUTPUT;
        }
        else
        {
            DDRC = copy_u8PortDirection;
        }
        break;
    case DIO_PORTD:
        if (DIO_PORT_INPUT == copy_u8PortDirection)
        {
            DDRD = DIO_PORT_INPUT;
        }
        else if (DIO_PORT_OUTPUT == copy_u8PortDirection)
        {
            DDRD = DIO_PORT_OUTPUT;
        }
        else
        {
            DDRD = copy_u8PortDirection;
        }
        break;
    }
#endif
}

/**
 * @return void
 * @param : copy_u8PortId           Port ID
 * @param : copy_u8PortValue        Port Value
 * @brief : Set Whole Port Value into High Low E.g. 0x55 0xFF
 */
void DIO_voidSetPortValue(u8 copy_u8PortId, u8 copy_u8PortValue)
{
/*Validate Input*/
#if ERR_DETECTION == ENABLED
    if ((DIO_PORT_LOW <= copy_u8PortValue) && (DIO_PORT_HIGH >= copy_u8PortValue))
    {

        switch (copy_u8PortId)
        {
        case DIO_PORTA:

            PORTA = copy_u8PortValue;
            break;

        case DIO_PORTB:
            PORTB = copy_u8PortValue;
            break;

        case DIO_PORTC:
            PORTC = copy_u8PortValue;
            break;

        case DIO_PORTD:
            PORTD = copy_u8PortValue;
            break;
            break;
        default:
            break;
        }
    }
#else
    /*Perform Function */
    switch (copy_u8PortId)
    {
    case DIO_PORTA:
        PORTA = copy_u8PortValue;
        break;

    case DIO_PORTB:
        PORTB = copy_u8PortValue;
        break;

    case DIO_PORTC:
        PORTC = copy_u8PortValue;
        break;

    case DIO_PORTD:
        PORTD = copy_u8PortValue;
        break;
    }
#endif
}

/**
 * @return void
 * @param : copy_u8PortId           Port ID
 * @param : *copy_pu8PortValue      Pointer to Port Value
 * @brief : Get Whole Port Value
 */
void DIO_voidGetPortValue(u8 copy_u8PortId, u8 *copy_pu8PortValue)
{
    /*Validate Input*/
    /*Perform Function */
    switch (copy_u8PortId)
    {
    case DIO_PORTA:
        *copy_pu8PortValue = PINA;
        break;
    case DIO_PORTB:
        *copy_pu8PortValue = PINB;
        break;
    case DIO_PORTC:
        *copy_pu8PortValue = PINC;
        break;
    case DIO_PORTD:
        *copy_pu8PortValue = PIND;
        break;
    }
}

/**
 * @return void
 * @param : copy_u8PortId           Port ID
 * @brief : Toggles Port Value
 */
void DIO_voidTogglePortValue(u8 copy_u8PortId)
{
    /*Validate Input*/
    /*Perform Function */
    switch (copy_u8PortId)
    {
    case DIO_PORTA:
        PORTA = ~PORTA;
        break;
    case DIO_PORTB:
        PORTB = ~PORTB;
        break;
    case DIO_PORTC:
        PORTC = ~PORTC;
        break;
    case DIO_PORTD:
        PORTD = ~PORTD;
        break;
    }
}

/**
 * @return void
 * @param : copy_u8PortId           Port ID
 * @brief : Activate Port internal pull-up resistors
 */
void DIO_voidActivePortInPullUpResistance(u8 copy_u8PortId)
{
    /*Validate Input*/
    /*Perform Function */
    // ?? Disable all interrupts  (SFIOR ,PUD)
    switch (copy_u8PortId)
    {
    case DIO_PORTA:
        DDRA = DIO_PORT_INPUT;
        PORTA = DIO_PORT_HIGH;
        break;
    case DIO_PORTB:
        DDRB = DIO_PORT_INPUT;
        PORTB = DIO_PORT_HIGH;
        break;
    case DIO_PORTC:
        DDRC = DIO_PORT_INPUT;
        PORTC = DIO_PORT_HIGH;
        break;
    case DIO_PORTD:
        DDRD = DIO_PORT_INPUT;
        PORTD = DIO_PORT_HIGH;
        break;
    }
}
