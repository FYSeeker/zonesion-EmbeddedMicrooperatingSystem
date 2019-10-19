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
        
        sprintf(pbuf," Ƕ��ʽ΢����ϵͳ ");
        LCDShowFont16(160-(strlen(pbuf)*4),y+2,pbuf,strlen(pbuf)*8,LCD_COLOR_WHITE,BackColor);
        
        y+=20;
        sprintf(pbuf," Contiki OS �߳� ");
        LCDShowFont16(160-(strlen(pbuf)*4),y+2,pbuf,strlen(pbuf)*8,LCD_COLOR_RED,BackColor);
        
        y+=30;
        sprintf(pbuf," ��Ϣ ");
        LCDShowFont16(160-(strlen(pbuf)*4),y+2,pbuf,strlen(pbuf)*8,LCD_COLOR_WHITE,BackColor);
    }
    sprintf(pbuf, "    Count is %d    ", thread_count);
    LCDShowFont16(160-(strlen(pbuf)*4),120+2,pbuf,strlen(pbuf)*8,LCD_COLOR_WHITE,BackColor);
}

PROCESS(lcd, "lcd");

PROCESS_THREAD(lcd, ev, data)                                   // lcd��������
{
    static struct etimer lcd_timer;                             // ����һ����ʱ��
    
    PROCESS_BEGIN();                                            // lcd���̿�ʼ
    
    ILI93xxInit();                                              // Һ������ʼ��
    lcd_Update(0x80);                                           // Һ������ʾ����
    process_post(&lcd, PROCESS_EVENT_TIMER, NULL);              // ����ʱ�������¼����ݵ�lcd������
    
    while (1)
    {
        PROCESS_WAIT_EVENT();                                   // �ȴ��¼�����
        if(ev == PROCESS_EVENT_TIMER)                           // �����ʱ���¼�����
        {
            etimer_set(&lcd_timer, 100);                        // ���ö�ʱ��Ϊ100ms
            lcd_Update(0x00);                                   // Һ������ʾ����
        }
        Thread_Test(ev, data);                                  // �����߳�
    }
    
    PROCESS_END();                                              // lcd���̽���
}