#include <fcntl.h>
#include <time.h>
#include <signal.h>
#include <unistd.h>
#include <stdio.h>
#include <stdlib.h>
#include <errno.h>
#include <stdarg.h>

void async_enable (int fd, int ok_to_block) {
  fcntl (fd, F_SETOWN, getpid());
  if (ok_to_block)
  {
    fcntl (fd, F_SETFL, // fcntl (fd, F_GETFL, 0) | 
    O_ASYNC | O_NONBLOCK);
  }
  else
  {
    fcntl (fd, F_SETFL, // fcntl (fd, F_GETFL, 0) | 
    O_ASYNC );
  }
}




