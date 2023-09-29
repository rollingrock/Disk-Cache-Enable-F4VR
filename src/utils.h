#ifndef UTILS_H
#define UTILS_H

// #include "../minisonar/minisonar.h"

#include <stdint.h>
#include <stdio.h>
#include <windows.h>

#ifdef __cplusplus
extern "C"
{
#endif // __cplusplus

  static void *g_thisAddr = NULL;

  static uintptr_t getbaseaddr()
  {
    return (uintptr_t)GetModuleHandle(NULL);
  }

  static uintptr_t getthisaddr()
  {
    return (uintptr_t)g_thisAddr;
  }

  static void setThisAddr(uintptr_t addr)
  {
    g_thisAddr = (void *)addr;
  }

  inline void *fillNOP(void *dest, size_t count)
  {
    DWORD origattrib = 0;
    int ret = 0;
    ret = VirtualProtect(dest, count, PAGE_EXECUTE_READWRITE, &origattrib);

    if (!ret)
    {
      printf("VirtualProtect(%p) Failed\n", dest);
      return NULL;
    }

    if (!memset(dest, 0x90, count))
    {
      puts("memset() Failed");
      return NULL;
    }

    VirtualProtect(dest, count, origattrib, NULL);
    return dest;
  }

  inline void *writeData(void *dest, void *src, size_t length)
  {
    DWORD origattrib = 0;
    int ret = 0;
    ret = VirtualProtect(dest, length, PAGE_EXECUTE_READWRITE, &origattrib);

    if (!ret)
    {
      printf("VirtualProtect(%p) Failed\n", dest);
      return NULL;
    }

    if (!memcpy(dest, src, length))
    {
      puts("memcpy() Failed");
      return NULL;
    }

    VirtualProtect(dest, length, origattrib, NULL);
    return dest;
  }

#ifdef __cplusplus
}
#endif // __cplusplus

#endif // UTILS_H
