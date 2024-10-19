#include "Mcu.h"

McuClkType ClkSelect_0[] = 
{
    {
        .MCU_CAN1     = STD_OFF,
        .MCU_CAN2     = STD_OFF,
        .PWREN        = STD_ON,
        .MCU_GPIOA    = STD_ON,
        .MCU_GPIOB    = STD_OFF,
        .MCU_GPIOC    = STD_OFF,
        .MCU_GPIOD    = STD_ON,
        .MCU_GPIOE    = STD_OFF,
        .MCU_GPIOF    = STD_OFF,
        .MCU_GPIOG    = STD_OFF,
        .MCU_GPIOH    = STD_OFF,
        .MCU_GPIOI    = STD_OFF,
        .MCU_USART2   = STD_ON,
		.MCU_USART1   = STD_OFF,
		.MCU_USART3   = STD_OFF,
		.MCU_USART4   = STD_OFF,
		.MCU_USART5   = STD_OFF,
		.MCU_USART6   = STD_OFF,
        .MCU_TIM1     = STD_ON ,
        .MCU_TIM8     = STD_ON ,
        .MCU_TIM2     = STD_ON ,
    },
};



McuClockReferencePointModule McuClkFreq_0[] = 
{
    {
      .McuClockReferencePointFrequency = 84,
    },
};


const Mcu_ClkSettingConfigType McuClkSettingData[] =
{
    {
        .McuClockSettingId             = McuConf_McuClockSetting_Id_0,
        .McuClockReferencePoint        = McuClkFreq_0,
        .PLLP                          = 2,                                                                         
        .PLLN                          = 336,
        .PLLM                          = 16,
        .HSE                           = STD_OFF,
        .HSI                           = STD_ON, 
        .McuClockType                  = ClkSelect_0,
    },
};



const Mcu_ConfigType McuConfigSet =
{
    .numClockSettings         = MCU_NUM_CLOCK_SETTING,
    .McuClockSettingData      = McuClkSettingData,
};
