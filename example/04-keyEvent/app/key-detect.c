#include <contiki.h>
#include <stdio.h>
#include "drive_key.h"

PROCESS(key_detect,"key_detect");

char result[30];
static struct etimer etimer_key;                                // ����һ����ʱ��
extern process_event_t process_event_key;                       // ����һ���¼�
extern struct process lcd;

PROCESS_THREAD(key_detect, ev, data)
{
  static unsigned char key_value = 0, key_flag = 1;
  PROCESS_BEGIN();                                              // key_detect���̿�ʼ
  key_init();                                                   // ������ʼ��
  process_event_key = process_alloc_event();                    // �����¼���
  etimer_set(&etimer_key, 50);                                  // ��ʼ����ʱ��Ϊ50ms
  while(1)
  {
    key_value = get_key_status();                               // ��ȡ����״̬
    if(key_value == 0 && key_flag == 0)                         
    {
      key_flag = 1;
      process_post(&lcd, process_event_key, &key_value);        // ������ʾ����
    }
    else if(key_flag == 1 && key_value != 0)
    {
      key_flag = 0;
      process_post(&lcd, process_event_key, &key_value);        // ������ʾ����
    }
    etimer_reset(&etimer_key);                                  // ���趨ʱ��
    PROCESS_WAIT_EVENT_UNTIL(ev == PROCESS_EVENT_TIMER);        // �ȴ���ʱ������
  }
  PROCESS_END();                                                // key_detect���̽���
}