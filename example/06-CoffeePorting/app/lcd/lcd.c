#include "ili93xx.h"
#include <stdio.h>
#include <string.h>

PROCESS(lcd, "lcd");

extern char result[40];
process_event_t process_event_lcd;
void LCD_DrawRectangle(u16 x1, u16 y1, u16 x2, u16 y2, u16 color);

void lcd_Update(uint8_t refresh, process_event_t ev, char* dataBuf)
{
    char pbuf[40] = {0};
    static uint16_t x = 8;
    static uint16_t y = 0;
    static uint8_t displayNum = 0;
    uint16_t PenColor = LCD_COLOR_WHITE;
    uint16_t BackColor = LCD_COLOR_BLACK;
    
    if(refresh&0x80 || displayNum >= 8)
    {
        LCDClear(LCD_COLOR_BLACK);
        if(displayNum >= 8)
        {
          displayNum = 0;
          y = 0;
        }
        LCD_DrawRectangle(5,10,315,45,LCD_COLOR_WHITE);
        LCD_DrawRectangle(5,60,315,235,LCD_COLOR_WHITE);
        
        sprintf(pbuf," 嵌入式微操作系统 ");
        LCDShowFont16(160-(strlen(pbuf)*4),y+2,pbuf,strlen(pbuf)*8,LCD_COLOR_WHITE,BackColor);
        
        y+=20;
        sprintf(pbuf," Contiki OS Coffee文件系统移植 ");
        LCDShowFont16(160-(strlen(pbuf)*4),y+2,pbuf,strlen(pbuf)*8,LCD_COLOR_RED,BackColor);
        
        y+=30;
        sprintf(pbuf," 信息 ");
        LCDShowFont16(160-(strlen(pbuf)*4),y+2,pbuf,strlen(pbuf)*8,LCD_COLOR_WHITE,BackColor);
        y = 70;
    }
    if(ev == process_event_lcd)
    {
      LCDShowFont16(x,y+2,dataBuf,strlen(dataBuf)*8,PenColor,BackColor);
      y += 20;
      displayNum++;
    }
}

PROCESS_THREAD(lcd, ev, data)                                   // lcd进程主体
{
  PROCESS_BEGIN();                                              // 进程开始
  ILI93xxInit();                                                // 液晶屏初始化
  process_event_lcd = process_alloc_event();                    // 申请事件
  lcd_Update(0x80,NULL,NULL);                                   // 液晶屏显示
  while (1)
  {
    if(ev == process_event_lcd)                                 // 如果事件发生
    {   
      lcd_Update(0x00,ev,(char*)data);                          // 更新液晶屏显示
    }
    PROCESS_YIELD();                                            // 进程让步
  }
  PROCESS_END();                                                // 进程结束
}