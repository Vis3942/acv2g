#include <stdio.h>
#include <sys/select.h>
#include <sys/socket.h>
#include <sys/un.h>
#include <stdlib.h>
#include <unistd.h>
#include <stdint.h>

#include "usock_utils.h"

char *sep2_client2server_path = "/tmp/client2server";
char *sep2_server2client_path = "/tmp/server2client";

int cli2srv_usock_fd = -1;
int conn_cli2srv_usock_fd = -1;
char rd_buf[1024];

static void (*process_messages)(char *buffer, int size) = NULL;

void register_process_messages_callback(void (*ptr)( char *buffer, int size ))
{
  //debug
  printf("in register callback \n");
  process_messages = ptr;
  printf("finished register call back assign \n");
}

void usock_client2server_open()
{
  conn_cli2srv_usock_fd = 0;

  struct sockaddr_un addr;
  if ( (cli2srv_usock_fd = socket(AF_UNIX, SOCK_STREAM, 0)) == -1 ) {
    perror ("unix socket error");
    exit (-1);
  }

  unlink(sep2_client2server_path);

  memset(&addr, 0, sizeof(addr));
  addr.sun_family = AF_UNIX;
  strncpy(addr.sun_path, sep2_client2server_path, sizeof(addr.sun_path)-1);

  async_enable(cli2srv_usock_fd, 0);

  if (bind(cli2srv_usock_fd, (struct sockaddr*)&addr, sizeof(addr)) == -1  ) 
  {
    perror("unix socket bind error.");
    exit(-1);
  }

  if (listen(cli2srv_usock_fd, 2) == -1)
  {
    perror("unix socket listen error.");
    exit(-1);
  }
}

void usock_client2server_close()
{
  if (cli2srv_usock_fd > 0)
  {
    close(cli2srv_usock_fd);
    cli2srv_usock_fd = -1;
  }
}

void usock_client2server_connection_close() // close existing connections
{
  if (conn_cli2srv_usock_fd > 0)
  {
    close(conn_cli2srv_usock_fd);
    conn_cli2srv_usock_fd = -1;
  }
}

void usock_client2server_accept()
{
  int tmp_fd;

  if ( (tmp_fd = accept(cli2srv_usock_fd, NULL, NULL)) == -1)
  {
    printf("client 2 server accept error\n");
    perror("accept");
    // accept failed so dont do anything;
    return;
  }

  if (conn_cli2srv_usock_fd > 0)
  {
    // already connected, do not accept any more connections
    printf("socket already connected assuming the client restarted, closing old connection and accept new connection");
    usock_client2server_connection_close();
  }
  conn_cli2srv_usock_fd = tmp_fd;
  async_enable(conn_cli2srv_usock_fd, 0);
  
}

void usock_client2server_read_message() 
{
  int n;
  // read data that the client sent to the server
  memset(rd_buf, 0, sizeof(rd_buf));
  n = recv(conn_cli2srv_usock_fd, rd_buf, sizeof(rd_buf), 0);
  //debug
  printf(" recvd from client: %d bytes\n", n);

  if (n < 0) {
    perror("recv from client:");
    usock_client2server_connection_close();
  }
  else if (n == 0) {
    // connection closed by client
    printf("connection closed by client\n");
    usock_client2server_connection_close();
  } 
  else {
    // process the message
    if (process_messages != NULL) {
      // debug
      //printf("processing message at %0xld\n", process_messages);
      printf("processing message \n");
      (*process_messages)(rd_buf, n);
    }
  }
}

int srv2cli_usock_fd = -1;
int conn_srv2cli_usock_fd = -1;
char wr_buf[1024];

void usock_server2client_open()
{
  conn_srv2cli_usock_fd = 0;

  struct sockaddr_un addr;
  if ( (srv2cli_usock_fd = socket(AF_UNIX, SOCK_STREAM, 0)) == -1 ) {
    perror ("unix socket error");
    exit (-1);
  }

  unlink(sep2_server2client_path);

  memset(&addr, 0, sizeof(addr));
  addr.sun_family = AF_UNIX;
  strncpy(addr.sun_path, sep2_server2client_path, sizeof(addr.sun_path)-1);

  async_enable(srv2cli_usock_fd, 0);

  if (bind(srv2cli_usock_fd, (struct sockaddr*)&addr, sizeof(addr)) == -1  ) 
  {
    perror("unix socket bind error.");
    exit(-1);
  }

  if (listen(srv2cli_usock_fd, 2) == -1)
  {
    perror("unix socket listen error.");
    exit(-1);
  }

}

void usock_server2client_accept()
{
  int tmp_fd;

  if ( (tmp_fd = accept(srv2cli_usock_fd, NULL, NULL)) == -1)
  {
      // accept failed so dont do anything;
      return;
  }

  if (conn_srv2cli_usock_fd > 0)
  {
    // already connected, do not accept any more connections
    printf("socket already connected assuming the client restarted, closing old connection and accept new connection\n");
    close(conn_srv2cli_usock_fd);
    conn_srv2cli_usock_fd = -1;
  }
  conn_srv2cli_usock_fd = tmp_fd;
  async_enable(conn_srv2cli_usock_fd, 0);
  
}

void usock_server2client_close()
{
  if (srv2cli_usock_fd > 0)
  {
    close(srv2cli_usock_fd);
    srv2cli_usock_fd = -1;
  }
}

void usock_server2client_connection_close()
{
  if (conn_srv2cli_usock_fd > 0)
  {
    close(conn_srv2cli_usock_fd);
    conn_srv2cli_usock_fd = -1;
  }
}

int usock_server2client_write_message(char* send_buf, int send_buf_len) 
{
  int n;

  n = -1;
  if (conn_srv2cli_usock_fd > 0) {
	n = send(conn_srv2cli_usock_fd, send_buf, send_buf_len, 0);
    if (n < 0) {
      perror("write to client:");
      usock_server2client_connection_close();
    }
  }
  return n;
}

int usock_write_message(char* send_buf, int send_buf_len) {
  return usock_server2client_write_message(send_buf, send_buf_len);
}


void usock_init() {
  usock_client2server_open();
  usock_server2client_open();
}

void usock_message_handler () {
  //struct timeval timeout = {0};
  int select_sts;
  // sigset_t origmask;
  fd_set rfds, wfds;
  int nfds = MAX (MAX (cli2srv_usock_fd, conn_cli2srv_usock_fd), srv2cli_usock_fd) + 1;
  FD_ZERO (&rfds); FD_ZERO (&wfds);
  FD_SET (cli2srv_usock_fd, &rfds);
  //FD_SET (conn_cli2srv_usock_fd, &rfds);
  FD_SET (srv2cli_usock_fd, &rfds);
  if (conn_cli2srv_usock_fd > 0)
  {
    FD_SET (conn_cli2srv_usock_fd, &rfds);
  }
  printf("in message received \n");
  //printf(" conn_cli2srv usock fd => %d, nfds = %d\n", conn_cli2srv_usock_fd, nfds);
  // no timeout
  //while (select (nfds, &rfds, NULL, NULL, NULL) > 0) {
  select_sts = select (nfds, &rfds, NULL, NULL, NULL);
  
  //printf("select ret value => %d \n", select_sts); 
  if ( select_sts > 0) {
    //printf(" in select call with io recv \n");

    if (FD_ISSET (cli2srv_usock_fd, &rfds)) 
    {
      printf(" client2server conn \n");
      usock_client2server_accept();
    }

    if (FD_ISSET (srv2cli_usock_fd, &rfds)) 
    {
      printf(" server2client conn \n");
      usock_server2client_accept();
    }

    if (conn_cli2srv_usock_fd > 0)
    {
      if (FD_ISSET (conn_cli2srv_usock_fd, &rfds)) usock_client2server_read_message();
    }
  }

}

void usock_task() {
  usock_init();
  while (1) {
    usock_message_handler(); // does all read and accept write use usock_write_message
    //sleep(15);
  }
}
