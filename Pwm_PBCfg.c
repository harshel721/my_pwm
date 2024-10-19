#include "Pwm.h"

const Pwm_ChannelConfigType PwmChannelData[] = {{
    .PwmChannelId = PwmConf_PwmChannel_CH_1,
    .PwmChannelClass = PWM_FIXED_PERIOD,
    .PwmDutycycleDefault = DUTY, // defaultDutyCycle,
    .PwmIdleState = PWM_LOW,
    .PwmNotification = STD_OFF,
    .PwmPeriodDefault = PERIOD,
    .PwmPolarity = PWM_HIGH,
}};

const Pwm_ContainerType PwmContainter = {
    .PwmChannelData = PwmChannelData,
};

const Pwm_ConfigType PwmConfigSet = {
		.defaultPeriod = 0x0800,
		.defaultDutyCycle = 0x0600,
		.polarity = PWM_HIGH,
    .PwmContainer = &PwmContainter,
};
