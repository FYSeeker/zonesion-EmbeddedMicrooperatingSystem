#include <contiki.h>

PROCESS_NAME(helloworld); 
PROCESS_NAME(led);
PROCESS_NAME(key);
PROCESS_NAME(lcd);

struct process * const autostart_processes[] = {
    &led,
    &key,
    &lcd,
    NULL
};
