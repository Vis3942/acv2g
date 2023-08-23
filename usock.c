#include <stdio.h>
#include <sys/select.h>
#include <sys/socket.h>
#include <sys/un.h>
#include <stdlib.h>
#include <unistd.h>

#include "usock_utils.h"

char *sep2_usock_path = "/tmp/can2sep2";

int srv_usock_fd;
int conn_usock_fd;

void usock_open()
{
  conn_usock_fd = 0;

  struct sockaddr_un addr;
  if ( (srv_usock_fd = socket(AF_UNIX, SOCK_STREAM, 0)) == -1 ) {
    perror ("unix socket error");
    exit (-1);
  }

  unlink(sep2_usock_path);

  memset(&addr, 0, sizeof(addr));
  addr.sun_family = AF_UNIX;
  strncpy(addr.sun_path, sep2_usock_path, sizeof(addr.sun_path)-1);

  async_enable(srv_usock_fd, 0);

  if (bind(srv_usock_fd, (struct sockaddr*)&addr, sizeof(addr)) == -1  ) 
  {
    perror("unix socket bind error.");
    exit(-1);
  }

  if (listen(srv_usock_fd, 2) == -1)
  {
    perror("unix socket listen error.");
    exit(-1);
  }

}

void usock_accept()
{
  int tmp_fd;
  if (conn_usock_fd > 0)
  {
    // already connected, do not accept any more connections
    fprintf(stdout,"socket already connected, cannot accept any more connections");
    // only solution is to accept and close connection
    if ( (tmp_fd = accept(srv_usock_fd, NULL, NULL)) == -1)
    {
      // accept failed so dont do anything;
    }
    else
    {
      close(tmp_fd);
    }

    return;
  }
  
  if ( (conn_usock_fd = accept(srv_usock_fd, NULL, NULL)) == -1)
  {
    perror("unix socket accept error");
  }
  else
  {
    async_enable(conn_usock_fd, 0);
    fprintf(stdout,"Connected to socket, fd %d \n", conn_usock_fd);
  }
}

void close_usock()
{
  if (conn_usock_fd > 0)
  {
    close(conn_usock_fd);
    conn_usock_fd = 0;
  }
}

