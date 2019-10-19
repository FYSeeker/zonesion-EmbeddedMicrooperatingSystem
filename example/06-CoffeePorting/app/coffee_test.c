#include <stdio.h>
#include <contiki.h>
#include "cfs/cfs.h"
#include "cfs-coffee-arch.h"

PROCESS(cfs_test_process, "cfs test");

char result[40];
extern process_event_t process_event_lcd;                       // ����һ���¼�
extern struct process lcd;                                      
extern int cfs_coffee_format(void);
char buf1[] = "Hello, World!";
char buf2[32] = "Orignal!";

PROCESS_THREAD(cfs_test_process, ev, data)                      // cfs_test_process��������
{   
  PROCESS_BEGIN();                                              // cfs_test_process���̿�ʼ 
  W25QXX_Init();                                                // W25Q64��ʼ��
  printf("***cfs test process start***\r\n");
  sprintf(result, "***cfs test process start***");
  process_post_synch(&lcd, process_event_lcd, result);          // ��lcd���̴������ݲ�����ִ��
  sprintf(result, "Formatting 125 sectors!");
  process_post_synch(&lcd, process_event_lcd, result);
  int format = cfs_coffee_format();                             // ��������Coffee����
  if(format == -1)
  {
    printf("Coffee format error.\r\n");
    sprintf(result, "Coffee format error.");
    process_post_synch(&lcd, process_event_lcd, result); 
    return -1;
  }
  
  int fd = cfs_open("CoffeeTest", CFS_WRITE | CFS_READ);        // ����ΪCoffeeTest���ļ������û���򴴽����ļ�
  if(fd == -1)                                                  
  {
    printf("First time open error.\r\n");
    sprintf(result, "First time open error.");
    process_post_synch(&lcd, process_event_lcd, result);  
    return -1;
  }

  sprintf(result, "The orignal buf1 is: %s", buf1);
  printf("The orignal buf1 is: %s\n", buf1);
  process_post_synch(&lcd, process_event_lcd, result);     
  
  sprintf(result, "The orignal buf2 is: %s", buf2);
  printf("The orignal buf2 is: %s\r\n", buf2);
  process_post_synch(&lcd, process_event_lcd, result);
  
  int size_write = cfs_write(fd, buf1, sizeof(buf1));           // ���ļ����Ϊfd��д��buf1
  cfs_seek(fd, 0, CFS_SEEK_SET);								// �ٴ򿪵��ļ��в���ָ��λ��
  int size_read = cfs_read(fd, buf2, sizeof(buf1));             // ���ļ����Ϊfd�ж�ȡbuf2

  sprintf(result, "The update buf1 is: %s", buf1);
  printf("The update buf1 is: %s\n", buf1);
  process_post_synch(&lcd, process_event_lcd, result);
  
  sprintf(result, "The update buf2 is: %s", buf2);
  printf("The update buf2 is: %s\r\n", buf2);
  process_post_synch(&lcd, process_event_lcd, result);

  cfs_close(fd);                                                // �رձ��Ϊfd���ļ�
  
  PROCESS_END();                                                // cfs_test_process���̽���
}