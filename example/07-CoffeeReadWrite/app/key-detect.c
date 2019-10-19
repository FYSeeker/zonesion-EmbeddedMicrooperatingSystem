#include <contiki.h>
#include <stdio.h>
#include "drive_key.h"

PROCESS(key_detect,"key_detect");

static struct etimer etimer_key;                                // 定义一个定时器
process_event_t process_event_key;                              // 定义一个事件
extern struct process lcd;
extern struct process cfs_test_process;

PROCESS_THREAD(key_detect, ev, data)
{
  static unsigned char key_value = 0, key_flag = 1;
  PROCESS_BEGIN();                                              // key_detect进程开始
  key_init();                                                   // 按键初始化
  process_event_key = process_alloc_event();                    // 申请事件号
  etimer_set(&etimer_key, 50);                                  // 初始化定时器为50ms
  while(1)
  {
    key_value = get_key_status();                               // 获取按键状态
    if(key_value == 0 && key_flag == 0)                         
    {
      key_flag = 1;
    }
    else if(key_flag == 1 && key_value != 0)
    {
      key_flag = 0;
      process_post(&cfs_test_process, process_event_key, &key_value);        // 进入显示进程
    }
    etimer_reset(&etimer_key);                                  // 重设定时器
    PROCESS_WAIT_EVENT_UNTIL(ev == PROCESS_EVENT_TIMER);        // 等待定时器触发
  }
  PROCESS_END();                                                // key_detect进程结束
}