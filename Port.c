/******************************************************************************
 *                            Includes
 ******************************************************************************/
/* Include own header file */
#include "Port.h"

#if (PORT_DEV_ERROR_DETECT == STD_ON)
#include "Det.h"
#endif

/*******************************************************************************
**                      Imported Compiler Switch Checks                       **
*******************************************************************************/
#ifndef PORT_SW_MAJOR_VERSION
#error "PORT_SW_MAJOR_VERSION is not defined."
#endif

#ifndef PORT_SW_MINOR_VERSION
#error "PORT_SW_MINOR_VERSION is not defined."
#endif

#ifndef PORT_SW_PATCH_VERSION
#error "PORT_SW_PATCH_VERSION is not defined."
#endif

#if (PORT_SW_MAJOR_VERSION != 1U)
#error "PORT_SW_MAJOR_VERSION does not match."
#endif

#if (PORT_SW_MINOR_VERSION != 0U)
#error "PORT_SW_MINOR_VERSION does not match."
#endif

#if (PORT_SW_PATCH_VERSION != 0U)
#error "PORT_SW_PATCH_VERSION does not match."
#endif

/* AUTOSAR Secification File Version Check */
#ifndef PORT_AR_RELEASE_MAJOR_VERSION
#error "PORT_AR_RELEASE_MAJOR_VERSION is not defined."
#endif

/* AUTOSAR Major and Minor release version check  */
#if (PORT_AR_RELEASE_MAJOR_VERSION != 4U)
#error "PORT_AR_RELEASE_MAJOR_VERSION does not match."
#endif
/* Inter Module Check for the correct version usage in the used modules */

/* Version check for DET module inclusion */
#if (PORT_DEV_ERROR_DETECT == STD_ON)

#ifndef DET_AR_RELEASE_MAJOR_VERSION
#error "DET_AR_RELEASE_MAJOR_VERSION is not defined."
#endif

#if (DET_AR_RELEASE_MAJOR_VERSION != PORT_AR_RELEASE_MAJOR_VERSION)
#error "DET_AR_RELEASE_MAJOR_VERSION does not match."
#endif

#endif /* PORT_DEV_ERROR_DETECT == STD_ON */

/******************************************************************************
 *                       Private Variable Definitions
 ******************************************************************************/
#define PORT_START_SEC_VAR_INIT_8
PortGlobalType PortGlobal;
#define PORT_STOP_SEC_VAR_INIT_8

PortRegsType *PortRegs[NUM_OF_PORTS] = {
    (PortRegsType *)(BASE_ADDRESS + (0x0400 * 0)),
    (PortRegsType *)(BASE_ADDRESS + (0x0400 * 1)),
    (PortRegsType *)(BASE_ADDRESS + (0x0400 * 2)),
    (PortRegsType *)(BASE_ADDRESS + (0x0400 * 3)),
    (PortRegsType *)(BASE_ADDRESS + (0x0400 * 4)),
    (PortRegsType *)(BASE_ADDRESS + (0x0400 * 5)),
    (PortRegsType *)(BASE_ADDRESS + (0x0400 * 6)),
    (PortRegsType *)(BASE_ADDRESS + (0x0400 * 7)),
    (PortRegsType *)(BASE_ADDRESS + (0x0400 * 8))};

static Port_PinModeType CurrentMode;

extern const Port_ConfigType PortConfigSet;

#define PORT_START_SEC_CODE
/******************************************************************************
 *                    Private Function Declaration
 ******************************************************************************/
static void Port_lclParamCheck(boolean expr, uint8 api_id, uint8 err_id,
                               Std_ReturnType *ret);

/******************************************************************************
 *                    Private Function
 ******************************************************************************/
static void Port_lclParamCheck(boolean expr, uint8 api_id, uint8 err_id,
                               Std_ReturnType *ret) {
  /* checks if the expr is TRUE */
  if ((TRUE == expr) && (E_OK == *ret)) {
#if (PORT_DEV_ERROR_DETECT == STD_ON)
    /* calls Det_ReportError from Det module */
    (void)Det_ReportError(PORT_MODULE_ID, 0, api_id, err_id);
#endif
    *ret = E_NOT_OK;
  }
}

static uint32 Port_lGetIdx(Port_PinType Pin) {
  uint32 i;

  for (i = 0; i < PortGlobal.CfgPtr->PortContainer->PortNumberOfPortPins; i++) {
    if (PortGlobal.CfgPtr->PortContainer->PortPinDetails[i].PortPin == Pin) {
      return (i);
    }
  }

  return (0xFF);
}

/* */
static void Set_Pin_Direction(Port_PinDirectionType PortPinDirection,
                              uint8 PortPin, uint8 Port, uint8 i) {
  Port_PinOutputType PortPinOutput;
  Port_PinOutputSpeedType PortPinOutputSpeed;
  Port_PinPUPDType PortPinPUPD;
  uint32 Val;

  PortRegs[Port]->GPIOx_MODER &= ~(0x03 << (PortPin * 2));
  PortRegs[Port]->GPIOx_OTYPER &= ~(0x01 << (PortPin));
  PortRegs[Port]->GPIOx_PUPDR &= ~(0x03 << (PortPin * 2));
  PortRegs[Port]->GPIOx_OSPEEDR &= ~(0x03 << (PortPin * 2));

  if (PortPinDirection == PORT_PIN_IN) {
    Val = 0x00;
    PortRegs[Port]->GPIOx_MODER |= (Val << (PortPin * 2));

    PortPinPUPD =
        PortGlobal.CfgPtr->PortContainer->PortPinDetails[i].PortPinPUPD;
    switch (PortPinPUPD) {
    case PORT_PIN_NO_PU_PD:
      Val = 0x00;
      break;
    case PORT_PIN_PU:
      Val = 0x01;
      break;
    case PORT_PIN_PD:
      Val = 0x02;
      break;
    default:
      Val = 0x00;
    }

    PortRegs[Port]->GPIOx_PUPDR |= (Val << (PortPin * 2));
  } else if (PortPinDirection == PORT_PIN_OUT) {
    Val = 0x01;
    PortRegs[Port]->GPIOx_MODER |= (Val << (PortPin * 2));

    /*Configuring output type*/
    PortPinOutput =
        PortGlobal.CfgPtr->PortContainer->PortPinDetails[i].PortPinOutput;
    switch (PortPinOutput) {
    case PORT_PIN_OUTPUT_PUSH_PULL:
      PortRegs[Port]->GPIOx_OTYPER &= ~(0x01 << PortPin);
      break;
    case PORT_PIN_OUTPUT_OPEN_DRAIN:
      PortRegs[Port]->GPIOx_OTYPER |= (0x01 << PortPin);
      break;
    default:
      PortRegs[Port]->GPIOx_OTYPER &= ~(0x01 << PortPin);
    }

    /*Configuring output speed*/
    PortPinOutputSpeed =
        PortGlobal.CfgPtr->PortContainer->PortPinDetails[i].PortPinOutputSpeed;
    switch (PortPinOutputSpeed) {
    case PORT_PIN_OUTPUT_SPEED_LOW:
      Val = 0x00;
      break;
    case PORT_PIN_OUTPUT_SPEED_MEDIUM:
      Val = 0x01;
      break;
    case PORT_PIN_OUTPUT_SPEED_HIGH:
      Val = 0x02;
      break;
    case PORT_PIN_OUTPUT_SPEED_VERY_HIGH:
      Val = 0x03;
      break;
    default:
      Val = 0x00;
    }

    PortRegs[Port]->GPIOx_OSPEEDR |= (Val << (PortPin * 2));

    /*Configuring PullUp/PullDown*/
    PortPinPUPD =
        PortGlobal.CfgPtr->PortContainer->PortPinDetails[i].PortPinPUPD;
    switch (PortPinPUPD) {
    case PORT_PIN_NO_PU_PD:
      Val = 0x00;
      break;
    case PORT_PIN_PU:
      Val = 0x01;
      break;
    case PORT_PIN_PD:
      Val = 0x02;
      break;
    default:
      Val = 0x00;
    }

    PortRegs[Port]->GPIOx_PUPDR |= (Val << (PortPin * 2));
  }
}

static void Set_AF_Mode(Port_PinModeType Mode, uint8 PortPin, uint8 Port) {
  uint8 Val = 0x02;
  PortRegs[Port]->GPIOx_MODER &= ~(0x03 << (PortPin * 2));
  PortRegs[Port]->GPIOx_MODER |= (Val << (PortPin * 2));

  switch (Mode) {
  case PORT_PIN_MODE_AF0:
    Val = 0x00;
    break;
  case PORT_PIN_MODE_AF1:
    Val = 0x01;
    break;
  case PORT_PIN_MODE_AF2:
    Val = 0x02;
    break;
  case PORT_PIN_MODE_AF3:
    Val = 0x03;
    break;
  case PORT_PIN_MODE_AF4:
    Val = 0x04;
    break;
  case PORT_PIN_MODE_AF5:
    Val = 0x05;
    break;
  case PORT_PIN_MODE_AF6:
    Val = 0x06;
    break;
  case PORT_PIN_MODE_AF7:
    Val = 0x07;
    break;
  case PORT_PIN_MODE_AF8:
    Val = 0x08;
    break;
  case PORT_PIN_MODE_AF9:
    Val = 0x09;
    break;
  case PORT_PIN_MODE_AF10:
    Val = 0xA;
    break;
  case PORT_PIN_MODE_AF11:
    Val = 0xB;
    break;
  case PORT_PIN_MODE_AF12:
    Val = 0xC;
    break;
  case PORT_PIN_MODE_AF13:
    Val = 0xD;
    break;
  case PORT_PIN_MODE_AF14:
    Val = 0xE;
    break;
  case PORT_PIN_MODE_AF15:
    Val = 0xF;
    break;
  default:
    Val = 0x00;
  }

  if ((PortPin >= 0) && (PortPin <= 7)) {
    PortRegs[Port]->GPIOx_AFRL &= ~(0xf << (PortPin * 4));
    PortRegs[Port]->GPIOx_AFRL |= (Val << (PortPin * 4));
  } else if ((PortPin >= 8) && (PortPin <= 15)) {
    PortRegs[Port]->GPIOx_AFRH &= ~(0xf << ((PortPin - 8) * 4));
    PortRegs[Port]->GPIOx_AFRH |= (Val << ((PortPin - 8) * 4));
  }
}

/******************************************************************************
 *                         Public Functions
 ******************************************************************************/

/******************************************************************************
 *  Service name    : Port_Init
 *  Syntax           : void Port_Init( const Port_ConfigType* ConfigPtr )
 *  Service ID      : 0x00
 *  Sync/Async       : Synchronous
 *  Reentrancy       : Non reentrant
 *  Parameters (in)  : ConfigPtr - Pointer to configuration set
 *  Parameters (out) : None
 *  Return value     : None
 *  Description      : Initializes the Port Driver module.
 ******************************************************************************/
void Port_Init(const Port_ConfigType *ConfigPtr) {
  uint32 Pin;
  uint8 PortPin;
  uint8 Port;
  uint8 Val;
  uint8 PortNumPins;
  uint8 i;
  Port_PinModeType PortPinInitialMode;
  Port_PinDirectionType PortPinDirection;

  /* Store the configuration for use by other APIs */
  if (ConfigPtr == NULL_PTR)
    PortGlobal.CfgPtr = &PortConfigSet;
  else
    PortGlobal.CfgPtr = ConfigPtr;

  PortNumPins = (PortGlobal.CfgPtr->PortContainer->PortNumberOfPortPins);
  for (i = 0; i < PortNumPins; i++) {
    Pin = PortGlobal.CfgPtr->PortContainer->PortPinDetails[i].PortPin;

    if (Pin == 13 || Pin == 14 || Pin == 15 || Pin == 18 || Pin == 19) {
      continue; // Skip excluded pins
    }

    if (Pin >= 0 && Pin <= PORT_NUM_MAX_PINS) {
      Port = Pin / 16;
      PortPin = Pin % 16;
    } else {
      continue;
    }

    PortPinInitialMode =
        PortGlobal.CfgPtr->PortContainer->PortPinDetails[i].PortPinInitialMode;

    if (PortPinInitialMode == PORT_PIN_MODE_DIO) {
      PortPinDirection =
          PortGlobal.CfgPtr->PortContainer->PortPinDetails[i].PortPinDirection;
      Set_Pin_Direction(PortPinDirection, PortPin, Port, i);
    } else if (PortPinInitialMode >= PORT_PIN_MODE_AF0 &&
               PortPinInitialMode <= PORT_PIN_MODE_AF15) {
      Set_AF_Mode(PortPinInitialMode, PortPin, Port);
    } else if (PortPinInitialMode == PORT_PIN_MODE_ANALOG) {
      Val = 0x03;
      PortRegs[Port]->GPIOx_MODER |= (Val << (PortPin * 2));
    }
  }

  PortGlobal.PortInitStatus = TRUE;
}

#if (PORT_SET_PIN_DIRECTION_API == STD_ON)
/******************************************************************************
*  Service name   : Port_SetPinDirection
*  Syntax          : void Port_SetPinDirection( Port_PinType Pin,
                     Port_PinDirectionType Direction)
*  Service ID     : 0x01
*  Sync/Async      : Synchronous
*  Reentrancy      : Reentrant
*  Parameters (in) : Pin       :Port Pin ID number
                     Direction :Port Pin Direction
*  Parameters (out): None
*  Return value    : None
*  Description     : Sets the port pin direction
******************************************************************************/
void Port_SetPinDirection(Port_PinType Pin, Port_PinDirectionType Direction) {
  uint32 Idx;
  Std_ReturnType ret = E_OK;
  uint8 PortPin;
  uint8 Port;
  uint8 Val;

  Port_lclParamCheck((PortGlobal.PortInitStatus != TRUE),
                     PORT_SET_PIN_DIRECTION_SID, PORT_E_UNINIT, &ret);

  Port_lclParamCheck((Pin > PORT_NUM_MAX_PINS), PORT_SET_PIN_DIRECTION_SID,
                     PORT_E_PARAM_PIN, &ret);

  Idx = Port_lGetIdx(Pin);

  Port_lclParamCheck((PortGlobal.CfgPtr->PortContainer->PortPinDetails[Idx]
                          .PortPinDirectionChangeable != TRUE),
                     PORT_SET_PIN_DIRECTION_SID, PORT_E_DIRECTION_UNCHANGEABLE,
                     &ret);

  if (Pin == 13 || Pin == 14 || Pin == 15 || Pin == 18 || Pin == 19) {
    ret = E_NOT_OK;
  }

  if (Pin >= 0 && Pin <= PORT_NUM_MAX_PINS) {
    Port = Pin / 16;
    PortPin = Pin % 16;
  } else {
    ret = E_NOT_OK;
  }

  if (ret == E_OK) {
    Val = (PortRegs[Port]->GPIOx_MODER & (0x03 << (PortPin * 2))) >>
          (PortPin * 2);
    /* Check if Pin is configured as DIO */
    if ((PortGlobal.CfgPtr->PortContainer->PortPinDetails[Idx]
             .PortPinInitialMode == PORT_PIN_MODE_DIO) ||
        Val == PORT_PIN_IN || Val == PORT_PIN_OUT) {
      Set_Pin_Direction(Direction, PortPin, Port, Idx);
    }
  }
}
#endif

/******************************************************************************
 *  Service name    :Port_RefreshPortDirection
 *  Syntax           : void Port_RefreshPortDirection( void)
 *  Service ID      : 0x02
 *  Sync/Async       : Synchronous
 *  Reentrancy       : Non reentrant
 *  Parameters (in)  : None
 *  Parameters (out) : None
 *  Return value     : None
 *  Description      : Refreshes PORT direction
 ******************************************************************************/
void Port_RefreshPortDirection(void) {
  uint8 i;
  uint8 PortNumPins;
  uint32 Pin;
  uint8 Port;
  uint8 PortPin;
  Port_PinDirectionType Direction;
  Std_ReturnType ret = E_OK;

  Port_lclParamCheck((PortGlobal.PortInitStatus != TRUE),
                     PORT_REFRESH_PORT_DIRECTION_SID, PORT_E_UNINIT, &ret);

  if (E_OK == ret) {
    PortNumPins = (PortGlobal.CfgPtr->PortContainer->PortNumberOfPortPins);

    for (i = 0; i < PortNumPins; i++) {
      Pin = PortGlobal.CfgPtr->PortContainer->PortPinDetails[i].PortPin;

      if (Pin == 13 || Pin == 14 || Pin == 15 || Pin == 18 || Pin == 19) {
        continue; // Skip excluded pins
      }

      if (Pin >= 0 && Pin <= PORT_NUM_MAX_PINS) {
        Port = Pin / 16;
        PortPin = Pin % 16;
      } else {
        continue;
      }

      /* Check if Pin is configured as DIO */
      if (PortGlobal.CfgPtr->PortContainer->PortPinDetails[i]
              .PortPinInitialMode == PORT_PIN_MODE_DIO) {
        /* Check if PortPinDirectionChangeable is FALSE for the pin */
        if (PortGlobal.CfgPtr->PortContainer->PortPinDetails[i]
                .PortPinDirectionChangeable == TRUE) {
          Direction = PortGlobal.CfgPtr->PortContainer->PortPinDetails[i]
                          .PortPinDirection;
          Set_Pin_Direction(Direction, PortPin, Port, i);
        }
      }
    }
  }
}

#if (PORT_VERSION_INFO_API == STD_ON)
/******************************************************************************
*  Service name    : Port_GetVersionInfo
*  Syntax           : void Port_GetVersionInfo( Std_VersionInfoType*
versioninfo)
*  Service ID      : 0x03
*  Sync/Async       : Synchronous
*  Reentrancy       : Reentrant
*  Parameters (in)  : versioninfo: Pointer to where to store the version
                      information of this module
*  Parameters (out) : None
*  Return value     : None
*  Description      : Returns the version information of this module.
******************************************************************************/
void Port_GetVersionInfo(Std_VersionInfoType *versioninfo) {

  Std_ReturnType ret = E_OK;

  /* SWS_Port_00225 */
  Port_lclParamCheck((boolean)(NULL_PTR == versioninfo),
                     PORT_GET_VERSION_INFO_SID, PORT_E_PARAM_POINTER, &ret);

  if (E_OK == ret) {
    versioninfo->vendorID = PORT_VENDOR_ID;
    versioninfo->moduleID = PORT_MODULE_ID;
    versioninfo->sw_major_version = PORT_SW_MAJOR_VERSION;
    versioninfo->sw_minor_version = PORT_SW_MINOR_VERSION;
    versioninfo->sw_patch_version = PORT_SW_PATCH_VERSION;
  }
}
#endif

#if (PORT_SET_PIN_MODE_API == STD_ON)
/******************************************************************************
*  Service name    : Port_SetPinMode
*  Syntax           : void Port_SetPinMode( Port_PinType Pin,
                                           Port_PinModeType Mode)
*  Service ID      : 0x04
*  Sync/Async       : Synchronous
*  Reentrancy       : Reentrant
*  Parameters (in)  : Pin :Port Pin ID number
                      Mode:New Port Pin mode to be set on port pin.
*  Parameters (out) : None
*  Return value     : None
*  Description      : Sets the PORT pin mode
******************************************************************************/
void Port_SetPinMode(Port_PinType Pin, Port_PinModeType Mode) {
  uint32 Idx;
  Std_ReturnType ret = E_OK;
  uint8 PortPin;
  uint8 Port;

  Port_lclParamCheck((PortGlobal.PortInitStatus != TRUE), PORT_SET_PIN_MODE_SID,
                     PORT_E_UNINIT, &ret);

  Port_lclParamCheck((Pin > PORT_NUM_MAX_PINS), PORT_SET_PIN_MODE_SID,
                     PORT_E_PARAM_PIN, &ret);

  Idx = Port_lGetIdx(Pin);

  Port_lclParamCheck((PortGlobal.CfgPtr->PortContainer->PortPinDetails[Idx]
                          .PortPinModeChangeable != TRUE),
                     PORT_SET_PIN_MODE_SID, PORT_E_MODE_UNCHANGEABLE, &ret);

  Pin = PortGlobal.CfgPtr->PortContainer->PortPinDetails[Idx].PortPin;

  if (Pin == 13 || Pin == 14 || Pin == 15 || Pin == 18 || Pin == 19) {
    ret = E_NOT_OK;
  }

  if (Pin >= 0 && Pin <= PORT_NUM_MAX_PINS) {
    Port = Pin / 16;
    PortPin = Pin % 16;
  } else {
    ret = E_NOT_OK;
  }

  if (E_OK == ret) {
    if (Mode == PORT_PIN_MODE_DIO) {
      PortRegs[Port]->GPIOx_MODER &= ~(0x03 << PortPin);
    } else if (Mode >= PORT_PIN_MODE_AF0 && Mode <= PORT_PIN_MODE_AF15) {
      Set_AF_Mode(Mode, PortPin, Port);
    } else if (Mode == PORT_PIN_MODE_ANALOG) {
      PortRegs[Port]->GPIOx_MODER |= (0x03 << PortPin);
    }
  }
}
#endif

#define PORT_STOP_SEC_CODE
