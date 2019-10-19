#include <contiki.h>
#include <stdio.h>

/******************hello world 进程****************************/
char result[20];
PROCESS(helloworld, "helloworld");

PROCESS_THREAD(helloworld, ev, data)
{
  PROCESS_BEGIN();                                              // helloworld进程开始
  
  printf("Hello World!\r\n");                                   // 串口打印信息
  sprintf(result,"Hello World!");                               // 将字符串复制到result中用于液晶屏显示
  PROCESS_END();                                                // helloworld进程结束
}