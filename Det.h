#ifndef DET_H
#define DET_H

#include "Std_Types.h"

#define DET_AR_RELEASE_MAJOR_VERSION 4

boolean CheckDetErr(uint16 ModuleId, uint8 InstanceId, uint8 ApiId,
                    uint8 ErrorId);

void Det_ReportError(uint16 ModuleId, uint8 InstanceId, uint8 ApiId,
                     uint8 ErrorId);

typedef struct {
  uint16 ModuleId;
  uint8 InstanceId;
  uint8 ApiId;
  uint8 ErrorId;
} Det_ErrorDataType;

#endif
