#ifndef TASK_QUEUE_H
#define TASK_QUEUE_H

void init_queue (void);
void enqueue (int value);
int dequeue ();
void topqueue(int value);
int count_queue();
void print_queue (void);
void error (char *msg);
void init_queue_2 (void);
void enqueue_2 (int value);
int dequeue_2 ();
int count_queue_2();
void clear_queue(void);
void clear_queue_2(void);

#endif