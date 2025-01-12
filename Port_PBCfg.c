#include "Port.h"

const Port_PinDetailsType PortPinDetails[] = {
    {
        .PortPin = PortConf_PortPin_LED,
        .PortPinDirection = PORT_PIN_OUT,
        .PortPinDirectionChangeable = TRUE,
        .PortPinInitialMode = PORT_PIN_MODE_DIO,
        .PortPinMode = PORT_PIN_MODE_AF1,
        .PortPinModeChangeable = TRUE,
        .PortPinOutputSpeed = PORT_PIN_OUTPUT_SPEED_MEDIUM,
        .PortPinOutput = PORT_PIN_OUTPUT_PUSH_PULL,
        .PortPinPUPD = PORT_PIN_PU,
    },
    {
        .PortPin = PortConf_PortPin_TMR1_PWM_CH1,
        .PortPinDirection = PORT_PIN_OUT,
        .PortPinDirectionChangeable = FALSE,
        .PortPinInitialMode = PORT_PIN_MODE_AF1,
        .PortPinMode = PORT_PIN_MODE_DIO,
        .PortPinModeChangeable = FALSE,
        .PortPinOutputSpeed = PORT_PIN_OUTPUT_SPEED_MEDIUM,
        .PortPinOutput = PORT_PIN_OUTPUT_PUSH_PULL,
        .PortPinPUPD = PORT_PIN_PU,
    },
    {
        .PortPin = PortConf_PortPin_TMR1_PWM_CH2,
        .PortPinDirection = PORT_PIN_OUT,
        .PortPinDirectionChangeable = TRUE,
        .PortPinInitialMode = PORT_PIN_MODE_AF1,
        .PortPinMode = PORT_PIN_MODE_AF1,
        .PortPinModeChangeable = FALSE,
        .PortPinOutputSpeed = PORT_PIN_OUTPUT_SPEED_MEDIUM,
        .PortPinOutput = PORT_PIN_OUTPUT_PUSH_PULL,
        .PortPinPUPD = PORT_PIN_PU,
    },
    {
        .PortPin = PortConf_PortPin_TMR1_PWM_CH3,
        .PortPinDirection = PORT_PIN_OUT,
        .PortPinDirectionChangeable = TRUE,
        .PortPinInitialMode = PORT_PIN_MODE_AF1,
        .PortPinMode = PORT_PIN_MODE_AF1,
        .PortPinModeChangeable = FALSE,
        .PortPinOutputSpeed = PORT_PIN_OUTPUT_SPEED_MEDIUM,
        .PortPinOutput = PORT_PIN_OUTPUT_PUSH_PULL,
        .PortPinPUPD = PORT_PIN_PU,
    },
    {
        .PortPin = PortConf_PortPin_TMR1_PWM_CH4,
        .PortPinDirection = PORT_PIN_OUT,
        .PortPinDirectionChangeable = TRUE,
        .PortPinInitialMode = PORT_PIN_MODE_AF1,
        .PortPinMode = PORT_PIN_MODE_AF1,
        .PortPinModeChangeable = FALSE,
        .PortPinOutputSpeed = PORT_PIN_OUTPUT_SPEED_MEDIUM,
        .PortPinOutput = PORT_PIN_OUTPUT_PUSH_PULL,
        .PortPinPUPD = PORT_PIN_PU,
    },
    {
        .PortPin = PortConf_PortPin_TMR8_PWM_CH1,
        .PortPinDirection = PORT_PIN_OUT,
        .PortPinDirectionChangeable = TRUE,
        .PortPinInitialMode = PORT_PIN_MODE_AF3,
        .PortPinMode = PORT_PIN_MODE_AF1,
        .PortPinModeChangeable = FALSE,
        .PortPinOutputSpeed = PORT_PIN_OUTPUT_SPEED_MEDIUM,
        .PortPinOutput = PORT_PIN_OUTPUT_PUSH_PULL,
        .PortPinPUPD = PORT_PIN_PU,
    },
    {
        .PortPin = PortConf_PortPin_TMR8_PWM_CH2,
        .PortPinDirection = PORT_PIN_OUT,
        .PortPinDirectionChangeable = TRUE,
        .PortPinInitialMode = PORT_PIN_MODE_AF3,
        .PortPinMode = PORT_PIN_MODE_AF1,
        .PortPinModeChangeable = FALSE,
        .PortPinOutputSpeed = PORT_PIN_OUTPUT_SPEED_MEDIUM,
        .PortPinOutput = PORT_PIN_OUTPUT_PUSH_PULL,
        .PortPinPUPD = PORT_PIN_PU,
    },
    {
        .PortPin = PortConf_PortPin_TMR8_PWM_CH3,
        .PortPinDirection = PORT_PIN_OUT,
        .PortPinDirectionChangeable = TRUE,
        .PortPinInitialMode = PORT_PIN_MODE_AF3,
        .PortPinMode = PORT_PIN_MODE_AF1,
        .PortPinModeChangeable = FALSE,
        .PortPinOutputSpeed = PORT_PIN_OUTPUT_SPEED_MEDIUM,
        .PortPinOutput = PORT_PIN_OUTPUT_PUSH_PULL,
        .PortPinPUPD = PORT_PIN_PU,
    },
    {
        .PortPin = PortConf_PortPin_TMR8_PWM_CH4,
        .PortPinDirection = PORT_PIN_OUT,
        .PortPinDirectionChangeable = TRUE,
        .PortPinInitialMode = PORT_PIN_MODE_AF3,
        .PortPinMode = PORT_PIN_MODE_AF1,
        .PortPinModeChangeable = FALSE,
        .PortPinOutputSpeed = PORT_PIN_OUTPUT_SPEED_MEDIUM,
        .PortPinOutput = PORT_PIN_OUTPUT_PUSH_PULL,
        .PortPinPUPD = PORT_PIN_PU,
    }};

const Port_ContainerType PortContainer = {
    .PortNumberOfPortPins = 9,
    .PortPinDetails = PortPinDetails,
};

const Port_ConfigType PortConfigSet = {
    .PortContainer = &PortContainer,
};
