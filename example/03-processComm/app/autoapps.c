#include <contiki.h>

PROCESS_NAME(lcd);
PROCESS_NAME(count);
PROCESS_NAME(print);

struct process * const autostart_processes[] = {
    &count,
    &print,
    &lcd,
    NULL
};

void StartProcesslist(void)
{
    autostart_start(autostart_processes);
}
