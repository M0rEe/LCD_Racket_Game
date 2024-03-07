#ifndef __ANIMATED_OBJ_H__
#define __ANIMATED_OBJ_H__

#include "Std_Types.h"

typedef struct
{
    u8 currentLine;
    u8 currentCol;

    u8 prevLine;
    u8 prevCol;

} Moving_Obj;

#endif //__ANIMATED_OBJ_H__