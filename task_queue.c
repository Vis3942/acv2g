#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <stddef.h>
#include <time.h>

// to test this file independently, uncomment the next define
//#define TEST_THIS_FILE  1

#ifdef TEST_THIS_FILE
#define BUFSIZE 128
#endif


struct element {
    int action;
    struct element *next;
};

struct element *tail_q1;
int num_elements_q1 = 0;

struct element *tail_q2;
int num_elements_q2 = 0;


void init_queue (void)
{
    tail_q1 = NULL;
    srand(time(NULL));
    num_elements_q1 = 0;
}

void init_queue_2(void) 
{
    tail_q2 = NULL;
    num_elements_q2 = 0;
}

void error (char *msg)
{
    perror (msg);
    exit (1);
}

void topqueue(int top_val)
{
    /*
    * normally elements are added to end of the queue in enqueue
    * however, there was a need for adding an immediate task to the top of the queue, so 
    * this method will add the element to the top of the queue, so that the next dequeue
    * will provide this element that was added to the top
    */
    struct element *ptr;
    struct element *head;

    if ((ptr = (struct element *) malloc (sizeof (struct element))) == NULL)
        error ("malloc");

    ptr -> action = top_val;

    if (tail_q1 == NULL) {
        ptr -> next = ptr;
    }
    else
    {
        head = tail_q1->next;
        ptr-> next = head;
        tail_q1 -> next = ptr;
    }
    num_elements_q1++;
}

void enqueue (int add_val)
{
    struct element *ptr;

    if ((ptr = (struct element *) malloc (sizeof (struct element))) == NULL)
        error ("malloc");

    ptr -> action = add_val;

    if (tail_q1 == NULL) {
        ptr -> next = ptr;
    }
    else
    {
        ptr -> next = tail_q1 -> next;
        tail_q1 -> next = ptr;
    }
    tail_q1 = ptr;
    num_elements_q1++;
}

int dequeue () // returns -1 on error
{
    struct element *ptr;
    int tmpi;

    if (!tail_q1) {
        fprintf (stderr, "Queue is empty\n");
        return -1;
    }
    // get the head
    ptr = tail_q1 -> next;
    tmpi = ptr -> action;

    if (ptr == tail_q1)
        tail_q1 = NULL;
    else
        tail_q1 -> next = ptr -> next;
    free (ptr);
    num_elements_q1--;
    return tmpi;
}

void print_queue (void)
{

    struct element *ptr, *head;

    if (!tail_q1) {
        fprintf (stderr, "Queue is empty\n");
        return;
    }

    printf ("Queue: \n");

    // get the head
    head = ptr = tail_q1 -> next;
    int i = 1;

    do {
        printf (" %d ", ptr -> action);
        ptr = ptr -> next;
        i++;
    } while (ptr != head);
    printf("\n");
}

int count_queue() 
{
    return num_elements_q1;
}

void enqueue_2 (int add_val)
{
    struct element *ptr;

    if ((ptr = (struct element *) malloc (sizeof (struct element))) == NULL)
        error ("malloc");

    ptr -> action = add_val;

    if (tail_q2 == NULL) {
        ptr -> next = ptr;
    }
    else
    {
        ptr -> next = tail_q2 -> next;
        tail_q2 -> next = ptr;
    }
    tail_q2 = ptr;
    num_elements_q2++;
}

int dequeue_2 () // returns -1 on error
{
    struct element *ptr;
    int tmpi;

    if (!tail_q2) {
        fprintf (stderr, "Queue is empty\n");
        return -1;
    }
    // get the head
    ptr = tail_q2 -> next;
    tmpi = ptr -> action;

    if (ptr == tail_q2)
        tail_q2 = NULL;
    else
        tail_q2 -> next = ptr -> next;
    free (ptr);
    num_elements_q2--;
    return tmpi;
}

int count_queue_2() 
{
    return num_elements_q2;
}


#ifdef TEST_THIS_FILE
int main (int argc, char **argv)
{
    char buf[BUFSIZE];
    int rnd_num;
    int upper = 999;
    int lower = 9;
    init_queue ();

    while (1) {
        printf ("\n1: Enqueue\n2: Dequeue\n3: Add to Top\n4: Print queue\n5: Number Elements\n0: Quit\n\nEnter your choice: ");
        if (fgets (buf, BUFSIZE, stdin) == NULL)
            break;
        if (buf [0] == '1') {
           // Enqueue
           // Get name
           rnd_num = (rand() % (upper - lower)) + lower;
           enqueue (rnd_num);
        } else if (buf [0] == '2') {
            // Dequeue
            rnd_num = dequeue();
            printf ("dequeued %d\n", rnd_num);
        } else if (buf[0] == '3' ) {
           rnd_num = (rand() % (upper - lower)) + lower;
           topqueue (rnd_num);
        } else if (buf [0] == '4')
           print_queue ();
        else if (buf [0] == '5') {
            rnd_num = count_queue();
            printf("num elements = %d\n", rnd_num);
        } else if (buf [0] == '0')
           break;
        else
            fprintf (stderr, "Error in input\n");
    }
    
    exit (0);
}
#endif
