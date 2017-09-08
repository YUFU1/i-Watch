#include "includes.h"
u8 WatchInfo_init(void)
{
  WatchInfo_setUserInfo(170,134); //设置身高、体重用于计算卡路里消耗
	return 0;  //初始化成功返回0
}
 personInfo_t user_info;
u8 WatchInfo_setUserInfo(u8 height,u8 weight)
{
	user_info.height = ((float)height)/100;
	user_info.weight = ((float)weight)/2;
  return 0;//成功 0
}

personInfo_t * WatchInfo_getUserInfo(u8 *error)
{
	u8 err;
	err = 0;//0表示获取成功
	error = &err;
  return &user_info;
}
