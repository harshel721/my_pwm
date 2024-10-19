/******************************************************************************
 *                            Includes
 ******************************************************************************/
#include "Dio.h"
#include "Port.h"

#if (DIO_DEV_ERROR_DETECT == STD_ON)
#include "Det.h"
#endif

/*******************************************************************************
**                      Imported Compiler Switch Checks                       **
*******************************************************************************/
#ifndef DIO_SW_MAJOR_VERSION
#error "DIO_SW_MAJOR_VERSION is not defined."
#endif

#ifndef DIO_SW_MINOR_VERSION
#error "DIO_SW_MINOR_VERSION is not defined."
#endif

#ifndef DIO_SW_PATCH_VERSION
#error "DIO_SW_PATCH_VERSION is not defined."
#endif

#if (DIO_SW_MAJOR_VERSION != 1U)
#error "DIO_SW_MAJOR_VERSION does not match."
#endif

#if (DIO_SW_MINOR_VERSION != 0U)
#error "DIO_SW_MINOR_VERSION does not match."
#endif

#if (DIO_SW_PATCH_VERSION != 0U)
#error "DIO_SW_PATCH_VERSION does not match."
#endif

/* AUTOSAR Secification File Version Check */
#ifndef DIO_AR_RELEASE_MAJOR_VERSION
#error "DIO_AR_RELEASE_MAJOR_VERSION is not defined."
#endif

/* AUTOSAR Major and Minor release version check */
#if (DIO_AR_RELEASE_MAJOR_VERSION != 4U)
#error "DIO_AR_RELEASE_MAJOR_VERSION does not match."
#endif

/******************************************************************************
                   Private Variable Definitions
*******************************************************************************/
extern const Dio_ConfigType DioConfigSet;

/*Base address and offsets*/
#define BASE_ADDRESS 0x40020000
#define NUM_OF_PORTS 9

#define DIO_START_SEC_VAR_INIT_UNSPECIFIED
Dio_GlobalType DioGlobal = {.Config = &DioConfigSet};
#define DIO_STOP_SEC_VAR_INIT_UNSPECIFIED

extern PortRegsType *PortRegs[NUM_OF_PORTS];

#define DIO_START_SEC_CODE
/******************************************************************************
 *                    Private Function API
 ******************************************************************************/
void Dio_lclParamCheck(boolean expr, uint8 api_id, uint8 err_id,
                       Std_ReturnType *ret) {
  /* checks if the expr is TRUE */
  if ((TRUE == expr) && (E_OK == *ret)) {
    *ret = E_NOT_OK;
#if (DIO_DEV_ERROR_DETECT == STD_ON)
    /* calls Det_ReportError from Det module */
    (void)Det_ReportError(DIO_MODULE_ID, 0, api_id, err_id);
#endif
  }
}

/******************************************************************************
                     Public API
*******************************************************************************/

/* *****************************************************************************
*  Service name    : Dio_WriteChannel
*  Syntax          : void Dio_WriteChannel( Dio_ChannelType ChannelId,
                                            Dio_LevelType Level )
*  Service ID      : 0x01
*  Sync/Async      : Synchronous
*  Reentrancy      : Reentrant
*  Parameters (in) : Channel - Channel ID.
                     Level   - value to be written.
*  Parameters (out): none
*  Return value    : none
*  Description     : Service to set a level of a channel.
******************************************************************************/
void Dio_WriteChannel(Dio_ChannelType ChannelId, Dio_LevelType Level) {
  Std_ReturnType RetVal = E_OK;
  uint8 Port;
  uint32 Channel;

  Dio_lclParamCheck((ChannelId > DIO_NUM_MAX_PINS), DIO_WRITECHANNEL_ID,
                    DIO_E_PARAM_INVALID_CHANNEL_ID, &RetVal);

  if (RetVal == E_OK) {
    Port = ChannelId / 16;
    Channel = ChannelId % 16;
    switch (Level) {
    case STD_LOW:
      PortRegs[Port]->GPIOx_ODR &= ~(0x01 << Channel);
      break;
    case STD_HIGH:
      PortRegs[Port]->GPIOx_ODR |= (0x01 << Channel);
      break;
    }
  }
}

#define DIO_STOP_SEC_CODE
