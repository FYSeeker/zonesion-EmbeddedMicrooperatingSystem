#include <contiki.h>

PROCESS_NAME(lcd);
PROCESS_NAME(timer_test);

struct process * const autostart_processes[] = {
    &lcd,
    &timer_test,
    NULL
};

void StartProcesslist(void)
{
    autostart_start(autostart_processes);
}
