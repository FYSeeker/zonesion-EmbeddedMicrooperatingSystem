#include <string.h>
#include <stdio.h>
#include "ili93xx.h"

extern char result[20];

PROCESS(lcd, "lcd");

static struct etimer lcd_timer;                                 // ����һ����ʱ��

void LCD_DrawRectangle(u16 x1, u16 y1, u16 x2, u16 y2, u16 color);

void lcd_Update(uint8_t refresh, process_event_t ev, char* dataBuf)
{
    char pbuf[40] = {0};
    static uint16_t y = 0;
    uint16_t BackColor = LCD_COLOR_BLACK;
    
    if(refresh&0x80)
    {
        LCDClear(LCD_COLOR_BLACK);                              // Һ��������Ϊ��ɫ
        LCD_DrawRectangle(5,10,315,45,LCD_COLOR_WHITE);         // ��ָ��λ�û��ƾ���
        LCD_DrawRectangle(5,60,315,235,LCD_COLOR_WHITE);
        
        sprintf(pbuf," Ƕ��ʽ΢����ϵͳ ");
        LCDShowFont16(160-(strlen(pbuf)*4),y+2,pbuf,strlen(pbuf)*8,LCD_COLOR_WHITE,BackColor);
        
        y+=20;
        sprintf(pbuf," Contiki OS ���̼�ͨ�� ");
        LCDShowFont16(160-(strlen(pbuf)*4),y+2,pbuf,strlen(pbuf)*8,LCD_COLOR_RED,BackColor);
        
        y+=30;
        sprintf(pbuf, " ��Ϣ ");
        LCDShowFont16(160-(strlen(pbuf)*4),y+2,pbuf,strlen(pbuf)*8,LCD_COLOR_WHITE,BackColor);
    }
    y = 120;
    sprintf(pbuf, result);
    LCDShowFont16(160-(strlen(pbuf)*4),y+2,pbuf,strlen(pbuf)*8,LCD_COLOR_WHITE,BackColor);
}

PROCESS_THREAD(lcd, ev, data)                                   // lcd��������
{
  PROCESS_BEGIN();                                              // lcd���̿�ʼ
  ILI93xxInit();                                                // Һ������ʼ��
  lcd_Update(0x80, NULL, NULL);                                 // Һ������ʾ����
  etimer_set(&lcd_timer, 100);                                  // ����lcd_timer���Ϊ100ms
  while (1)
  {
    PROCESS_WAIT_EVENT();                                       // �ȴ���ʱ������
    if(ev == PROCESS_EVENT_TIMER)                               // �����ʱ���¼�����
    {
      lcd_Update(0x00, NULL, result);                           // Һ������ʾ����
      etimer_reset(&lcd_timer);                                 // ���趨ʱ��
    }
  }
  PROCESS_END();                                                // lcd���̽���
}