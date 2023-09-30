#ifndef USOCK_SERVER_H
#define USOCK_SERVER_H

void usock_message_handler();
void usock_init();
void usock_task();
int usock_write_message(char* send_buf, int send_buf_len);
void register_process_messages_callback(void (*ptr)( char *buffer, int size ));
void usock_client2server_accept();
void usock_server2client_accept();
void usock_client2server_read_message();

extern int srv2cli_usock_fd;
extern int conn_srv2cli_usock_fd;
extern int cli2srv_usock_fd;
extern int conn_cli2srv_usock_fd;


#endif /* for USOCK_SERVER_H */