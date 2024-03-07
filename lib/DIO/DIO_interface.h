/*
 * DIO_interface.h
 *
 * Created: 2/2/2024 6:53:04 PM
 *  Author: Kareem Hussein
 */

#ifndef DIO_INTERFACE_H_
#define DIO_INTERFACE_H_

#include "Std_Types.h"
/*************** MACROS FOR PORT ***************/
/* macros for port id */
#define DIO_PORTA 0
#define DIO_PORTB 1
#define DIO_PORTC 2
#define DIO_PORTD 3

/* macros for port direction */
#define DIO_PORT_INPUT 0x00
#define DIO_PORT_OUTPUT 0xff

/* macros for port value */
#define DIO_PORT_LOW 0x00
#define DIO_PORT_HIGH 0xff

/*************** MACROS FOR PIN ***************/
/* macros for pin id */
#define DIO_PIN0 0
#define DIO_PIN1 1
#define DIO_PIN2 2
#define DIO_PIN3 3
#define DIO_PIN4 4
#define DIO_PIN5 5
#define DIO_PIN6 6
#define DIO_PIN7 7

/* macros for pin direction */
#define DIO_PIN_INPUT 0
#define DIO_PIN_OUTPUT 1

/* macros for pin value */
#define DIO_PIN_LOW 0
#define DIO_PIN_HIGH 1

/*************** APIS PROTO TYPES ***************/

/**
 * @return void
 * @brief : Initialize all MCU Pins As defined in config file
 */
void DIO_voidInitPins(void);

/* Pin Apis */

/**
 * @return void
 * @param : copy_u8PortId       Port ID
 * @param : copy_u8PinId        Pin ID
 * @param : copy_u8PinDirection Pin Direction
 * @brief : Set given pin At port to Direction E.g, Input /Output
 */
void DIO_voidSetPinDirection(u8 copy_u8PortId, u8 copy_u8PinId, u8 copy_u8PinDirection);

/**
 * @return void
 * @param : copy_u8PortId       Port ID
 * @param : copy_u8PinId        Pin ID
 * @param : copy_u8PinValue     Pin Value
 * @brief : Set given pin At port to Value E.g, High / Low
 */
void DIO_voidSetPinValue(u8 copy_u8PortId, u8 copy_u8PinId, u8 copy_u8PinValue);

/**
 * @return void
 * @param : copy_u8PortId       Port ID
 * @param : copy_u8PinId        Pin ID
 * @param : *copy_pu8PinValue   pointer to Pin Value
 * @brief : Get pin Value at port E.g, High / Low
 */
void DIO_voidGetPinValue(u8 copy_u8PortId, u8 copy_u8PinId, u8 *copy_pu8PinValue);

/**
 * @return void
 * @param : copy_u8PortId       Port ID
 * @param : copy_u8PinId        Pin ID
 * @brief : Toggles pin value
 */
void DIO_voidTogglePinValue(u8 copy_u8PortId, u8 copy_u8PinId);

/**
 * @return void
 * @param : copy_u8PortId       Port ID
 * @param : copy_u8PinId        Pin ID
 * @brief : Activate Internal Pull-Up resistor
 */
void DIO_voidActivePinInPullUpResistance(u8 copy_u8PortId, u8 copy_u8PinId);

//! Disable Pull-ups  ??
/* Port Apis */

/**
 * @return void
 * @param : copy_u8PortId               Port ID
 * @param : copy_u8PortDirection        Port Direction
 * @brief : Set Whole Port into Input /Output
 */
void DIO_voidSetPortDirection(u8 copy_u8PortId, u8 copy_u8PortDirection);

/**
 * @return void
 * @param : copy_u8PortId           Port ID
 * @param : copy_u8PortValue        Port Value
 * @brief : Set Whole Port Value into High Low E.g. 0x55 0xFF
 */
void DIO_voidSetPortValue(u8 copy_u8PortId, u8 copy_u8PortValue);

/**
 * @return void
 * @param : copy_u8PortId           Port ID
 * @param : *copy_pu8PortValue      Pointer to Port Value
 * @brief : Get Whole Port Value
 */
void DIO_voidGetPortValue(u8 copy_u8PortId, u8 *copy_pu8PortValue);

/**
 * @return void
 * @param : copy_u8PortId           Port ID
 * @brief : Toggles Port Value
 */
void DIO_voidTogglePortValue(u8 copy_u8PortId);

/**
 * @return void
 * @param : copy_u8PortId           Port ID
 * @brief : Activate Port internal pull-up resistors
 */
void DIO_voidActivePortInPullUpResistance(u8 copy_u8PortId);

#endif /* DIO_INTERFACE_H_ */