#ifndef CAN_H
#define CAN_H

void can_transmit (int id, char *data, int length);
void can_open ();
void send_test_can();
void send_test_can_messages();

extern int can_socket;

#endif // CAN_H