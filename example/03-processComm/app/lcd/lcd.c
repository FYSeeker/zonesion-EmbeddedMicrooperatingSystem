#include <string.h>
#include <stdio.h>
#include "ili93xx.h"

extern char result[20];

PROCESS(lcd, "lcd");

static struct etimer lcd_timer;                                 // 定义一个定时器

void LCD_DrawRectangle(u16 x1, u16 y1, u16 x2, u16 y2, u16 color);

void lcd_Update(uint8_t refresh, process_event_t ev, char* dataBuf)
{
    char pbuf[40] = {0};
    static uint16_t y = 0;
    uint16_t BackColor = LCD_COLOR_BLACK;
    
    if(refresh&0x80)
    {
        LCDClear(LCD_COLOR_BLACK);                              // 液晶屏清屏为黑色
        LCD_DrawRectangle(5,10,315,45,LCD_COLOR_WHITE);         // 在指定位置绘制矩形
        LCD_DrawRectangle(5,60,315,235,LCD_COLOR_WHITE);
        
        sprintf(pbuf," 嵌入式微操作系统 ");
        LCDShowFont16(160-(strlen(pbuf)*4),y+2,pbuf,strlen(pbuf)*8,LCD_COLOR_WHITE,BackColor);
        
        y+=20;
        sprintf(pbuf," Contiki OS 进程间通信 ");
        LCDShowFont16(160-(strlen(pbuf)*4),y+2,pbuf,strlen(pbuf)*8,LCD_COLOR_RED,BackColor);
        
        y+=30;
        sprintf(pbuf, " 信息 ");
        LCDShowFont16(160-(strlen(pbuf)*4),y+2,pbuf,strlen(pbuf)*8,LCD_COLOR_WHITE,BackColor);
    }
    y = 120;
    sprintf(pbuf, result);
    LCDShowFont16(160-(strlen(pbuf)*4),y+2,pbuf,strlen(pbuf)*8,LCD_COLOR_WHITE,BackColor);
}

PROCESS_THREAD(lcd, ev, data)                                   // lcd进程主体
{
  PROCESS_BEGIN();                                              // lcd进程开始
  ILI93xxInit();                                                // 液晶屏初始化
  lcd_Update(0x80, NULL, NULL);                                 // 液晶屏显示更新
  etimer_set(&lcd_timer, 100);                                  // 设置lcd_timer间隔为100ms
  while (1)
  {
    PROCESS_WAIT_EVENT();                                       // 等待定时器到达
    if(ev == PROCESS_EVENT_TIMER)                               // 如果定时器事件触发
    {
      lcd_Update(0x00, NULL, result);                           // 液晶屏显示更新
      etimer_reset(&lcd_timer);                                 // 重设定时器
    }
  }
  PROCESS_END();                                                // lcd进程结束
}