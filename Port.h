#ifndef PORT_H
#define PORT_H

/* Includes */
#include "PortRegs.h"
#include "Port_Cfg.h"
#include "Std_Types.h"

/*Base address and offsets*/
#define BASE_ADDRESS 0x40020000
#define NUM_OF_PORTS 9

/* Macro definitions for API Service ID */
#define PORT_INIT_SID 0x00u /* Service Id for Port_Init API */
#define PORT_SET_PIN_DIRECTION_SID                                             \
  0x01u /* Service Id for Port_SetPinDirection API */
#define PORT_REFRESH_PORT_DIRECTION_SID                                        \
  0x02u /* Service Id for Port_RefreshPortDirection API */
#define PORT_GET_VERSION_INFO_SID                                              \
  0x03u                             /* Service Id for Port_GetVersionInfo API */
#define PORT_SET_PIN_MODE_SID 0x04u /* Service Id for Port_SetPinMode API */

/* Macro definitions for Error Codes specified by AUTOSAR */
#define PORT_E_PARAM_PIN 0x0A
#define PORT_E_DIRECTION_UNCHANGEABLE 0x0B
#define PORT_E_INIT_FAILED 0x0C
#define PORT_E_PARAM_INVALID_MODE 0x0D
#define PORT_E_MODE_UNCHANGEABLE 0x0E
#define PORT_E_UNINIT 0x0F
#define PORT_E_PARAM_POINTER 0x10

/* ----------------------------[Type Definitions]-----------------*/
typedef uint8 Port_PinType;

/*enum definitions */
typedef enum {
  PORT_PIN_IN = 0u, /* INPUT PIN is assigned with value 0*/
  PORT_PIN_OUT = 1u /* OUTPUT PIN is assigned with value 1*/
} Port_PinDirectionType;

typedef enum {
  PORT_PIN_MODE_DIO = 0U, /*INPUT MODE*/
  PORT_PIN_MODE_AF0 = 1U,
  PORT_PIN_MODE_AF1 = 2U,
  PORT_PIN_MODE_AF2 = 3U,
  PORT_PIN_MODE_AF3 = 4U,
  PORT_PIN_MODE_AF4 = 5U,
  PORT_PIN_MODE_AF5 = 6U,
  PORT_PIN_MODE_AF6 = 7U,
  PORT_PIN_MODE_AF7 = 8U,
  PORT_PIN_MODE_AF8 = 9U,
  PORT_PIN_MODE_AF9 = 10U,
  PORT_PIN_MODE_AF10 = 11U,
  PORT_PIN_MODE_AF11 = 12U,
  PORT_PIN_MODE_AF12 = 13U,
  PORT_PIN_MODE_AF13 = 14U,
  PORT_PIN_MODE_AF14 = 15U,
  PORT_PIN_MODE_AF15 = 16U,   /*Alternate function mode*/
  PORT_PIN_MODE_ANALOG = 17U, /*Analog mode*/
} Port_PinModeType;

typedef enum {
  PORT_PIN_OUTPUT_PUSH_PULL = 0U,
  PORT_PIN_OUTPUT_OPEN_DRAIN = 1U,
} Port_PinOutputType;

typedef enum {
  PORT_PIN_LEVEL_LOW = 0U,
  PORT_PIN_LEVEL_HIGH = 1U,
} Port_PinLevelType;

typedef enum {
  PORT_PIN_OUTPUT_SPEED_LOW = 0U,
  PORT_PIN_OUTPUT_SPEED_MEDIUM = 1U,
  PORT_PIN_OUTPUT_SPEED_HIGH = 2U,
  PORT_PIN_OUTPUT_SPEED_VERY_HIGH = 3U,
} Port_PinOutputSpeedType;

typedef enum {
  PORT_PIN_NO_PU_PD = 0U,
  PORT_PIN_PU = 1U,
  PORT_PIN_PD = 2U,
} Port_PinPUPDType;

typedef enum {
  PORT_PIN_LCKK_NOT_ACTIVE = 0U,
  PORT_PIN_LCKK_ACTIVE = 1U,
} Port_LockKeyType;

/*structure definitions */
typedef struct {
  uint8 PortPin;
  Port_PinDirectionType PortPinDirection;
  boolean PortPinDirectionChangeable;
  Port_PinModeType PortPinInitialMode;
  Port_PinOutputSpeedType PortPinOutputSpeed;
  Port_PinOutputType PortPinOutput;
  Port_PinPUPDType PortPinPUPD;
  boolean PortPinModeChangeable;
  Port_PinModeType PortPinMode;
} Port_PinDetailsType;

typedef struct {
  const uint8 PortNumberOfPortPins;
  const Port_PinDetailsType *PortPinDetails;
} Port_ContainerType;

typedef struct {
  const Port_ContainerType *PortContainer;
} Port_ConfigType;

typedef struct {
  const Port_ConfigType *CfgPtr;
  boolean PortInitStatus;
} PortGlobalType;

#define PORT_START_SEC_CONFIG_DATA_UNSPECIFIED
extern const Port_ConfigType Port_ConfigData;
#define PORT_STOP_SEC_CONFIG_DATA_UNSPECIFIED

#define PORT_START_SEC_CODE
/******************************************************************************
 *                    Public Function Declaration
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
void Port_Init(const Port_ConfigType *ConfigPtr);

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
void Port_SetPinDirection(Port_PinType Pin, Port_PinDirectionType Direction);
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
void Port_RefreshPortDirection(void);

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
void Port_GetVersionInfo(Std_VersionInfoType *versioninfo);
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
void Port_SetPinMode(Port_PinType Pin, Port_PinModeType Mode);
#endif

#define PORT_STOP_SEC_CODE

#endif
