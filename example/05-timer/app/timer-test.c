#include <contiki.h>
#include <stdio.h>
#include "drive_led.h"

PROCESS(timer_test,"timer_test");
extern process_event_t process_event_lcd;
extern struct process lcd;
char result[20];

PROCESS_THREAD(timer_test, ev, data)                            // timer_test进程主体
{
  static struct etimer timer_t;                                 // 定义一个定时器
  static int count = 0, i = 0, sec = 0; 
  PROCESS_BEGIN();                                              // timer_test进程开始
  led_init();                                                   // led初始化
  etimer_set(&timer_t, 2 * CLOCK_SECOND);                       // 设置定时器为2s
  PROCESS_WAIT_EVENT();                                         // 等待事件触发
  printf("Clock tick and etimer test, 1 sec (%u clock ticks):\r\n", CLOCK_SECOND);
  sprintf(result, "Clock seconds test (1s):");
  process_post_synch(&lcd, process_event_lcd, result); 
  while(i < 10) {
    etimer_set(&timer_t, CLOCK_SECOND);                         // 设置定时器为1s
    PROCESS_WAIT_EVENT_UNTIL(ev==PROCESS_EVENT_TIMER);          // 等待定时器事件触发
    etimer_reset(&timer_t);                                     // 重设定时器
    count = clock_seconds();                                    // 
    printf("%lu seconds\r\n", count);                           // 串口输出信息
    sprintf(result, "%lu seconds", count);
    process_post_synch(&lcd, process_event_lcd, result); 
    turn_on(LEDR_NUM);                                          // 打开RGB红灯
    if(i % 2 == 0)
    {
      turn_on(LED3_NUM);
      turn_off(LED4_NUM);
    }
    else
    {
      turn_on(LED4_NUM);
      turn_off(LED3_NUM);
    }
    i++;
  }
  printf("Clock seconds test (5s):\r\n");                       // 串口输出信息
  sprintf(result, "Clock seconds test (5s):");
  process_post_synch(&lcd, process_event_lcd, result); 
  i = 0;
  while(i < 10) {
    etimer_set(&timer_t, 5 * CLOCK_SECOND);                     // 设置定时器5s
    PROCESS_WAIT_EVENT_UNTIL(ev==PROCESS_EVENT_TIMER);          // 等待定时器事件触发
    etimer_reset(&timer_t);                                     // 重设定时器
    sec = clock_seconds();
    printf("%lu seconds\r\n", sec);                             // 串口输出信息
    sprintf(result, "%lu seconds", sec);
    process_post_synch(&lcd, process_event_lcd, result); 
    if(i == 0)
    {
      turn_off(LEDR_NUM);
      turn_on(LEDB_NUM);
    }
    if(i % 2 == 0)
    {
      turn_on(LED3_NUM);
      turn_off(LED4_NUM);
    }
    else
    {
      turn_on(LED4_NUM);
      turn_off(LED3_NUM);
    }
    i++;
  }
  turn_off(LEDB_NUM);
  turn_on(LEDG_NUM);
  turn_off(LED3_NUM);
  turn_off(LED4_NUM);
  printf("Done!\r\n");
  sprintf(result, "Done!");
  process_post_synch(&lcd, process_event_lcd, result);
  PROCESS_END();                                                // timer_test进程结束
}