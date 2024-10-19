/* Header Protection */
#ifndef MCU_H
#define MCU_H

/* Includes */
#include "Dem.h"
#include "McuRegs.h"
#include "Mcu_Cfg.h"
#include "Std_Types.h"

/* Macro definitions for API Service ID */
#define MCU_INIT_SID 0x00      /* Service ID for MCU_Init API */
#define MCU_INITCLOCK_SID 0x02 /* Service ID for MCU_InitClock API */
#define MCU_DISTRIBUTEPLLCLK_SID                                               \
  0x03 /* Service ID for MCU_DistributePllClock API */
#define MCU_GETPLLSTATUS_SID 0x04 /* Service ID for MCU_GetPllStatus API */
#define MCU_GETVERSIONINFO_SID                                                 \
  0x09 /* Service ID for MCU_GetVersionInfo API                                \
        */
#define MCU_GETPERIPHERALCLKFREQ_SID                                           \
  0x0B /* Service ID for MCU_GetPeripheralClkFreq API */

/* Macro definitions for Error Codes specified by AUTOSAR */
#define MCU_E_PARAM_CONFIG 0x0A /* API service called with wrong parameter */
#define MCU_E_PARAM_CLOCK 0x0B  /* API service called with wrong parameter */
#define MCU_E_PARAM_MODE 0x0C   /* API service called with wrong parameter */
#define MCU_E_PARAM_RAMSECTION                                                 \
  0x0D /* API service called with wrong parameter */
#define MCU_E_PLL_NOT_LOCKED                                                   \
  0x0E                    /* API service called when PLL status is not locked */
#define MCU_E_UNINIT 0x0F /* API service used without module initialisation */
#define MCU_E_PARAM_POINTER 0x10 /* APIs called with a Null Pointer */
#define MCU_E_INIT_FAILED                                                      \
  0x11 /* API service used when initalisation failed                           \
        */

/* General defines */
#define MCU_RESET_VAL_UNDEFINED 0xFF

/*enum definitions */
/* SWS_Mcu_00250 */
typedef enum {
  MCU_PLL_LOCKED,
  MCU_PLL_UNLOCKED,
  MCU_PLL_STATUS_UNDEFINED
} Mcu_PllStatusType;

typedef struct {
  uint8 MCU_GPIOA;
  uint8 MCU_GPIOB;
  uint8 MCU_GPIOC;
  uint8 MCU_GPIOD;
  uint8 MCU_GPIOE;
  uint8 MCU_GPIOF;
  uint8 MCU_GPIOG;
  uint8 MCU_GPIOH;
  uint8 MCU_GPIOI;
  uint8 MCU_USART1;
  uint8 MCU_USART2;
  uint8 MCU_USART3;
  uint8 MCU_USART4;
  uint8 MCU_USART5;
  uint8 MCU_USART6;
  uint8 MCU_CAN1;
  uint8 MCU_CAN2;
  uint8 MCU_TIM1;
  uint8 MCU_TIM2;
  uint8 MCU_TIM8;
  uint8 PWREN;
} McuClkType;

typedef struct {
  float32 McuClockReferencePointFrequency;
} McuClockReferencePointModule;

/* SWS_Mcu_00251 */
typedef uint8 Mcu_ClockType;

typedef struct {
  uint8 McuClockSettingId;
  McuClkType *McuClockType;
  McuClockReferencePointModule *McuClockReferencePoint;
  uint32 PLLM;
  uint32 PLLN;
  uint32 PLLP;
  uint32 HSE;
  uint32 HSI;
} Mcu_ClkSettingConfigType;

/* Structure definitions */

typedef struct {
  uint8 numClockSettings;
  const Mcu_ClkSettingConfigType *McuClockSettingData;
} Mcu_ConfigType;

typedef struct {
  const Mcu_ConfigType *CfgPtr;
  boolean McuInitialized;
  boolean McuClkInit;
  uint8 mcuClockId;
} Mcu_GlobalType;

#define MCU_START_SEC_CONFIG_DATA_UNSPECIFIED
extern const Mcu_ConfigType McuConfigData;
#define MCU_STOP_SEC_CONFIG_DATA_UNSPECIFIED

/* Public Function Declarations */
#define MCU_START_SEC_CODE
/******************************************************************************
 *  Service name    : Mcu_Init
 *  Syntax          : void Mcu_Init( const Mcu_ConfigType *ConfigPtr )
 *  Service ID      : 0x00
 *  Sync/Async      : Synchronous
 *  Reentrancy      : Non reentrant
 *  Parameters (in) : ConfigPtr - Pointer to MCU driver configuration set
 *  Parameters (out): None
 *  Return value    : None
 *  Description     : Service for MCU initialization
 ******************************************************************************/
void Mcu_Init(const Mcu_ConfigType *ConfigPtr);

#if (MCU_INIT_CLOCK == STD_ON)
/******************************************************************************
 *  Service name    : Mcu_InitClock
 *  Syntax          : Std_ReturnType Mcu_InitClock( Mcu_ClockType ClockSetting )
 *  Service ID      : 0x02
 *  Sync/Async      : Synchronous
 *  Reentrancy      : Non reentrant
 *  Parameters (in) : Clock Setting
 *  Parameters (out): None
 *  Return value    : E_OK: command has been accepted
 *                    E_NOT_OK: command has not been accepted
 *  Description     : Service to initalize the PLL & other MCU clock options
 ******************************************************************************/
Std_ReturnType Mcu_InitClock(Mcu_ClockType ClockSetting);
#endif

#if (MCU_NO_PLL == STD_OFF)
/******************************************************************************
 *  Service name    : Mcu_DistributePllClock
 *  Syntax          : Std_ReturnType Mcu_DistributePllClock( void )
 *  Service ID      : 0x03
 *  Sync/Async      : Synchronous
 *  Reentrancy      : Non reentrant
 *  Parameters (in) : None
 *  Parameters (out): None
 *  Return value    : E_OK: command has been accepted
 *                    E_NOT_OK: command has not been accepted
 *  Description     : Activates the PLL clock to the MCU clock distribution.
 ******************************************************************************/
Std_ReturnType Mcu_DistributePllClock(void);
#endif

/******************************************************************************
 *  Service name    : Mcu_GetPllStatus
 *  Syntax          : Mcu_PllStatusType Mcu_GetPllStatus( void )
 *  Service ID      : 0x04
 *  Sync/Async      : Synchronous
 *  Reentrancy      : Reentrant
 *  Parameters (in) : None
 *  Parameters (out): None
 *  Return value    : Mcu_PllStatusType - PLL status
 *  Description     : This service provides the lock status of the PLL.
 ******************************************************************************/
Mcu_PllStatusType Mcu_GetPllStatus(void);

#if (MCU_VERSION_INFO_API == STD_ON)
/******************************************************************************
*  Service name    : Mcu_GetVersionInfo
*  Syntax          : void Mcu_GetVersionInfo(Std_VersionInfoType *versioninfo)
*  Service ID      : 0x09
*  Sync/Async      : Synchronous
*  Reentrancy      : Reentrant
*  Parameters (in) : None
*  Parameters (out): None
*  Return value    : versioninfo : Pointer to where to store the version
                     information of this module.
*  Description     : This service returns the version information of this
module.
********************************************************************************/
void Mcu_GetVersionInfo(Std_VersionInfoType *versioninfo);
#endif

#define MCU_STOP_SEC_CODE

#endif /* MCU_H */
