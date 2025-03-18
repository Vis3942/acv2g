
#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include "utils_event_arr.h"
#include "can2sep2.h"
#include "ss_proto.h"

// COMMENT NEXT LINE FOR INTEGRATING WITH OTHER FILES IN PROJECT
//#define TEST_UTILS_STR_ARR 1

#define MAX_LENGTH 256

static char active_mrid_fixedw[MAX_LENGTH] = {0};
static char active_mrid_maxlimw[MAX_LENGTH] = {0};
static char active_mrid_targetw[MAX_LENGTH] = {0};
static uint8_t active_fixedw_sts = 0; // 0=> false,1 => true
static uint8_t active_maxlimw_sts = 0; // 0=> false,1 => true
static uint8_t active_targetw_sts = 0; // 0=> false,1 => true


// Node structure
typedef struct Node {
    char mrid_str[MAX_LENGTH];
    uint8_t event_status;
    int64_t event_start_time;
    uint32_t event_duration;
    int16_t opModFixedW;
    uint16_t opModMaxLimW;
    int16_t opModTargetW;
    uint8_t event_type;     
    uint8_t event_active;// 1 => active, 0=> inactive
    struct Node *next;
} Node;

// Static variable to hold the head of the linked list
static Node *head = NULL;

// Create a new node with the given string
static Node* createNode(const char *str, uint8_t loc_sts, 
    int64_t loc_start_time, uint32_t loc_duration, 
    int32_t loc_value, uint8_t loc_event_type) {
    int tmplen;
    tmplen = strlen(str);
    if (tmplen >= MAX_LENGTH) 
    {
        return NULL; // Cannot store more than 255 chars in item
    }
    Node *newNode = (Node*)malloc(sizeof(Node));
    if (newNode == NULL) {
        return NULL; // Memory allocation failed
    }
    
    strncpy(newNode->mrid_str, str, tmplen);
    newNode->mrid_str[tmplen] = '\0'; // Ensure null-termination
    newNode->event_status = loc_sts;
    newNode->event_start_time = loc_start_time;
    newNode->event_duration = loc_duration;
    newNode->event_type = loc_event_type;
    if (loc_event_type == NODE_EVENT_TYPE_FIXEDW)
    {
        newNode->opModFixedW = (int16_t)loc_value;
    }
    else if (loc_event_type == NODE_EVENT_TYPE_MAXLIMW)
    {
        newNode->opModMaxLimW = (uint16_t) loc_value;
    }
    else if (loc_event_type == NODE_EVENT_TYPE_TARGETW)
    {
        newNode->opModTargetW = (int16_t) loc_value;
    }
    else 
    {
        // any other value set it to NONE
        newNode->event_type = NODE_EVENT_TYPE_NONE;
    }
    newNode->event_active = 0;
    newNode->next = NULL;
    return newNode;
}

static void setupActiveEvent(char * str, uint8_t loc_event_type) 
{
    fprintf(stdout, "$$$$ => setup active event %d for %s \n", loc_event_type, str);
    // setups up inernal vars to indicate an event is active and what its mrid is
    if (loc_event_type == NODE_EVENT_TYPE_FIXEDW) 
    {
        memset(active_mrid_fixedw, 0, MAX_LENGTH);
        memcpy(active_mrid_fixedw, str, strlen(str));
        active_fixedw_sts = 1;
    }
    else if (loc_event_type == NODE_EVENT_TYPE_MAXLIMW)
    {
        memset(active_mrid_maxlimw, 0, MAX_LENGTH);
        memcpy(active_mrid_maxlimw, str, strlen(str));
        active_maxlimw_sts = 1;
    }
    else if (loc_event_type == NODE_EVENT_TYPE_TARGETW)
    {
        memset(active_mrid_targetw, 0, MAX_LENGTH);
        memcpy(active_mrid_targetw, str, strlen(str));
        active_targetw_sts = 1;
    }
}

static void resetActiveEvent(uint8_t loc_event_type) 
{
    // clears up inernal vars to indicate an event is no longer active and set mrid to all zeros
    if (loc_event_type == NODE_EVENT_TYPE_FIXEDW) 
    {
        memset(active_mrid_fixedw, 0, MAX_LENGTH);
        active_fixedw_sts = 0;
    }
    else if (loc_event_type == NODE_EVENT_TYPE_MAXLIMW)
    {
        memset(active_mrid_maxlimw, 0, MAX_LENGTH);
        active_maxlimw_sts = 0;
    }
    else if (loc_event_type == NODE_EVENT_TYPE_TARGETW)
    {
        memset(active_mrid_targetw, 0, MAX_LENGTH);
        active_targetw_sts = 0;
    }
}

static int getEventValue(char * str)
{
    Node *current = head;
    while (current != NULL) {
        if (strcmp(current->mrid_str, str) == 0) 
        {
            if (current->event_type == NODE_EVENT_TYPE_FIXEDW)
            {
                return (int) current->opModFixedW/100;
            }else if (current->event_type == NODE_EVENT_TYPE_MAXLIMW)
            {
                return (int) (current->opModMaxLimW/100);
            }else if (current->event_type == NODE_EVENT_TYPE_TARGETW)
            {
                return (int) (current->opModTargetW);
            }
        }
        current = current->next;
    }
    return 0; // Not found
}

int ComputeActivePowerPercent()
{
    int tmpval = 0;
    int tmpval2;
    int reduce_by = 0;
    tmpval = getEventValue(active_mrid_fixedw);
    //fprintf(stdout, "$$$$%%%%% => Active Power event exists, compute active power percent func \n");
    fprintf(stdout, "$$$$ => Active Power %d \n", tmpval);

    if (tmpval != 0)
    {
        if (active_maxlimw_sts == 1)
        {
            tmpval2 = getEventValue(active_mrid_maxlimw);
            fprintf(stdout, "$$$$%%%%% => maxLimW %d \n", tmpval2);
            if (abs(tmpval) > abs(tmpval2))
            {
                if (tmpval < 0) 
                {
                    tmpval = -abs(tmpval2);
                }
                else // it is > 0 
                {
                    tmpval = abs(tmpval2);
                }
            }
            fprintf(stdout, "$$$$ => adjusted active power %d \n", tmpval);
        }
    }
    if (tmpval != 0)
    {
        if (active_targetw_sts == 1)
        {
            tmpval2 = getEventValue(active_mrid_targetw);
            fprintf(stdout, "$$$$ => targetW %d , curr power usage W %d\n", tmpval2, obc_current_charging_pwr_w);
            if ( ( obc_current_charging_pwr_w > 0) && (tmpval2 > 0) )
            {
                // discharging target W to be applied
                if (obc_current_charging_pwr_w > tmpval2)
                {
                    // set current wset_pct value based on tmpval2 
                    tmpval = (int)( (tmpval2 * 1.0) / (obc_current_charging_pwr_w/wset_pct_704) );
                }
            }
            else if ( ( obc_current_charging_pwr_w < 0) && (tmpval2 < 0) )
            {
                // charging targetW to be applied
                if (obc_current_charging_pwr_w < tmpval2)
                {
                    // set current wset_pct value based on tmpval2 
                    tmpval = (int)( (tmpval2 * 1.0) / (obc_current_charging_pwr_w/wset_pct_704) );
                }
            }
            fprintf(stdout, "$$$$ => adjusted active power %d \n", tmpval);
        }
    }
    // it will return 0 here
    return tmpval;
}

// Add a event to the list
int addEvent(const char *str, uint8_t loc_sts, 
        int64_t loc_start_time, uint32_t loc_duration,
        int32_t loc_value, uint8_t loc_event_type) {
    Node *newNode = createNode(str, loc_sts, loc_start_time, loc_duration, 
        loc_value, loc_event_type);
    if (newNode == NULL) {
        return -1; // Memory allocation failed
    }
    if (head == NULL) {
        head = newNode;
    } else {
        Node *current = head;
        while (current->next != NULL) {
            current = current->next;
        }
        current->next = newNode;
    }
    return 0; // Success
}

//setevent as active
int setEventActive(const char * str) {
    Node *current = head;
    while (current != NULL) {
        if (strcmp(current->mrid_str, str) == 0) {
            current->event_active = 1;
            setupActiveEvent(str, current->event_type);
            return 0; // success
        }
        current = current->next;
    }
    return -1; // Not found

}

int clearEventActive(const char * str) {
    Node *current = head;
    while (current != NULL) {
        if (strcmp(current->mrid_str, str) == 0) {
            current->event_active = 0;
            resetActiveEvent(current->event_type);
            // call remove event after clearing 
            return 0; // success
        }
        current = current->next;
    }
    return -1; // Not found

}


int isEventActive(const char *str) {
    Node *current = head;
    while (current != NULL) {
        if (strcmp(current->mrid_str, str) == 0) {
            return current->event_active; // success could be 0 (inactive) or 1 (active)
        }
        current = current->next;
    }
    return -1; // Not found
}

// active power event exists
uint8_t fixedWEventExists() 
{
    // => false, 1 => true
    return active_fixedw_sts;
}

// Search for a event in the list
int getStatusForEvent(const char *str) {
    Node *current = head;
    while (current != NULL) {
        if (strcmp(current->mrid_str, str) == 0) {
            return current->event_status; // found item
        }
        current = current->next;
    }
    return -1; // Not found
}

// update status for event
int updateStatusForEvent(const char *str, uint8_t loc_event_status) {
    Node *current = head;
    while (current != NULL) {
        if (strcmp(current->mrid_str, str) == 0) {
            current->event_status = loc_event_status;
            return 0; // found and updated item; success
        }
        current = current->next;
    }
    return -1; // Not found
}

// Remove a event from the list
int removeEvent(const char *str) {
    Node *current = head;
    Node *previous = NULL;
    while (current != NULL) {
        if (strcmp(current->mrid_str, str) == 0) {
            if (previous == NULL) {
                // Removing the head
                head = current->next;
            } else {
                // Removing a non-head node
                previous->next = current->next;
            }
            free(current);
            return 0; // Success
        }
        previous = current;
        current = current->next;
    }
    return -1; // Not found
}

// Print all events in the list
void printEventList() {
    Node *current = head;
    printf("Current list of events\n");
    while (current != NULL) {
        printf("[%s] -> type (%d), status = %d, isActive (val 1) = %d\n", current->mrid_str,
            current->event_type, current->event_status, current->event_active);
        current = current->next;
    }
}

// Free all nodes in the list
void freeEventList() {
    Node *current = head;
    while (current != NULL) {
        Node *next = current->next;
        free(current);
        current = next;
    }
    head = NULL;
}

#ifdef TEST_UTILS_STR_ARR
// Example usage
int main() {
    // Adding events to the list; times are all random
    addEvent("Event 1", 1, 1000, 320, 100);
    addEvent("Event 2, second item", 2, 10000, 300, -75);
    addEvent("EEEVVVVent", 4, 50000, 400, 50);

    // Printing the list
    printf("List contents:\n");
    printEventList();

    // Searching for a string
    printf("\nSearching for 'Event 2, second item':\n");
    int sts = getStatusForEvent("Event 2, second item");
    if (sts != -1) {
        printf("Found  %d\n", sts);
    } else {
        printf("Not found\n");
    }

    // Removing a string
    printf("\nRemoving 'Event 2, second item':\n");
    removeEvent("Event 2, second item");

    // Printing the list after removal
    printf("List contents after removal:\n");
    printEventList();

    // Freeing the list before exiting
    freeEventList();

    return 0;
}
#endif