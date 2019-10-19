#include "thread.h"

unsigned int thread_count = 0;

struct pt threadTest;

PT_THREAD(Thread_Test(process_event_t ev, void *data))          // Thread_Test线程主体
{
    static struct etimer etimer_threadTest;                     // 定义一个定时器
    
    PT_BEGIN(&threadTest);                                      // Thread_Test线程开始
    
    etimer_set(&etimer_threadTest, 1000);                       // 设置定时器1s
    
    while(1)
    {
        PT_YIELD(&threadTest);                                  // 让出线程
        if(etimer_expired(&etimer_threadTest))                  // 等待定时器过期
        {
            etimer_set(&etimer_threadTest,1000);                // 设置定时器1s
            thread_count++;                                     // 计数加一
        }
    }
    
    PT_END(&threadTest);                                        // Thread_Test线程结束
}

