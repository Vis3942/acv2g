#ifndef LOC_CAN_H
#define LOC_CAN_H

void can_transmit (int id, char *data, int length);
void can_open ();
void send_test_can();
void send_test_can_messages();

extern int can_socket;


#endif // LOC_CAN_H