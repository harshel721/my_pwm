#include "Det.h"

static Det_ErrorDataType DetErrData;

boolean CheckDetErr(uint16 ModuleId, uint8 InstanceId, uint8 ApiId,
                    uint8 ErrorId) {
  if ((DetErrData.ModuleId == ModuleId) &&
      (DetErrData.InstanceId == InstanceId) && (DetErrData.ApiId == ApiId) &&
      (DetErrData.ErrorId == ErrorId)) {
    return TRUE;
  } else {
    return FALSE;
  }
}

void Det_ReportError(uint16 ModuleId, uint8 InstanceId, uint8 ApiId,
                     uint8 ErrorId) {
  DetErrData.ModuleId = ModuleId;
  DetErrData.InstanceId = InstanceId;
  DetErrData.ApiId = ApiId;
  DetErrData.ErrorId = ErrorId;
}
