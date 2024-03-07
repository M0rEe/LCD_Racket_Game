#include "LCD_interface.h"
#include "DIO_interface.h"
#include "util/delay.h"
#include "string.h"

#if LCD_4BIT == ENABLED

static void LCD_4_bit_voidShift(u8 copy_u8Data);
static void LCD_4_bit_voidPulse(void);
static void atoi(u16 copy_u16Number, u8 *copy_Char, u8 copy_u8ArraySize);

#define swap(a, b) \
    do             \
    {              \
        a = a ^ b; \
        b = a ^ b; \
        a = a ^ b; \
    } while (0)

static void atoi(u16 copy_u16Number, u8 *copy_pu8Char, u8 copy_u8ArraySize)
{

    /* convert number into array */
    memset((char *)copy_pu8Char, '\0', copy_u8ArraySize);

    u8 *tempPtr = copy_pu8Char;

    while (copy_u16Number != 0)
    {
        *tempPtr++ = '0' + (copy_u16Number % 10);
        copy_u16Number /= 10;
    }

    /* reverse array */
    u8 start = 0;
    u8 end = copy_u8ArraySize - 1;
    // move end of array to first digit
    while (copy_pu8Char[end] == '\0' && end > 0)
    {
        end--;
    }
    // swap array elemnts left to right
    while (start < end)
    {
        swap(copy_pu8Char[start], copy_pu8Char[end]);
        start++;
        end--;
    }
}

static void LCD_4_bit_voidPulse(void)
{
    DIO_voidSetPinValue(LCD_4_BIT_EN_PORT, LCD_4_BIT_EN_PIN, DIO_PIN_HIGH); // Pulse Enable pin
    _delay_us(50);
    DIO_voidSetPinValue(LCD_4_BIT_EN_PORT, LCD_4_BIT_EN_PIN, DIO_PIN_LOW); // Pulse Enable pin
    _delay_us(50);
}

static void LCD_4_bit_voidShift(u8 data)
{
    DIO_voidSetPinValue(LCD_4_BIT_D4_PORT, LCD_4_BIT_D4_PIN, ((data >> 0) & 0x01));
    DIO_voidSetPinValue(LCD_4_BIT_D5_PORT, LCD_4_BIT_D5_PIN, ((data >> 1) & 0x01));
    DIO_voidSetPinValue(LCD_4_BIT_D6_PORT, LCD_4_BIT_D6_PIN, ((data >> 2) & 0x01));
    DIO_voidSetPinValue(LCD_4_BIT_D7_PORT, LCD_4_BIT_D7_PIN, ((data >> 3) & 0x01));
}

static void LCD_4_BIT_voidSendData(u8 data)
{

    LCD_4_bit_voidShift(data >> 4);                                         // write command to data pins
    DIO_voidSetPinValue(LCD_4_BIT_RW_PORT, LCD_4_BIT_RW_PIN, DIO_PIN_LOW);  // select write operation
    DIO_voidSetPinValue(LCD_4_BIT_RS_PORT, LCD_4_BIT_RS_PIN, DIO_PIN_HIGH); // Select data Regsiter
    LCD_4_bit_voidPulse();

    LCD_4_bit_voidShift(data);                                              // write command to data pins
    DIO_voidSetPinValue(LCD_4_BIT_RW_PORT, LCD_4_BIT_RW_PIN, DIO_PIN_LOW);  // select write operation
    DIO_voidSetPinValue(LCD_4_BIT_RS_PORT, LCD_4_BIT_RS_PIN, DIO_PIN_HIGH); // Select Instruction Regsiter
    LCD_4_bit_voidPulse();
}

/**
 * @return void
 * @param : copy_u8Command      LCD Command
 * @brief : Write given Command on LCD Datalines
 */
void LCD_4_bit_voidSendCommand(u8 copy_u8Command)
{
    LCD_4_bit_voidShift(copy_u8Command >> 4);                              // write command to data pins
    DIO_voidSetPinValue(LCD_4_BIT_RW_PORT, LCD_4_BIT_RW_PIN, DIO_PIN_LOW); // select write operation
    DIO_voidSetPinValue(LCD_4_BIT_RS_PORT, LCD_4_BIT_RS_PIN, DIO_PIN_LOW); // Select Instruction Regsiter
    LCD_4_bit_voidPulse();

    LCD_4_bit_voidShift(copy_u8Command);                                   // write command to data pins
    DIO_voidSetPinValue(LCD_4_BIT_RW_PORT, LCD_4_BIT_RW_PIN, DIO_PIN_LOW); // select write operation
    DIO_voidSetPinValue(LCD_4_BIT_RS_PORT, LCD_4_BIT_RS_PIN, DIO_PIN_LOW); // Select Instruction Regsiter
    LCD_4_bit_voidPulse();
}

/**
 * @return void
 * @brief : Initialize LCD
 */
void LCD_4_bit_voidInit(void)
{
    // * pins already initialized
    _delay_ms(40);
    LCD_4_bit_voidSendCommand(_LCD_RETURN_HOME);      //  Function set
    LCD_4_bit_voidSendCommand(_LCD_4BIT_MODE_2_LINE); //  Function set
    _delay_us(1000);
    LCD_4_bit_voidSendCommand(_LCD_DISPLAY_ON_UNDERLINE_OFF_CURSOR_ON); //  Display On / Control Off
    _delay_us(1000);
    LCD_4_bit_voidSendCommand(_LCD_CLEAR); //  Clear Screen
    _delay_us(2000);
    LCD_4_bit_voidSendCommand(_LCD_ENTRY_MODE_INC_SHIFT_OFF); //  Cursor On /blinking
    _delay_us(1000);
}

/**
 * @return void
 * @param : copy_u8Command      LCD Command
 * @brief : Write given Command on LCD Datalines
 */
void LCD_4_bit_voidWriteChar(u8 copy_u8Char)
{
    LCD_4_BIT_voidSendData(copy_u8Char);
}

/**
 * @return void
 * @param : copy_pu8Char        String To be printed on LCD
 * @param : copy_u8Line         Line Index of LCD
 * @param : copy_u8Col          Column Index of LCD
 * @brief : Write given String on LCD at line,column
 */
void LCD_4_bit_voidWriteStringAt(u8 *copy_pu8Char, u8 copy_u8Line, u8 copy_u8Col)
{
    LCD_4_bit_voidSetCursor(copy_u8Line, copy_u8Col);
    _delay_ms(1);
    while (*copy_pu8Char)
    {
        LCD_4_bit_voidWriteChar(*copy_pu8Char++);
    }
}

/**
 * @return void
 * @param : copy_u8Line         Line Index of LCD
 * @param : copy_u8Col          Column Index of LCD
 * @brief : Sets Cursour at given line column
 */
void LCD_4_bit_voidSetCursor(u8 copy_u8Line, u8 copy_u8Col)
{
    switch (copy_u8Line)
    {
    case 0:
        LCD_4_bit_voidSendCommand((LINE1 + copy_u8Col));
        break;

    case 1:
        LCD_4_bit_voidSendCommand((LINE2 + copy_u8Col));
        break;

    case 2:
        LCD_4_bit_voidSendCommand((LINE3 + copy_u8Col));
        break;

    case 3:
        LCD_4_bit_voidSendCommand((LINE4 + copy_u8Col));
        break;
    }
}

/**
 * @return void
 * @param : copy_u8Line         Line Index of LCD
 * @param : copy_u8Col          Column Index of LCD
 * @param : copy_u8Mempos       DDRAM Position
 * @brief : Write given Memory position on LCD
 */
void LCD_4_bit_voidWriteCustomChar(u8 copy_u8Line, u8 copy_u8Col, u8 copy_u8Mempos)
{
    LCD_4_bit_voidSetCursor(copy_u8Line, copy_u8Col);
    _delay_us(10);
    LCD_4_bit_voidWriteChar(copy_u8Mempos);
}

/**
 * @return void
 * @param : copy_pu8Char        Pointer to String
 * @param : copy_u8Mempos       DDRAM Position
 * @brief : Write given Character on CGRAM
 */
void LCD_4_bit_voidCreateCustomChar(u8 *copy_pu8Char, u8 copy_u8Mempos)
{
    LCD_4_bit_voidSendCommand((_LCD_CGRAM_START + (copy_u8Mempos * 8)));
    for (u8 i = 0; i < 8; i++)
    {
        LCD_4_BIT_voidSendData(copy_pu8Char[i]);
    }
}

/**
 * @return void
 * @param : copy_u8Number       Integer number
 * @brief : Write number to LCD
 */
void LCD_4_bit_voidWriteInt(u16 copy_u16Number)
{
    u8 tempArr[7];
    u8 i = 0;
    atoi(copy_u16Number, tempArr, 7);
    while (tempArr[i] != '\0')
    {
        LCD_4_bit_voidWriteChar(tempArr[i]);
        i++;
    }
}
#endif

#if LCD_8BIT == ENABLED
static void LCD_8_BIT_Send_CMD(u8);
static void LCD_8BIT_INTIT_PINS();

static void LCD_8_BIT_Send_CMD(u8 cmd)
{
    DIO_voidSetPinValue(LCD_8_BIT_EN_PORT, LCD_8_BIT_EN_PIN, DIO_PIN_HIGH); // Pulse Enable pin
    _delay_us(10);
    DIO_voidSetPinValue(LCD_8_BIT_D0_PORT, LCD_8_BIT_D0_PIN, ((cmd >> 0) & 0x01));
    DIO_voidSetPinValue(LCD_8_BIT_D1_PORT, LCD_8_BIT_D1_PIN, ((cmd >> 1) & 0x01));
    DIO_voidSetPinValue(LCD_8_BIT_D2_PORT, LCD_8_BIT_D2_PIN, ((cmd >> 2) & 0x01));
    DIO_voidSetPinValue(LCD_8_BIT_D3_PORT, LCD_8_BIT_D3_PIN, ((cmd >> 3) & 0x01));
    DIO_voidSetPinValue(LCD_8_BIT_D4_PORT, LCD_8_BIT_D4_PIN, ((cmd >> 4) & 0x01));
    DIO_voidSetPinValue(LCD_8_BIT_D5_PORT, LCD_8_BIT_D5_PIN, ((cmd >> 5) & 0x01));
    DIO_voidSetPinValue(LCD_8_BIT_D6_PORT, LCD_8_BIT_D6_PIN, ((cmd >> 6) & 0x01));
    DIO_voidSetPinValue(LCD_8_BIT_D7_PORT, LCD_8_BIT_D7_PIN, ((cmd >> 7) & 0x01));
    // write command onto data pins
    DIO_voidSetPinValue(LCD_8_BIT_RW_PORT, LCD_8_BIT_RW_PIN, DIO_PIN_LOW); // select write operation
    DIO_voidSetPinValue(LCD_8_BIT_RS_PORT, LCD_8_BIT_RS_PIN, DIO_PIN_LOW); // Select Instruction Regsiter

    DIO_voidSetPinValue(LCD_8_BIT_EN_PORT, LCD_8_BIT_EN_PIN, DIO_PIN_LOW); // Pulse Enable pin
}

static void LCD_8_BIT_Send_DATA(u8 data)
{
    DIO_voidSetPinValue(LCD_8_BIT_EN_PORT, LCD_8_BIT_EN_PIN, DIO_PIN_HIGH); // Pulse Enable pin
    _delay_us(10);
    DIO_voidSetPinValue(LCD_8_BIT_D0_PORT, LCD_8_BIT_D0_PIN, ((data >> 0) & 0x01));
    DIO_voidSetPinValue(LCD_8_BIT_D1_PORT, LCD_8_BIT_D1_PIN, ((data >> 1) & 0x01));
    DIO_voidSetPinValue(LCD_8_BIT_D2_PORT, LCD_8_BIT_D2_PIN, ((data >> 2) & 0x01));
    DIO_voidSetPinValue(LCD_8_BIT_D3_PORT, LCD_8_BIT_D3_PIN, ((data >> 3) & 0x01));
    DIO_voidSetPinValue(LCD_8_BIT_D4_PORT, LCD_8_BIT_D4_PIN, ((data >> 4) & 0x01));
    DIO_voidSetPinValue(LCD_8_BIT_D5_PORT, LCD_8_BIT_D5_PIN, ((data >> 5) & 0x01));
    DIO_voidSetPinValue(LCD_8_BIT_D6_PORT, LCD_8_BIT_D6_PIN, ((data >> 6) & 0x01));
    DIO_voidSetPinValue(LCD_8_BIT_D7_PORT, LCD_8_BIT_D7_PIN, ((data >> 7) & 0x01));
    // write Data onto data pins
    DIO_voidSetPinValue(LCD_8_BIT_RW_PORT, LCD_8_BIT_RW_PIN, DIO_PIN_LOW);  // select write operation
    DIO_voidSetPinValue(LCD_8_BIT_RS_PORT, LCD_8_BIT_RS_PIN, DIO_PIN_HIGH); // Select data Regsiter

    DIO_voidSetPinValue(LCD_8_BIT_EN_PORT, LCD_8_BIT_EN_PIN, DIO_PIN_LOW); // Pulse Enable pin
}

static void LCD_8BIT_INTIT_PINS()
{
    DIO_voidSetPinDirection(LCD_8_BIT_D0_PORT, LCD_8_BIT_D0_PIN, DIO_PIN_OUTPUT);
    DIO_voidSetPinDirection(LCD_8_BIT_D1_PORT, LCD_8_BIT_D1_PIN, DIO_PIN_OUTPUT);
    DIO_voidSetPinDirection(LCD_8_BIT_D2_PORT, LCD_8_BIT_D2_PIN, DIO_PIN_OUTPUT);
    DIO_voidSetPinDirection(LCD_8_BIT_D3_PORT, LCD_8_BIT_D3_PIN, DIO_PIN_OUTPUT);
    DIO_voidSetPinDirection(LCD_8_BIT_D4_PORT, LCD_8_BIT_D4_PIN, DIO_PIN_OUTPUT);
    DIO_voidSetPinDirection(LCD_8_BIT_D5_PORT, LCD_8_BIT_D5_PIN, DIO_PIN_OUTPUT);
    DIO_voidSetPinDirection(LCD_8_BIT_D6_PORT, LCD_8_BIT_D6_PIN, DIO_PIN_OUTPUT);
    DIO_voidSetPinDirection(LCD_8_BIT_D7_PORT, LCD_8_BIT_D7_PIN, DIO_PIN_OUTPUT);

    DIO_voidSetPinDirection(LCD_8_BIT_RS_PORT, LCD_8_BIT_RS_PIN, DIO_PIN_OUTPUT); // rs
    DIO_voidSetPinDirection(LCD_8_BIT_RW_PORT, LCD_8_BIT_RW_PIN, DIO_PIN_OUTPUT); // rw

    DIO_voidSetPinDirection(LCD_8_BIT_EN_PORT, LCD_8_BIT_EN_PIN, DIO_PIN_OUTPUT); // en
}

void LCD_8_bit_INIT(void)
{
    LCD_8BIT_INTIT_PINS();
    // * pins already initialized
    _delay_ms(30);
    LCD_8_BIT_Send_CMD(_LCD_8BIT_MODE_2_LINE);
    _delay_ms(5);

    LCD_8_BIT_Send_CMD(_LCD_DISPLAY_ON_UNDERLINE_OFF_CURSOR_ON);
    _delay_us(150);

    LCD_8_BIT_Send_CMD(_LCD_CLEAR);
    _delay_us(150);

    LCD_8_BIT_Send_CMD(_LCD_ENTRY_MODE_INC_SHIFT_OFF);
    _delay_us(150);

    // LCD_8_BIT_Send_CMD(_LCD_4BIT_MODE_2_LINE);

    LCD_8_BIT_Send_CMD(_LCD_DDRAM_START);
    LCD_8_bit_Set_Cursor(1, 0);
}

void LCD_8_bit_Write_Char(u8 ch)
{
    LCD_8_BIT_Send_DATA(ch);
}

void LCD_8_bit_Write_String_At(u8 *ptr, u8 line, u8 col)
{
    u8 *tempPtr = ptr;
    u8 offsetX = 0, offsetY = 0;
    while (*tempPtr != '\0')
    {
        LCD_8_bit_Set_Cursor((line + offsetX), (col + offsetY));
        LCD_8_bit_Write_Char(*tempPtr);
        tempPtr++;
        if (offsetY == 19)
        {
            offsetX = (offsetX + 1) % 5;
        }
        else
        {
        }
        offsetY = (offsetY + 1) % 20;
    }
}

void LCD_8_bit_Set_Cursor(u8 line, u8 col)
{
    switch (line)
    {
    case 1:
        LCD_8_BIT_Send_CMD((LINE1 + col));
        break;

    case 2:
        LCD_8_BIT_Send_CMD((LINE2 + col));
        break;

    case 3:
        LCD_8_BIT_Send_CMD((LINE3 + col));
        break;

    case 4:
        LCD_8_BIT_Send_CMD((LINE4 + col));
        break;

    default:
        break;
    }
}

void LCD_8_bit_Write_Custom_Char(u8 line, u8 col, u8 mempos)
{
    LCD_8_BIT_Send_CMD((_LCD_CGRAM_START + (mempos * 8)));
    LCD_8_bit_Set_Cursor(line, col);
    LCD_8_bit_Write_Char(mempos);
}
void LCD_8_bit_Create_Custom_Char(u8 *dataArr, u8 mempos)
{
    LCD_8_BIT_Send_CMD((_LCD_CGRAM_START + (mempos * 8)));
    for (u8 i = 0; i < 8; i++)
    {
        LCD_8_BIT_Send_DATA(dataArr[i]);
    }
}
#endif