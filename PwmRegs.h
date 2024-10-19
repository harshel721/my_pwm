#ifndef PWMREGS_H
#define PWMREGS_H

#include "stdint.h"

/* Base addresses for peripheral registers */
#define PERIPH_BASE (0x40000000UL) // Base address for peripheral registers
#define APB1PERIPH_BASE (PERIPH_BASE + 0x00000000UL)
#define APB2PERIPH_BASE (PERIPH_BASE + 0x00010000UL)
#define AHB1PERIPH_BASE (PERIPH_BASE + 0x00020000UL)

/* RCC - Reset and Clock Control */
#define RCC_BASE (AHB1PERIPH_BASE + 0x3800UL)

#define TIM1_BASE (APB2PERIPH_BASE + 0x0000UL)
#define TIM8_BASE (APB2PERIPH_BASE + 0x0400UL)

#define TIM2_BASE (APB1PERIPH_BASE + 0x0000UL)
#define TIM3_BASE (APB1PERIPH_BASE + 0x0400UL)
#define TIM4_BASE (APB1PERIPH_BASE + 0x0800UL)
#define TIM5_BASE (APB1PERIPH_BASE + 0x0C00UL)

/* RCC Register definitions */
#define RCC ((RCC_TypeDef *)RCC_BASE)

typedef struct {
  volatile uint32_t CR;           /* Clock control register */
  volatile uint32_t PLLCFGR;      /* PLL configuration register */
  volatile uint32_t CFGR;         /* Clock configuration register */
  volatile uint32_t CIR;          /* Clock interrupt register */
  volatile uint32_t AHB1RSTR;     /* AHB1 peripheral reset register */
  volatile uint32_t AHB2RSTR;     /* AHB2 peripheral reset register */
  volatile uint32_t AHB3RSTR;     /* AHB3 peripheral reset register */
  volatile uint32_t RESERVED0;    /* Reserved */
  volatile uint32_t APB1RSTR;     /* APB1 peripheral reset register */
  volatile uint32_t APB2RSTR;     /* APB2 peripheral reset register */
  volatile uint32_t RESERVED1[2]; /* Reserved */
  volatile uint32_t AHB1ENR;      /* AHB1 peripheral clock enable register */
  volatile uint32_t AHB2ENR;      /* AHB2 peripheral clock enable register */
  volatile uint32_t AHB3ENR;      /* AHB3 peripheral clock enable register */
  volatile uint32_t RESERVED2;    /* Reserved */
  volatile uint32_t APB1ENR;      /* APB1 peripheral clock enable register */
  volatile uint32_t APB2ENR;      /* APB2 peripheral clock enable register */
  volatile uint32_t RESERVED3[2]; /* Reserved */
  volatile uint32_t
      AHB1LPENR; /* AHB1 peripheral clock enable in low power mode register */
  volatile uint32_t
      AHB2LPENR; /* AHB2 peripheral clock enable in low power mode register */
  volatile uint32_t
      AHB3LPENR; /* AHB3 peripheral clock enable in low power mode register */
  volatile uint32_t RESERVED4; /* Reserved */
  volatile uint32_t
      APB1LPENR; /* APB1 peripheral clock enable in low power mode register */
  volatile uint32_t
      APB2LPENR; /* APB2 peripheral clock enable in low power mode register */
  volatile uint32_t RESERVED5[2]; /* Reserved */
  volatile uint32_t BDCR;         /* Backup domain control register */
  volatile uint32_t CSR;          /* Clock control & status register */
  volatile uint32_t RESERVED6[2]; /* Reserved */
  volatile uint32_t SSCGR;      /* Spread spectrum clock generation register */
  volatile uint32_t PLLI2SCFGR; /* PLLI2S configuration register */
  volatile uint32_t PLLSAICFGR; /* PLLSAI configuration register */
  volatile uint32_t DCKCFGR;    /* Dedicated Clocks configuration register */
} RCC_TypeDef;

/* Bit definitions for RCC_APB1ENR register */
#define RCC_APBxENR_TIMxEN (1U << 0) // TIMx clock enable

#define TIM1 ((TIM_TypeDef *)TIM1_BASE)
#define TIM8 ((TIM_TypeDef *)TIM8_BASE)

#define TIM2 ((TIM_TypeDef *)TIM2_BASE)
#define TIM3 ((TIM_TypeDef *)TIM3_BASE)
#define TIM4 ((TIM_TypeDef *)TIM4_BASE)
#define TIM5 ((TIM_TypeDef *)TIM5_BASE)

typedef struct {
  volatile uint32_t CR1;       /* Control register 1 */
  volatile uint32_t CR2;       /* Control register 2 */
  volatile uint32_t SMCR;      /* Slave mode control register */
  volatile uint32_t DIER;      /* DMA/Interrupt enable register */
  volatile uint32_t SR;        /* Status register */
  volatile uint32_t EGR;       /* Event generation register */
  volatile uint32_t CCMR1;     /* Capture/compare mode register 1 */
  volatile uint32_t CCMR2;     /* Capture/compare mode register 2 */
  volatile uint32_t CCER;      /* Capture/compare enable register */
  volatile uint32_t CNT;       /* Counter */
  volatile uint32_t PSC;       /* Prescaler */
  volatile uint32_t ARR;       /* Auto-reload register */
  volatile uint32_t RESERVED0; /* Reserved */
  volatile uint32_t CCR1;      /* Capture/compare register 1 */
  volatile uint32_t CCR2;      /* Capture/compare register 2 */
  volatile uint32_t CCR3;      /* Capture/compare register 3 */
  volatile uint32_t CCR4;      /* Capture/compare register 4 */
  volatile uint32_t RESERVED1; /* Reserved */
  volatile uint32_t DCR;       /* DMA control register */
  volatile uint32_t DMAR;      /* DMA address for full transfer */
  volatile uint32_t OR;        /* Option register */
} TIM_TypeDef;

/* Bit definitions for TIM_CR1 register */
#define TIM_CR1_CEN (1U << 0) // Counter enable

/* Bit definitions for TIM_CCMR1 register */
#define TIM_CCMR1_OC1M_PWM1 (6U << 4) // Output Compare 1 mode (PWM mode 1)

/* Bit definitions for TIM_CCER register */
#define TIM_CCER_CC1E (1U << 0) // Capture/Compare 1 output enable
#define TIM_CCER_CC1P (1U << 1) // Capture/Compare 1 output polarity

/* Bit definitions for TIM_EGR register */
#define TIM_EGR_UG (1U << 0) // Update generation (re-initialize counter)

/* Example usage macros */
#define ENABLE_TIM2_CLOCK() (RCC->APB1ENR |= RCC_APBxENR_TIMxEN)
#define DISABLE_TIM2_CLOCK() (RCC->APB1ENR &= ~RCC_APBxENR_TIMxEN)

#define ENABLE_TIM1_CLOCK() (RCC->APB2ENR |= RCC_APBxENR_TIMxEN)
#define DISABLE_TIM1_CLOCK() (RCC->APB2ENR &= ~RCC_APBxENR_TIMxEN)

#define ENABLE_TIM8_CLOCK() (RCC->APB2ENR |= RCC_APBxENR_TIMxEN)
#define DISABLE_TIM8_CLOCK() (RCC->APB2ENR &= ~RCC_APBxENR_TIMxEN)

#endif
