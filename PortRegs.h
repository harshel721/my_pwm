#ifndef PORTREGS_H
#define PORTREGS_H

#include "Std_Types.h"
#include "DioRegs.h"

typedef struct
{
    uint32 GPIOx_MODER;
    uint32 GPIOx_OTYPER;
    uint32 GPIOx_OSPEEDR;
    uint32 GPIOx_PUPDR;
    uint32 GPIOx_IDR;
    uint32 GPIOx_ODR;
		uint32 GPIOx_BSRR;
    uint32 GPIOx_LCKR;
    uint32 GPIOx_AFRL;
    uint32 GPIOx_AFRH;
}PortRegsType;

typedef struct
{
    uint32 GPIOx_AFRL;
    uint32 GPIOx_AFRH;
}AFRegsType;

#endif