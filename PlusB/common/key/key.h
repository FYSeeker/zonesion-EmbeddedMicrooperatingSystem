/*********************************************************************************************
* 文件：key.h
* 作者：fuyou
* 说明：按键处理进程驱动头文件  
* 修改：
*********************************************************************************************/

#ifndef __KEY_H__
#define __KEY_H__

#include "contiki.h"

PROCESS_NAME(key);

extern process_event_t SysInit_Event;
extern process_event_t key_event;

#endif
