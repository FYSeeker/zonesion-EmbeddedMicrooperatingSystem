#include "sys_ui.h"


void sysUI_update()
{
    char pbuf[20] = {0};
    uint16_t x=0,y=0;
    
    GUI_SetFont(&GUI_Font32B_ASCII);//字体大小
    GUI_SetColor(GUI_WHITE);//字体颜色
    sprintf(pbuf,"GUI Example: \r\n 2D Graph Test");
	GUI_DispStringAt(pbuf,8,4);
    
    GUI_SetColor(GUI_RED);//笔的颜色
    GUI_SetDrawMode(GUI_DRAWMODE_NORMAL);//绘图模式：正常模式
    x = 10;
    y = 120;
    GUI_FillRect(x,y,x+50,y+50);//填充
    
    GUI_SetColor(GUI_GREEN);//笔的颜色
    x += 60;
    GUI_AA_DrawLine(x,y,x+40,y+50);//画线
    
    GUI_SetColor(GUI_BLUE);//笔的颜色
    x += 80;
    y += 30;
    GUI_DrawCircle(x,y,20);//画圆
    
    GUI_SetColor(GUI_WHITE);//笔的颜色
    x += 60;
    GUI_AA_FillCircle(x,y,20);//填充圆
    
    GUI_SetColor(GUI_YELLOW);//笔的颜色
    x += 60;
    GUI_DrawArc(x,y,20,20,-30,210);//画弧线
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