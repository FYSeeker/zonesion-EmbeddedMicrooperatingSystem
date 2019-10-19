#include <contiki.h>

PROCESS_NAME(helloworld);
PROCESS_NAME(lcd);

struct process * const autostart_processes[] = {
    &helloworld,
    &lcd,
    NULL
};

void StartProcesslist(void)
{
    autostart_start(autostart_processes);
}
