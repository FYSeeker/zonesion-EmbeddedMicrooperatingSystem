#include <string.h>
#include <stdio.h>
#include "ili93xx.h"

PROCESS(lcd, "lcd");

extern char result[30];
process_event_t process_event_key;                              // 定义一个事件
static struct etimer etimer_lcdUpdate;                          // 定义一个定时器
void LCD_DrawRectangle(u16 x1, u16 y1, u16 x2, u16 y2, u16 color);

void lcd_Update(uint8_t refresh, process_event_t ev, char* dataBuf)
{
    char pbuf[40] = {0};
    static uint16_t y = 0;
    uint16_t BackColor = LCD_COLOR_BLACK;
    
    if(refresh&0x80)
    {
        LCDClear(LCD_COLOR_BLACK);
        LCD_DrawRectangle(5,10,315,45,LCD_COLOR_WHITE);
        LCD_DrawRectangle(5,60,315,235,LCD_COLOR_WHITE);
        
        sprintf(pbuf," 嵌入式微操作系统 ");
        LCDShowFont16(160-(strlen(pbuf)*4),y+2,pbuf,strlen(pbuf)*8,LCD_COLOR_WHITE,BackColor);
        
        y+=20;
        sprintf(pbuf," Contiki OS 按键 ");
        LCDShowFont16(160-(strlen(pbuf)*4),y+2,pbuf,strlen(pbuf)*8,LCD_COLOR_RED,BackColor);
        
        y+=30;
        sprintf(pbuf," 信息 ");
        LCDShowFont16(160-(strlen(pbuf)*4),y+2,pbuf,strlen(pbuf)*8,LCD_COLOR_WHITE,BackColor);
        
    }
    y = 120;
    LCDShowFont16(160-92,y+2,dataBuf,184,LCD_COLOR_WHITE,BackColor);
}

PROCESS_THREAD(lcd, ev, data)
{
  PROCESS_BEGIN();                                              // lcd进程开始
  ILI93xxInit();                                                // 液晶屏初始化
  sprintf(result, "Please press the button");                   
  lcd_Update(0x80, NULL, NULL);                                 // 液晶屏显示更新
  etimer_set(&etimer_lcdUpdate, 100);                           // 设置定时器为100ms
  while (1)
  {
    if(ev == process_event_key)                                 // 如果按键事件触发
    {
      if((*(unsigned char*)data) == 0x01)                       // 如果按键一按下
      {
        printf("K1 Press\r\n");
        sprintf(result, "K1 Press");
      }
      else if((*(unsigned char*)data) == 0x02)                  // 如果按键二按下
      {
        printf("K2 Press\r\n");
        sprintf(result, "K2 Press");
      }
      else if((*(unsigned char*)data) == 0x04)                  // 如果按键三按下
      {
        printf("K3 Press\r\n");
        sprintf(result, "K3 Press");
      }
      else if((*(unsigned char*)data) == 0x08)                  // 如果按键四按下
      {
        printf("K4 Press\r\n");
        sprintf(result, "K4 Press");
      }
      else                                                      // 如果其它状态
      {
        printf("Please press the button\r\n");
        sprintf(result, "Please press the button");
      }
      etimer_reset(&etimer_lcdUpdate);                          // 重设定时器
    }
    lcd_Update(0x00, NULL, result);                             // 液晶屏显示更新
    PROCESS_YIELD();                                            //进程让步
  }
  PROCESS_END();                                                // lcd进程结束
}