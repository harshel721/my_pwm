#ifndef UART_H
#define UART_H

#include "Std_Types.h"
#include "string.h"
#include <stdarg.h>
#include <stdio.h>

#define DEBUG_UART 1
#define UART_OPERATION_MODE UART_POLLING_MODE
#define PCLK 42

typedef enum {
  UART_BAUD_4800 = 4800,
  UART_BAUD_7200 = 7200,
  UART_BAUD_9600 = 9600,
  UART_BAUD_14400 = 14400,
  UART_BAUD_19200 = 19200,
  UART_BAUD_57600 = 57600,
  UART_BAUD_115200 = 115200
} UartBaudType;

typedef enum {
  UART_WL_8BIT = 0U,
  UART_WL_9BIT = 1U,
} UartWordLenType;

typedef enum {
  UART_STP_BIT_1 = 0U,
  UART_STP_BIT_05 = 1U,
  UART_STP_BIT_2 = 2U,
  UART_STP_BIT_15 = 3U
} UartStopBitType;

typedef enum {
  UART_PARITY_ODD,
  UART_PARITY_EVEN,
} UartParityType;

// typedef struct
//{
//     uint32 SR;
//     uint32 DR;
//     uint32 BRR;
//     uint32 CR1;
//     uint32 CR2;
//     uint32 CR3;
//     uint32 GTPR;
// }UartRegsType;

typedef struct {
  uint16
      SR; /*!< USART Status register,                   Address offset: 0x00 */
  uint16 RESERVED0; /*!< Reserved, 0x02 */
  uint16
      DR; /*!< USART Data register,                     Address offset: 0x04 */
  uint16 RESERVED1; /*!< Reserved, 0x06 */
  uint16
      BRR; /*!< USART Baud rate register,                Address offset: 0x08 */
  uint16 RESERVED2; /*!< Reserved, 0x0A */
  uint16
      CR1; /*!< USART Control register 1,                Address offset: 0x0C */
  uint16 RESERVED3; /*!< Reserved, 0x0E */
  uint16
      CR2; /*!< USART Control register 2,                Address offset: 0x10 */
  uint16 RESERVED4; /*!< Reserved, 0x12 */
  uint16
      CR3; /*!< USART Control register 3,                Address offset: 0x14 */
  uint16 RESERVED5; /*!< Reserved, 0x16 */
  uint16 GTPR; /*!< USART Guard time and prescaler register, Address offset:
                  0x18 */
  uint16 RESERVED6; /*!< Reserved, 0x1A */
} UartRegsType;

void uart_init(uint8 idx, uint32 pclk_mhz, UartBaudType speed,
               UartWordLenType Wls, UartStopBitType StpBit,
               UartParityType Parity, boolean ParityCheck);
void uart_init1(uint8 idx, uint32 pclk_mhz, UartBaudType BaudRate,
                UartWordLenType Wls, UartStopBitType StpBit,
                UartParityType Parity, boolean ParityCheck);
void USART2_Init(void);
void USART2_write(char ch);
void uart_printf(char *str);

#endif
