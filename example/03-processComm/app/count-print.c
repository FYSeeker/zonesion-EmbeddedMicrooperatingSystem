#include <contiki.h>
#include <stdio.h>
#include "drive_led.h"

PROCESS(count,"count");                                         // 定义进程count
PROCESS(print,"print");                                         // 定义进程print
char result[20];
static process_event_t event_data_ready;

PROCESS_THREAD(count, ev, data){                                // 进程主体
  static struct etimer count_timer;
  static unsigned int count = 0;
  
  PROCESS_BEGIN();                                              // 开始进程
  
  event_data_ready = process_alloc_event();                     // 进程标识（进程号）
  etimer_set(&count_timer, CLOCK_SECOND);                       // 设置定时器1s
  led_init();                                                   // LED初始化
  while(1){
    PROCESS_WAIT_EVENT();                                       // 等待定时器到达
    if(ev == PROCESS_EVENT_TIMER)
    {
      count++;                                                  // 计数加一
      if(count%2 == 0)
      {
        turn_on(LED3_NUM);                                      // 打开LED3
        turn_on(LED4_NUM);                                      // 打开LED4
      }
      else
      {
        turn_off(LED3_NUM);                                     // 关闭LED3
        turn_off(LED4_NUM);                                     // 关闭LED4
      }
      process_post(&print, event_data_ready, &count);           // 传递事件（调度print进程）
      etimer_reset(&count_timer);                               // 重设定时器
    }
  }
  PROCESS_END();                                                // 进程结束
}

PROCESS_THREAD(print, ev, data)                                 // print进程主体
{                                
    PROCESS_BEGIN();                                            // 进程开始
    while(1)
    {
      PROCESS_WAIT_EVENT_UNTIL(ev == event_data_ready);         // 等待调度事件发生
      sprintf(result,"Counter is %d",(*(int *)data));
      printf("Counter is %d\r\n", (*(int *)data));              // 串口输出
    }
    PROCESS_END();                                              // 进程结束
}