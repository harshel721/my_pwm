/******************************************************************************
 *                            Includes
 ******************************************************************************/
#include "Mcu.h"

#if (MCU_DEV_ERROR_DETECT == STD_ON)
#include "Det.h"
#endif

/*******************************************************************************
 **                      Imported Compiler Switch Checks **
 *******************************************************************************/
#ifndef MCU_SW_MAJOR_VERSION
#error "MCU_SW_MAJOR_VERSION is not defined."
#endif

#ifndef MCU_SW_MINOR_VERSION
#error "MCU_SW_MINOR_VERSION is not defined."
#endif

#ifndef MCU_SW_PATCH_VERSION
#error "MCU_SW_PATCH_VERSION is not defined."
#endif

#if (MCU_SW_MAJOR_VERSION != 1U)
#error "MCU_SW_MAJOR_VERSION does not match."
#endif

#if (MCU_SW_MINOR_VERSION != 0U)
#error "MCU_SW_MINOR_VERSION does not match."
#endif

#if (MCU_SW_PATCH_VERSION != 0U)
#error "MCU_SW_PATCH_VERSION does not match."
#endif

/* AUTOSAR Secification File Version Check */
#ifndef MCU_AR_RELEASE_MAJOR_VERSION
#error "MCU_AR_RELEASE_MAJOR_VERSION is not defined."
#endif

/* AUTOSAR Major and Minor release version check  */
#if (MCU_AR_RELEASE_MAJOR_VERSION != 4U)
#error "MCU_AR_RELEASE_MAJOR_VERSION does not match."
#endif

/* Inter Module Check for the correct version usage in the used modules */

/* Version Check */
/* Version check for DET module inclusion */
#if (MCU_DEV_ERROR_DETECT == STD_ON)

#ifndef DET_AR_RELEASE_MAJOR_VERSION
#error "DET_AR_RELEASE_MAJOR_VERSION is not defined."
#endif

#if (DET_AR_RELEASE_MAJOR_VERSION != MCU_AR_RELEASE_MAJOR_VERSION)
#error "DET_AR_RELEASE_MAJOR_VERSION does not match."
#endif

#endif /* MCU_DEV_ERROR_DETECT == STD_ON */

/******************************************************************************
 *                       Private Variable Definitions
 ******************************************************************************/
#define MCU_START_SEC_VAR_INIT_8
Mcu_GlobalType McuGlobal;
#define MCU_STOP_SEC_VAR_INIT_8

Mcu_RCC *RCC = (Mcu_RCC *)0x40023800;
#define MCU_START_SEC_CODE

/******************************************************************************
 *                    Private Function Declaration
 ******************************************************************************/
static void Mcu_lclParamCheck(boolean expr, uint8 api_id, uint8 err_id,
                              Std_ReturnType *rv);

/******************************************************************************
 *                         Public Functions
 ******************************************************************************/

/******************************************************************************
 *  Service name    : Mcu_Init
 *  Syntax          : void Mcu_Init( const Mcu_ConfigType* ConfigPtr )
 *  Service ID      : 0x00
 *  Sync/Async      : Synchronous
 *  Reentrancy      : Non reentrant
 *  Parameters (in) : ConfigPtr - Pointer to MCU driver configuration set
 *  Parameters (out): None
 *  Return value    : None
 *  Description     : Service for MCU initialization
 ******************************************************************************/
void Mcu_Init(const Mcu_ConfigType *ConfigPtr) {
  Std_ReturnType rv = E_OK;

  Mcu_lclParamCheck((boolean)(NULL_PTR != ConfigPtr), MCU_INIT_SID,
                    MCU_E_PARAM_POINTER, &rv);
  /* Store the Configuration for use by other APIs */
  McuGlobal.CfgPtr = ConfigPtr;

  if (rv == E_OK) {
    /* Reset CFGR register */
    RCC->CFGR = 0;

    /* Reset CR register */
    RCC->CR = (1 << 0) | (1 << 1) | (1 << 16) | (1 << 24);

    /* Reset PLLCFGR register */
    RCC->PLLCFGR = (0x2 << 0) | (0x0 << 4) | (0x0 << 6) | (0x2 << 16) |
                   (0x0 << 22) | (0x0 << 24) | (0x0 << 25) | (0x0 << 26) |
                   (0x0 << 27) | (0x0 << 28);

    /* Disable all interrupts */
    RCC->CIR = 0;

    RCC->APB1ENR = 0;
    RCC->APB2ENR = 0;
  }

  McuGlobal.McuInitialized = TRUE;
}

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
Std_ReturnType Mcu_InitClock(Mcu_ClockType ClockSetting) {
  Std_ReturnType rv = E_OK;
  uint32 PLLM;
  uint32 PLLN;
  uint32 PLLP;
  uint32 PLLPVal;
  uint32 PLLMVal;
  uint32 ClockType;
  uint32 Hse = McuGlobal.CfgPtr->McuClockSettingData[ClockSetting].HSE;
  uint32 Hsi = McuGlobal.CfgPtr->McuClockSettingData[ClockSetting].HSI;
  float McuClkFrequency;

  /* SWS_Mcu_00125 */
  Mcu_lclParamCheck((boolean)(McuGlobal.McuInitialized == TRUE),
                    MCU_INITCLOCK_SID, MCU_E_UNINIT, &rv);

  /* SWS_Mcu_00019 */
  Mcu_lclParamCheck(
      (boolean)(ClockSetting < McuGlobal.CfgPtr->numClockSettings),
      MCU_INITCLOCK_SID, MCU_E_PARAM_CLOCK, &rv);

  if (rv == E_OK) {
    if (Hse == STD_ON) {
      RCC->CR &= ~(1 << 0); /* Clear HSION bit */
      RCC->CR |= (1 << 16); /* Enable HSEON bit */
      /* Wait until HSE is ready */
      while (!(RCC->CR & (1 << 17)))
        ;
      /* Make HSE as PLL source */
      RCC->PLLCFGR |= (1 << 22);
    } else if (Hsi == STD_ON) {
      RCC->CR &= ~(1 << 16); /* Clear HSEON bit*/
      RCC->CR |= (1 << 0);   /* Enable HSION bit */
      /* Wait until HSI is ready */
      while (!(RCC->CR & (1 << 1)))
        ;
      /* Make HSI as PLL source */
      RCC->PLLCFGR &= ~(1 << 22);
    }

    PLLM = McuGlobal.CfgPtr->McuClockSettingData[ClockSetting].PLLM;
    PLLN = McuGlobal.CfgPtr->McuClockSettingData[ClockSetting].PLLN;
    PLLP = McuGlobal.CfgPtr->McuClockSettingData[ClockSetting].PLLP;
    McuClkFrequency =
        McuGlobal.CfgPtr->McuClockSettingData[ClockSetting]
            .McuClockReferencePoint->McuClockReferencePointFrequency;

    switch (PLLP) {
    case 2:
      PLLPVal = 0;
      break;
    case 4:
      PLLPVal = 1;
      break;
    case 6:
      PLLPVal = 2;
      break;
    case 8:
      PLLPVal = 3;
      break;
    default:
      RCC->PLLCFGR = (uint32)0x00000000;
      break;
    }

    RCC->PLLCFGR &= ~(0x1FF << 6);
    RCC->PLLCFGR &= ~(0x0F << 24); /* clear PLLQ bits */
    /* Configure the PLLCFG register with the new values */
    RCC->PLLCFGR |= (PLLM << 0) | (PLLN << 6) | (PLLPVal << 16) | (0 << 22);

    /* Enable PLL */
    RCC->CR &= ~(1 << 24);
    RCC->CR |= (1 << 24);
    /*wait until PLL is ready*/
    while (!(RCC->CR & (1 << 25)))
      ;
    RCC->CFGR &= ~(1 << 4); // HPRE Prescaler by 1

    /*Set Prescaler values using McuClkFrequency*/
    switch ((uint8)McuClkFrequency) {
    case 84:
      RCC->CFGR |= (1 << 15);
      break;
    case 42:
      RCC->CFGR |= (5 << 10);
      break;
    case 168:
      RCC->CFGR &= (15 << 4);
      break;
    default:
      RCC->CFGR |= (uint32)0x00000000;
      break;
    }

    RCC->CFGR |= (5 << 13); /* Prescaler2 (APB1) */

    RCC->CFGR &= ~(3 << 0); /* reset SW bit */
    /*Making the PLL clock as source */
    RCC->CFGR |= (2 << 0);

    /* Wait until PLL clock to be source */
    while (!(RCC->CFGR & (2 << 2)))
      ;
  }
  McuGlobal.McuClkInit = TRUE;

  return rv;
}
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
Std_ReturnType Mcu_DistributePllClock(void) {
  Std_ReturnType rv = E_OK;
  /* SWS_Mcu_00125 */
  Mcu_lclParamCheck((boolean)(McuGlobal.McuInitialized == TRUE),
                    MCU_DISTRIBUTEPLLCLK_SID, MCU_E_UNINIT, &rv);

  /* SWS_Mcu_00122 */
  Mcu_lclParamCheck((boolean)(1 != MCU_PLL_LOCKED), MCU_DISTRIBUTEPLLCLK_SID,
                    MCU_E_PLL_NOT_LOCKED, &rv);

  if (McuGlobal.CfgPtr->McuClockSettingData[McuGlobal.mcuClockId]
          .McuClockType->PWREN == STD_ON) {
    RCC->APB1ENR |= (1 << 28); /* Enable the clock for PWREN */
  }

  if (McuGlobal.CfgPtr->McuClockSettingData[McuGlobal.mcuClockId]
          .McuClockType->MCU_GPIOA == STD_ON) {
    RCC->AHB1ENR |= (1 << 0); /* Enable the clock for GPIOAEN */
  }

  if (McuGlobal.CfgPtr->McuClockSettingData[McuGlobal.mcuClockId]
          .McuClockType->MCU_GPIOB == STD_ON) {
    RCC->AHB1ENR |= (1 << 1); /* Enable the clock for GPIOBEN */
  }

  if (McuGlobal.CfgPtr->McuClockSettingData[McuGlobal.mcuClockId]
          .McuClockType->MCU_GPIOC == STD_ON) {
    RCC->AHB1ENR |= (1 << 2); /* Enable the clock for GPIOCEN */
  }

  if (McuGlobal.CfgPtr->McuClockSettingData[McuGlobal.mcuClockId]
          .McuClockType->MCU_GPIOD == STD_ON) {
    RCC->AHB1ENR |= (1 << 3); /* Enable the clock for GPIODEN */
  }

  if (McuGlobal.CfgPtr->McuClockSettingData[McuGlobal.mcuClockId]
          .McuClockType->MCU_GPIOE == STD_ON) {
    RCC->AHB1ENR |= (1 << 4); /* Enable the clock for GPIOEEN */
  }

  if (McuGlobal.CfgPtr->McuClockSettingData[McuGlobal.mcuClockId]
          .McuClockType->MCU_GPIOF == STD_ON) {
    RCC->AHB1ENR |= (1 << 5); /* Enable the clock for GPIOFEN */
  }

  if (McuGlobal.CfgPtr->McuClockSettingData[McuGlobal.mcuClockId]
          .McuClockType->MCU_GPIOG == STD_ON) {
    RCC->AHB1ENR |= (1 << 6); /* Enable the clock for GPIOGEN */
  }

  if (McuGlobal.CfgPtr->McuClockSettingData[McuGlobal.mcuClockId]
          .McuClockType->MCU_GPIOH == STD_ON) {
    RCC->AHB1ENR |= (1 << 7); /* Enable the clock for GPIOHEN */
  }

  if (McuGlobal.CfgPtr->McuClockSettingData[McuGlobal.mcuClockId]
          .McuClockType->MCU_GPIOI == STD_ON) {
    RCC->AHB1ENR |= (1 << 8); /* Enable the clock for GPIOIEN */
  }

  if (McuGlobal.CfgPtr->McuClockSettingData[McuGlobal.mcuClockId]
          .McuClockType->MCU_CAN1 == STD_ON) {
    RCC->APB1ENR |= (1 << 25); /* Enable the clock for CAN1EN */
  }
  if (McuGlobal.CfgPtr->McuClockSettingData[McuGlobal.mcuClockId]
          .McuClockType->MCU_CAN2 == STD_ON) {
    RCC->APB1ENR |= (1 << 26); /* Enable the clock for CAN2EN */
  }

  if (McuGlobal.CfgPtr->McuClockSettingData[McuGlobal.mcuClockId]
          .McuClockType->MCU_USART1 == STD_ON) {
    RCC->APB2ENR |= (1 << 4); /* Enable the clock for UART1 */
  }

  if (McuGlobal.CfgPtr->McuClockSettingData[McuGlobal.mcuClockId]
          .McuClockType->MCU_USART2 == STD_ON) {
    RCC->APB1ENR |= (1 << 17); /* Enable the clock for UART2 */
  }

  if (McuGlobal.CfgPtr->McuClockSettingData[McuGlobal.mcuClockId]
          .McuClockType->MCU_USART3 == STD_ON) {
    RCC->APB1ENR |= (1 << 18); /* Enable the clock for UART3 */
  }

  if (McuGlobal.CfgPtr->McuClockSettingData[McuGlobal.mcuClockId]
          .McuClockType->MCU_USART4 == STD_ON) {
    RCC->APB1ENR |= (1 << 19); /* Enable the clock for UART4 */
  }

  if (McuGlobal.CfgPtr->McuClockSettingData[McuGlobal.mcuClockId]
          .McuClockType->MCU_USART5 == STD_ON) {
    RCC->APB1ENR |= (1 << 20); /* Enable the clock for UART6 */
  }

  if (McuGlobal.CfgPtr->McuClockSettingData[McuGlobal.mcuClockId]
          .McuClockType->MCU_USART6 == STD_ON) {
    RCC->APB2ENR |= (1 << 5); /* Enable the clock for UART6 */
  }

  if (McuGlobal.CfgPtr->McuClockSettingData[McuGlobal.mcuClockId]
          .McuClockType->MCU_TIM1 == STD_ON) {
    RCC->APB2ENR |= (1 << 0); /* Enable the clock for TIM1 */
  }

  if (McuGlobal.CfgPtr->McuClockSettingData[McuGlobal.mcuClockId]
          .McuClockType->MCU_TIM2 == STD_ON) {
    RCC->APB1ENR |= (1 << 0); /* Enable the clock for TIM2 */
  }

  if (McuGlobal.CfgPtr->McuClockSettingData[McuGlobal.mcuClockId]
          .McuClockType->MCU_TIM8 == STD_ON) {
    RCC->APB2ENR |= (1 << 1); /* Enable the clock for TIM8 */
  }

  return rv;
}
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
Mcu_PllStatusType Mcu_GetPllStatus(void) {
  Std_ReturnType rv = E_OK;
  Mcu_PllStatusType status = MCU_PLL_STATUS_UNDEFINED;

  /* SWS_Mcu_00206 */
  if (MCU_NO_PLL != STD_ON) {
    /* SWS_Mcu_00132 */
    Mcu_lclParamCheck((boolean)(McuGlobal.McuInitialized == TRUE),
                      MCU_GETPLLSTATUS_SID, MCU_E_UNINIT, &rv);
    if (rv == E_OK) {
      if (RCC->CR & (1 << 25)) {
        status = MCU_PLL_LOCKED;
      } else {
        status = MCU_PLL_UNLOCKED;
      }
    }
  }

  return status;
}

#if (MCU_VERSION_INFO_API == STD_ON)
/******************************************************************************
 *  Service name    : Mcu_GetVersionInfo
 *  Syntax          : void Mcu_GetVersionInfo(Std_VersionInfoType* versioninfo)
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
void Mcu_GetVersionInfo(Std_VersionInfoType *versioninfo) {
  Std_ReturnType rv = E_OK;

  Mcu_lclParamCheck((boolean)(NULL_PTR != versioninfo), MCU_GETVERSIONINFO_SID,
                    MCU_E_PARAM_POINTER, &rv);

  if (E_OK == rv) {
    versioninfo->vendorID = MCU_VENDOR_ID;
    versioninfo->moduleID = MCU_MODULE_ID;
    versioninfo->sw_major_version = MCU_SW_MAJOR_VERSION;
    versioninfo->sw_minor_version = MCU_SW_MINOR_VERSION;
    versioninfo->sw_patch_version = MCU_SW_PATCH_VERSION;
  }
}
#endif

/******************************************************************************
 *                         Private Function Defination
 ******************************************************************************/
static void Mcu_lclParamCheck(boolean expr, uint8 api_id, uint8 err_id,
                              Std_ReturnType *rv) {
  if ((E_OK == *rv) && (expr == FALSE)) {
#if (MCU_DEV_ERROR_DETECT == STD_ON)
    /* calls Det_ReportError from Det module */
    (void)Det_ReportError(MCU_MODULE_ID, 0, api_id, err_id);
#endif
    *rv = E_NOT_OK;
  }
}

#define MCU_STOP_SEC_CODE
