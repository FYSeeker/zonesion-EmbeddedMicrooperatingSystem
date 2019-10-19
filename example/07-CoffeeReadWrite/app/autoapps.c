#include <contiki.h>

PROCESS_NAME(key_detect);
PROCESS_NAME(cfs_test_process);
PROCESS_NAME(lcd);

struct process * const autostart_processes[] = {
    &lcd,
    &key_detect,
    &cfs_test_process,
    NULL
};

void StartProcesslist(void)
{
    autostart_start(autostart_processes);
}
