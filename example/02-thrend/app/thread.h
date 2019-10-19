#ifndef _thread_h_
#define _thread_h_

#include <stdio.h>
#include <contiki.h>
#include "key.h"

PT_THREAD(Thread_Test(process_event_t ev, void *data));

#endif