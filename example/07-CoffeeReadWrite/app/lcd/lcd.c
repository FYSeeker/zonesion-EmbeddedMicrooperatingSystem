#include "ili93xx.h"
#include <stdio.h>
#include <string.h>

PROCESS(lcd, "lcd");

process_event_t process_event_lcd;
void LCD_DrawRectangle(u16 x1, u16 y1, u16 x2, u16 y2, u16 color);

void lcd_Update(uint8_t refresh, process_event_t ev, char* dataBuf)
{
    char pbuf[40] = {0};
    static uint16_t x = 8;
    static uint16_t y = 0;
    int dataLen = 0;
    static uint8_t displayNum = 0;
    uint16_t PenColor = LCD_COLOR_WHITE;
    uint16_t BackColor = LCD_COLOR_BLACK;
    
    if(refresh&0x80)
    {
        LCDClear(LCD_COLOR_BLACK);
        if(displayNum >= 7)
        {
          displayNum = 0;
          y = 0;
        }
        LCD_DrawRectangle(5,10,315,45,LCD_COLOR_WHITE);
        LCD_DrawRectangle(5,60,315,235,LCD_COLOR_WHITE);
        
        sprintf(pbuf," Ƕ��ʽ΢����ϵͳ ");
        LCDShowFont16(160-(strlen(pbuf)*4),y+2,pbuf,strlen(pbuf)*8,LCD_COLOR_WHITE,BackColor);
        
        y+=20;
        sprintf(pbuf," Contiki OS Coffee�ļ�ϵͳ��д ");
        LCDShowFont16(160-(strlen(pbuf)*4),y+2,pbuf,strlen(pbuf)*8,LCD_COLOR_RED,BackColor);
        
        y+=30;
        sprintf(pbuf," ��Ϣ ");
        LCDShowFont16(160-(strlen(pbuf)*4),y+2,pbuf,strlen(pbuf)*8,LCD_COLOR_WHITE,BackColor);
        
        sprintf(pbuf," K1:�� K2:д�� K3:��ȡ K4:�ر� ");
        LCDShowFont16(160-(strlen(pbuf)*4),210+2,pbuf,strlen(pbuf)*8,LCD_COLOR_BLUE,BackColor);
        y = 70;
    }
    
    if(ev == process_event_lcd)
    {
      unsigned char dataNum = 0;
      dataLen = strlen(dataBuf);
      if(dataLen > 38)
      {
        dataNum = dataLen / 38 + 1;
        memcpy(pbuf, dataBuf, 38);
      }
      else
      {
        dataNum = 1;
        memcpy(pbuf, dataBuf, strlen(dataBuf));
      }
      for(unsigned int i=1; i<dataNum+1; i++)
      {
        if(displayNum >= 7)
          lcd_Update(0x80, NULL, pbuf);
        displayNum++;
        LCDShowFont16(x,y+2,pbuf,strlen(pbuf)*8,PenColor,BackColor);
        int residueLen = dataLen-38*i;
        if(residueLen > 0)
        {
          memset(pbuf, 0, strlen(pbuf));
          if(residueLen >= 38)
            residueLen = 38;
          for(unsigned int j=0; j<residueLen; j++)
            pbuf[j] = dataBuf[38*i+j];
        }
        y += 20;
        
      }
    }
}

PROCESS_THREAD(lcd, ev, data)
{
  PROCESS_BEGIN();                                              // ���̿�ʼ
  ILI93xxInit();                                                // Һ������ʼ��
  process_event_lcd = process_alloc_event();                    // �����¼�
  lcd_Update(0x80, NULL, NULL);                                 // Һ������ʾ
  while (1)
  {
    if(ev == process_event_lcd)                                 // ����¼�����
    {   
      lcd_Update(0x00, ev, (char*)data);                        // ����Һ������ʾ
    }
    PROCESS_YIELD();                                            // �����ò�
  }
  PROCESS_END();                                                // ���̽���
}