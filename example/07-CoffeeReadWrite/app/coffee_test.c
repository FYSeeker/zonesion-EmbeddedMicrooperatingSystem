#include <stdio.h>
#include <string.h>
#include <contiki.h>
#include "cfs/cfs.h"
#include "cfs-coffee-arch.h"

PROCESS(cfs_test_process, "cfs dirTest");

char result[300];
extern process_event_t process_event_lcd;
extern process_event_t process_event_key;
extern struct process lcd;
extern int cfs_coffee_format(void);
static unsigned int writeByteNum = 0;
char buf1[13] = "Hello, World!";
char buf2[256] = {0};

PROCESS_THREAD(cfs_test_process, ev, data)
{
  int fd = 0;
  int size_writeFlag = 0;
  int size_readFlag = 0;
  static struct etimer etimer_coffee;
  PROCESS_BEGIN();                                              // cfs_test_process进程开始
  W25QXX_Init();                                                // W25Q64初始化
  printf("K1:打开 K2:写入 K3:读取 K4:关闭\r\n");                // 串口打印信息
  sprintf(result, "Formatting 125 sectors...");
  process_post_synch(&lcd, process_event_lcd, result);
  if(cfs_coffee_format() == -1)
  {
    printf("coffee format error.\r\n");
    sprintf(result, "Coffee format error.");
    process_post_synch(&lcd, process_event_lcd, result); 
    return -1;
  }
  sprintf(result, "Done!");
  process_post_synch(&lcd, process_event_lcd, result);
  etimer_set(&etimer_coffee, 100);
  while(1)
  {
    if(ev == process_event_key)
    {
      if((*(unsigned char*)data) == 0x01)                       // 如果按键一按下 打开文件
      {
        fd = cfs_open("CoffeeTest", CFS_WRITE | CFS_READ);      // 打开文件如果没有则创建文件
        if(fd == -1)
        {
          printf("Coffee Create File Error!\r\n");
          sprintf(result, "Coffee Create File Error!");
          process_post_synch(&lcd, process_event_lcd, result); 
          return -1;
        }
        else
        {
          printf("Coffee Create File Succeed!\r\n");
          sprintf(result, "Coffee Create File Succeed!");
          process_post_synch(&lcd, process_event_lcd, result);
        }
      }
      else if((*(unsigned char*)data) == 0x02)                  // 如果按键二按下,写文件
      {
        if(writeByteNum+strlen(buf1) <= 256)
        {
          size_writeFlag = cfs_write(fd, buf1, sizeof(buf1));
          if(size_writeFlag == -1)
          {
            printf("Coffee Write File Error!\r\n");
            sprintf(result, "Coffee Write File Error!");
            process_post_synch(&lcd, process_event_lcd, result); 
            return -1;
          }
          else
          {
            writeByteNum += strlen(buf1);
            printf("Coffee Write:%s\r\n", buf1);
            sprintf(result, "Coffee Write:%s", buf1);
            process_post_synch(&lcd, process_event_lcd, result);
          }
        }
        else
        {
          printf("Coffee Write File Too Much!\r\n");
          sprintf(result, "Coffee Write File Too Much!");
          process_post_synch(&lcd, process_event_lcd, result);
          return -1;
        }
      }
      else if((*(unsigned char*)data) == 0x04)                  // 如果按键三按下
      {
        cfs_seek(fd, 0, CFS_SEEK_SET);
        size_readFlag = cfs_read(fd, buf2, writeByteNum);
        if(size_readFlag == -1)
        {
          printf("Coffee Read File Error!\r\n");
          sprintf(result, "Coffee Read File Error!");
          process_post_synch(&lcd, process_event_lcd, result); 
          return -1;
        }
        else
        {
          printf("Coffee Read File Content:%s\r\n", buf2);
          sprintf(result, "Coffee Read File Content:%s", buf2);
          process_post_synch(&lcd, process_event_lcd, result);
        }
      }
      else if((*(unsigned char*)data) == 0x08)                  // 如果按键四按下
      {
        cfs_close(fd);
        printf("Coffee Close File Succeed!\r\n");
        sprintf(result, "Coffee Close File Succeed!");
        process_post_synch(&lcd, process_event_lcd, result);
      }
    }
    etimer_reset(&etimer_coffee);
    PROCESS_YIELD();                                            // 进程让步
  }
  PROCESS_END();
}