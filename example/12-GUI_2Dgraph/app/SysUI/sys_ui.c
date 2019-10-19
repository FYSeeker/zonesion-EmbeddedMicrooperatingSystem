#include "sys_ui.h"


void sysUI_update()
{
    char pbuf[20] = {0};
    uint16_t x=0,y=0;
    
    GUI_SetFont(&GUI_Font32B_ASCII);//�����С
    GUI_SetColor(GUI_WHITE);//������ɫ
    sprintf(pbuf,"GUI Example: \r\n 2D Graph Test");
	GUI_DispStringAt(pbuf,8,4);
    
    GUI_SetColor(GUI_RED);//�ʵ���ɫ
    GUI_SetDrawMode(GUI_DRAWMODE_NORMAL);//��ͼģʽ������ģʽ
    x = 10;
    y = 120;
    GUI_FillRect(x,y,x+50,y+50);//���
    
    GUI_SetColor(GUI_GREEN);//�ʵ���ɫ
    x += 60;
    GUI_AA_DrawLine(x,y,x+40,y+50);//����
    
    GUI_SetColor(GUI_BLUE);//�ʵ���ɫ
    x += 80;
    y += 30;
    GUI_DrawCircle(x,y,20);//��Բ
    
    GUI_SetColor(GUI_WHITE);//�ʵ���ɫ
    x += 60;
    GUI_AA_FillCircle(x,y,20);//���Բ
    
    GUI_SetColor(GUI_YELLOW);//�ʵ���ɫ
    x += 60;
    GUI_DrawArc(x,y,20,20,-30,210);//������
}


void GUI_Config()
{
    GUI_SetFont(&GUI_Font8x16);//�����С
    GUI_SetBkColor(GUI_BLACK);//������ɫ     
    GUI_SetColor(GUI_WHITE);//������ɫ
}


PROCESS(SysUI_process, "system ui process");

PROCESS_THREAD(SysUI_process, ev, data)
{
    static struct etimer etimer_uiUpdate;
    
    PROCESS_BEGIN();
    
	GUI_Init();
    GUI_Config();
    process_post(&SysUI_process,PROCESS_EVENT_TIMER,NULL);
    
    while(1)
    {
        PROCESS_WAIT_EVENT();  
        if(ev == PROCESS_EVENT_TIMER)
        {
            etimer_set(&etimer_uiUpdate,100);
            sysUI_update();
        }
    }
    
    PROCESS_END();
}