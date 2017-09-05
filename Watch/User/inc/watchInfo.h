#ifndef WATCHINFO_H
#define WATCHINFO_H
#include "includes.h"

#define     SYS_VERSION       0x0101
#define     TEST_VERSION      0x00

u8 WatchInfo_init(void);
u8 WatchInfo_setUserInfo(u8 height,u8 weight);
personInfo_t * WatchInfo_getUserInfo(u8 *error);



#endif


