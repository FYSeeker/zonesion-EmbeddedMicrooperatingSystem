#include <contiki.h>
#include <stdio.h>
#include "drive_led.h"

PROCESS(timer_test,"timer_test");
extern process_event_t process_event_lcd;
extern struct process lcd;
char result[20];

PROCESS_THREAD(timer_test, ev, data)                            // timer_test��������
{
  static struct etimer timer_t;                                 // ����һ����ʱ��
  static int count = 0, i = 0, sec = 0; 
  PROCESS_BEGIN();                                              // timer_test���̿�ʼ
  led_init();                                                   // led��ʼ��
  etimer_set(&timer_t, 2 * CLOCK_SECOND);                       // ���ö�ʱ��Ϊ2s
  PROCESS_WAIT_EVENT();                                         // �ȴ��¼�����
  printf("Clock tick and etimer test, 1 sec (%u clock ticks):\r\n", CLOCK_SECOND);
  sprintf(result, "Clock seconds test (1s):");
  process_post_synch(&lcd, process_event_lcd, result); 
  while(i < 10) {
    etimer_set(&timer_t, CLOCK_SECOND);                         // ���ö�ʱ��Ϊ1s
    PROCESS_WAIT_EVENT_UNTIL(ev==PROCESS_EVENT_TIMER);          // �ȴ���ʱ���¼�����
    etimer_reset(&timer_t);                                     // ���趨ʱ��
    count = clock_seconds();                                    // 
    printf("%lu seconds\r\n", count);                           // ���������Ϣ
    sprintf(result, "%lu seconds", count);
    process_post_synch(&lcd, process_event_lcd, result); 
    turn_on(LEDR_NUM);                                          // ��RGB���
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
  printf("Clock seconds test (5s):\r\n");                       // ���������Ϣ
  sprintf(result, "Clock seconds test (5s):");
  process_post_synch(&lcd, process_event_lcd, result); 
  i = 0;
  while(i < 10) {
    etimer_set(&timer_t, 5 * CLOCK_SECOND);                     // ���ö�ʱ��5s
    PROCESS_WAIT_EVENT_UNTIL(ev==PROCESS_EVENT_TIMER);          // �ȴ���ʱ���¼�����
    etimer_reset(&timer_t);                                     // ���趨ʱ��
    sec = clock_seconds();
    printf("%lu seconds\r\n", sec);                             // ���������Ϣ
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
  PROCESS_END();                                                // timer_test���̽���
}