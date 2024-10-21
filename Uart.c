#include "Uart.h"
#include "McuRegs.h"
#include "PortRegs.h"

extern Mcu_RCC *RCC;
extern PortRegsType *PortRegs[9];
static UartRegsType *UartRegs[] = {
    (UartRegsType *)0x40011000, (UartRegsType *)0x40004400,
    (UartRegsType *)0x40004800, (UartRegsType *)0x40004C00,
    (UartRegsType *)0x40005000, (UartRegsType *)0x40011400};

void uart_init1(uint8 idx, uint32 pclk_mhz, UartBaudType BaudRate,
                UartWordLenType Wls, UartStopBitType StpBit,
                UartParityType Parity, boolean ParityCheck) {
  uint32 CR1Val = 0x00;
  uint32 CR2Val = 0x00;
  uint16 DivVal;
  float DivValFraction;
  UartRegs[1]->BRR = 0x00000000;
  switch (BaudRate) {
  case UART_BAUD_4800:
    UartRegs[1]->BRR = 0x222E;
    break;
  case UART_BAUD_7200:
    UartRegs[1]->BRR = 0x16C9;
    break;
  case UART_BAUD_9600:
    UartRegs[1]->BRR = 0x1117;
    break;
  case UART_BAUD_14400:
    UartRegs[1]->BRR = 0xB65;
    break;
  case UART_BAUD_19200:
    UartRegs[1]->BRR = 0x889;
    break;
  case UART_BAUD_57600:
    UartRegs[1]->BRR = 0x2DA;
    break;
  case UART_BAUD_115200:
    UartRegs[1]->BRR = 0x16D;
    break;
  default:
    UartRegs[1]->BRR = 0x1117;
  }

  // Configure word length
  if (Wls == UART_WL_8BIT) {
    CR1Val &= ~(1 << 12);
  } else if (Wls == UART_WL_9BIT) {
    CR1Val |= (1 << 12);
  }

  // Configure stop bits
  switch (StpBit) {
  case UART_STP_BIT_1:
    CR2Val &= ~(0x03 << 12);
    break;
  case UART_STP_BIT_05:
    CR2Val |= (0x01 << 12);
    break;
  case UART_STP_BIT_2:
    CR2Val |= (0x02 << 12);
    break;
  case UART_STP_BIT_15:
    CR2Val |= (0x03 << 12);
    break;
  default:
    CR2Val &= ~(0x03 << 12);
  }

  // Configure parity
  if (ParityCheck) {
    CR1Val |= (1 << 10);
    if (Parity == UART_PARITY_ODD) {
      CR1Val |= (1 << 9);
    } else if (Parity == UART_PARITY_EVEN) {
      CR1Val &= ~(1 << 9);
    }
  } else {
    CR1Val &= ~(1 << 10);
  }

  UartRegs[idx]->CR1 = CR1Val;
  UartRegs[idx]->CR2 = CR2Val;

  // Enable UART and transmitter
  UartRegs[idx]->CR1 |= (1 << 13); // USART Enable
  UartRegs[idx]->CR1 |= (1 << 3);  // TX Enable
}

void USART2_write(char ch) {
  UartRegs[1]->DR &= ~(0xff);
  UartRegs[1]->DR |= (ch);
  while (!(UartRegs[1]->SR & (1 << 7)))
    ;
}

void uart_printf(char *str) {
  while (*str) {
    int i;
    USART2_write(*(str++));
    for (i = 0; i < 1000; i++)
      ; // some delay
  }
}
