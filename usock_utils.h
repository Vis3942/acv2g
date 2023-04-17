#ifndef USOCK_UTILS_H
#define USOCK_UTILS_H 

void async_enable (int fd, int ok_to_block);

#define MAX(a,b) ((a) > (b) ? (a) : (b))
#define MIN(a,b) ((a) < (b) ? (a) : (b))


#endif /* matches USOCK_UTILS_H */