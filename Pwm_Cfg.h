#ifndef PWM_CFG_H
#define PWM_CFG_H

#include "Std_Types.h"

/* Development Error Detection */
#define PWM_DEV_ERROR_DETECT STD_OFF
#define PWM_GET_OUTPUT_STATE_API STD_ON
#define PWM_SET_DUTY_CYCLE_API STD_ON
#define PWM_SET_OUTPUT_TO_IDLE_API STD_ON
#define PWM_SET_PERIOD_AND_DUTY_API STD_ON
#define PWM_VERSION_INFO_API STD_OFF
#define PWM_DE_INIT_API STD_ON

/* Number of PWM channels */
#define PWM_CHANNEL_COUNT 1

/* Symbolic names for all channels */
#define PwmConf_PwmChannel_CH_1 0

#define PERIOD 0x0800
#define DUTY 0x0600

#endif /* PWM_CFG_H */
