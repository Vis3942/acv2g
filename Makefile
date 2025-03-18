####################################################################################################
#                                                                                                  #
#  Set up tools and tool configurations.                                                           #
#                                                                                                  #
####################################################################################################
# for IoTehca board
# export  path (see commands below)
#ensure you set up export before using this file
#export PATH=$PATH:~/Documents/EPRI/spin/mevse_toolchain/arm-2009q1/bin
# new path for the toolchain Feb2025
#export PATH=$PATH:/media/viswanath/ExtraDrive1/toolchain/mevse_toolchain/arm-2009q1/bin

CROSS=arm-none-linux-gnueabi-
CC := $(CROSS)gcc
#CFLAGS := -v -Wall -Wno-missing-braces -DPF_CAN=29 -DAF_CAN=PF_CAN
CFLAGS := -Wall -Wno-missing-braces -DPF_CAN=29 -DAF_CAN=PF_CAN -std=gnu99
STRIP := $(CROSS)strip
TARGET := can2sep2
OBJFILES := loc_can.o usock.o ss_proto_can.o ss_proto.o task_queue.o usock_proto.o usock_utils.o utils.o usock_server.o can2sep2.o utils_event_arr.o
LDFLAGS := -lm -lrt

all: $(TARGET)

.c.o:
	${CC} -g -c ${CFLAGS} $<

can2sep2: $(OBJFILES)
	${CC} $(CFLAGS) -g -o $(TARGET) $(OBJFILES) $(LDFLAGS) 
#	$(STRIP) -g $@

test_can2sep2_usock: test_can2sep2_usock.c can2sep2_proxy.c
	${CC} $(CFLAGS) -o $@ test_can2sep2_usock.c -lrt -lm 
	$(STRIP) -g $@
	
test_timerfd_man_eg: test_timerfd_man_eg.c 
	$(CC) -o $@ test_timerfd_man_eg.c -lrt

test_timerfd_can2sep2: test_timerfd_can2sep2.c 
	$(CC) -o $@ test_timerfd_can2sep2.c -lrt

clean: 
	rm -f $(OBJFILES) $(TARGET) test_timerfd_man_eg test_timerfd_can2sep2 *~
