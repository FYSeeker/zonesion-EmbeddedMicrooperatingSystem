#include "lcd.h"

extern unsigned int thread_count;

void lcd_Update(uint8_t refresh)
{
    char pbuf[40] = {0};
    uint16_t y = 0;
    uint16_t BackColor = LCD_COLOR_BLACK;
    
    if(refresh&0x80)
    {
        LCD_DrawRectangle(5,10,315,45,LCD_COLOR_WHITE);
        LCD_DrawRectangle(5,60,315,235,LCD_COLOR_WHITE);
        
        sprintf(pbuf," 嵌入式微操作系统 ");
        LCDShowFont16(160-(strlen(pbuf)*4),y+2,pbuf,strlen(pbuf)*8,LCD_COLOR_WHITE,BackColor);
        
        y+=20;
        sprintf(pbuf," Contiki OS 线程 ");
        LCDShowFont16(160-(strlen(pbuf)*4),y+2,pbuf,strlen(pbuf)*8,LCD_COLOR_RED,BackColor);
        
        y+=30;
        sprintf(pbuf," 信息 ");
        LCDShowFont16(160-(strlen(pbuf)*4),y+2,pbuf,strlen(pbuf)*8,LCD_COLOR_WHITE,BackColor);
    }
    sprintf(pbuf, "    Count is %d    ", thread_count);
    LCDShowFont16(160-(strlen(pbuf)*4),120+2,pbuf,strlen(pbuf)*8,LCD_COLOR_WHITE,BackColor);
}

PROCESS(lcd, "lcd");

PROCESS_THREAD(lcd, ev, data)                                   // lcd进程主体
{
    static struct etimer lcd_timer;                             // 定义一个定时器
    
    PROCESS_BEGIN();                                            // lcd进程开始
    
    ILI93xxInit();                                              // 液晶屏初始化
    lcd_Update(0x80);                                           // 液晶屏显示更新
    process_post(&lcd, PROCESS_EVENT_TIMER, NULL);              // 将定时器触发事件传递到lcd进程中
    
    while (1)
    {
        PROCESS_WAIT_EVENT();                                   // 等待事件触发
        if(ev == PROCESS_EVENT_TIMER)                           // 如果定时器事件触发
        {
            etimer_set(&lcd_timer, 100);                        // 设置定时器为100ms
            lcd_Update(0x00);                                   // 液晶屏显示更新
        }
        Thread_Test(ev, data);                                  // 运行线程
    }
    
    PROCESS_END();                                              // lcd进程结束
}