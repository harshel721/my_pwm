#ifndef PWM_H
#define PWM_H

#include "Dem.h"
#include "PwmRegs.h"
#include "Pwm_Cfg.h"
#include "Std_Types.h"

/* Macro definitions for API Service ID */
#define PWM_INIT_SID 0x00u         /* Service ID for PWM_Init API */
#define PWM_DEINIT_SID 0x01u       /* Service ID for PWM_DeInit API */
#define PWM_SETDUTYCYCLE_SID 0x02u /* Service Id for Pwm_SetDutyCycle API */
#define PWM_SETPERIODANDDUTY_SID                                               \
  0x03u /* Service Id for Pwm_SetPeriodAndDuty API */
#define PWM_SETOUTPUTTOIDLE_SID                                                \
  0x04u /* Service Id for Pwm_SetOutputToIdle API */
#define PWM_GETOUTPUTSTATE_SID                                                 \
  0x05u /* Service Id for Pwm_GetOutputState API                               \
         */
#define PWM_DISABLENOTIFICATION_SID                                            \
  0x06u /* Service Id for Pwm_DisableNotification API */
#define PWM_ENABLENOTIFICATION_SID                                             \
  0x07u /* Service Id for Pwm_EnableNotification API */
#define PWM_GETVERSIONINFO_SID                                                 \
  0x08u /* Service Id for Pwm_GetVersionInfo API                               \
         */
#define PWM_SETPOWERSTATE_SID                                                  \
  0x09u /* Service Id for Pwm_SetPowerState API (not supported) */
#define PWM_GETPOWERSTATE_SID                                                  \
  0x0Au /* Service Id for Pwm_GetTargetPowerState API (not supported) */
#define PWM_GETTARGETPOWERSTATE_SID                                            \
  0x0Bu /* Service Id for Pwm_GetTargetPowerState API (not supported) */
#define PWM_PREPAREPOWERSTATE_SID                                              \
  0x0Cu /* Service Id for Pwm_PreparePowerState API (not supported) */

/* Macro definitions for Error Codes specified by AUTOSAR */
#define PWM_E_INIT_FAILED                                                      \
  0x10u /* API Pwm_Init service called with wrong parameter */
#define PWM_E_UNINIT                                                           \
  0x11u /* API service used without module initialization                      \
         */
#define PWM_E_PARAM_CHANNEL                                                    \
  0x12u /* API service used with an invalid channel Identifier */
#define PWM_E_PERIOD_UNCHANGEABLE                                              \
  0x13u /* Usage of unauthorized PWM service on PWM channel configured a fixed \
           period */
#define PWM_E_ALREADY_INITIALIZED                                              \
  0x14u /* API Pwm_Init service called while the PWM driver has already been   \
           initialised */
#define PWM_E_PARAM_POINTER 0x15u /* API called with a NULL parameter */
#define PWM_E_POWER_STATE_NOT_SUPPORTED                                        \
  0x17u /* The requested power state is not supported by the PWM module */
#define PWM_E_TRANSITION_NOT_POSSIBLE                                          \
  0x18u /* The requested power state is not reachable from the current one */
#define PWM_E_PERIPHERAL_NOT_PREPARED                                          \
  0x19u /* API Pwm_SetPowerState has been called without having called the API \
           Pwm_PreparePowerState before */

/*enum definitions */
/* SWS_Pwm_00108 */
typedef enum { PWM_HIGH, PWM_LOW } Pwm_OutputStateType;

/* SWS_Pwm_00109 */
typedef enum {
  PWM_RISING_EDGE,
  PWM_FALLING_EDGE,
  PWM_BOTH_EDGES
} Pwm_EdgeNotificationType;

/* SWS_Pwm_00110 */
typedef enum {
  PWM_VARIABLE_PERIOD,     /* The duty cycle and the period can be changed. */
  PWM_FIXED_PERIOD,        /* Only the duty cycle can be changed. */
  PWM_FIXED_PERIOD_SHIFTED /* Impossible to change it (not supported by
                              hardware) */
} Pwm_ChannelClassType;

/* SWS_Pwm_00165 */
typedef enum {
  PWM_SERVICE_ACCEPTED,
  PWM_NOT_INIT,
  PWM_SEQUENCE_ERROR,
  PWM_HW_FAILURE,
  PWM_POWER_STATE_NOT_SUPP,
  PWM_TRANS_NOT_POSSIBLE
} Pwm_PowerStateRequestResultType;

/* SWS_Pwm_00197 */
typedef enum { PWM_FULL_POWER } Pwm_PowerStateType;

/* SWS_Pwm_00106 */
typedef uint8 Pwm_ChannelType;

/* SWS_Pwm_00107 */
typedef uint16 Pwm_PeriodType;

// PWM Duty Cycle Type (Duty cycle value)
typedef uint16 Pwm_DutyCycleType;

typedef void (*Pwm_Notification)(void);

/* Structure definitions */
typedef struct {
  Pwm_ChannelType PwmChannelId;
  Pwm_ChannelClassType PwmChannelClass;
  uint16 PwmDutycycleDefault;
  Pwm_OutputStateType PwmIdleState;
  Pwm_Notification PwmNotification;
  uint32 PwmPeriodDefault;
  Pwm_OutputStateType PwmPolarity;
} Pwm_ChannelConfigType;

typedef struct {
  const Pwm_ChannelConfigType *PwmChannelData;
} Pwm_ContainerType;

typedef struct {
	Pwm_PeriodType defaultPeriod;
	Pwm_DutyCycleType defaultDutyCycle;
	Pwm_OutputStateType polarity;
  const Pwm_ContainerType *PwmContainer;
} Pwm_ConfigType;

typedef struct {
  Pwm_ConfigType *CfgPtr;
  boolean PwmInitialized;
} Pwm_GlobalType;

/* Public Function Declarations */
#define PWM_START_SEC_CODE
/******************************************************************************
 *  Service name    : Pwm_Init
 *  Syntax          : void Pwm_Init( const Pwm_ConfigType *ConfigPtr )
 *  Service ID      : 0x00
 *  Sync/Async      : Synchronous
 *  Reentrancy      : Non reentrant
 *  Parameters (in) : ConfigPtr - Pointer to PWM driver configuration set
 *  Parameters (out): None
 *  Return value    : None
 *  Description     : Service for PWM initialization
 ******************************************************************************/
void Pwm_Init(const Pwm_ConfigType *ConfigPtr);

#if (PWM_DE_INIT_API == STD_ON)
/******************************************************************************
 *  Service name    : Pwm_DeInit
 *  Syntax          : void Pwm_DeInit( void )
 *  Service ID      : 0x01
 *  Sync/Async      : Synchronous
 *  Reentrancy      : Non reentrant
 *  Parameters (in) : None
 *  Parameters (out): None
 *  Return value    : None
 *  Description     : Service for PWM De-initialization
 ******************************************************************************/
void Pwm_DeInit(void);
#endif

#if (PWM_SET_DUTY_CYCLE_API == STD_ON)
/******************************************************************************
*  Service name    : Pwm_SetDutyCycle
*  Syntax          : void Pwm_SetDutyCycle( Pwm_ChannelType ChannelNumber,
                                                            uint16 DutyCycle )
*  Service ID      : 0x02
*  Sync/Async      : Synchronous
*  Reentrancy      : Reentrant for different channel numbers
*  Parameters (in) : ChannelNumber - Numeric identifier of the PWM
                     DutyCycle - Min=0x0000 Max=0x8000
*  Parameters (out): None
*  Return value    : None
*  Description     : Service sets the duty cycle of the PWM channel.
******************************************************************************/
void Pwm_SetDutyCycle(Pwm_ChannelType ChannelNumber, uint16 DutyCycle);
#endif

#if (PWM_SET_PERIOD_AND_DUTY_API == STD_ON)
/*******************************************************************************
*  Service name    : Pwm_SetPeriodAndDuty
*  Syntax          : void Pwm_SetPeriodAndDuty( Pwm_ChannelType ChannelNumber,
                                        Pwm_PeriodType Period, uint16 DutyCycle
)
*  Service ID      : 0x03
*  Sync/Async      : Synchronous
*  Reentrancy      : Reentrant for different channel numbers
*  Parameters (in) : ChannelNumber - Numeric identifier of the PWM
                     Period - Period of the PWM signal
                     DutyCycle - Min=0x0000 Max=0x8000
*  Parameters (out): None
*  Return value    : None
*  Description     : Service sets the period and the duty cycle of a PWM channel
********************************************************************************/
void Pwm_SetPeriodAndDuty(Pwm_ChannelType ChannelNumber, Pwm_PeriodType Period,
                          uint16 DutyCycle);
#endif

#if (PWM_SET_OUTPUT_TO_IDLE_API == STD_ON)
/*******************************************************************************
 *  Service name    : Pwm_SetOutputToIdle
 *  Syntax          : void Pwm_SetOutputToIdle( Pwm_ChannelType ChannelNumber )
 *  Service ID      : 0x04
 *  Sync/Async      : Synchronous
 *  Reentrancy      : Reentrant for different channel numbers
 *  Parameters (in) : ChannelNumber - Numeric identifier of the PWM
 *  Parameters (out): None
 *  Return value    : None
 *  Description     : Service sets the PWM output to the configured Idle state.
 ********************************************************************************/
void Pwm_SetOutputToIdle(Pwm_ChannelType ChannelNumber);
#endif

#if (PWM_GET_OUTPUT_STATE_API == STD_ON)
/*******************************************************************************
*  Service name    : Pwm_GetOutputState
*  Syntax          : Pwm_OutputStateType Pwm_GetOutputState( Pwm_ChannelType
                                                                ChannelNumber )
*  Service ID      : 0x05
*  Sync/Async      : Synchronous
*  Reentrancy      : Reentrant for different channel numbers
*  Parameters (in) : ChannelNumber - Numeric identifier of the PWM
*  Parameters (out): None
*  Return value    : Pwm_OutputStateType PWM_HIGH The PWM output state is high
                                         PWM_LOW The PWM output state is low
*  Description     : Service to read the internal state of the PWM output
signal.
********************************************************************************/
Pwm_OutputStateType Pwm_GetOutputState(Pwm_ChannelType ChannelNumber);
#endif

#if (PWM_NOTIFICATION_SUPPORTED == STD_ON)
/*******************************************************************************
 *  Service name    : Pwm_DisableNotification
 *  Syntax          : void Pwm_DisableNotification(Pwm_ChannelType
 *ChannelNumber) Service ID      : 0x06 Sync/Async      : Synchronous Reentrancy
 *: Reentrant for different channel numbers Parameters (in) : ChannelNumber -
 *Numeric identifier of the PWM Parameters (out): None Return value    : None
 *  Description     : Service to disable the PWM signal edge notification.
 ********************************************************************************/
void Pwm_DisableNotification(Pwm_ChannelType ChannelNumber);

/*********************************************************************************
*  Service name    : Pwm_EnableNotification
*  Syntax          : void Pwm_EnableNotification( Pwm_ChannelType ChannelNumber,
                                            Pwm_EdgeNotificationType
Notification )
*  Service ID      : 0x07
*  Sync/Async      : Synchronous
*  Reentrancy      : Reentrant for different channel numbers
*  Parameters (in) : ChannelNumber - Numeric identifier of the PWM
                     Notification - Type of notification
                     PWM_RISING_EDGE or PWM_FALLING_EDGE or PWM_BOTH_EDGES
*  Parameters (out): None
*  Return value    : None
*  Description     : Service to enable the PWM signal edge notification
according to notification parameter.
**********************************************************************************/
void Pwm_EnableNotification(Pwm_ChannelType ChannelNumber,
                            Pwm_EdgeNotificationType Notification);
#endif

#if (PWM_VERSION_INFO_API == STD_ON)
/*******************************************************************************
*  Service name    : Pwm_GetVersionInfo
*  Syntax          : void Pwm_GetVersionInfo( Std_VersionInfoType* versioninfo )
*  Service ID      : 0x08
*  Sync/Async      : Synchronous
*  Reentrancy      : Reentrant
*  Parameters (in) : None
*  Parameters (out): versioninfo - Pointer to where to store the version
                                   information of this module.
*  Return value    : None
*  Description     : Service returns the version information of this module.
********************************************************************************/
void Pwm_GetVersionInfo(Std_VersionInfoType *versioninfo);
#endif

#if (PWM_LOW_POWER_STATE_SUPPORT == STD_ON)
/******************************************************************************************
*  Service name    : Pwm_SetPowerState
*  Syntax          : Std_ReturnType Pwm_SetPowerState(
Pwm_PowerStateRequestResultType *Result )
*  Service ID      : 0x09
*  Sync/Async      : Synchronous
*  Reentrancy      : Non-Reentrant
*  Parameters (in) : None
*  Parameters (out): Result: E_OK: PWM_SERVICE_ACCEPTED:Power state change
executed. E_NOT_OK: PWM_NOT_INIT: PWM Module not initialized.
                             PWM_SEQUENCE_ERROR: wrong API call sequence.
                             PWM_HW_FAILURE: the HW module has a failure which
prevents it to enter the required power state.
*  Return value    : Std_ReturnType E_OK: Power Mode changed
                                    E_NOT_OK: request rejected
*  Description     : This API configures the Pwm module so that it enters the
already prepared power state, chosen between a predefined set of configured
ones.
**********************************************************************************************/
Std_ReturnType Pwm_SetPowerState(Pwm_PowerStateRequestResultType *Result);

/*************************************************************************************************
*  Service name    : Pwm_GetCurrentPowerState
*  Syntax          : Std_ReturnType Pwm_GetCurrentPowerState(
Pwm_PowerStateType* CurrentPowerState, Pwm_PowerStateRequestResultType* Result )
*  Service ID      : 0x0A
*  Sync/Async      : Synchronous
*  Reentrancy      : Non-Reentrant
*  Parameters (in) : None
*  Parameters (out): CurrentPowerState - The current power mode of the PWM HW
Unit is returned in this parameter Result: E_OK: Current power mode was
returned. E_NOT_OK: PWM_NOT_INIT: PWM Module not initialized.
*  Return value    : Std_ReturnType E_OK: Power Mode could be read.
                                    E_NOT_OK: request rejected
*  Description     : This API returns the current power state of the PWM HW
unit.
**************************************************************************************************/
Std_ReturnType
Pwm_GetCurrentPowerState(Pwm_PowerStateType *CurrentPowerState,
                         Pwm_PowerStateRequestResultType *Result);

/*************************************************************************************************
*  Service name    : Pwm_GetTargetPowerState
*  Syntax          : Std_ReturnType Pwm_GetTargetPowerState( Pwm_PowerStateType*
TargetPowerState, Pwm_PowerStateRequestResultType* Result )
*  Service ID      : 0x0B
*  Sync/Async      : Synchronous
*  Reentrancy      : Non-Reentrant
*  Parameters (in) : None
*  Parameters (out): TargetPowerState - The Target power mode of the PWM HW Unit
is returned in this parameter Result: E_OK: Target power mode was returned.
                             E_NOT_OK: PWM_NOT_INIT: PWM Module not initialized.
*  Return value    : Std_ReturnType E_OK: Power Mode could be read.
                                    E_NOT_OK: request rejected
*  Description     : This API returns the Target power state of the PWM HW unit.
**************************************************************************************************/
Std_ReturnType Pwm_GetTargetPowerState(Pwm_PowerStateType *TargetPowerState,
                                       Pwm_PowerStateRequestResultType *Result);

/*************************************************************************************************
*  Service name    : Pwm_PreparePowerState
*  Syntax          : Std_ReturnType Pwm_PreparePowerState( Pwm_PowerStateType
PowerState, Pwm_PowerStateRequestResultType* Result )
*  Service ID      : 0x0C
*  Sync/Async      : Synchronous
*  Reentrancy      : Non-Reentrant
*  Parameters (in) : PowerState - The target power state intended to be attained
*  Parameters (out): Result: E_OK: PWM Module power state preparation was
started. E_NOT_OK: PWM_NOT_INIT: PWM Module not initialized. PWM_SEQUENCE_ERROR:
wrong API call sequence (Current Power State = Target Power State)
                     PWM_POWER_STATE_NOT_SUPP: PWM Module does not support the
requested power state. PWM_TRANS_NOT_POSSIBLE: PWM Module cannot transition
directly from the current power state to the requested power state or the HW
peripheral is still busy.
*  Return value    : Std_ReturnType E_OK: Preparation process started
                                    E_NOT_OK: request rejected
*  Description     : This API starts the needed process to allow the PWM HW
module to enter the requested power state.
**************************************************************************************************/
Std_ReturnType Pwm_PreparePowerState(Pwm_PowerStateType PowerState,
                                     Pwm_PowerStateRequestResultType *Result);
#endif

#define PWM_STOP_SEC_CODE

#endif
