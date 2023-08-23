#include <sys/select.h>
#include <fcntl.h>
#include <time.h>
#include <sys/timerfd.h>
#include <signal.h>
#include <unistd.h>
#include <stdio.h>
#include <stdlib.h>
#include <errno.h>
#include <stdarg.h>
#include <sys/socket.h>
#include <linux/can.h>
#include <linux/can/raw.h>
#include <stdint.h>

#define MAX(a,b) ((a) > (b) ? (a) : (b))

int test_timer_seconds = 60;
int test_timerfd;
int proto_timerfd; // for sunspec profile proto impl
struct timespec now;


void message_received (int x) {
  struct can_frame frame;
  struct timeval timeout = {0};
  fd_set rfds, wfds;
  int nfds;
  ssize_t s;
  uint64_t exp_count;

  int tmpmax;
//   tmpmax = MAX(can_socket, srv2cli_usock_fd);
//   tmpmax = MAX(tmpmax, conn_srv2cli_usock_fd);
//   tmpmax = MAX(tmpmax, cli2srv_usock_fd);
//   tmpmax = MAX(tmpmax, conn_cli2srv_usock_fd);
  tmpmax = MAX(test_timerfd, proto_timerfd);
//   if ( (test_can_messages) || (test_sep2_mirror_usock) || (test_ev_param_post_usock)) 
//   {
//     tmpmax = MAX(tmpmax, test_timerfd);
//   }
  nfds = tmpmax+1;

  FD_ZERO (&rfds); FD_ZERO (&wfds);
//   FD_SET (can_socket, &rfds);
//   FD_SET (cli2srv_usock_fd, &rfds);
//   if (conn_cli2srv_usock_fd > 0)
//   {
//     FD_SET (conn_cli2srv_usock_fd, &rfds);
//   }
//   FD_SET(srv2cli_usock_fd, &rfds);
//   if (conn_srv2cli_usock_fd > 0)
//   {
//     FD_SET (conn_srv2cli_usock_fd, &rfds);
//   }
  FD_SET(proto_timerfd, &rfds);
//   if ( (test_can_messages) || (test_sep2_mirror_usock) || (test_ev_param_post_usock) )
//   {
    FD_SET(test_timerfd, &rfds);
//   }
  fprintf(stdout, "in message received \n");
  //if (select (nfds, &rfds, NULL, NULL, &timeout) > 0) {
  if (select (nfds, &rfds, NULL, NULL, NULL) > 0) {
    fprintf(stdout," in select call with io recv \n");


    // conn_srv2cli_usock_fd is only for writing messages
    if (FD_ISSET (proto_timerfd, &rfds))
    {
      fprintf(stdout, "proto timer triggered \n");
    //   ss_proto_task();
        s = read(proto_timerfd, &exp_count, sizeof(uint64_t));
        if (s != sizeof(uint64_t))
        {
          perror("read proto timerfd:");
          return;
        }
        else 
        {
          //debug
          fprintf(stdout, "proto timerfd fired %llu \n", (unsigned long long) exp_count);
        }
    }

    // if ( (test_can_messages) || (test_sep2_mirror_usock) || (test_ev_param_post_usock) )
    // {
      if (FD_ISSET (test_timerfd, &rfds)) 
      {
        // debug 
        fprintf(stdout, "test timer id triggered \n");

        s = read(test_timerfd, &exp_count, sizeof(uint64_t));
        if (s != sizeof(uint64_t))
        {
          perror("read timerfd:");
          return;
        }
        else 
        {
          //debug
          fprintf(stdout, "test timerfd fired %llu \n", (unsigned long long)exp_count);
        }
      }
    // }

  }
}


void signal_init () {
  struct sigaction action;
  // struct sigevent event;
  // struct itimerspec expire;
  signal (SIGPIPE, SIG_IGN); 
  action.sa_handler = message_received;
  action.sa_flags = 0;
  if (sigaction (SIGIO, &action, NULL) < 0)
    fprintf(stdout,"sigaction: %d\n", errno);
  // enable SIGIO signaling for new messages
  }

void setup_proto_timerfd()
{
  struct itimerspec new_value;
    if (clock_gettime(CLOCK_REALTIME, &now) == -1)
        perror("clock_gettime");

  new_value.it_value.tv_sec = now.tv_sec + test_timer_seconds;
  new_value.it_value.tv_nsec = now.tv_nsec;
  new_value.it_interval.tv_sec = test_timer_seconds;
  new_value.it_interval.tv_nsec = 0;
  proto_timerfd = timerfd_create(CLOCK_REALTIME, 0);
  //proto_timerfd = timerfd_create(CLOCK_MONOTONIC, 0);
  if (proto_timerfd == -1)
  {
    perror("timerfd_create");
    exit(EXIT_FAILURE);
  }

  // set it to non-blocking
  if (fcntl(proto_timerfd, F_SETFL, O_NONBLOCK))
  {
    perror("non-blocking-setup-error");
    exit(EXIT_FAILURE);
  }

  if (timerfd_settime(proto_timerfd, TFD_TIMER_ABSTIME, &new_value, NULL) == -1)
  {
    perror("timerfd_settime");
    exit(EXIT_FAILURE);
  }
}


void setup_timerfd_for_test() 
{
  struct itimerspec new_value;
    if (clock_gettime(CLOCK_REALTIME, &now) == -1)
        perror("clock_gettime");

  new_value.it_value.tv_sec = now.tv_sec + test_timer_seconds;
  new_value.it_value.tv_nsec = now.tv_nsec;
  new_value.it_interval.tv_sec = test_timer_seconds;
  new_value.it_interval.tv_nsec = 0;
  test_timerfd = timerfd_create(CLOCK_REALTIME, 0);
  if (test_timerfd == -1)
  {
    perror("timerfd_create");
    exit(EXIT_FAILURE);
  }

  // set it to non-blocking
  if (fcntl(test_timerfd, F_SETFL, O_NONBLOCK))
  {
    perror("non-blocking-setup-error");
    exit(EXIT_FAILURE);
  }

  if (timerfd_settime(test_timerfd, TFD_TIMER_ABSTIME, &new_value, NULL) == -1)
  {
    perror("timerfd_settime");
    exit(EXIT_FAILURE);
  }
  
}

int main (int argc, char **argv) {
//   version ();
//   init_data();
//   // options (argc-1, argv+1);
//   parse_options(argc, argv);
//   //signal_init ();
//   can_open ();
//   init_ssproto();
    setup_proto_timerfd();
//   if ( (test_can_messages) || (test_sep2_mirror_usock) || (test_ev_param_post_usock))
//   {
    //send_test_can();
    setup_timerfd_for_test();
    fprintf(stdout, "timerfd setup for test \n");
//   }


//   register_process_messages_callback(process_recv_message);

//   signal_init();
//   while (1) pause ();

    while (1)
    {
        message_received(27);
    }

  // fprintf(stdout, "before message_received loop \n");
  // while (1) 
  // {
  //   fprintf(stdout, "before calling message_received \n");
  //   //message_received(27); // 27 just a random value, to be compatible with earlier signature, not used
  //   sleep(5);
  // }

  return 0;
}
