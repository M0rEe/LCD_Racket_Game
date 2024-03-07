#include "LCD_interface.h"
#include "DIO_interface.h"
#include "KEYPAD_interface.h"
#include "Animated_Obj.h"
#include "Std_Types.h"

#include <util/delay.h>

#include <time.h>
#include <stdlib.h>

#define randnum(min, max) \
  ((rand() % (int)(((max) + 1) - (min))) + (min))

u8 keybadMatrix[4][4] = {
    {'7', '8', '9', 'A'},
    {'4', '5', '6', 'B'},
    {'1', '2', '3', 'C'},
    {'*', '0', '#', 'D'}};

u8 Racket_CC[] = {
    0x00,
    0x0E,
    0x11,
    0x11,
    0x11,
    0x0E,
    0x04,
    0x04};

u8 Ball_CC[] = {
    0x00,
    0x0E,
    0x1F,
    0x1B,
    0x1F,
    0x0E,
    0x00,
    0x00};

int main()
{
  srand(time(NULL));
  DIO_voidInitPins();
  LCD_4_bit_voidInit();
  /* Creating Custom Char for Racket*/
  LCD_4_bit_voidCreateCustomChar(Racket_CC, 0);
  /* Creating Custom Char for Ball*/
  LCD_4_bit_voidCreateCustomChar(Ball_CC, 1);

  // Ball Initiale Position
  Moving_Obj ball;
  ball.currentCol = 2;
  ball.currentLine = 2;
  ball.prevCol = 1;
  ball.prevLine = 2;

  // LeftRacket Initiale Position
  Moving_Obj LeftRacket;
  LeftRacket.currentCol = 1;
  LeftRacket.currentLine = 1;

  // RightRacket Initiale Position
  Moving_Obj RightRacket;
  RightRacket.currentCol = 19;
  RightRacket.currentLine = 0;
  u8 KeyPressed;
  u8 isCollided = 0;

  while (1)
  {
    /* doesn't handle debounce */
    KEYPAD_voidGetChar(&KeyPressed, (u8 *)keybadMatrix);
    u8 tempVal;
    /* update each racket */
    switch (KeyPressed)
    {
    case '7':
      /* UP LEFT racket */
      LeftRacket.prevLine = LeftRacket.currentLine;
      tempVal = (++LeftRacket.currentLine) % 4;
      LeftRacket.currentLine = tempVal;
      break;

    case '4':
      /* DOWN LEFT racket */
      LeftRacket.prevLine = LeftRacket.currentLine;
      tempVal = (--LeftRacket.currentLine) % 4;
      LeftRacket.currentLine = tempVal;
      break;

    case '8':
      /* UP RIGHT racket */
      RightRacket.prevLine = RightRacket.currentLine;
      tempVal = (++RightRacket.currentLine) % 4;
      RightRacket.currentLine = tempVal;
      break;

    case '5':
      /* DOWN RIGHT racket */
      RightRacket.prevLine = RightRacket.currentLine;
      tempVal = (--RightRacket.currentLine) % 4;
      RightRacket.currentLine = tempVal;
      break;

    default:
      break;
    }
    /*inValidate Keypressed */
    KeyPressed = '0';

    if ((ball.currentCol == RightRacket.currentCol) && (ball.currentLine == RightRacket.currentLine)) // Rightracket collison detected
    {
      ball.currentCol--;                // bounced back
      ball.currentLine = randnum(0, 3); // choose random line go
      isCollided = 1;
    }
    else if ((ball.currentCol <= LeftRacket.currentCol) && (ball.currentLine == LeftRacket.currentLine)) // Left Racket collison detected
    {
      ball.prevCol = ball.currentCol;
      ball.currentCol++; // bounced back
      ball.currentLine = randnum(0, 3); // choose random line go
      isCollided = 1;
    }

    // ball choose path to go on up or down or middle
    if (isCollided == 0)
    {
      if (ball.prevCol < ball.currentCol) // ball moves right
      {
        ball.prevCol = (ball.currentCol++); // ball goes brrr
        if (ball.currentCol > 19)
        {
          // racket 1 scored
          LCD_4_bit_voidWriteStringAt((u8 *)"Racket 1 Scored !!", 2, 2);
          _delay_ms(450);
          ball.currentCol = 2;
          ball.currentLine = 2;
          ball.prevCol = 1;
          ball.prevLine = 2;
        }
      }
      else // ball moves left
      {
        ball.prevCol = (ball.currentCol--); // ball goes brrr
        if (ball.currentCol <= 1 || ball.currentCol > 19)
        {
          ball.currentCol = 1;
        }

        if (ball.currentCol <= 1 && (LeftRacket.currentLine != ball.currentLine))
        {
          // racket 1 scored
          LCD_4_bit_voidWriteStringAt((u8 *)"Racket 2 Scored !!", 2, 2);
          _delay_ms(450);
          ball.currentCol = 2;
          ball.currentLine = 2;
          ball.prevCol = 1;
          ball.prevLine = 2;
        }
      }
    }

    // inValidate collision
    isCollided = 0;
    // Erase last Frame from LCD
    LCD_4_bit_voidSendCommand(_LCD_CLEAR);
    _delay_ms(2);
    // Draw new positions on LCD
    LCD_4_bit_voidWriteCustomChar(LeftRacket.currentLine, LeftRacket.currentCol, 0);
    LCD_4_bit_voidWriteCustomChar(RightRacket.currentLine, RightRacket.currentCol, 0);
    LCD_4_bit_voidWriteCustomChar(ball.currentLine, ball.currentCol, 1);
    _delay_ms(100);
  }

  return 0;
}