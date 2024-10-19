#ifndef MCUREGS_H
#define MCUREGS_H

#include "Std_Types.h"
typedef struct
{
    volatile uint32 CR;
    volatile uint32 PLLCFGR;
    volatile uint32 CFGR;
    volatile uint32 CIR;
    volatile uint32 AHB1RSTR;
    volatile uint32 AHB2RSTR;
    volatile uint32 AHB3RSTR;
        uint32 RESERVED0;
    volatile uint32 APB1RSTR;
    volatile uint32 APB2RSTR;
        uint32 DUMMY1[2];
    volatile uint32 AHB1ENR;
    volatile uint32 AHB2ENR;
    volatile uint32 AHB3ENR;
        uint32 RESERVED2;
    volatile uint32 APB1ENR;
    volatile uint32 APB2ENR;
        uint32 DUMMY3[2];
    volatile uint32 AHB1LPENR;
    volatile uint32 AHB2LPENR;
    volatile uint32 AHB3LPENR;
        uint32 RESERVED4; 
    volatile uint32 APB1LPENR;
    volatile uint32 APB2LPENR;
        uint32 DUMMY5[2];
    volatile uint32 BDCR;
    volatile uint32 CSR;
        uint32 DUMMY6[2];
    volatile uint32 SSCGR;
    volatile uint32 PLLI2SCFGR;
} Mcu_RCC;

#endif
