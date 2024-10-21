#include "LedBlinking.h"
#include "Uart.h"

extern const Mcu_ConfigType McuConfigSet;
extern const Port_ConfigType PortConfigSet;
extern Mcu_GlobalType McuGlobal;
extern const Pwm_ConfigType PwmConfigSet;

void delay(int count) {
  for (int i = 0; i < (count * 1000); i++)
    ;
}

// int main() {
//   boolean mcuStatus;
//   Mcu_PllStatusType status;
//   Mcu_Init(&McuConfigSet);
//   Mcu_InitClock(McuConf_McuClockSetting_Id_0);

//  if (status == MCU_PLL_LOCKED) {
//    Mcu_DistributePllClock();
//  }
//
//	Port_Init(&PortConfigSet);
//
//	Pwm_Init(&PwmConfigSet);
//}

// System initialization function
void init_system(void) {
  Mcu_PllStatusType status;

  // Initialize MCU
  Mcu_Init(&McuConfigSet);
  Mcu_InitClock(McuConf_McuClockSetting_Id_0);

  // Check if PLL is locked
  if (status == MCU_PLL_LOCKED) {
    Mcu_DistributePllClock();
  }

  uart_init1(DEBUG_UART, PCLK, UART_BAUD_9600, UART_WL_8BIT, UART_STP_BIT_1,
             UART_PARITY_EVEN, FALSE);

  // Initialize Port
  Port_Init(&PortConfigSet);
  uart_printf("Mcu and Port Initilization done\n\r");

  // Initialize PWM
  Pwm_Init(&PwmConfigSet);
  uart_printf("Pwm Initilization done\n\r");
}

void led_fade(void) {
  int duty_cycle;
  const int max_brightness = 999; // Maximum duty cycle value
  const int step = 1;             // Step size for fading

  // Fade-in effect
  for (duty_cycle = 0; duty_cycle <= max_brightness; duty_cycle += step) {
    Pwm_SetPeriodAndDuty(PwmConf_PwmChannel_CH_1, max_brightness, duty_cycle);
    delay(10);
  }

  // Fade-out effect
  for (duty_cycle = max_brightness; duty_cycle >= 0; duty_cycle -= step) {
    Pwm_SetPeriodAndDuty(PwmConf_PwmChannel_CH_1, max_brightness, duty_cycle);
    delay(10);
  }
}

int main() {
  // Initialize the system components
  init_system();

  // Continuously fade the LED in and out
  while (1) {
    led_fade();
  }

  return 0;
}
