#include <contiki.h>
#include <stdio.h>
#include "drive_led.h"

PROCESS(count,"count");                                         // �������count
PROCESS(print,"print");                                         // �������print
char result[20];
static process_event_t event_data_ready;

PROCESS_THREAD(count, ev, data){                                // ��������
  static struct etimer count_timer;
  static unsigned int count = 0;
  
  PROCESS_BEGIN();                                              // ��ʼ����
  
  event_data_ready = process_alloc_event();                     // ���̱�ʶ�����̺ţ�
  etimer_set(&count_timer, CLOCK_SECOND);                       // ���ö�ʱ��1s
  led_init();                                                   // LED��ʼ��
  while(1){
    PROCESS_WAIT_EVENT();                                       // �ȴ���ʱ������
    if(ev == PROCESS_EVENT_TIMER)
    {
      count++;                                                  // ������һ
      if(count%2 == 0)
      {
        turn_on(LED3_NUM);                                      // ��LED3
        turn_on(LED4_NUM);                                      // ��LED4
      }
      else
      {
        turn_off(LED3_NUM);                                     // �ر�LED3
        turn_off(LED4_NUM);                                     // �ر�LED4
      }
      process_post(&print, event_data_ready, &count);           // �����¼�������print���̣�
      etimer_reset(&count_timer);                               // ���趨ʱ��
    }
  }
  PROCESS_END();                                                // ���̽���
}

PROCESS_THREAD(print, ev, data)                                 // print��������
{                                
    PROCESS_BEGIN();                                            // ���̿�ʼ
    while(1)
    {
      PROCESS_WAIT_EVENT_UNTIL(ev == event_data_ready);         // �ȴ������¼�����
      sprintf(result,"Counter is %d",(*(int *)data));
      printf("Counter is %d\r\n", (*(int *)data));              // �������
    }
    PROCESS_END();                                              // ���̽���
}