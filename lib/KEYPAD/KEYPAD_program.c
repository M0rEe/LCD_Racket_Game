#include "KEYPAD_interface.h"
#include "util/delay.h"

static int rowPins[MAX_ROW_SIZE] = {ROW1_PIN, ROW2_PIN, ROW3_PIN, ROW4_PIN};
static int rowPorts[MAX_ROW_SIZE] = {ROW1_PORT, ROW2_PORT, ROW3_PORT, ROW4_PORT};

static int colPins[MAX_COL_SIZE] = {COL1_PIN, COL2_PIN, COL3_PIN, COL4_PIN};
static int colPorts[MAX_COL_SIZE] = {COL1_PORT, COL2_PORT, COL3_PORT, COL4_PORT};


/**
 * @return u8
 * @param : copy_pu8CharPressed         KeyPad Keyp Pressed
 * @param : copy_pu8KeypadMatrix        KeyPad Matrix
 * @brief : Returns Value from given matrix ampped to keypressed
 */
void KEYPAD_voidGetChar(u8 *copy_pu8CharPressed, const u8 *copy_pu8KeypadMatrix)
{
    
    // *Keypad Pins already initialized through DIO_INIT
    u8 Row, Col;
    u8 tempValue = 0;

    for (Row = 0; Row < MAX_ROW_SIZE; Row++)
    {
        // Apply Activator value on row pin and chech each col if low
        DIO_voidSetPinValue(rowPorts[Row], rowPins[Row], ACTIVATOR);
        for (Col = 0; Col < MAX_COL_SIZE; Col++)
        {
            DIO_voidGetPinValue(colPorts[Col], colPins[Col], &tempValue);
            if (tempValue == ACTIVATOR)
            {
                _delay_ms(50);
                DIO_voidGetPinValue(colPorts[Col], colPins[Col], &tempValue);
                *copy_pu8CharPressed = *((copy_pu8KeypadMatrix + Row * MAX_ROW_SIZE) + Col);
                DIO_voidSetPinValue(rowPorts[Row], rowPins[Row], NOT_ACTIVATOR);
                return ;
            }
        }
        DIO_voidSetPinValue(rowPorts[Row], rowPins[Row], NOT_ACTIVATOR);
    }
    return ;
    

}
