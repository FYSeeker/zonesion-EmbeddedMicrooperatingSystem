#include <contiki.h>
#include <stdio.h>

/******************hello world ����****************************/
char result[20];
PROCESS(helloworld, "helloworld");

PROCESS_THREAD(helloworld, ev, data)
{
  PROCESS_BEGIN();                                              // helloworld���̿�ʼ
  
  printf("Hello World!\r\n");                                   // ���ڴ�ӡ��Ϣ
  sprintf(result,"Hello World!");                               // ���ַ������Ƶ�result������Һ������ʾ
  PROCESS_END();                                                // helloworld���̽���
}