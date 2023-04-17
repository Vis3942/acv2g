#include <string.h>
#include <stdlib.h>
#include <stdio.h>
#include <syslog.h>
#include <stdint.h>
#include <math.h>
#include <inttypes.h>
#include <sys/socket.h>
#include <sys/un.h>
#include <time.h>
#include <stdarg.h>
#include <errno.h>
#include <limits.h>
#include <unistd.h>
#include "can2sep2_proxy.h"

#include "can2sep2_proxy.c"

int main()
{
    int ii;
    can2sep2_task_init();

    server_status = 1;
    charge_percent = -100;
    duration_secs = 353;
    time_to_event_start_secs = 0x00FFFFFF;

    ii = 0;
    //while (ii < 9)
    while (1)
    {
        can2sep2_task_func();
        sleep(10);
        time_to_event_start_secs -= (60*10);
        if (time_to_event_start_secs <= 0 )
        {
            time_to_event_start_secs = 0x00FFFFFF;
        }

        ii++;
    }
    
    return 0;
}