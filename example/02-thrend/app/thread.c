#include "thread.h"

unsigned int thread_count = 0;

struct pt threadTest;

PT_THREAD(Thread_Test(process_event_t ev, void *data))          // Thread_Test�߳�����
{
    static struct etimer etimer_threadTest;                     // ����һ����ʱ��
    
    PT_BEGIN(&threadTest);                                      // Thread_Test�߳̿�ʼ
    
    etimer_set(&etimer_threadTest, 1000);                       // ���ö�ʱ��1s
    
    while(1)
    {
        PT_YIELD(&threadTest);                                  // �ó��߳�
        if(etimer_expired(&etimer_threadTest))                  // �ȴ���ʱ������
        {
            etimer_set(&etimer_threadTest,1000);                // ���ö�ʱ��1s
            thread_count++;                                     // ������һ
        }
    }
    
    PT_END(&threadTest);                                        // Thread_Test�߳̽���
}

