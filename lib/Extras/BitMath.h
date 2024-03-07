#ifndef __BIT_MATH__
#define __BIT_MATH__

#define Set_Bit(Reg, bit) (Reg |= (1 << bit))
#define Clr_Bit(Reg, bit) (Reg &= ~(1 << bit))
#define Get_Bit(Reg, bit) ((Reg >> bit) & 1)
#define Tog_Bit(Reg, bit) (Reg ^= (1 << bit))

#endif  //*__BIT_MATH__