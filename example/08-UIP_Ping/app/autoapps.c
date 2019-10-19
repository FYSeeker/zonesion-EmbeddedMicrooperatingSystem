#include <contiki.h>

PROCESS_NAME(helloworld); 
PROCESS_NAME(led);
PROCESS_NAME(key);
PROCESS_NAME(onboard_sensors);
PROCESS_NAME(lcd);
PROCESS_NAME(rfUart_process);
PROCESS_NAME(ethernet_process);

struct process * const autostart_processes[] = {
    &led,
    &key,
    &lcd,
    &ethernet_process,
    NULL
};
