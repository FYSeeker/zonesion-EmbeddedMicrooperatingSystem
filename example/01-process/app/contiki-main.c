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
    clock_init();                                               // 系统时钟初始化
    uart1_init(38400);                                          // 串口1初始化波特率为38400
    debug_init(uart1_putc);
    uart1_set_input(debug_input);
    
    printf("\r\nStarting ");                                    // 打印提示信息
    printf(CONTIKI_VERSION_STRING);
    printf(" on STM32F40x\r\n");

    process_start(&etimer_process, NULL);                       // 启动 etimer 进程
    StartProcesslist();
    while(1)
    {
        do {
        }
        while(process_run() > 0);
        idle_count++;
    }
}