#include "sys_ui.h"


void sysUI_update()
{
    char pbuf[20] = {0};
    
    GUI_SetFont(&GUI_Font32B_ASCII);//字体大小
    GUI_SetColor(GUI_WHITE);//字体颜色
    sprintf(pbuf,"GUI Example: \r\n Text Test");
	GUI_DispStringAt(pbuf,8,4);
    
    GUI_SetFont(&GUI_Font8x16);//字体大小  
    GUI_SetColor(GUI_RED);//字体颜色
    sprintf(pbuf,"hello world!");
	GUI_DispStringAt(pbuf,8,82);
    
    GUI_SetColor(GUI_BLUE);//字体颜色
    sprintf(pbuf,"0123456789");
	GUI_DispStringAt(pbuf,8,102);
    
    GUI_SetColor(GUI_GREEN);//字体颜色
    sprintf(pbuf,"^_^");
	GUI_DispStringAt(pbuf,8,122);
}


void GUI_Config()
{
    GUI_SetFont(&GUI_Font8x16);//字体大小
    GUI_SetBkColor(GUI_BLACK);//背景颜色     
    GUI_SetColor(GUI_WHITE);//字体颜色
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