#include "LedBlinking.h"

extern const Mcu_ConfigType McuConfigSet;
extern const Port_ConfigType PortConfigSet;
extern Mcu_GlobalType McuGlobal;
extern const Pwm_ConfigType PwmConfigSet;

void delay(int n) {
  int i;
  for (i = 0; i < (n * 1000); i++)
    ;
}

int main() {
  boolean mcuStatus;
  Mcu_PllStatusType status;
  Mcu_Init(&McuConfigSet);
  Mcu_InitClock(McuConf_McuClockSetting_Id_0);

  if (status == MCU_PLL_LOCKED) {
    Mcu_DistributePllClock();
  }
	
	Port_Init(&PortConfigSet);
	
	Pwm_Init(&PwmConfigSet);
	Pwm_SetPeriodAndDuty(PwmConf_PwmChannel_CH_1, 0x0500, 0x0200);
	
	
  while (1) {
    Dio_WriteChannel(DioConf_DioChannel_LED, STD_HIGH);
    delay(6000);
    Dio_WriteChannel(DioConf_DioChannel_LED, STD_LOW);
    delay(6000);
  }
}
