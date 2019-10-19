#include <string.h>
#include <stdio.h>
#include "ili93xx.h"

PROCESS(lcd, "lcd");

extern char result[30];
process_event_t process_event_key;                              // ����һ���¼�
static struct etimer etimer_lcdUpdate;                          // ����һ����ʱ��
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
        
        sprintf(pbuf," Ƕ��ʽ΢����ϵͳ ");
        LCDShowFont16(160-(strlen(pbuf)*4),y+2,pbuf,strlen(pbuf)*8,LCD_COLOR_WHITE,BackColor);
        
        y+=20;
        sprintf(pbuf," Contiki OS ���� ");
        LCDShowFont16(160-(strlen(pbuf)*4),y+2,pbuf,strlen(pbuf)*8,LCD_COLOR_RED,BackColor);
        
        y+=30;
        sprintf(pbuf," ��Ϣ ");
        LCDShowFont16(160-(strlen(pbuf)*4),y+2,pbuf,strlen(pbuf)*8,LCD_COLOR_WHITE,BackColor);
        
    }
    y = 120;
    LCDShowFont16(160-92,y+2,dataBuf,184,LCD_COLOR_WHITE,BackColor);
}

PROCESS_THREAD(lcd, ev, data)
{
  PROCESS_BEGIN();                                              // lcd���̿�ʼ
  ILI93xxInit();                                                // Һ������ʼ��
  sprintf(result, "Please press the button");                   
  lcd_Update(0x80, NULL, NULL);                                 // Һ������ʾ����
  etimer_set(&etimer_lcdUpdate, 100);                           // ���ö�ʱ��Ϊ100ms
  while (1)
  {
    if(ev == process_event_key)                                 // ��������¼�����
    {
      if((*(unsigned char*)data) == 0x01)                       // �������һ����
      {
        printf("K1 Press\r\n");
        sprintf(result, "K1 Press");
      }
      else if((*(unsigned char*)data) == 0x02)                  // �������������
      {
        printf("K2 Press\r\n");
        sprintf(result, "K2 Press");
      }
      else if((*(unsigned char*)data) == 0x04)                  // �������������
      {
        printf("K3 Press\r\n");
        sprintf(result, "K3 Press");
      }
      else if((*(unsigned char*)data) == 0x08)                  // ��������İ���
      {
        printf("K4 Press\r\n");
        sprintf(result, "K4 Press");
      }
      else                                                      // �������״̬
      {
        printf("Please press the button\r\n");
        sprintf(result, "Please press the button");
      }
      etimer_reset(&etimer_lcdUpdate);                          // ���趨ʱ��
    }
    lcd_Update(0x00, NULL, result);                             // Һ������ʾ����
    PROCESS_YIELD();                                            //�����ò�
  }
  PROCESS_END();                                                // lcd���̽���
}