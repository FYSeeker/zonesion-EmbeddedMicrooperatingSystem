#include <contiki.h>

PROCESS_NAME(helloworld); 
PROCESS_NAME(led);
PROCESS_NAME(key);
PROCESS_NAME(onboard_sensors);
PROCESS_NAME(SysUI_process);

struct process * const autostart_processes[] = {
    &led,
    &key,
    &onboard_sensors,
    &SysUI_process,
    NULL
};

void StartProcesslist(void)
{
    autostart_start(autostart_processes);
}
