#include <time.h>
#include <signal.h>
#include <stdio.h>
#include <unistd.h>
#include <sys/socket.h>
#include <netinet/in.h>
#include <net/if.h>
#include <sys/ioctl.h>
#include <stdlib.h>
#include <string.h>
#include <errno.h>
#include <linux/socket.h>
#include <linux/can.h>
#include <linux/can/raw.h>
#include "loc_can.h"
#include "usock_utils.h"
#include "utils.h"

int can_socket;


void can_open () {
  struct sockaddr_can address;
  struct ifreq request;
  can_socket = socket (PF_CAN, SOCK_RAW, CAN_RAW);
  if (can_socket < 0) {
    perror ("CAN socket error");
    exit (0);
  }
  async_enable (can_socket, 1);

  int loopback = 0; /* 0 = disabled, 1 = enabled (default) */
  setsockopt(can_socket, SOL_CAN_RAW, CAN_RAW_LOOPBACK, &loopback, sizeof(loopback));

  strcpy(request.ifr_name, "can0");
  ioctl (can_socket, SIOCGIFINDEX, &request);
  address.can_family = AF_CAN;
  address.can_ifindex = request.ifr_ifindex;
  bind (can_socket, (struct sockaddr *)&address, sizeof(address));
}


void can_transmit (int id, char *data, int length) {
  int sts;
  struct can_frame frame;
  frame.can_id = id; // | CAN_EFF_FLAG;
  frame.can_dlc = length;
  memcpy (frame.data, data, length);
  sts = write (can_socket, &frame, sizeof (struct can_frame));
  //fprintf(stdout, "cansocket write id %d ; sts %d \n", id, sts);
  if (sts != 16)
  {
    fprintf(stdout, "[check] cansocket write id %d ; sts %d \n", id, sts);  
  }
#ifdef PRINT_CAN_IDS  
  fprintf(stdout,"Transmitted %d [%d] [%d] [%d] [%d] [%d] \n", id, data[0], 
    data[1], data[2], data[3], data[4]);
  fprintf(stdout, "Write Sts %d\n", sts);
#endif
}

void send_test_can()
{
  int id = 0x9af;
  char data[8];
  data[0] = 0x21;
  data[1] = 0x78;
  data[2] = 0x64;
  data[3] = 0x35;
  data[4] = 0xab;
  data[5] = 0x95;
  data[6] = 0xfc;
  data[7] = 0xde;
  can_transmit(id, data, 8);
}

void send_test_can_messages()
{
  char data[8];
  int i;
  for (i=0; i < 7; i++)
  {
    data[i+1] = rand() % 255;
  }
  displayTime();
  fprintf(stdout,"CAN tx id %4x:  \n", 0x105);
  can_transmit(0x105, data, 8);
  // fprintf(stdout, "before sleep \n");
  // sleep(1);
  // fprintf(stdout, "after sleep \n");
  // for (i=0; i < 7; i++)
  // {
  //   data[i+1] = rand() % 255;
  // }
  // fprintf(stdout,"CAN tx id %4x:  \n", 0x111);
  // can_transmit(0x111, data, 8);

}