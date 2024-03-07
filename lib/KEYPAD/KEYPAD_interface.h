#ifndef __KEYPAD_INTERFACE__
#define __KEYPAD_INTERFACE__

#include "KEYPAD_private.h"
#include "KEYPAD_config.h"

/**
 * @return u8
 * @param : copy_pu8CharPressed         KeyPad Keyp Pressed
 * @param : copy_pu8KeypadMatrix        KeyPad Matrix
 * @brief : Returns Value from given matrix ampped to keypressed
 */
void KEYPAD_voidGetChar(u8 *copy_pu8CharPressed, const u8 *copy_pu8KeypadMatrix);

#endif