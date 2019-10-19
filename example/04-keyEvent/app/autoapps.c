#include <contiki.h>

PROCESS_NAME(key_detect);
PROCESS_NAME(lcd);

struct process * const autostart_processes[] = {
    &key_detect,
    &lcd,
    NULL
};

void StartProcesslist(void)
{
    autostart_start(autostart_processes);
}
