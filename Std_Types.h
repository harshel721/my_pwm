#ifndef STD_TYPES_H
#define STD_TYPES_H

typedef unsigned char  uint8;
typedef unsigned short uint16;
typedef unsigned long  uint32;
typedef unsigned char  boolean;
typedef float          float32;

#define TRUE        (1U)
#define FALSE       (0U)

#define STD_ON      (1U)
#define STD_OFF     (0U)

#define STD_HIGH    0x01u
#define STD_LOW     0x00u

typedef struct
{
    uint16 vendorID;
    uint16 moduleID;
    uint8 sw_major_version;
    uint8 sw_minor_version;
    uint8 sw_patch_version;
} Std_VersionInfoType;

typedef enum
{
    E_OK,
    E_NOT_OK,
}Std_ReturnType;

#define NULL_PTR    ((void*)0)

#endif
