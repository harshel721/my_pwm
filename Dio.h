#ifndef DIO_H
#define DIO_H

#include "Dio_Cfg.h"
#include "Std_Types.h"

#define DIO_READCHANNEL_ID 0x00u
#define DIO_WRITECHANNEL_ID 0x01u
#define DIO_READPORT_ID 0x02u
#define DIO_WRITEPORT_ID 0x03u
#define DIO_READCHANNELGROUP_ID 0x04u
#define DIO_WRITECHANNELGROUP_ID 0x05u
#define DIO_INIT_ID 0x10u
#define DIO_FLIPCHANNEL_ID 0x11u
#define DIO_GETVERSIONINFO_ID 0x12u
#define DIO_GLOBAL_ID 0xFFu

/*SWS_DIO_00175 - Invalid channel name requested */
#define DIO_E_PARAM_INVALID_CHANNEL_ID 0x0Au
#define DIO_E_PARAM_CONFIG 0x10u
#define DIO_E_PARAM_INVALID_PORT_ID 0x14u
#define DIO_E_PARAM_INVALID_GROUP_ID 0x1Fu
#define DIO_E_PARAM_POINTER 0x20u

typedef enum {
  DIO_PIN_IN = 0u, /* INPUT PIN is assigned with value 0*/
  DIO_PIN_OUT = 1u /* OUTPUT PIN is assigned with value 1*/
} Dio_PinDirectionType;

/* Dio_ChannelType
SWS_Dio_00182 - Dio_ChannelType
SWS_Dio_00015 - Parameters of type Dio_ChannelType contain the numeric ID of a
DIO channel. SWS_Dio_00180 - The mapping of the ID is implementation specific
but not configurable.*/

typedef uint32 Dio_ChannelType;

/* Dio_PortType
SWS_Dio_00183 - Dio_PortType
SWS_Dio_00018 - Parameters of type Dio_PortType contain the numeric ID of a DIO
port. SWS_Dio_00181 - The mapping of ID is implementation specific but not
configurable.*/

typedef uint32 Dio_PortType;

typedef struct {
  Dio_ChannelType channelId;
  Dio_PinDirectionType Direction;
} Dio_ChannelConfigType;

typedef struct {
  uint8 DioChannelGroupIdentification;
  uint32 DioPortMask;
  uint8 DioPortOffset;
} Dio_ChannelGroupType;

/* Dio_LevelType
SWS_Dio_00185 - Dio_LevelType
SWS_Dio_00023 - Dio_LevelType is the type for the possible levels that a DIO
channel can have (input or output) */
typedef uint8 Dio_LevelType;

/* Dio_PortLevelType
SWS_Dio_00186 - Dio_PortLevelType
SWS_Dio_00103 - The port width within the types defined for the DIO Driver
                shall be the size of the largest port on the MCU which may be
                accessed by the DIO Drive.
SWS_Dio_00024 - Dio_PortLevelType is the type for the value of a DIO port*/
typedef uint16 Dio_PortLevelType;

typedef struct {
  const uint8 DioNumPorts;
  const uint8 DioNumChannels;
  const uint8 DioNumChannelGroups;
  const Dio_PortType *DioPortData;
  const Dio_ChannelType *DioChannelData;
  const Dio_ChannelGroupType *DioNumChannelGroupsData;
} Dio_ConfigType;

typedef struct {
  const Dio_ConfigType *Config;
} Dio_GlobalType;

/* Dio_ConfigData holds the configuration for Dio module. */
#define DIO_START_SEC_CONFIG_DATA_UNSPECIFIED
extern const Dio_ConfigType Dio_ConfigData;
#define DIO_STOP_SEC_CONFIG_DATA_UNSPECIFIED

/* ----------------------------[Public API's]-----------------*/
#define DIO_START_SEC_CODE
Dio_LevelType Dio_ReadChannel(Dio_ChannelType channelId);

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
void Dio_WriteChannel(Dio_ChannelType channelId, Dio_LevelType level);

void Dio_lclParamCheck(boolean expr, uint8 api_id, uint8 err_id,
                       Std_ReturnType *ret);

#define DIO_STOP_SEC_CODE

#endif
