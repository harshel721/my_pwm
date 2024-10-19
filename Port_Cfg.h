#ifndef PORT_CFG_H
#define PORT_CFG_H

#define PORT_MODULE_ID                    124
#define PORT_VENDOR_ID                    136

#define PORT_AR_RELEASE_MAJOR_VERSION     4
#define PORT_AR_RELEASE_MINOR_VERSION     3

#define PORT_SW_MAJOR_VERSION             1
#define PORT_SW_MINOR_VERSION             0
#define PORT_SW_PATCH_VERSION             0

#define PORT_DEV_ERROR_DETECT             STD_ON
#define PORT_SET_PIN_DIRECTION_API        STD_ON
#define PORT_SET_PIN_MODE_API             STD_ON
#define PORT_VERSION_INFO_API             STD_ON

#define PORT_NUM_MAX_PINS          143

/* Symbolic names */
#define PortConf_PortPin_LED      60

#define PortConf_PortPin_TMR1_PWM_CH1			8
#define PortConf_PortPin_TMR1_PWM_CH2			9
#define PortConf_PortPin_TMR1_PWM_CH3			10
#define PortConf_PortPin_TMR1_PWM_CH4           11

#define PortConf_PortPin_TMR8_PWM_CH1			38
#define PortConf_PortPin_TMR8_PWM_CH2			39
#define PortConf_PortPin_TMR8_PWM_CH3			118
#define PortConf_PortPin_TMR8_PWM_CH4           119

#endif
