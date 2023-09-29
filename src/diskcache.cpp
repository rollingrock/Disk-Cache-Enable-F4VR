// F4SE
#include <common/IPrefix.h>
#include <f4se/PluginAPI.h>
#include <f4se_common/f4se_version.h>

#include "utils.h"

static bool patch()
{
  uintptr_t fnadr = 0x1bc6f80 + getbaseaddr();
  char buf[512];
  uintptr_t addr = fnadr + 0x80;
  DWORD param = FILE_FLAG_RANDOM_ACCESS;

  if (!writeData((void *)(addr + 1), &param, sizeof(param)))
  {
    sprintf(buf, "%p error", addr);
    MessageBoxA(NULL, buf, buf, MB_OK);
    return false;
  }
  addr = fnadr + 0x94;
  if (!writeData((void *)(addr + 1), &param, sizeof(param)))
  {
    sprintf(buf, "%p error", addr);
    MessageBoxA(NULL, buf, buf, MB_OK);
    return false;
  }
  addr = fnadr + 0x89;
  param = FILE_FLAG_OVERLAPPED | FILE_FLAG_RANDOM_ACCESS;

  if (!writeData((void *)(addr + 1), &param, sizeof(param)))
  {
    sprintf(buf, "%p error", addr);
    MessageBoxA(NULL, buf, buf, MB_OK);
    return false;
  }

  return true;
}

extern "C" __declspec(dllexport) bool F4SEPlugin_Query(const F4SEInterface *f4se, PluginInfo *info)
{
  if (!f4se || !info)
  {
    return false;
  }

  info->infoVersion = PluginInfo::kInfoVersion;
  info->name = "DiskCacheEnablerVR - Fallout 4 VR";
  info->version = 1;

  return true;
}

extern "C" __declspec(dllexport) bool F4SEPlugin_Load(const F4SEInterface *f4se)
{
  if (!f4se)
  {
    return false;
  }

  if (f4se->runtimeVersion < RUNTIME_VR_VERSION_1_2_72)
  {
    return false;
  }

  return patch();
}
