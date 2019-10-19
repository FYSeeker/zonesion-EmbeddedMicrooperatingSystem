#include <stdio.h>
#include <contiki.h>
#include <contiki-net.h>
#include "usart.h"

unsigned int idle_count = 0;
void StartProcesslist(void);
void debug_init(void (*f)(char));
int debug_input(char c);

void main(void)
{
    clock_init();                                               // ϵͳʱ�ӳ�ʼ��
    uart1_init(38400);                                          // ����1��ʼ��������Ϊ38400
    debug_init(uart1_putc);
    uart1_set_input(debug_input);
    
    printf("\r\nStarting ");                                    // ��ӡ��ʾ��Ϣ
    printf(CONTIKI_VERSION_STRING);
    printf(" on STM32F40x\r\n");

    process_start(&etimer_process, NULL);                       // ���� etimer ����
    StartProcesslist();
    while(1)
    {
        do {
        }
        while(process_run() > 0);
        idle_count++;
    }
}